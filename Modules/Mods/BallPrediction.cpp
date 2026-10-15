                                                          
#include "BallPrediction.hpp"
#include "KingFeatures.hpp"
#include "../../Components/Includes.hpp"
#include "GameEventHook.hpp"
#include "../../ImGui/imgui.h"
#include <array>
#include <chrono>
#include <vector>
#include <cmath>
#include <filesystem>
#include <algorithm>
#include <unordered_set>
#include <utility>

                            
#define RS_DONT_LOG

                                                                                       
#include "../../RocketSim/src/RocketSim.h"
#include "../../RocketSim/src/Sim/BallPredTracker/BallPredTracker.h"

                                      
#include "../../Components/Components/GUI.hpp"

                           
#include <windows.h>
#include <shlobj.h>
#include <fstream>
#include <nlohmann/json.hpp>

                                                  
namespace RS = RocketSim;
 
                                                                
static std::vector<byte> LoadResourceData(int resourceId)
{
    std::vector<byte> data;
    
                                                          
    HMODULE hModule = GUIComponent::DllModule;
    if (!hModule)
    {
        Console.Write("[BallPrediction] Warning: DLL module handle not available, trying process handle");
        hModule = GetModuleHandle(NULL);
    }
    
    if (!hModule)
    {
        Console.Write("[BallPrediction] Error: Failed to get module handle");
        return data;
    }
    
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    if (!hResource)
    {
        Console.Write("[BallPrediction] Error: Failed to find resource ID " + std::to_string(resourceId));
        return data;
    }
    
    HGLOBAL hGlobal = LoadResource(hModule, hResource);
    if (!hGlobal)
    {
        Console.Write("[BallPrediction] Error: Failed to load resource ID " + std::to_string(resourceId));
        return data;
    }
    
    DWORD dataSize = SizeofResource(hModule, hResource);
    LPVOID pData = LockResource(hGlobal);
    
    if (pData && dataSize > 0)
    {
        data.resize(dataSize);
        memcpy(data.data(), pData, dataSize);
        Console.Write("[BallPrediction] Successfully loaded resource ID " + std::to_string(resourceId) + " (" + std::to_string(dataSize) + " bytes)");
    }
    else
    {
        Console.Write("[BallPrediction] Error: Invalid resource data for ID " + std::to_string(resourceId));
    }
    
    return data;
}
 
namespace BallPrediction
{
                                                       
    static inline float rsqrt(float x)
    {
                                                                               
        union { float f; int32_t i; } conv;
        float x2 = x * 0.5f;
        conv.f = x;
        conv.i = 0x5f3759df - (conv.i >> 1);
        float y = conv.f;
        y = y * (1.5f - x2 * y * y);                     
        return y;
    }

                         
    BallPredictionConfig& GetSettings()
    {
        static BallPredictionConfig s_Settings;
        return s_Settings;
    }
    
                      
    static bool s_RocketSimInitialized = false;
    static bool s_RocketSimFailed = false;                          
    static RocketSim::Arena* s_PredArena = nullptr;
    static RocketSim::BallPredTracker* s_BallPredTracker = nullptr;
    static RocketSim::BallPredTracker* s_PreHitPredTracker = nullptr;
    static constexpr size_t PRED_TICKS = 1200;                                
    static constexpr size_t PREHIT_PRED_TICKS = 240;                           
    static constexpr float PREHIT_POST_SECONDS = 1.75f;
    static std::vector<PreHitPredictionData> s_PreHitPredictions;
    static std::chrono::steady_clock::time_point s_LastPreHitUpdate{};
    static std::vector<FVector> s_EffectiveWorldPoints;
    static std::vector<float> s_EffectiveTimes;
    static std::vector<FVector> s_EffectiveBouncePoints;
    
                                     
    struct PredictionCache
    {
        std::vector<FVector> WorldPoints;
        std::vector<FVector> PreviousWorldPoints;
        std::vector<FVector> BouncePoints;
        std::chrono::steady_clock::time_point LastUpdate;
        std::chrono::steady_clock::time_point LastBallSearch;
        std::chrono::steady_clock::time_point LerpStartTime;
                                                                                
                                                                                
                                                                                 
                                                                                   
                                                                                  
                                                                                   
                            
        float PredBaseTimeSeconds = -1.0f;
                                                                          
                                                                             
                                                                                
                                                                           
        float LastResimTimeSeconds = -1.0f;
        FVector LastBallLocation{ 0.f, 0.f, 0.f };
        FVector LastBallVelocity{ 0.f, 0.f, 0.f };
        FVector LastBallAngVelocity{ 0.f, 0.f, 0.f };
        ABall_TA* CachedBall = nullptr;
        bool bInitialized = false;
        bool bGoalPredicted = false;
        bool bLerping = false;

                           
        FVector GoalImpactPoint{ 0.f, 0.f, 0.f };
        bool bHasGoalImpact = false;
        float fGoalImpactTime = 0.f;
        FVector LandingPoint{ 0.f, 0.f, 0.f };
        bool bHasLanding = false;
    };
    
    static PredictionCache s_Cache;
    static bool s_LastInGameState = false;
    static bool s_LastReplayState = false;

    static float GetPredictionTimeSeconds()
    {
        const float maxPossible = static_cast<float>(PRED_TICKS) / 120.0f;
        float predictionTime = GetSettings().fPredictionTime;
        if (predictionTime <= 0.0f)
            predictionTime = maxPossible;
        if (predictionTime > maxPossible)
            predictionTime = maxPossible;
        return predictionTime;
    }

    static int GetSampleCount(float predictionTime)
    {
                                                                              
                                                                             
                                                                                
                                                                    
        int tickrate = GetSettings().iTickrate;
        if (tickrate < 15) tickrate = 15;
        if (tickrate > 120) tickrate = 120;
        GetSettings().fTimeStep = 1.0f / static_cast<float>(tickrate);

        const float samplesPerSecond = static_cast<float>(tickrate);
        const int minimumStepsForDistance = static_cast<int>(std::ceil(predictionTime * samplesPerSecond)) + 1;

        int steps = GetSettings().iMaxPoints;
        if (steps < 2)
            steps = 2;
        if (steps < minimumStepsForDistance)
            steps = minimumStepsForDistance;
        if (steps > static_cast<int>(PRED_TICKS))
            steps = static_cast<int>(PRED_TICKS);
        return steps;
    }
    
                           
    static void InitRocketSim()
    {
        if (s_RocketSimInitialized || s_RocketSimFailed)
            return;
            
        try
        {
                                                            
            std::map<RocketSim::GameMode, std::vector<RocketSim::FileData>> meshFilesMap;
            
                                                          
            std::vector<int> soccarResourceIds = {
                IDR_COLLISION_MESH_SOCCAR_0, IDR_COLLISION_MESH_SOCCAR_1, IDR_COLLISION_MESH_SOCCAR_2,
                IDR_COLLISION_MESH_SOCCAR_3, IDR_COLLISION_MESH_SOCCAR_4, IDR_COLLISION_MESH_SOCCAR_5,
                IDR_COLLISION_MESH_SOCCAR_6, IDR_COLLISION_MESH_SOCCAR_7, IDR_COLLISION_MESH_SOCCAR_8,
                IDR_COLLISION_MESH_SOCCAR_9, IDR_COLLISION_MESH_SOCCAR_10, IDR_COLLISION_MESH_SOCCAR_11,
                IDR_COLLISION_MESH_SOCCAR_12, IDR_COLLISION_MESH_SOCCAR_13, IDR_COLLISION_MESH_SOCCAR_14,
                IDR_COLLISION_MESH_SOCCAR_15
            };
            
            int loadedMeshes = 0;
            for (int resourceId : soccarResourceIds)
            {
                std::vector<byte> data = LoadResourceData(resourceId);
                if (!data.empty())
                {
                    meshFilesMap[RocketSim::GameMode::SOCCAR].push_back(data);
                    loadedMeshes++;
                }
            }
            
            if (meshFilesMap.empty())
            {
                                                                          
                s_RocketSimFailed = true;
                return;
            }
            
                                                                     
            RocketSim::InitFromMem(meshFilesMap, true);                  
            
                                                                       
            s_PredArena = RocketSim::Arena::Create(RocketSim::GameMode::SOCCAR, RocketSim::ArenaConfig(), 120.0f);
            
            if (s_PredArena)
            {
                                                 
                s_BallPredTracker = new RocketSim::BallPredTracker(s_PredArena, PRED_TICKS);
                s_PreHitPredTracker = new RocketSim::BallPredTracker(s_PredArena, PREHIT_PRED_TICKS);
                s_RocketSimInitialized = true;
            }
        }
        catch (...)
        {
                                                                          
            s_RocketSimInitialized = false;
            s_RocketSimFailed = true;
        }
    }
    

    

    
                                                  
    static bool IsBallValid(ABall_TA* ball)
    {
        if (!ball)
            return false;
        
        __try
        {
            FVector loc = ball->Location;
            if (std::abs(loc.X) > 10000.f || std::abs(loc.Y) > 10000.f || loc.Z < -500.f || loc.Z > 3000.f)
                return false;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }
    
                                       
    static bool SafeReadBallState(ABall_TA* ball, FVector& outLocation, FVector& outVelocity, FVector& outAngVel)
    {
        if (!ball)
            return false;
        
        __try
        {
            outLocation = ball->Location;
            outVelocity = ball->Velocity;
            outAngVel = ball->AngularVelocity;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

                                                                            
    static float Length3(const FVector& v);
    static FVector Normalize3(const FVector& v);
    static float Dot3(const FVector& a, const FVector& b);

    struct CarPhysicsSnapshot
    {
        FVector Position{};
        FVector LinearVelocity{};
        FVector AngularVelocity{};
        FQuat Rotation{};
        FVector CollisionOffset{};
        FVector CollisionExtent{};
        float CollisionScale = 1.0f;
        float Throttle = 0.0f;
        float Steer = 0.0f;
        bool OnGround = false;
        bool Boosting = false;
    };

    static bool IsFinite3(const FVector& v)
    {
        return std::isfinite(v.X) && std::isfinite(v.Y) && std::isfinite(v.Z);
    }

    static FQuat NormalizeQuat(const FQuat& q)
    {
        const float lenSq = q.X*q.X + q.Y*q.Y + q.Z*q.Z + q.W*q.W;
        if (!std::isfinite(lenSq) || lenSq < 0.01f)
            return FQuat{ 0.f, 0.f, 0.f, 1.f };
        const float inv = 1.0f / std::sqrt(lenSq);
        return FQuat{ q.X*inv, q.Y*inv, q.Z*inv, q.W*inv };
    }

    static FQuat QuatMul(const FQuat& a, const FQuat& b)
    {
        return FQuat{
            a.W*b.X + a.X*b.W + a.Y*b.Z - a.Z*b.Y,
            a.W*b.Y - a.X*b.Z + a.Y*b.W + a.Z*b.X,
            a.W*b.Z + a.X*b.Y - a.Y*b.X + a.Z*b.W,
            a.W*b.W - a.X*b.X - a.Y*b.Y - a.Z*b.Z
        };
    }

    static FVector RotateByQuat(const FQuat& qIn, const FVector& v)
    {
        const FQuat q = NormalizeQuat(qIn);
        const FVector u{ q.X, q.Y, q.Z };
        const float s = q.W;
        const float uv = u.X*v.X + u.Y*v.Y + u.Z*v.Z;
        const float uu = u.X*u.X + u.Y*u.Y + u.Z*u.Z;
        const FVector cross{
            u.Y*v.Z - u.Z*v.Y,
            u.Z*v.X - u.X*v.Z,
            u.X*v.Y - u.Y*v.X
        };
        return FVector{
            2.f*uv*u.X + (s*s-uu)*v.X + 2.f*s*cross.X,
            2.f*uv*u.Y + (s*s-uu)*v.Y + 2.f*s*cross.Y,
            2.f*uv*u.Z + (s*s-uu)*v.Z + 2.f*s*cross.Z
        };
    }

    static FVector InverseRotateByQuat(const FQuat& qIn, const FVector& v)
    {
        FQuat q = NormalizeQuat(qIn);
        q.X = -q.X; q.Y = -q.Y; q.Z = -q.Z;
        return RotateByQuat(q, v);
    }

    static FQuat PredictQuat(const FQuat& base, const FVector& angularVelocity, float t)
    {
        const float speed = std::sqrt(angularVelocity.X*angularVelocity.X +
                                      angularVelocity.Y*angularVelocity.Y +
                                      angularVelocity.Z*angularVelocity.Z);
        if (!std::isfinite(speed) || speed < 0.0001f || t <= 0.f)
            return NormalizeQuat(base);
                                                                                
                                                                                   
        const float safeSpeed = (std::min)(speed, 12.0f);
        const float angle = safeSpeed * t;
        const float half = angle * 0.5f;
        const float k = std::sin(half) / speed;
        const FQuat delta{
            angularVelocity.X*k,
            angularVelocity.Y*k,
            angularVelocity.Z*k,
            std::cos(half)
        };
        return NormalizeQuat(QuatMul(delta, base));
    }

    static FVector Cross3(const FVector& a, const FVector& b)
    {
        return FVector{
            a.Y*b.Z - a.Z*b.Y,
            a.Z*b.X - a.X*b.Z,
            a.X*b.Y - a.Y*b.X
        };
    }

    static bool SafeReadCarPhysics(ACar_TA* car, CarPhysicsSnapshot* out)
    {
        if (!car || !out)
            return false;

        __try
        {
            if (car->bDeleteMe)
                return false;

            CarPhysicsSnapshot snap{};
            snap.Position = car->Location;
            snap.LinearVelocity = car->Velocity;
            snap.AngularVelocity = car->AngularVelocity;
            snap.Rotation = car->RBState.Quaternion;

                                                                                
                                                                 
            const FVector rbPos = car->RBState.Location;
            const FVector rbVel = car->RBState.LinearVelocity;
            const FVector rbAng = car->RBState.AngularVelocity;
            if (IsFinite3(rbPos) && IsFinite3(rbVel) && IsFinite3(rbAng))
            {
                const float dx = rbPos.X - snap.Position.X;
                const float dy = rbPos.Y - snap.Position.Y;
                const float dz = rbPos.Z - snap.Position.Z;
                if (dx*dx + dy*dy + dz*dz < 160000.0f)
                    snap.Position = rbPos;
                snap.LinearVelocity = rbVel;
                snap.AngularVelocity = rbAng;
            }

                                                                            
                                                                             
                                           
            snap.CollisionOffset = car->LocalCollisionOffset;
            snap.CollisionExtent = car->LocalCollisionExtent;
            snap.CollisionScale = car->ReplicatedCollisionScale;

                                                                                 
                                                                               
                                                                
            snap.Throttle = std::clamp(car->Input.Throttle, -1.0f, 1.0f);
            snap.Steer = std::clamp(car->Input.Steer, -1.0f, 1.0f);
            snap.OnGround = car->bOnGround != 0;
            snap.Boosting = (car->Input.bActivateBoost || car->Input.bHoldingBoost);
            if (IsPointerReadable(car->BoostComponent))
                snap.Boosting = snap.Boosting && car->BoostComponent->bActive && !car->BoostComponent->bNoBoost;

            if (!IsFinite3(snap.Position) || !IsFinite3(snap.LinearVelocity) ||
                !IsFinite3(snap.AngularVelocity) || !IsFinite3(snap.CollisionOffset) ||
                !IsFinite3(snap.CollisionExtent))
                return false;

            if (snap.CollisionExtent.X < 20.f || snap.CollisionExtent.X > 300.f ||
                snap.CollisionExtent.Y < 20.f || snap.CollisionExtent.Y > 300.f ||
                snap.CollisionExtent.Z < 10.f || snap.CollisionExtent.Z > 180.f)
            {
                snap.CollisionExtent = FVector{ 118.f, 84.f, 36.f };
                snap.CollisionOffset = FVector{ 13.f, 0.f, 20.f };
            }
            if (!std::isfinite(snap.CollisionScale) || snap.CollisionScale < 0.5f || snap.CollisionScale > 3.0f)
                snap.CollisionScale = 1.0f;

            snap.CollisionExtent.X *= snap.CollisionScale;
            snap.CollisionExtent.Y *= snap.CollisionScale;
            snap.CollisionExtent.Z *= snap.CollisionScale;
            snap.CollisionOffset.X *= snap.CollisionScale;
            snap.CollisionOffset.Y *= snap.CollisionScale;
            snap.CollisionOffset.Z *= snap.CollisionScale;
            snap.Rotation = NormalizeQuat(snap.Rotation);
            *out = snap;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    static bool TestBallVsPredictedCarBox(const CarPhysicsSnapshot& car,
                                          const FVector& ballPos,
                                          float time,
                                          float padding,
                                          FVector* outNormal,
                                          FVector* outCarPointVelocity)
    {
        if (!outNormal || !outCarPointVelocity)
            return false;

        const FQuat q = PredictQuat(car.Rotation, car.AngularVelocity, time);
        const FVector forward = Normalize3(RotateByQuat(q, FVector{ 1.f, 0.f, 0.f }));

                                                                                 
                                                                               
                                                                               
                                                                                 
        float driveAccel = car.OnGround ? car.Throttle * 850.0f : 0.0f;
        if (car.Boosting)
            driveAccel += 990.0f;
        const float halfT2 = 0.5f * time * time;
        const FVector carPos{
            car.Position.X + car.LinearVelocity.X * time + forward.X * driveAccel * halfT2,
            car.Position.Y + car.LinearVelocity.Y * time + forward.Y * driveAccel * halfT2,
            car.Position.Z + car.LinearVelocity.Z * time + forward.Z * driveAccel * halfT2
        };
        const FVector relWorld{
            ballPos.X - carPos.X,
            ballPos.Y - carPos.Y,
            ballPos.Z - carPos.Z
        };
        FVector local = InverseRotateByQuat(q, relWorld);
        local.X -= car.CollisionOffset.X;
        local.Y -= car.CollisionOffset.Y;
        local.Z -= car.CollisionOffset.Z;

        constexpr float ballRadius = 93.0f;
        const float radius = ballRadius + (std::max)(0.0f, padding);
        const FVector e = car.CollisionExtent;
        const FVector closest{
            (std::max)(-e.X, (std::min)(local.X, e.X)),
            (std::max)(-e.Y, (std::min)(local.Y, e.Y)),
            (std::max)(-e.Z, (std::min)(local.Z, e.Z))
        };
        FVector delta{
            local.X - closest.X,
            local.Y - closest.Y,
            local.Z - closest.Z
        };
        const float distSq = delta.X*delta.X + delta.Y*delta.Y + delta.Z*delta.Z;
        if (distSq > radius * radius)
            return false;

        FVector localNormal{};
        if (distSq > 0.01f)
        {
            localNormal = Normalize3(delta);
        }
        else
        {
            const float px = e.X - std::abs(local.X);
            const float py = e.Y - std::abs(local.Y);
            const float pz = e.Z - std::abs(local.Z);
            if (px <= py && px <= pz) localNormal = FVector{ local.X >= 0.f ? 1.f : -1.f, 0.f, 0.f };
            else if (py <= pz)        localNormal = FVector{ 0.f, local.Y >= 0.f ? 1.f : -1.f, 0.f };
            else                      localNormal = FVector{ 0.f, 0.f, local.Z >= 0.f ? 1.f : -1.f };
        }

        *outNormal = Normalize3(RotateByQuat(q, localNormal));
        const FVector r = relWorld;
        const FVector rotational = Cross3(car.AngularVelocity, r);
        *outCarPointVelocity = FVector{
            car.LinearVelocity.X + rotational.X + forward.X * driveAccel * time,
            car.LinearVelocity.Y + rotational.Y + forward.Y * driveAccel * time,
            car.LinearVelocity.Z + rotational.Z + forward.Z * driveAccel * time
        };
        return true;
    }

    static int SafeCopyGameCars(AGameEvent_TA* gameEvent, ACar_TA** outCars, int capacity)
    {
        if (!gameEvent || !outCars || capacity <= 0)
            return 0;

        __try
        {
            const int count = gameEvent->Cars.size();
            if (count <= 0 || count > 64 || gameEvent->Cars.capacity() < count)
                return 0;

            const int copyCount = count < capacity ? count : capacity;
            for (int i = 0; i < copyCount; ++i)
                outCars[i] = gameEvent->Cars[i];
            return copyCount;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
    }

    static ACar_TA* SafeGetLocalCar()
    {
        __try
        {
            APlayerController* pc = Instances.IAPlayerController();
            if (!pc || !pc->Pawn || !pc->Pawn->IsA<ACar_TA>())
                return nullptr;
            return static_cast<ACar_TA*>(pc->Pawn);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return nullptr;
        }
    }

    static float Length3(const FVector& v)
    {
        return std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    }

    static FVector Normalize3(const FVector& v)
    {
        const float len = Length3(v);
        if (len <= 0.001f)
            return FVector{ 0.f, 0.f, 1.f };
        return FVector{ v.X / len, v.Y / len, v.Z / len };
    }

    static float Dot3(const FVector& a, const FVector& b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }

                                                                              
                                                                                
                                                                         
                                                                           
    static float GetGameTimeSeconds()
    {
        __try
        {
            if (GameEventHookModule::CurrentGameEvent &&
                GameEventHookModule::CurrentGameEvent->WorldInfo)
            {
                return GameEventHookModule::CurrentGameEvent->WorldInfo->TimeSeconds;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
        return -1.0f;
    }

    static bool IsReplayGameInfo(AGameInfo* gameInfo)
    {
        return gameInfo && gameInfo->IsA(AGameInfo_Replay_TA::StaticClass());
    }

    static bool IsReplayActive()
    {
        if (!GameEventHookModule::IsInGame)
            return false;

        if (GameEventHookModule::CurrentGameEvent &&
            GameEventHookModule::CurrentGameEvent->WorldInfo &&
            IsReplayGameInfo(GameEventHookModule::CurrentGameEvent->WorldInfo->Game))
        {
            return true;
        }

        return false;
    }

    static std::vector<ABall_TA*> CollectCandidateBalls()
    {
        std::vector<ABall_TA*> candidates;
        std::unordered_set<ABall_TA*> seenBalls;

        auto addBall = [&](ABall_TA* ball)
        {
            if (ball && seenBalls.insert(ball).second)
            {
                candidates.push_back(ball);
            }
        };

        if (GameEventHookModule::CurrentGameEvent)
        {
            for (ABall_TA* ball : GameEventHookModule::CurrentGameEvent->GameBalls)
            {
                addBall(ball);
            }
        }

        if (candidates.empty())
        {
            for (ABall_TA* ball : Instances.GetAllInstancesOf<ABall_TA>())
            {
                addBall(ball);
            }
        }

        return candidates;
    }
    
    static bool ShouldRefreshCache(const FVector& location, const FVector& velocity, const FVector& angVel,
        const std::chrono::steady_clock::time_point& now)
    {
                                                                              
                                                                               
                                                                              
                                                                                
                                                                             
                                                                               
                                                                                
                                                        
        (void)location; (void)velocity; (void)angVel; (void)now;
        return true;
    }

    static FVector BlendWorldPoint(const FVector& currentPoint, const FVector& previousPoint, float previousWeight)
    {
        const float currentWeight = 1.0f - previousWeight;
        return FVector{
            currentPoint.X * currentWeight + previousPoint.X * previousWeight,
            currentPoint.Y * currentWeight + previousPoint.Y * previousWeight,
            currentPoint.Z * currentWeight + previousPoint.Z * previousWeight
        };
    }

    static size_t MapPredictionIndex(size_t currentIndex, size_t currentCount, size_t previousCount)
    {
        if (currentCount <= 1 || previousCount == 0)
            return 0;

        return (currentIndex * (previousCount - 1)) / (currentCount - 1);
    }

    static void StabilizePredictionTail(std::vector<FVector>& points, const std::vector<FVector>& previousPoints)
    {
        if (points.size() < 12 || previousPoints.size() < 12)
            return;

        if (!previousPoints.empty() && points.size() == previousPoints.size())
        {
            float totalDelta = 0.0f;
            size_t sampleCount = (std::min)(points.size(), static_cast<size_t>(10));
            for (size_t i = 0; i < sampleCount; ++i)
            {
                size_t idx = (i * points.size()) / sampleCount;
                float dx = points[idx].X - previousPoints[idx].X;
                float dy = points[idx].Y - previousPoints[idx].Y;
                float dz = points[idx].Z - previousPoints[idx].Z;
                totalDelta += dx * dx + dy * dy + dz * dz;
            }
            if (totalDelta < 10000.0f)
                return;
        }

        const size_t startIndex = (points.size() * 65) / 100;
        const size_t tailPointCount = points.size() - startIndex;
        if (tailPointCount < 2)
            return;

        for (size_t idx = startIndex; idx < points.size(); ++idx)
        {
            const size_t previousIndex = MapPredictionIndex(idx, points.size(), previousPoints.size());
            if (previousIndex >= previousPoints.size())
                break;

            const float tailT = static_cast<float>(idx - startIndex) / static_cast<float>(tailPointCount - 1);
            float previousWeight = 0.10f + (0.30f * tailT);

            const float dx = points[idx].X - previousPoints[previousIndex].X;
            const float dy = points[idx].Y - previousPoints[previousIndex].Y;
            const float dz = points[idx].Z - previousPoints[previousIndex].Z;
            const float deltaSq = dx * dx + dy * dy + dz * dz;

            if (deltaSq > 810000.0f)
                previousWeight *= 0.10f;
            else if (deltaSq > 202500.0f)
                previousWeight *= 0.30f;

            points[idx] = BlendWorldPoint(points[idx], previousPoints[previousIndex], previousWeight);
        }
    }

    static float Vec3DistSq(const RocketSim::Vec& a, const RocketSim::Vec& b)
    {
        const float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        return dx * dx + dy * dy + dz * dz;
    }

    static RocketSim::Vec Vec3Lerp(const RocketSim::Vec& a, const RocketSim::Vec& b, float t)
    {
        return RocketSim::Vec(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t);
    }

                                                                           
                                                                              
                                                                              
                                                                           
                                                                            
                                                                            
    static void SlidePredictionWindow(int ticks)
    {
        if (ticks <= 0)
            return;

        auto& pred = s_BallPredTracker->predData;
        const size_t n = s_BallPredTracker->numPredTicks;
        if (static_cast<size_t>(ticks) >= pred.size())
        {
                                                                               
            RocketSim::BallState tail = pred.empty() ? RocketSim::BallState{} : pred.back();
            s_BallPredTracker->ForceUpdateAllPred(tail);
            return;
        }

        pred.erase(pred.begin(), pred.begin() + ticks);
        s_BallPredTracker->ballPredArena->ball->SetState(pred.back());
        while (pred.size() < n)
        {
            s_BallPredTracker->ballPredArena->Step(1);
            pred.push_back(s_BallPredTracker->ballPredArena->ball->GetState());
        }
        s_BallPredTracker->lastUpdateTickCount += ticks;
    }

                                                  
      
                                                                          
                                                                                
                                                                                 
                                                                              
                                                                              
                                                                                 
                                                                            
                                                                            
      
                                                                              
                                                                           
                                                                                 
                                                                   
                                                                           
                                                               
      
                                                          
                                                                            
                                                                                
                                                                          
                                                                            
                                                                                
                                                                                  
                                                                                  
                                                                               
                             
      
                                                                        
    static bool UpdateTracker(const RocketSim::BallState& ballState)
    {
                                                                           
                                                                            
                                                                                
                                             
        float kTick = s_BallPredTracker->ballPredArena
                    ? s_BallPredTracker->ballPredArena->tickTime
                    : (1.0f / 120.0f);
        if (kTick <= 0.0f)
            kTick = 1.0f / 120.0f;
        const float gameTime = GetGameTimeSeconds();

        auto fullResim = [&](const RocketSim::BallState& anchor)
        {
            s_BallPredTracker->ForceUpdateAllPred(anchor);
            s_Cache.PredBaseTimeSeconds  = gameTime;
            s_Cache.LastResimTimeSeconds = gameTime;
        };

                                                                             
                                                                           
                                                                                
                                                                          
                                        
        if (!s_Cache.bInitialized || s_Cache.PredBaseTimeSeconds < 0.0f || gameTime < 0.0f)
        {
            fullResim(ballState);
            return true;
        }

        const float elapsedTicks = (gameTime - s_Cache.PredBaseTimeSeconds) / kTick;
        if (elapsedTicks < 0.0f || elapsedTicks > 1.0f / kTick)                       
        {
            fullResim(ballState);
            return true;
        }

        int   k    = static_cast<int>(std::floor(elapsedTicks));
        float frac = elapsedTicks - static_cast<float>(k);
        if (k < 0) { k = 0; frac = 0.0f; }

        const auto& pred = s_BallPredTracker->predData;
        if (static_cast<size_t>(k) + 1 >= pred.size())
        {
            fullResim(ballState);
            return true;
        }

                                                                      
        RocketSim::BallState predicted = pred[k];
        predicted.pos    = Vec3Lerp(pred[k].pos,    pred[k + 1].pos,    frac);
        predicted.vel    = Vec3Lerp(pred[k].vel,    pred[k + 1].vel,    frac);
        predicted.angVel = Vec3Lerp(pred[k].angVel, pred[k + 1].angVel, frac);

        const float dPosSq = Vec3DistSq(ballState.pos, predicted.pos);
        const float dVelSq = Vec3DistSq(ballState.vel, predicted.vel);

                                                                                 
                                                                                
        constexpr float kReusePosSq = 12.0f * 12.0f;                                    
        constexpr float kReuseVelSq = 60.0f * 60.0f;              
        constexpr float kHitPosSq   = 60.0f * 60.0f;                                 
        constexpr float kHitVelSq   = 300.0f * 300.0f;             

                                                                          
                                                 
        if (dPosSq > kHitPosSq || dVelSq > kHitVelSq)
        {
            fullResim(ballState);
            return true;
        }

                                                                                 
                                        
        if (k > 0)
        {
            SlidePredictionWindow(k);
            s_Cache.PredBaseTimeSeconds += static_cast<float>(k) * kTick;
        }

        if (dPosSq > kReusePosSq || dVelSq > kReuseVelSq)
        {
                                                                                   
                                                                                
                                                                                 
                                                                                 
                                         
            if (s_Cache.LastResimTimeSeconds < 0.0f ||
                gameTime - s_Cache.LastResimTimeSeconds >= 0.25f)
            {
                constexpr float kCorrect = 0.35f;
                RocketSim::BallState anchor = ballState;
                anchor.pos    = Vec3Lerp(predicted.pos,    ballState.pos,    kCorrect);
                anchor.vel    = Vec3Lerp(predicted.vel,    ballState.vel,    kCorrect);
                anchor.angVel = Vec3Lerp(predicted.angVel, ballState.angVel, kCorrect);
                fullResim(anchor);
                return true;
            }
        }

        return false;
    }

                                             
      
                                                                
                                                        
                                                                                
                                                                              
                                                                             
                                                                               
                                                                            
                                                                                
                                                                                
                                                                           
    static RocketSim::BallState SampleBallStateAtTime(float predTime)
    {
        const auto& pred = s_BallPredTracker->predData;
        if (pred.empty())
            return RocketSim::BallState{};

        float tickTime = s_BallPredTracker->ballPredArena
                       ? s_BallPredTracker->ballPredArena->tickTime
                       : (1.0f / 120.0f);
        if (tickTime <= 0.0f)
            tickTime = 1.0f / 120.0f;

        if (predTime <= 0.0f)
            return pred.front();

        const float exact = predTime / tickTime;
        const float maxIndex = static_cast<float>(pred.size() - 1);
        if (exact >= maxIndex)
            return pred.back();

        const int   i = static_cast<int>(std::floor(exact));
        const float f = exact - static_cast<float>(i);

        RocketSim::BallState out = pred[i];
        out.pos    = Vec3Lerp(pred[i].pos,    pred[i + 1].pos,    f);
        out.vel    = Vec3Lerp(pred[i].vel,    pred[i + 1].vel,    f);
        out.angVel = Vec3Lerp(pred[i].angVel, pred[i + 1].angVel, f);
        return out;
    }

    static void RefreshCacheWithRocketSim(const FVector& ballPos, const FVector& ballVel, const FVector& ballAngVel)
    {
        if (!s_RocketSimInitialized || !s_BallPredTracker || !s_PredArena)
            return;

                                 
        auto& s_Settings = GetSettings();

                                      
        RocketSim::BallState ballState;
        ballState.pos = RocketSim::Vec(ballPos.X, ballPos.Y, ballPos.Z);
        ballState.vel = RocketSim::Vec(ballVel.X, ballVel.Y, ballVel.Z);
        ballState.angVel = RocketSim::Vec(ballAngVel.X, ballAngVel.Y, ballAngVel.Z);

                                                                         
                                                                         
        const bool discontinuity = UpdateTracker(ballState);

        const float predictionTime = GetPredictionTimeSeconds();
        const int steps = GetSampleCount(predictionTime);
        const int divisor = (steps - 1) > 0 ? (steps - 1) : 1;
        const std::vector<FVector> previousWorldPoints = s_Cache.WorldPoints;

                                                              
        s_Cache.WorldPoints.clear();
        s_Cache.WorldPoints.reserve(static_cast<size_t>(steps));
        s_Cache.BouncePoints.clear();
        s_Cache.bGoalPredicted = false;
        s_Cache.bHasGoalImpact = false;
        s_Cache.fGoalImpactTime = 0.f;
        s_Cache.bHasLanding = false;

        RocketSim::BallState prevState = SampleBallStateAtTime(0.0f);

                                        
                                  
                                 
                                  
        const float GOAL_Y = 5120.0f;
        const float GOAL_X = 892.755f;                       
        const float GOAL_Z = 642.775f;                        
        constexpr float BALL_RADIUS = 93.0f;

                                          
        s_Cache.WorldPoints.emplace_back(FVector{
            static_cast<float>(prevState.pos.x),
            static_cast<float>(prevState.pos.y),
            static_cast<float>(prevState.pos.z)
        });

        for (int i = 1; i < steps; ++i)
        {
            const float predTime = predictionTime * (static_cast<float>(i) / static_cast<float>(divisor));

            RocketSim::BallState predState = SampleBallStateAtTime(predTime);

                                                                                      
            if (!s_Cache.bGoalPredicted)
            {
                float absY = std::abs(predState.pos.y);
                float absX = std::abs(predState.pos.x);
                float absPrevY = std::abs(prevState.pos.y);

                                                                             
                                                                               
                                                                                
                if (absY >= GOAL_Y && absPrevY < GOAL_Y)
                {
                                                                          
                    bool movingTowardWall = (predState.pos.y > 0) ? (predState.vel.y > 0.0f) : (predState.vel.y < 0.0f);

                                                                                                 
                    if (movingTowardWall && absX <= GOAL_X - BALL_RADIUS && predState.pos.z <= GOAL_Z - BALL_RADIUS)
                    {
                        s_Cache.bGoalPredicted = true;

                                                                                   
                                                                                     
                        const float planeY = (predState.pos.y > 0) ? GOAL_Y : -GOAL_Y;
                        const float denom = (predState.pos.y - prevState.pos.y);
                        float t = 0.5f;
                        if (std::abs(denom) > 0.0001f)
                            t = (planeY - static_cast<float>(prevState.pos.y)) / static_cast<float>(denom);
                        if (t < 0.f) t = 0.f;
                        if (t > 1.f) t = 1.f;

                        s_Cache.GoalImpactPoint = FVector{
                            static_cast<float>(prevState.pos.x + (predState.pos.x - prevState.pos.x) * t),
                            planeY,
                            static_cast<float>(prevState.pos.z + (predState.pos.z - prevState.pos.z) * t)
                        };
                        s_Cache.bHasGoalImpact = true;

                                                                                
                        const float prevPredTime = predictionTime * (static_cast<float>(i - 1) / static_cast<float>(divisor));
                        s_Cache.fGoalImpactTime = prevPredTime + (predTime - prevPredTime) * t;
                    }
                }
            }

                                                                        
            if (!s_Cache.bHasLanding)
            {
                const float floorZ = BALL_RADIUS + 5.0f;
                if (prevState.pos.z > floorZ && predState.pos.z <= floorZ && predState.vel.z <= 0.0f)
                {
                    const float denom = (predState.pos.z - prevState.pos.z);
                    float t = 0.5f;
                    if (std::abs(denom) > 0.0001f)
                        t = (floorZ - static_cast<float>(prevState.pos.z)) / static_cast<float>(denom);
                    if (t < 0.f) t = 0.f;
                    if (t > 1.f) t = 1.f;
                    s_Cache.LandingPoint = FVector{
                        static_cast<float>(prevState.pos.x + (predState.pos.x - prevState.pos.x) * t),
                        static_cast<float>(prevState.pos.y + (predState.pos.y - prevState.pos.y) * t),
                        floorZ
                    };
                    s_Cache.bHasLanding = true;
                }
            }

                                                                                        
            if (i % 3 == 0)
            {
                float dot = (prevState.vel.x * predState.vel.x + prevState.vel.y * predState.vel.y + prevState.vel.z * predState.vel.z);
                float magPrevSq = (prevState.vel.x * prevState.vel.x + prevState.vel.y * prevState.vel.y + prevState.vel.z * prevState.vel.z);
                float magCurrSq = (predState.vel.x * predState.vel.x + predState.vel.y * predState.vel.y + predState.vel.z * predState.vel.z);
                
                if (magPrevSq > 100.0f && magCurrSq > 100.0f)
                {
                                                                               
                    float cosTheta = dot * rsqrt(magPrevSq * magCurrSq);
                    if (cosTheta < 0.9f)
                    {
                        if (s_Cache.BouncePoints.empty())
                        {
                            s_Cache.BouncePoints.emplace_back(FVector{
                                static_cast<float>(predState.pos.x),
                                static_cast<float>(predState.pos.y),
                                static_cast<float>(predState.pos.z)
                            });
                        }
                        else
                        {
                            float dx = s_Cache.BouncePoints.back().X - predState.pos.x;
                            float dy = s_Cache.BouncePoints.back().Y - predState.pos.y;
                            float dz = s_Cache.BouncePoints.back().Z - predState.pos.z;
                            float distSq = dx * dx + dy * dy + dz * dz;
                            if (distSq > 2500.f)
                            {
                                s_Cache.BouncePoints.emplace_back(FVector{
                                    static_cast<float>(predState.pos.x),
                                    static_cast<float>(predState.pos.y),
                                    static_cast<float>(predState.pos.z)
                                });
                            }
                        }
                    }
                }
            }

            s_Cache.WorldPoints.emplace_back(FVector{ 
                static_cast<float>(predState.pos.x), 
                static_cast<float>(predState.pos.y), 
                static_cast<float>(predState.pos.z) 
            });
            
            prevState = predState;
        }

                                                                              
                                                                              
                                                                           
                                                                            
        s_Cache.PreviousWorldPoints = previousWorldPoints;
        s_Cache.LerpStartTime = std::chrono::steady_clock::now();
        s_Cache.bLerping = discontinuity && !previousWorldPoints.empty();
        s_Cache.LastBallLocation = ballPos;
        s_Cache.LastBallVelocity = ballVel;
        s_Cache.LastBallAngVelocity = ballAngVel;
        s_Cache.LastUpdate = std::chrono::steady_clock::now();
        s_Cache.bInitialized = true;
    }

                                                                       
    static void RefreshCacheSimple(const FVector& startPos, const FVector& startVel)
    {
        constexpr float tickRate = 30.0f;                                      
        const float predictionTime = GetPredictionTimeSeconds();
        const float timeStep = 1.0f / tickRate;
        const int totalSteps = static_cast<int>(predictionTime * tickRate);
        const int steps = GetSampleCount(predictionTime);
        const int divisor = (steps - 1) > 0 ? (steps - 1) : 1;
        const int storeInterval = totalSteps / divisor > 0 ? totalSteps / divisor : 1;
        const std::vector<FVector> previousWorldPoints = s_Cache.WorldPoints;
        
        s_Cache.WorldPoints.clear();
        s_Cache.WorldPoints.reserve(static_cast<size_t>(steps));
        s_Cache.BouncePoints.clear();
        s_Cache.bGoalPredicted = false;
        s_Cache.bHasGoalImpact = false;
        s_Cache.fGoalImpactTime = 0.0f;

        FVector currentPos = startPos;
        FVector currentVel = startVel;
        
        constexpr float gravity = -650.0f;
        constexpr float ballRadius = 93.0f;
        constexpr float restitution = 0.6f;
        constexpr float arenaHalfX = 4096.0f;
        constexpr float arenaHalfY = 5120.0f;
        constexpr float arenaHeight = 2044.0f;
        constexpr float goalHalfWidth = 893.0f;
        constexpr float goalHeight = 642.0f;
        
        s_Cache.WorldPoints.emplace_back(currentPos);

        for (int i = 0; i < totalSteps; ++i)
        {
            FVector nextPos;
            nextPos.X = currentPos.X + currentVel.X * timeStep;
            nextPos.Y = currentPos.Y + currentVel.Y * timeStep;
            nextPos.Z = currentPos.Z + currentVel.Z * timeStep;

                                                                              
                                                                             
                                                                 
            const bool canEnterGoal =
                (std::abs(nextPos.X) <= goalHalfWidth - ballRadius) &&
                (nextPos.Z <= goalHeight - ballRadius);

            bool reachedGoalPlane = false;
            if (canEnterGoal && currentVel.Y > 0.0f &&
                currentPos.Y < arenaHalfY && nextPos.Y >= arenaHalfY)
            {
                const float dy = nextPos.Y - currentPos.Y;
                float f = std::abs(dy) > 0.0001f ? (arenaHalfY - currentPos.Y) / dy : 1.0f;
                f = (std::max)(0.0f, (std::min)(1.0f, f));
                s_Cache.GoalImpactPoint = FVector{
                    currentPos.X + (nextPos.X - currentPos.X) * f,
                    arenaHalfY,
                    currentPos.Z + (nextPos.Z - currentPos.Z) * f
                };
                s_Cache.bGoalPredicted = true;
                s_Cache.bHasGoalImpact = true;
                s_Cache.fGoalImpactTime = (static_cast<float>(i) + f) * timeStep;
                nextPos = s_Cache.GoalImpactPoint;
                reachedGoalPlane = true;
            }
            else if (canEnterGoal && currentVel.Y < 0.0f &&
                     currentPos.Y > -arenaHalfY && nextPos.Y <= -arenaHalfY)
            {
                const float dy = nextPos.Y - currentPos.Y;
                float f = std::abs(dy) > 0.0001f ? (-arenaHalfY - currentPos.Y) / dy : 1.0f;
                f = (std::max)(0.0f, (std::min)(1.0f, f));
                s_Cache.GoalImpactPoint = FVector{
                    currentPos.X + (nextPos.X - currentPos.X) * f,
                    -arenaHalfY,
                    currentPos.Z + (nextPos.Z - currentPos.Z) * f
                };
                s_Cache.bGoalPredicted = true;
                s_Cache.bHasGoalImpact = true;
                s_Cache.fGoalImpactTime = (static_cast<float>(i) + f) * timeStep;
                nextPos = s_Cache.GoalImpactPoint;
                reachedGoalPlane = true;
            }
            else if (!canEnterGoal && nextPos.Y > arenaHalfY - ballRadius)
            {
                nextPos.Y = arenaHalfY - ballRadius;
                currentVel.Y = -std::abs(currentVel.Y) * restitution;
            }
            else if (!canEnterGoal && nextPos.Y < -arenaHalfY + ballRadius)
            {
                nextPos.Y = -arenaHalfY + ballRadius;
                currentVel.Y = std::abs(currentVel.Y) * restitution;
            }

            if (reachedGoalPlane)
            {
                currentPos = nextPos;
                s_Cache.WorldPoints.emplace_back(currentPos);
                break;
            }
            
            if (nextPos.Z < ballRadius)
            {
                nextPos.Z = ballRadius;
                currentVel.Z = -currentVel.Z * restitution;
            }
            else
            {
                currentVel.Z += gravity * timeStep;
            }
            
            if (nextPos.Z >= arenaHeight - ballRadius)
            {
                nextPos.Z = arenaHeight - ballRadius;
                if (currentVel.Z > 0.0f)
                    currentVel.Z = -currentVel.Z * restitution;
            }
            
            if (nextPos.X > arenaHalfX - ballRadius)
            {
                nextPos.X = arenaHalfX - ballRadius;
                currentVel.X = -std::abs(currentVel.X) * restitution;
            }
            else if (nextPos.X < -arenaHalfX + ballRadius)
            {
                nextPos.X = -arenaHalfX + ballRadius;
                currentVel.X = std::abs(currentVel.X) * restitution;
            }
            
            currentPos = nextPos;

            if (i % storeInterval == 0)
            {
                s_Cache.WorldPoints.emplace_back(currentPos);
            }
        }
        
        if (!s_Cache.WorldPoints.empty() && s_Cache.WorldPoints.size() < static_cast<size_t>(steps))
        {
            s_Cache.WorldPoints.emplace_back(currentPos);
        }

        StabilizePredictionTail(s_Cache.WorldPoints, previousWorldPoints);

        s_Cache.PreviousWorldPoints = previousWorldPoints;
        s_Cache.LerpStartTime = std::chrono::steady_clock::now();
        s_Cache.bLerping = !previousWorldPoints.empty();
        s_Cache.LastBallLocation = startPos;
        s_Cache.LastBallVelocity = startVel;
        s_Cache.LastBallAngVelocity = FVector{ 0.f, 0.f, 0.f };
        s_Cache.LastUpdate = std::chrono::steady_clock::now();
        s_Cache.bInitialized = true;
    }

    void UpdatePrediction()
    {
                                             
        if (!s_RocketSimInitialized)
        {
            InitRocketSim();
        }

        using namespace std::chrono;
        auto now = steady_clock::now();
        const bool isReplayActive = IsReplayActive();

        if (isReplayActive != s_LastReplayState)
        {
            ForceRefresh();
        }
        s_LastReplayState = isReplayActive;

                                                              
        bool currentInGameState = GameEventHook.IsInGame;
        if (currentInGameState && !s_LastInGameState)
        {
                                                                         
            s_Cache.CachedBall = nullptr;
            s_Cache.bInitialized = false;
            s_Cache.WorldPoints.clear();
            s_Cache.LastBallSearch = now - milliseconds(500);                          
        }
        s_LastInGameState = currentInGameState;

                               
        if (s_Cache.CachedBall && !IsBallValid(s_Cache.CachedBall))
        {
            s_Cache.CachedBall = nullptr;
            s_Cache.bInitialized = false;
        }

                                                                                                  
        int searchIntervalMs = s_Cache.CachedBall ? 500 : 100;
        if (!s_Cache.CachedBall || duration_cast<milliseconds>(now - s_Cache.LastBallSearch).count() > searchIntervalMs)
        {
            std::vector<ABall_TA*> balls = CollectCandidateBalls();
            ABall_TA* bestBall = nullptr;
            float bestSpeedSq = -1.0f;
            for (ABall_TA* candidate : balls)
            {
                if (!IsBallValid(candidate))
                    continue;

                FVector loc, vel, ang;
                if (!SafeReadBallState(candidate, loc, vel, ang))
                    continue;

                float speedSq = vel.X * vel.X + vel.Y * vel.Y + vel.Z * vel.Z;
                if (speedSq > bestSpeedSq)
                {
                    bestSpeedSq = speedSq;
                    bestBall = candidate;
                }
            }
            s_Cache.CachedBall = bestBall;
            s_Cache.LastBallSearch = now;
            
            if (s_Cache.CachedBall)
            {
                s_Cache.bInitialized = false;
            }
        }

        if (!s_Cache.CachedBall)
            return;

                                
        FVector ballLocation, ballVelocity, ballAngVel;
        if (!SafeReadBallState(s_Cache.CachedBall, ballLocation, ballVelocity, ballAngVel))
        {
                                                                          
            s_Cache.CachedBall = nullptr;
            s_Cache.bInitialized = false;
            return;
        }
        
                                                                                                       
                                                                                                             

        now = std::chrono::steady_clock::now();

        if (s_RocketSimInitialized)
        {
                                                                           
                                                                               
                                                                      
            RefreshCacheWithRocketSim(ballLocation, ballVelocity, ballAngVel);
        }
        else
        {
                                                                           
            static auto lastPredictionTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPredictionTime).count();
            if (elapsed >= 33)
            {
                lastPredictionTime = now;
                RefreshCacheSimple(ballLocation, ballVelocity);
            }
        }
    }

    void Draw(UCanvas* canvas)
    {
        if (!canvas)
            return;

                                              
        auto& settings = GetSettings();
                                                                      
        if (!settings.bShowLine && !settings.bShowBallShape && !settings.bPredictGoal)
            return;
            
                                                            
        if (!GameEventHook.IsInGame)
            return;

        UpdatePrediction();

        if (s_Cache.WorldPoints.empty())
            return;

                                                                          
        float lerpT = 1.0f;
        if (s_Cache.bLerping && !s_Cache.PreviousWorldPoints.empty())
        {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - s_Cache.LerpStartTime).count();
            if (elapsed < 100)
                lerpT = static_cast<float>(elapsed) / 100.0f;
            else
                s_Cache.bLerping = false;
        }

                                      
        FColor lineColor = UObject::MakeColor(
            static_cast<uint8_t>(settings.cLineColor.R * 255.0f),
            static_cast<uint8_t>(settings.cLineColor.G * 255.0f),
            static_cast<uint8_t>(settings.cLineColor.B * 255.0f),
            static_cast<uint8_t>(settings.fOpacity * 255.0f)
        );
        
        const int lineThickness = static_cast<int>(std::round(settings.fThickness));

        FVector previousScreenPos{ 0.f, 0.f, 0.f };
        bool hasPrevious = false;
        const size_t numPoints = s_Cache.WorldPoints.size();

        const size_t pointsToDraw = numPoints;
        
        for (size_t idx = 0; idx < pointsToDraw; ++idx)
        {
            FVector worldPoint = s_Cache.WorldPoints[idx];

            if (lerpT < 1.0f && !s_Cache.PreviousWorldPoints.empty())
            {
                size_t prevIdx = MapPredictionIndex(idx, pointsToDraw, s_Cache.PreviousWorldPoints.size());
                if (prevIdx < s_Cache.PreviousWorldPoints.size())
                {
                    worldPoint = BlendWorldPoint(worldPoint, s_Cache.PreviousWorldPoints[prevIdx], 1.0f - lerpT);
                }
            }

            FVector screenPos = canvas->Project(worldPoint);
            
            if (screenPos.Z <= 0.0f)
            {
                hasPrevious = false;
                continue;
            }

            if (settings.bShowLine && hasPrevious)
            {
                const int half = lineThickness / 2;
                float ldx = screenPos.X - previousScreenPos.X;
                float ldy = screenPos.Y - previousScreenPos.Y;
                float len = std::sqrt(ldx * ldx + ldy * ldy);
                float nx = 0.0f, ny = 1.0f;
                if (len > 0.001f)
                {
                    nx = -ldy / len;
                    ny =  ldx / len;
                }
                for (int i = -half; i <= half; ++i)
                {
                    canvas->Draw2DLine(
                        previousScreenPos.X + nx * i, previousScreenPos.Y + ny * i,
                        screenPos.X + nx * i, screenPos.Y + ny * i,
                        lineColor
                    );
                }
            }

            previousScreenPos = screenPos;
            hasPrevious = true;
        }
    }

                                                                        
                                                                       
                                                          
    static std::vector<FVector> s_BlendedWorldPoints;

                                                         
    PredictionData GetPredictionData()
    {
        auto& settings = GetSettings();
        const int fadeMs = settings.bExtraSmoothing ? 220 : 130;

        float lerpT = 1.0f;
        if (s_Cache.bLerping && !s_Cache.PreviousWorldPoints.empty())
        {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - s_Cache.LerpStartTime).count();
            if (elapsed < fadeMs)
                lerpT = static_cast<float>(elapsed) / (float)fadeMs;
            else
                s_Cache.bLerping = false;
        }

        s_BlendedWorldPoints.clear();
        s_BlendedWorldPoints.reserve(s_Cache.WorldPoints.size());
        if (lerpT >= 1.0f || s_Cache.PreviousWorldPoints.empty())
            s_BlendedWorldPoints = s_Cache.WorldPoints;
        else
        {
            const size_t curCount = s_Cache.WorldPoints.size();
            for (size_t idx = 0; idx < curCount; ++idx)
            {
                FVector p = s_Cache.WorldPoints[idx];
                const size_t prevIdx = MapPredictionIndex(idx, curCount, s_Cache.PreviousWorldPoints.size());
                if (prevIdx < s_Cache.PreviousWorldPoints.size())
                    p = BlendWorldPoint(p, s_Cache.PreviousWorldPoints[prevIdx], 1.0f - lerpT);
                s_BlendedWorldPoints.emplace_back(p);
            }
        }

        PredictionData data{};
        data.WorldPoints = &s_BlendedWorldPoints;
        data.bGoalPredicted = s_Cache.bGoalPredicted;
        data.GoalImpactPoint = s_Cache.GoalImpactPoint;
        data.bHasGoalImpact = s_Cache.bHasGoalImpact;
        data.fGoalImpactTime = s_Cache.fGoalImpactTime;
        data.LandingPoint = s_Cache.LandingPoint;
        data.bHasLanding = s_Cache.bHasLanding;
        data.BouncePoints = &s_Cache.BouncePoints;

                                                                           
                                                                             
                                                                              
                                                                     
        if (settings.bPreHitEnabled && !s_PreHitPredictions.empty() &&
            !s_BlendedWorldPoints.empty())
        {
            const PreHitPredictionData& hit = s_PreHitPredictions.front();
            const size_t contactIndex = (std::min)(hit.ContactPathIndex, s_BlendedWorldPoints.size() - 1);
            s_EffectiveWorldPoints.clear();
            s_EffectiveTimes.clear();
            s_EffectiveBouncePoints.clear();
            s_EffectiveWorldPoints.reserve(contactIndex + 1 + hit.WorldPoints.size());
            s_EffectiveTimes.reserve(contactIndex + 1 + hit.WorldPoints.size());

            const float basePredictionTime = GetPredictionTimeSeconds();
            const float denom = (float)(std::max)(size_t(1), s_BlendedWorldPoints.size() - 1);
            for (size_t i = 0; i <= contactIndex; ++i)
            {
                s_EffectiveWorldPoints.push_back(s_BlendedWorldPoints[i]);
                s_EffectiveTimes.push_back(basePredictionTime * ((float)i / denom));
            }
            for (size_t i = 0; i < hit.WorldPoints.size(); ++i)
            {
                if (i == 0 && !s_EffectiveWorldPoints.empty())
                    continue;
                s_EffectiveWorldPoints.push_back(hit.WorldPoints[i]);
                const float t = hit.WorldPoints.size() > 1
                    ? PREHIT_POST_SECONDS * ((float)i / (float)(hit.WorldPoints.size() - 1))
                    : 0.0f;
                s_EffectiveTimes.push_back(hit.TimeToHit + t);
            }

            data.WorldPoints = &s_EffectiveWorldPoints;
            data.BouncePoints = &s_EffectiveBouncePoints;
            data.bGoalPredicted = false;
            data.bHasGoalImpact = false;
            data.fGoalImpactTime = 0.f;
            data.bHasLanding = false;

            constexpr float GOAL_Y = 5120.0f;
            constexpr float GOAL_X = 892.755f;
            constexpr float GOAL_Z = 642.775f;
            constexpr float BALL_RADIUS = 93.0f;
            const float floorZ = BALL_RADIUS + 5.0f;

            for (size_t i = 1; i < s_EffectiveWorldPoints.size(); ++i)
            {
                const FVector& a = s_EffectiveWorldPoints[i - 1];
                const FVector& b = s_EffectiveWorldPoints[i];
                if (!data.bGoalPredicted && std::abs(b.Y) >= GOAL_Y &&
                    std::abs(a.Y) < GOAL_Y && std::abs(b.X) <= GOAL_X - BALL_RADIUS &&
                    b.Z <= GOAL_Z - BALL_RADIUS)
                {
                    const float planeY = b.Y > 0.f ? GOAL_Y : -GOAL_Y;
                    const float dy = b.Y - a.Y;
                    float f = std::abs(dy) > 0.001f ? (planeY - a.Y) / dy : 0.5f;
                    f = (std::max)(0.f, (std::min)(1.f, f));
                    data.GoalImpactPoint = FVector{ a.X + (b.X-a.X)*f, planeY, a.Z + (b.Z-a.Z)*f };
                    data.bGoalPredicted = true;
                    data.bHasGoalImpact = true;
                    if (i < s_EffectiveTimes.size())
                        data.fGoalImpactTime = s_EffectiveTimes[i-1] + (s_EffectiveTimes[i]-s_EffectiveTimes[i-1])*f;
                }
                if (!data.bHasLanding && a.Z > floorZ && b.Z <= floorZ)
                {
                    const float dz = b.Z - a.Z;
                    float f = std::abs(dz) > 0.001f ? (floorZ - a.Z) / dz : 0.5f;
                    f = (std::max)(0.f, (std::min)(1.f, f));
                    data.LandingPoint = FVector{ a.X+(b.X-a.X)*f, a.Y+(b.Y-a.Y)*f, floorZ };
                    data.bHasLanding = true;
                }
                if (i >= 2)
                {
                    const FVector& p = s_EffectiveWorldPoints[i - 2];
                    const FVector v0{ a.X-p.X, a.Y-p.Y, a.Z-p.Z };
                    const FVector v1{ b.X-a.X, b.Y-a.Y, b.Z-a.Z };
                    const float l0 = Length3(v0), l1 = Length3(v1);
                    if (l0 > 1.f && l1 > 1.f && Dot3(v0,v1)/(l0*l1) < 0.82f)
                    {
                        if (s_EffectiveBouncePoints.empty() ||
                            Length3(FVector{a.X-s_EffectiveBouncePoints.back().X,
                                            a.Y-s_EffectiveBouncePoints.back().Y,
                                            a.Z-s_EffectiveBouncePoints.back().Z}) > 50.f)
                            s_EffectiveBouncePoints.push_back(a);
                    }
                }
            }
        }
        return data;
    }

    void UpdatePreHitPredictions()
    {
        auto& settings = GetSettings();
        if (!settings.bPreHitEnabled || !GameEventHookModule::IsInGame ||
            GameEventHookModule::IsInReplayPlayback || !GameEventHookModule::CurrentGameEvent)
        {
            s_PreHitPredictions.clear();
            return;
        }

        if (!s_RocketSimInitialized)
            InitRocketSim();
        if (!s_PreHitPredTracker || s_Cache.WorldPoints.size() < 3)
        {
            s_PreHitPredictions.clear();
            return;
        }

        using namespace std::chrono;
        const auto now = steady_clock::now();
        if (s_LastPreHitUpdate != steady_clock::time_point{} &&
            duration_cast<milliseconds>(now - s_LastPreHitUpdate).count() < 16)
            return;
        s_LastPreHitUpdate = now;
        s_PreHitPredictions.clear();

        ACar_TA* cars[24]{};
        const int carCount = SafeCopyGameCars(GameEventHookModule::CurrentGameEvent, cars, (int)_countof(cars));
        if (carCount <= 0)
            return;

        ACar_TA* localCar = settings.iPreHitCarMode == 1 ? SafeGetLocalCar() : nullptr;
        if (settings.iPreHitCarMode == 1 && !localCar)
            return;

        const float predictionTime = GetPredictionTimeSeconds();
        const float pathDt = predictionTime / (float)(std::max)(size_t(1), s_Cache.WorldPoints.size() - 1);
        const float lookAhead = (std::max)(0.15f, (std::min)(settings.fPreHitLookAhead, 2.0f));
        const float maxDistance = (std::max)(250.0f, (std::min)(settings.fPreHitMaxCarDistance, 5000.0f));
        const float hitboxPadding = (std::max)(0.0f, (std::min)(settings.fPreHitHitboxPadding, 80.0f));
        constexpr float kMinClosingSpeed = 20.0f;
        constexpr float kMaxBallSpeed = 6000.0f;

        struct Candidate
        {
            int CarIndex = -1;
            size_t PathIndex = 0;
            CarPhysicsSnapshot Car{};
            FVector Contact{};
            FVector Normal{};
            FVector BallVelAtContact{};
            FVector CarPointVelocity{};
            float Time = 0.0f;
            float Distance = 0.0f;
            float ClosingSpeed = 0.0f;
        };

        std::vector<Candidate> candidates;
        candidates.reserve((size_t)carCount);

        for (int carIndex = 0; carIndex < carCount; ++carIndex)
        {
            ACar_TA* car = cars[carIndex];
            if (!car) continue;
            if (settings.iPreHitCarMode == 1 && car != localCar) continue;
            if (settings.iPreHitCarMode == 2 &&
                carIndex != std::clamp(settings.iPreHitSelectedCarIndex, 0, carCount - 1)) continue;

            CarPhysicsSnapshot snap{};
            if (!SafeReadCarPhysics(car, &snap)) continue;

            const FVector toBall{
                s_Cache.WorldPoints.front().X - snap.Position.X,
                s_Cache.WorldPoints.front().Y - snap.Position.Y,
                s_Cache.WorldPoints.front().Z - snap.Position.Z
            };
            const float currentDistance = Length3(toBall);
            if (currentDistance > maxDistance) continue;

            Candidate best{};
            best.CarIndex = carIndex;
            best.Car = snap;
            best.Distance = currentDistance;
            bool found = false;

            for (size_t i = 1; i < s_Cache.WorldPoints.size(); ++i)
            {
                const float t = (float)i * pathDt;
                if (t > lookAhead) break;

                const size_t prevIndex = i - 1;
                const size_t nextIndex = (std::min)(i + 1, s_Cache.WorldPoints.size() - 1);
                const float velDt = (float)(nextIndex - prevIndex) * pathDt;
                if (velDt <= 0.0001f) continue;
                const FVector ballVel{
                    (s_Cache.WorldPoints[nextIndex].X - s_Cache.WorldPoints[prevIndex].X) / velDt,
                    (s_Cache.WorldPoints[nextIndex].Y - s_Cache.WorldPoints[prevIndex].Y) / velDt,
                    (s_Cache.WorldPoints[nextIndex].Z - s_Cache.WorldPoints[prevIndex].Z) / velDt
                };

                FVector normal{}, carPointVel{};
                if (!TestBallVsPredictedCarBox(snap, s_Cache.WorldPoints[i], t,
                                               hitboxPadding, &normal, &carPointVel))
                    continue;

                const FVector relative{
                    carPointVel.X - ballVel.X,
                    carPointVel.Y - ballVel.Y,
                    carPointVel.Z - ballVel.Z
                };
                const float closing = Dot3(relative, normal);
                if (closing < kMinClosingSpeed) continue;

                best.PathIndex = i;
                best.Contact = s_Cache.WorldPoints[i];
                best.Normal = normal;
                best.BallVelAtContact = ballVel;
                best.CarPointVelocity = carPointVel;
                best.Time = t;
                best.ClosingSpeed = closing;
                found = true;
                break;
            }
            if (found) candidates.push_back(best);
        }

        if (candidates.empty()) return;
        std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
            if (std::abs(a.Time - b.Time) > 0.0001f) return a.Time < b.Time;
            if (std::abs(a.ClosingSpeed - b.ClosingSpeed) > 0.1f) return a.ClosingSpeed > b.ClosingSpeed;
            return a.Distance < b.Distance;
        });

                                                                             
                                                                           
                                                                              
                                                                             
                                                              
        const Candidate& candidate = candidates.front();
        const float carSpeed = Length3(candidate.Car.LinearVelocity);
        const FVector normal = candidate.Normal;
        const float impulse = (std::min)(5000.0f,
            candidate.ClosingSpeed * 1.62f + (std::min)(carSpeed * 0.10f, 340.0f) + 120.0f);

                                                                              
                                                                               
                                                                 
        const float carNormal = Dot3(candidate.CarPointVelocity, normal);
        const FVector tangent{
            candidate.CarPointVelocity.X - normal.X * carNormal,
            candidate.CarPointVelocity.Y - normal.Y * carNormal,
            candidate.CarPointVelocity.Z - normal.Z * carNormal
        };
        FVector postVel{
            candidate.BallVelAtContact.X + normal.X * impulse + tangent.X * 0.10f,
            candidate.BallVelAtContact.Y + normal.Y * impulse + tangent.Y * 0.10f,
            candidate.BallVelAtContact.Z + normal.Z * impulse + tangent.Z * 0.10f
        };
        const float postSpeed = Length3(postVel);
        if (postSpeed > kMaxBallSpeed && postSpeed > 0.001f)
        {
            const float scale = kMaxBallSpeed / postSpeed;
            postVel.X *= scale; postVel.Y *= scale; postVel.Z *= scale;
        }

        RocketSim::BallState state;
        state.pos = RocketSim::Vec(candidate.Contact.X, candidate.Contact.Y, candidate.Contact.Z);
        state.vel = RocketSim::Vec(postVel.X, postVel.Y, postVel.Z);
        state.angVel = RocketSim::Vec(s_Cache.LastBallAngVelocity.X,
                                      s_Cache.LastBallAngVelocity.Y,
                                      s_Cache.LastBallAngVelocity.Z);
        try { s_PreHitPredTracker->ForceUpdateAllPred(state); }
        catch (...) { return; }

        auto fillMetadata = [](PreHitPredictionData& output, const Candidate& c)
        {
            output.CarIndex = c.CarIndex;
            output.ContactPathIndex = c.PathIndex;
            output.ContactPoint = c.Contact;
            output.CarHitboxExtent = c.Car.CollisionExtent;
            output.TimeToHit = c.Time;
            output.CurrentCarDistance = c.Distance;
            output.CarSpeed = Length3(c.Car.LinearVelocity);
            output.ClosingSpeed = c.ClosingSpeed;
            output.Throttle = c.Car.Throttle;
            output.Steer = c.Car.Steer;
            output.OnGround = c.Car.OnGround;
            output.Boosting = c.Car.Boosting;
        };

        PreHitPredictionData output{};
        fillMetadata(output, candidate);

        constexpr int kSamples = 72;
        output.WorldPoints.reserve(kSamples);
        for (int sample = 0; sample < kSamples; ++sample)
        {
            const float t = PREHIT_POST_SECONDS * (float)sample / (float)(kSamples - 1);
            RocketSim::BallState predicted;
            try { predicted = s_PreHitPredTracker->GetBallStateForTime(t); }
            catch (...) { break; }
            output.WorldPoints.push_back(FVector{
                (float)predicted.pos.x, (float)predicted.pos.y, (float)predicted.pos.z
            });
        }
        if (output.WorldPoints.size() >= 2)
        {
            s_PreHitPredictions.push_back(std::move(output));

                                                                            
                                                                              
                                                                            
                                                                                
            if (settings.iPreHitCarMode == 0)
            {
                for (size_t i = 1; i < candidates.size(); ++i)
                {
                    PreHitPredictionData marker{};
                    fillMetadata(marker, candidates[i]);
                    s_PreHitPredictions.push_back(std::move(marker));
                }
            }
        }
    }

    const std::vector<PreHitPredictionData>& GetPreHitPredictions()
    {
        return s_PreHitPredictions;
    }

                                                                             
    BallPredictionConfig& GetSettingsLegacy()
    {
        return GetSettings();
    }
    
    void UpdateColorFromPicker()
    {
        auto& settings = GetSettings();
                                                                           
        settings.fLineColorRGB[0] = settings.cLineColor.R;
        settings.fLineColorRGB[1] = settings.cLineColor.G;
        settings.fLineColorRGB[2] = settings.cLineColor.B;
        
                            
        int r = static_cast<int>(settings.cLineColor.R * 255.0f);
        int g = static_cast<int>(settings.cLineColor.G * 255.0f);
        int b = static_cast<int>(settings.cLineColor.B * 255.0f);
        sprintf_s(settings.szLineColorHex, "%02X%02X%02X", r, g, b);
    }
    
    void SetEnabled(bool enabled)
    {
        auto& settings = GetSettings();
        if (enabled && !settings.bEnabled)
        {
            s_Cache.bInitialized = false;
            s_Cache.WorldPoints.clear();
            s_Cache.CachedBall = nullptr;
                                                                      
            settings.bSafeConfig = true;
            settings.iMaxPoints = 40;
        }
        settings.bEnabled = enabled;
    }
    
    void ForceRefresh()
    {
        s_Cache.bInitialized = false;
        s_Cache.WorldPoints.clear();
        s_Cache.BouncePoints.clear();
        s_Cache.CachedBall = nullptr;
        s_Cache.LastBallSearch = std::chrono::steady_clock::now() - std::chrono::milliseconds(500);
        s_Cache.LastUpdate = std::chrono::steady_clock::now() - std::chrono::seconds(10);
        s_Cache.bGoalPredicted = false;
        s_PreHitPredictions.clear();
        s_LastPreHitUpdate = std::chrono::steady_clock::time_point{};
                                                                    
        s_LastInGameState = false;
    }
    
    bool IsEnabled()
    {
        return GetSettings().bEnabled;
    }

                                                                            
                                                                                   
                                                                                  
                                                                            
    namespace {
        std::string GetPresetsFilePath()
        {
            char exePath[MAX_PATH] = {};
            std::string dir;
            if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
                dir = (std::filesystem::path(exePath).parent_path() / "KingMod" / "resources").string();
            else
                dir = (std::filesystem::current_path() / "KingMod" / "resources").string();
            SHCreateDirectoryExA(NULL, dir.c_str(), NULL);
            return dir + "\\BallPredictionPresets.json";
        }

        nlohmann::json LoadPresetsFile()
        {
            nlohmann::json root;
            std::ifstream in(GetPresetsFilePath());
            if (in.good())
            {
                try { in >> root; }
                catch (...) { root = nlohmann::json::object(); }
            }
            if (!root.is_object()) root = nlohmann::json::object();
            if (!root.contains("presets") || !root["presets"].is_object())
                root["presets"] = nlohmann::json::object();
            if (!root.contains("favorite")) root["favorite"] = "";
            return root;
        }

        void SavePresetsFile(const nlohmann::json& root)
        {
            std::ofstream out(GetPresetsFilePath(), std::ios::trunc);
            if (out.good()) out << root.dump(2);
        }

        void ReadColor(const nlohmann::json& o, const char* key, FLinearColor& col)
        {
            if (o.contains(key) && o[key].is_array() && o[key].size() >= 4)
            {
                col.R = o[key][0].get<float>();
                col.G = o[key][1].get<float>();
                col.B = o[key][2].get<float>();
                col.A = o[key][3].get<float>();
            }
        }

        nlohmann::json ConfigToJson(const BallPredictionConfig& c)
        {
            nlohmann::json o;
            o["master_enabled"] = GameEventHookModule::BallPredictionEnabled;
            o["show_line"] = c.bShowLine;
            o["time"] = c.fPredictionTime;
            o["color_rgba"] = { c.cLineColor.R, c.cLineColor.G, c.cLineColor.B, c.cLineColor.A };
            o["thickness"] = c.fThickness;
            o["opacity"] = c.fOpacity;
            o["use_speed_color"] = c.bUseSpeedColor;
            o["draw_style"] = c.iDrawStyle;
            o["rainbow"] = c.bRainbow;
            o["rainbow_speed"] = c.fRainbowSpeed;
            o["tickrate"] = c.iTickrate;
            o["max_points"] = c.iMaxPoints;
            o["predict_goal"] = c.bPredictGoal;
            o["goal_color_rgba"] = { c.cGoalColor.R, c.cGoalColor.G, c.cGoalColor.B, c.cGoalColor.A };
            o["goal_crosshair"] = c.bGoalCrosshair;
            o["goal_crosshair_color_rgba"] = { c.cGoalCrosshairColor.R, c.cGoalCrosshairColor.G, c.cGoalCrosshairColor.B, c.cGoalCrosshairColor.A };
            o["show_landing"] = c.bShowLanding;
            o["landing_color_rgba"] = { c.cLandingColor.R, c.cLandingColor.G, c.cLandingColor.B, c.cLandingColor.A };
            o["show_bounces"] = c.bShowBounces;
            o["show_goal_impact"] = c.bShowGoalImpact;
            o["show_goal_timer"] = c.bShowGoalTimer;
            o["prehit_enabled"] = c.bPreHitEnabled;
            o["prehit_car_mode"] = c.iPreHitCarMode;
            o["prehit_selected_car_index"] = c.iPreHitSelectedCarIndex;
            o["prehit_max_car_distance"] = c.fPreHitMaxCarDistance;
            o["prehit_lookahead"] = c.fPreHitLookAhead;
            o["prehit_hitbox_padding"] = c.fPreHitHitboxPadding;
            return o;
        }

        void JsonToConfig(const nlohmann::json& o, BallPredictionConfig& c)
        {
            GameEventHookModule::BallPredictionEnabled = o.value("master_enabled", GameEventHookModule::BallPredictionEnabled);
            c.bShowLine = o.value("show_line", c.bShowLine);
            c.fPredictionTime = o.value("time", c.fPredictionTime);
            ReadColor(o, "color_rgba", c.cLineColor);
            c.fThickness = o.value("thickness", c.fThickness);
            c.fOpacity = o.value("opacity", c.fOpacity);
            c.bUseSpeedColor = o.value("use_speed_color", c.bUseSpeedColor);
            c.iDrawStyle = o.value("draw_style", c.iDrawStyle);
            c.bRainbow = o.value("rainbow", c.bRainbow);
            c.fRainbowSpeed = o.value("rainbow_speed", c.fRainbowSpeed);
            c.iTickrate = o.value("tickrate", c.iTickrate);
            c.iMaxPoints = o.value("max_points", c.iMaxPoints);
            c.bPredictGoal = o.value("predict_goal", c.bPredictGoal);
            ReadColor(o, "goal_color_rgba", c.cGoalColor);
            c.bGoalCrosshair = o.value("goal_crosshair", c.bGoalCrosshair);
            ReadColor(o, "goal_crosshair_color_rgba", c.cGoalCrosshairColor);
            c.bShowLanding = o.value("show_landing", c.bShowLanding);
            ReadColor(o, "landing_color_rgba", c.cLandingColor);
            c.bShowBounces = o.value("show_bounces", c.bShowBounces);
            c.bShowGoalImpact = o.value("show_goal_impact", c.bShowGoalImpact);
            c.bShowGoalTimer = o.value("show_goal_timer", c.bShowGoalTimer);
            c.bPreHitEnabled = o.value("prehit_enabled", c.bPreHitEnabled);
            c.iPreHitCarMode = std::clamp(o.value("prehit_car_mode", c.iPreHitCarMode), 0, 3);
            c.iPreHitSelectedCarIndex = std::clamp(o.value("prehit_selected_car_index", c.iPreHitSelectedCarIndex), 0, 23);
            c.fPreHitMaxCarDistance = std::clamp(o.value("prehit_max_car_distance", c.fPreHitMaxCarDistance), 250.0f, 5000.0f);
            c.fPreHitLookAhead = std::clamp(o.value("prehit_lookahead", c.fPreHitLookAhead), 0.15f, 2.0f);
            c.fPreHitHitboxPadding = std::clamp(o.value("prehit_hitbox_padding", c.fPreHitHitboxPadding), 0.0f, 80.0f);
        }
    }

    std::vector<std::string> ListPresets()
    {
        std::vector<std::string> names;
        nlohmann::json root = LoadPresetsFile();
        for (auto it = root["presets"].begin(); it != root["presets"].end(); ++it)
            names.push_back(it.key());
        std::sort(names.begin(), names.end());
        return names;
    }

    bool SavePreset(const std::string& name)
    {
        if (name.empty()) return false;
        nlohmann::json root = LoadPresetsFile();
        root["presets"][name] = ConfigToJson(GetSettings());
        SavePresetsFile(root);
        return true;
    }

    bool LoadPreset(const std::string& name)
    {
        nlohmann::json root = LoadPresetsFile();
        if (!root["presets"].contains(name)) return false;
        JsonToConfig(root["presets"][name], GetSettings());
        ForceRefresh();
        return true;
    }

    bool DeletePreset(const std::string& name)
    {
        nlohmann::json root = LoadPresetsFile();
        if (!root["presets"].contains(name)) return false;
        root["presets"].erase(name);
        if (root.value("favorite", std::string()) == name) root["favorite"] = "";
        SavePresetsFile(root);
        return true;
    }

    void SetFavorite(const std::string& name)
    {
        nlohmann::json root = LoadPresetsFile();
        root["favorite"] = name;
        SavePresetsFile(root);
    }

    std::string GetFavorite()
    {
        nlohmann::json root = LoadPresetsFile();
        return root.value("favorite", std::string());
    }

    void ApplyFavoriteOnStartup()
    {
        std::string fav = GetFavorite();
        if (!fav.empty())
            LoadPreset(fav);
    }
}
