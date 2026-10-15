#include "TAS.hpp"
#include "KingFeatures.hpp"

#include "../../Components/Includes.hpp"
#include "nlohmann/json.hpp"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace
{
                                                                               
                                                                                   
    constexpr int kTasFileVersion = 2;
    constexpr float kMinSpeed = 0.01f;
    constexpr float kMaxSpeed = 4.0f;
    constexpr float kMinFrameTime = 1.0f / 1000.0f;
    constexpr float kAnalogInterruptThreshold = 0.075f;
    constexpr float kSensitivityTolerance = 0.001f;
    constexpr float kHitboxTolerance = 0.5f;

    struct TASFrame
    {
        float DeltaTime = 1.0f / 120.0f;
        FVehicleInputs Input{};

                                                                              
                                                                             
                                                                              
                                                                
        FReplicatedRBState CarState{};
        FReplicatedRBState BallState{};
        bool HasState = false;
    };

    struct TASData
    {
        std::string Name;
        std::string MapName;

        FReplicatedRBState CarStart{};
        FReplicatedRBState BallStart{};
        bool HasBall = false;

        float StartBoostAmount = 0.0f;
        bool HasBoostAmount = false;

        float ExpectedSteeringSensitivity = 0.0f;
        float ExpectedAirSensitivity = 0.0f;
        float ExpectedDodgeThreshold = 0.0f;

        FVector ExpectedHitboxExtent{};
        FVector ExpectedHitboxOffset{};
        bool HasExpectedHitbox = false;

        float ReplaySpeed = 1.0f;
        float RecordSpeed = 1.0f;

        KingTAS::InterruptInputs Interrupts{};
        bool StartReplayOnReset = true;

        std::vector<TASFrame> Frames;
    };

    TASData g_tas;
    bool g_hasTas = false;

    KingTAS::State g_state = KingTAS::State::Idle;
    std::string g_status = "Idle";
    std::string g_saveDirectory = "KingMod\\TAS";

    bool g_hooksInstalled = false;
                                                                               
                                                                             
                                                                               
                                                                            
    bool g_allowListenServer = true;
    bool g_validateEnvironment = true;

    APlayerController_TA* g_lastController = nullptr;

    std::vector<TASFrame> g_pendingFrames;
    std::size_t g_branchFrame = 0;

    std::size_t g_replayFrame = 0;
    float g_replayFrameElapsed = 0.0f;

    float g_originalTimeDilation = 1.0f;
    bool g_haveOriginalTimeDilation = false;
    bool g_speedToggled = false;

    uint32_t g_previousInterruptBits = 0;

                                                                               
                                                                                
                                                                          
    bool g_trainingResetPending = false;
    int  g_trainingResetStableTicks = 0;

    enum InterruptBit : uint32_t
    {
        Interrupt_Throttle   = 1u << 0,
        Interrupt_Steer      = 1u << 1,
        Interrupt_AirRoll    = 1u << 2,
        Interrupt_Powerslide = 1u << 3,
        Interrupt_Jump       = 1u << 4,
        Interrupt_Boost      = 1u << 5
    };

    float ClampSpeed(float value)
    {
        if (!std::isfinite(value))
            return 1.0f;
        return (std::max)(kMinSpeed, (std::min)(kMaxSpeed, value));
    }

    bool NearlyEqual(float a, float b, float tolerance)
    {
        return std::fabs(a - b) <= tolerance;
    }

    bool NearlyEqualVector(const FVector& a, const FVector& b, float tolerance)
    {
        return NearlyEqual(a.X, b.X, tolerance) &&
               NearlyEqual(a.Y, b.Y, tolerance) &&
               NearlyEqual(a.Z, b.Z, tolerance);
    }

    bool IsControllerUsable(APlayerController_TA* pc)
    {
        if (!pc)
            return false;

                                                                            
                                                                             
                                                                              
        __try
        {
            if (!pc->IsA(APlayerController_TA::StaticClass()) || pc->bDeleteMe)
                return false;
            if (!pc->PlayerInput || !IsPointerReadable(pc->PlayerInput))
                return false;
            if (!pc->Car || !IsPointerReadable(pc->Car) || pc->Car->bDeleteMe)
                return false;
            if (!pc->WorldInfo || !IsPointerReadable(pc->WorldInfo))
                return false;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool IsSafeLocalSession(APlayerController_TA* pc)
    {
        if (!IsControllerUsable(pc))
            return false;

        const ENetMode mode = pc->WorldInfo->NetMode;

        if (mode == ENetMode::NM_Standalone)
            return true;

        if (mode == ENetMode::NM_ListenServer)
            return g_allowListenServer;

        return false;
    }

    APlayerController_TA* GetController()
    {
        if (IsControllerUsable(g_lastController))
            return g_lastController;

        return nullptr;
    }

    ABall_TA* GetBall(APlayerController_TA* pc)
    {
        if (!pc)
            return nullptr;

                                                                                
                                                                                
                                                                               
                                                                                
        __try
        {
            AGameEvent_Soccar_TA* soccar = pc->SoccarGameEvent;

            if (!soccar)
            {
                AGameEvent_TA* gameEvent = pc->GetGameEvent();
                if (gameEvent &&
                    gameEvent->IsA(AGameEvent_Soccar_TA::StaticClass()))
                {
                    soccar = static_cast<AGameEvent_Soccar_TA*>(gameEvent);
                }
            }

            if (!soccar || soccar->bDeleteMe)
                return nullptr;

            const int32_t count = soccar->GameBalls.size();
            if (count <= 0 || count > 16)
                return nullptr;

            for (int32_t i = 0; i < count; ++i)
            {
                ABall_TA* ball = soccar->GameBalls[i];
                if (ball && !ball->bDeleteMe &&
                    ball->IsA(ABall_TA::StaticClass()))
                    return ball;
            }

            return nullptr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return nullptr;
        }
    }

    std::string GetCurrentMapName(APlayerController_TA* pc)
    {
        if (!pc || !pc->WorldInfo || !IsPointerReadable(pc->WorldInfo))
            return std::string();

        try
        {
            return pc->WorldInfo->GetMapName(false).ToString();
        }
        catch (...)
        {
            return std::string();
        }
    }

    uint32_t GetRawInterruptBits(APlayerController_TA* pc)
    {
        if (!pc)
            return 0;

        uint32_t bits = 0;

                                                                          
                                                                            
                                                                          
                                 
        __try
        {
            UPlayerInput_TA* input = nullptr;
            if (pc->PlayerInput &&
                pc->PlayerInput->IsA(UPlayerInput_TA::StaticClass()))
            {
                input = static_cast<UPlayerInput_TA*>(pc->PlayerInput);
            }

            if (input)
            {
                const float triggerThrottle =
                    input->aRightAnalogTrigger - input->aLeftAnalogTrigger;

                const float throttle =
                    (std::fabs(triggerThrottle) > std::fabs(input->aForward))
                        ? triggerThrottle
                        : input->aForward;

                float steer = input->aTurn;
                const float splitSteer = input->aTurnRight - input->aTurnLeft;
                if (std::fabs(splitSteer) > std::fabs(steer))
                    steer = splitSteer;

                const float airRoll =
                    input->aPositiveRoll - input->aNegativeRoll;

                if (std::fabs(throttle) >= kAnalogInterruptThreshold)
                    bits |= Interrupt_Throttle;

                if (std::fabs(steer) >= kAnalogInterruptThreshold)
                    bits |= Interrupt_Steer;

                if (input->bRoll != 0 ||
                    std::fabs(airRoll) >= kAnalogInterruptThreshold)
                {
                    bits |= Interrupt_AirRoll;
                }
            }

            if (pc->bHandbrakePressed)
                bits |= Interrupt_Powerslide;
            if (pc->bJumpPressed)
                bits |= Interrupt_Jump;
            if (pc->bBoostPressed)
                bits |= Interrupt_Boost;

            return bits;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
    }

    uint32_t EnabledInterruptBits()
    {
        uint32_t bits = 0;

        if (g_tas.Interrupts.Throttle)   bits |= Interrupt_Throttle;
        if (g_tas.Interrupts.Steer)      bits |= Interrupt_Steer;
        if (g_tas.Interrupts.AirRoll)    bits |= Interrupt_AirRoll;
        if (g_tas.Interrupts.Powerslide) bits |= Interrupt_Powerslide;
        if (g_tas.Interrupts.Jump)       bits |= Interrupt_Jump;
        if (g_tas.Interrupts.Boost)      bits |= Interrupt_Boost;

        return bits;
    }

    bool ShouldInterruptReplay(APlayerController_TA* pc)
    {
        const uint32_t current = GetRawInterruptBits(pc);
        const uint32_t enabled = EnabledInterruptBits();

        const uint32_t newlyPressed =
            (current & ~g_previousInterruptBits) & enabled;

        g_previousInterruptBits = current;
        return newlyPressed != 0;
    }

    void SetTimeDilation(APlayerController_TA* pc, float value)
    {
        if (!pc)
            return;

                                                                                
                                                                               
                                                
        __try
        {
            if (!pc->WorldInfo)
                return;
            pc->WorldInfo->eventSetTimeDilation(ClampSpeed(value));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    void RememberTimeDilation(APlayerController_TA* pc)
    {
        if (!pc || !pc->WorldInfo || !IsPointerReadable(pc->WorldInfo) ||
            g_haveOriginalTimeDilation)
            return;

        try
        {
            float value = pc->WorldInfo->TimeDilation;
            if (!std::isfinite(value) || value <= 0.0f)
                value = 1.0f;

            g_originalTimeDilation = value;
            g_haveOriginalTimeDilation = true;
        }
        catch (...)
        {
            g_originalTimeDilation = 1.0f;
            g_haveOriginalTimeDilation = true;
        }
    }

    void RestoreTimeDilation(APlayerController_TA* pc)
    {
        if (!g_haveOriginalTimeDilation)
            return;

        SetTimeDilation(pc, g_originalTimeDilation);
        g_haveOriginalTimeDilation = false;
        g_speedToggled = false;
    }

    void DisableInputOverride(APlayerController_TA* pc)
    {
        if (!pc)
            return;

        __try
        {
            pc->bOverrideInput = 0;
            pc->OverrideInput = FVehicleInputs{};
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    void ApplyReplayInput(APlayerController_TA* pc, const FVehicleInputs& input)
    {
        if (!pc)
            return;

                                                                     
                                                                                
                                                                              
                                           
        __try
        {
            pc->OverrideInput = input;
            pc->bOverrideInput = 1;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    FReplicatedRBState MakeRestorableState(const FReplicatedRBState& input)
    {
        FReplicatedRBState result = input;
        result.bNewData = 1;
        result.bSleeping = 0;
        return result;
    }

    bool RestoreStartState(APlayerController_TA* pc)
    {
        if (!IsControllerUsable(pc))
            return false;

        try
        {
            FReplicatedRBState carState =
                MakeRestorableState(g_tas.CarStart);
            pc->Car->SetPhysicsState(carState);

            if (g_tas.HasBoostAmount && IsPointerReadable(pc->Car->BoostComponent))
                pc->Car->BoostComponent->SetBoostAmount(g_tas.StartBoostAmount);

            if (g_tas.HasBall)
            {
                ABall_TA* ball = GetBall(pc);
                if (!ball)
                {
                    g_status = "TAS expects a ball but no game ball is ready";
                    return false;
                }

                FReplicatedRBState ballState =
                    MakeRestorableState(g_tas.BallStart);
                ball->SetPhysicsState(ballState);
            }

            return true;
        }
        catch (...)
        {
            g_status = "Could not restore TAS car/ball state";
            return false;
        }
    }

    bool ValidateEnvironment(APlayerController_TA* pc)
    {
        if (!g_validateEnvironment)
            return true;

        if (!IsSafeLocalSession(pc))
        {
            g_status =
                "TAS is limited to standalone/freeplay unless listen-server use is enabled";
            return false;
        }

        const std::string map = GetCurrentMapName(pc);
        if (!g_tas.MapName.empty() &&
            !map.empty() &&
            map != g_tas.MapName)
        {
            g_status = "Map mismatch: TAS was created on " + g_tas.MapName;
            return false;
        }

        if (pc->PRI && IsPointerReadable(pc->PRI))
        {
            if (g_tas.ExpectedSteeringSensitivity > 0.0f &&
                !NearlyEqual(pc->PRI->SteeringSensitivity,
                             g_tas.ExpectedSteeringSensitivity,
                             kSensitivityTolerance))
            {
                g_status = "Steering sensitivity does not match this TAS";
                return false;
            }

            if (g_tas.ExpectedAirSensitivity > 0.0f &&
                !NearlyEqual(pc->PRI->AirControlSensitivity,
                             g_tas.ExpectedAirSensitivity,
                             kSensitivityTolerance))
            {
                g_status = "Air sensitivity does not match this TAS";
                return false;
            }

            if (g_tas.ExpectedDodgeThreshold > 0.0f &&
                !NearlyEqual(pc->PRI->DodgeInputThreshold,
                             g_tas.ExpectedDodgeThreshold,
                             kSensitivityTolerance))
            {
                g_status = "Dodge input threshold does not match this TAS";
                return false;
            }
        }

        if (g_tas.HasExpectedHitbox && pc->Car)
        {
            if (!NearlyEqualVector(pc->Car->LocalCollisionExtent,
                                   g_tas.ExpectedHitboxExtent,
                                   kHitboxTolerance) ||
                !NearlyEqualVector(pc->Car->LocalCollisionOffset,
                                   g_tas.ExpectedHitboxOffset,
                                   kHitboxTolerance))
            {
                g_status = "Current car hitbox does not match this TAS";
                return false;
            }
        }

        return true;
    }

    void BeginRecording(APlayerController_TA* pc, std::size_t branchFrame)
    {
        DisableInputOverride(pc);

        g_branchFrame = (std::min)(branchFrame, g_tas.Frames.size());
        g_pendingFrames.clear();

        g_state = KingTAS::State::Recording;
        g_replayFrame = g_branchFrame;
        g_replayFrameElapsed = 0.0f;

        g_speedToggled = false;
        SetTimeDilation(pc, g_tas.RecordSpeed);

        g_status =
            "Recording from frame " + std::to_string(g_branchFrame);
    }

    void RecordFrame(APlayerController_TA* pc, float deltaTime)
    {
        if (!pc)
            return;

        TASFrame frame{};
        frame.DeltaTime =
            (std::max)(kMinFrameTime,
                       std::isfinite(deltaTime) ? deltaTime
                                                : (1.0f / 120.0f));

        frame.Input = pc->VehicleInput;

                                                                             
                                                                               
                                                                               
                                                                       
        if (g_tas.HasBall)
        {
            try
            {
                if (pc->Car && !pc->Car->bDeleteMe)
                {
                    frame.CarState = pc->Car->GetCurrentRBState();
                    frame.HasState = true;

                    if (ABall_TA* ball = GetBall(pc))
                        frame.BallState = ball->GetCurrentRBState();
                }
            }
            catch (...)
            {
            }
        }

        g_pendingFrames.push_back(frame);
    }

                                                                               
                                                                                
                                                             
    void ApplyReplayState(APlayerController_TA* pc, const TASFrame& frame)
    {
        if (!pc || !frame.HasState || !g_tas.HasBall)
            return;

        try
        {
            if (pc->Car && !pc->Car->bDeleteMe)
            {
                FReplicatedRBState carState =
                    MakeRestorableState(frame.CarState);
                pc->Car->SetPhysicsState(carState);
            }

            if (ABall_TA* ball = GetBall(pc))
            {
                FReplicatedRBState ballState =
                    MakeRestorableState(frame.BallState);
                ball->SetPhysicsState(ballState);
            }
        }
        catch (...)
        {
        }
    }

    void ReplayTick(APlayerController_TA* pc, float deltaTime)
    {
        if (ShouldInterruptReplay(pc))
        {
            BeginRecording(pc, g_replayFrame);
            return;
        }

        if (g_replayFrame >= g_tas.Frames.size())
        {
            BeginRecording(pc, g_tas.Frames.size());
            return;
        }

        ApplyReplayInput(pc, g_tas.Frames[g_replayFrame].Input);
        ApplyReplayState(pc, g_tas.Frames[g_replayFrame]);

        float dt = std::isfinite(deltaTime) && deltaTime > 0.0f
            ? deltaTime
            : (1.0f / 120.0f);

        g_replayFrameElapsed += dt;

                                                                             
                                                                                
                                                
        while (g_replayFrame < g_tas.Frames.size())
        {
            const float frameDuration =
                (std::max)(kMinFrameTime,
                           g_tas.Frames[g_replayFrame].DeltaTime);

            if (g_replayFrameElapsed < frameDuration)
                break;

            g_replayFrameElapsed -= frameDuration;
            ++g_replayFrame;

            if (g_replayFrame >= g_tas.Frames.size())
            {
                BeginRecording(pc, g_tas.Frames.size());
                return;
            }

            ApplyReplayInput(pc, g_tas.Frames[g_replayFrame].Input);
            ApplyReplayState(pc, g_tas.Frames[g_replayFrame]);
        }
    }

    std::string SanitizeName(const std::string& input)
    {
        std::string result;
        result.reserve(input.size());

        for (char c : input)
        {
            const unsigned char uc = static_cast<unsigned char>(c);
            if (std::isalnum(uc) || c == '-' || c == '_' || c == ' ')
                result.push_back(c);
        }

        while (!result.empty() && result.front() == ' ')
            result.erase(result.begin());

        while (!result.empty() && result.back() == ' ')
            result.pop_back();

        if (result.empty())
            result = "Untitled TAS";

        return result;
    }

    std::string DefaultSavePath()
    {
        const fs::path directory(g_saveDirectory);
        const std::string fileName =
            SanitizeName(g_tas.Name) + ".json";
        return (directory / fileName).string();
    }

    json VectorToJson(const FVector& v)
    {
        return json{
            {"x", v.X},
            {"y", v.Y},
            {"z", v.Z}
        };
    }

    FVector VectorFromJson(const json& value)
    {
        FVector v{};
        v.X = value.value("x", 0.0f);
        v.Y = value.value("y", 0.0f);
        v.Z = value.value("z", 0.0f);
        return v;
    }

    json QuatToJson(const FQuat& q)
    {
        return json{
            {"x", q.X},
            {"y", q.Y},
            {"z", q.Z},
            {"w", q.W}
        };
    }

    FQuat QuatFromJson(const json& value)
    {
        FQuat q{};
        q.X = value.value("x", 0.0f);
        q.Y = value.value("y", 0.0f);
        q.Z = value.value("z", 0.0f);
        q.W = value.value("w", 1.0f);
        return q;
    }

    json RBStateToJson(const FReplicatedRBState& state)
    {
        return json{
            {"rotation", QuatToJson(state.Quaternion)},
            {"location", VectorToJson(state.Location)},
            {"linear_velocity", VectorToJson(state.LinearVelocity)},
            {"angular_velocity", VectorToJson(state.AngularVelocity)},
            {"time", state.Time}
        };
    }

    FReplicatedRBState RBStateFromJson(const json& value)
    {
        FReplicatedRBState state{};

        if (value.contains("rotation"))
            state.Quaternion = QuatFromJson(value["rotation"]);
        else
            state.Quaternion.W = 1.0f;

        if (value.contains("location"))
            state.Location = VectorFromJson(value["location"]);

        if (value.contains("linear_velocity"))
            state.LinearVelocity =
                VectorFromJson(value["linear_velocity"]);

        if (value.contains("angular_velocity"))
            state.AngularVelocity =
                VectorFromJson(value["angular_velocity"]);

        state.Time = value.value("time", 0.0f);
        state.bSleeping = 0;
        state.bNewData = 1;
        return state;
    }

    json VehicleInputToJson(const FVehicleInputs& input)
    {
        return json{
            {"throttle", input.Throttle},
            {"steer", input.Steer},
            {"pitch", input.Pitch},
            {"yaw", input.Yaw},
            {"roll", input.Roll},
            {"dodge_forward", input.DodgeForward},
            {"dodge_right", input.DodgeRight},
            {"handbrake", input.bHandbrake != 0},
            {"jump", input.bJump != 0},
            {"activate_boost", input.bActivateBoost != 0},
            {"holding_boost", input.bHoldingBoost != 0},
            {"jumped", input.bJumped != 0},
            {"grab", input.bGrab != 0},
            {"button_mash", input.bButtonMash != 0},
            {"air_roll", input.bAirRoll != 0}
        };
    }

    FVehicleInputs VehicleInputFromJson(const json& value)
    {
        FVehicleInputs input{};

        input.Throttle = value.value("throttle", 0.0f);
        input.Steer = value.value("steer", 0.0f);
        input.Pitch = value.value("pitch", 0.0f);
        input.Yaw = value.value("yaw", 0.0f);
        input.Roll = value.value("roll", 0.0f);
        input.DodgeForward = value.value("dodge_forward", 0.0f);
        input.DodgeRight = value.value("dodge_right", 0.0f);

        input.bHandbrake =
            value.value("handbrake", false) ? 1 : 0;
        input.bJump =
            value.value("jump", false) ? 1 : 0;
        input.bActivateBoost =
            value.value("activate_boost", false) ? 1 : 0;
        input.bHoldingBoost =
            value.value("holding_boost", false) ? 1 : 0;
        input.bJumped =
            value.value("jumped", false) ? 1 : 0;
        input.bGrab =
            value.value("grab", false) ? 1 : 0;
        input.bButtonMash =
            value.value("button_mash", false) ? 1 : 0;
        input.bAirRoll =
            value.value("air_roll", false) ? 1 : 0;

        return input;
    }

    json InterruptsToJson(const KingTAS::InterruptInputs& inputs)
    {
        return json{
            {"throttle", inputs.Throttle},
            {"steer", inputs.Steer},
            {"air_roll", inputs.AirRoll},
            {"powerslide", inputs.Powerslide},
            {"jump", inputs.Jump},
            {"boost", inputs.Boost}
        };
    }

    KingTAS::InterruptInputs InterruptsFromJson(const json& value)
    {
        KingTAS::InterruptInputs inputs{};
        inputs.Throttle = value.value("throttle", false);
        inputs.Steer = value.value("steer", false);
        inputs.AirRoll = value.value("air_roll", false);
        inputs.Powerslide = value.value("powerslide", false);
        inputs.Jump = value.value("jump", false);
        inputs.Boost = value.value("boost", true);
        return inputs;
    }

    json TASDataToJson()
    {
        json frames = json::array();
        for (const TASFrame& frame : g_tas.Frames)
        {
            json entry = {
                {"dt", frame.DeltaTime},
                {"input", VehicleInputToJson(frame.Input)}
            };

                                                                               
            if (frame.HasState)
            {
                entry["car"] = RBStateToJson(frame.CarState);
                if (g_tas.HasBall)
                    entry["ball"] = RBStateToJson(frame.BallState);
            }

            frames.push_back(entry);
        }

        return json{
            {"version", kTasFileVersion},
            {"name", g_tas.Name},
            {"map", g_tas.MapName},
            {"replay_speed", g_tas.ReplaySpeed},
            {"record_speed", g_tas.RecordSpeed},
            {"start_replay_on_reset", g_tas.StartReplayOnReset},
            {"interrupts", InterruptsToJson(g_tas.Interrupts)},
            {"expected", {
                {"steering_sensitivity",
                 g_tas.ExpectedSteeringSensitivity},
                {"air_sensitivity",
                 g_tas.ExpectedAirSensitivity},
                {"dodge_threshold",
                 g_tas.ExpectedDodgeThreshold},
                {"has_hitbox", g_tas.HasExpectedHitbox},
                {"hitbox_extent",
                 VectorToJson(g_tas.ExpectedHitboxExtent)},
                {"hitbox_offset",
                 VectorToJson(g_tas.ExpectedHitboxOffset)}
            }},
            {"start_state", {
                {"car", RBStateToJson(g_tas.CarStart)},
                {"has_ball", g_tas.HasBall},
                {"ball", RBStateToJson(g_tas.BallStart)},
                {"has_boost", g_tas.HasBoostAmount},
                {"boost_amount", g_tas.StartBoostAmount}
            }},
            {"frames", frames}
        };
    }

    bool TASDataFromJson(const json& root, TASData& out)
    {
        if (!root.is_object())
            return false;

        const int version = root.value("version", 0);
        if (version < 1 || version > kTasFileVersion)
            return false;

        TASData loaded{};
        loaded.Name = root.value("name", std::string("Untitled TAS"));
        loaded.MapName = root.value("map", std::string());
        loaded.ReplaySpeed =
            ClampSpeed(root.value("replay_speed", 1.0f));
        loaded.RecordSpeed =
            ClampSpeed(root.value("record_speed", 1.0f));
        loaded.StartReplayOnReset =
            root.value("start_replay_on_reset", true);

        if (root.contains("interrupts"))
            loaded.Interrupts =
                InterruptsFromJson(root["interrupts"]);

        if (root.contains("expected"))
        {
            const json& expected = root["expected"];

            loaded.ExpectedSteeringSensitivity =
                expected.value("steering_sensitivity", 0.0f);
            loaded.ExpectedAirSensitivity =
                expected.value("air_sensitivity", 0.0f);
            loaded.ExpectedDodgeThreshold =
                expected.value("dodge_threshold", 0.0f);

            loaded.HasExpectedHitbox =
                expected.value("has_hitbox", false);

            if (expected.contains("hitbox_extent"))
                loaded.ExpectedHitboxExtent =
                    VectorFromJson(expected["hitbox_extent"]);

            if (expected.contains("hitbox_offset"))
                loaded.ExpectedHitboxOffset =
                    VectorFromJson(expected["hitbox_offset"]);
        }

        if (!root.contains("start_state"))
            return false;

        const json& start = root["start_state"];

        if (!start.contains("car"))
            return false;

        loaded.CarStart = RBStateFromJson(start["car"]);
        loaded.HasBall = start.value("has_ball", false);

        if (loaded.HasBall && start.contains("ball"))
            loaded.BallStart = RBStateFromJson(start["ball"]);

        loaded.HasBoostAmount =
            start.value("has_boost", false);
        loaded.StartBoostAmount =
            start.value("boost_amount", 0.0f);

        if (root.contains("frames") &&
            root["frames"].is_array())
        {
            for (const json& item : root["frames"])
            {
                if (!item.is_object() ||
                    !item.contains("input"))
                {
                    continue;
                }

                TASFrame frame{};
                frame.DeltaTime =
                    (std::max)(kMinFrameTime,
                               item.value("dt", 1.0f / 120.0f));
                frame.Input =
                    VehicleInputFromJson(item["input"]);

                                                                            
                                                                               
                                                                   
                if (item.contains("car"))
                {
                    frame.CarState = RBStateFromJson(item["car"]);
                    frame.HasState = true;

                    if (item.contains("ball"))
                        frame.BallState = RBStateFromJson(item["ball"]);
                }

                loaded.Frames.push_back(frame);
            }
        }

        out = std::move(loaded);
        return true;
    }

    void CaptureExpectedEnvironment(APlayerController_TA* pc)
    {
        if (!pc)
            return;

        g_tas.MapName = GetCurrentMapName(pc);

        if (pc->PRI && IsPointerReadable(pc->PRI))
        {
            g_tas.ExpectedSteeringSensitivity =
                pc->PRI->SteeringSensitivity;
            g_tas.ExpectedAirSensitivity =
                pc->PRI->AirControlSensitivity;
            g_tas.ExpectedDodgeThreshold =
                pc->PRI->DodgeInputThreshold;
        }

        if (pc->Car && IsPointerReadable(pc->Car))
        {
            g_tas.ExpectedHitboxExtent =
                pc->Car->LocalCollisionExtent;
            g_tas.ExpectedHitboxOffset =
                pc->Car->LocalCollisionOffset;
            g_tas.HasExpectedHitbox = true;
        }
    }
}

void KingTAS::InstallHooks()
{
    if (g_hooksInstalled)
        return;

    g_hooksInstalled = true;

    Events.HookEventPost(
        "Function TAGame.PlayerController_TA.PlayerTick",
        [](const PostEvent& event)
        {
            UObject* caller = event.Caller();
            if (!caller ||
                !caller->IsA(APlayerController_TA::StaticClass()))
            {
                return;
            }

            auto* pc = static_cast<APlayerController_TA*>(caller);

                                                                                 
                                                                                  
                                               
            if (!IsControllerUsable(pc))
                return;

            const auto* params =
                event.GetParams<APlayerController_TA_execPlayerTick_Params>();

            const float dt =
                params ? params->DeltaTime : (1.0f / 120.0f);

            KingTAS::Tick(pc, dt);
        });

                                                                           
                                                                                 
                                                                                

    g_status = "TAS hooks installed";
}

bool KingTAS::NewTAS(const std::string& name)
{
    APlayerController_TA* pc = GetController();

    if (!IsSafeLocalSession(pc))
    {
        g_status =
            "Enter standalone Freeplay/local custom map before creating a TAS";
        return false;
    }

    if (g_state == State::Replaying ||
        g_state == State::Recording)
    {
        Stop();
    }

    g_tas = TASData{};
    g_tas.Name = SanitizeName(name);
    g_tas.ReplaySpeed = 1.0f;
    g_tas.RecordSpeed = 1.0f;
    g_tas.Interrupts.Boost = true;
    g_tas.StartReplayOnReset = true;

    try
    {
        g_tas.CarStart = pc->Car->GetCurrentRBState();

        if (IsPointerReadable(pc->Car->BoostComponent))
        {
            g_tas.StartBoostAmount =
                pc->Car->BoostComponent->CurrentBoostAmount;
            g_tas.HasBoostAmount = true;
        }

        if (ABall_TA* ball = GetBall(pc))
        {
            g_tas.BallStart = ball->GetCurrentRBState();
            g_tas.HasBall = true;
        }

        CaptureExpectedEnvironment(pc);
    }
    catch (...)
    {
        g_status = "Failed to capture TAS starting state";
        g_hasTas = false;
        return false;
    }

    g_pendingFrames.clear();
    g_branchFrame = 0;
    g_replayFrame = 0;
    g_replayFrameElapsed = 0.0f;

    g_hasTas = true;
    g_state = State::Stopped;
    g_status = "Created TAS: " + g_tas.Name;
    return true;
}

bool KingTAS::Start()
{
    APlayerController_TA* pc = GetController();

    if (!g_hasTas)
    {
        g_status = "Create or load a TAS first";
        return false;
    }

    if (!ValidateEnvironment(pc))
        return false;

    if (!RestoreStartState(pc))
        return false;

    RememberTimeDilation(pc);

    g_pendingFrames.clear();
    g_branchFrame = 0;
    g_replayFrame = 0;
    g_replayFrameElapsed = 0.0f;
    g_speedToggled = false;

    g_previousInterruptBits =
        GetRawInterruptBits(pc);

    if (g_tas.Frames.empty())
    {
        BeginRecording(pc, 0);
        g_status = "New TAS: recording";
        return true;
    }

    g_state = State::Replaying;
    SetTimeDilation(pc, g_tas.ReplaySpeed);

    ApplyReplayInput(pc, g_tas.Frames.front().Input);

    g_status =
        "Replaying TAS from start (" +
        std::to_string(g_tas.Frames.size()) +
        " frames)";
    return true;
}

void KingTAS::Stop()
{
    APlayerController_TA* pc = GetController();

    DisableInputOverride(pc);
    RestoreTimeDilation(pc);

    if (g_hasTas)
        g_state = State::Stopped;
    else
        g_state = State::Idle;

    if (!g_pendingFrames.empty())
    {
        g_status =
            "Stopped - " +
            std::to_string(g_pendingFrames.size()) +
            " recorded frames waiting for Update";
    }
    else
    {
        g_status = "Stopped";
    }
}

bool KingTAS::Update()
{
    if (!g_hasTas)
    {
        g_status = "No TAS is loaded";
        return false;
    }

    if (g_state == State::Replaying ||
        g_state == State::Recording)
    {
        g_status = "Stop before updating the TAS";
        return false;
    }

    if (g_pendingFrames.empty())
    {
        g_status = "There is no new recording to update";
        return false;
    }

    g_branchFrame =
        (std::min)(g_branchFrame, g_tas.Frames.size());

    g_tas.Frames.resize(g_branchFrame);
    g_tas.Frames.insert(
        g_tas.Frames.end(),
        g_pendingFrames.begin(),
        g_pendingFrames.end());

    const std::size_t added = g_pendingFrames.size();

    g_pendingFrames.clear();
    g_branchFrame = g_tas.Frames.size();

    g_status =
        "TAS updated: " +
        std::to_string(added) +
        " new frames, " +
        std::to_string(g_tas.Frames.size()) +
        " total";

    return true;
}

bool KingTAS::StopAndUpdate()
{
    Stop();
    return Update();
}

bool KingTAS::ChangeSpeed()
{
    APlayerController_TA* pc = GetController();

    if (!g_hasTas || !pc || !pc->WorldInfo)
    {
        g_status = "No active TAS session";
        return false;
    }

    if (g_state != State::Replaying &&
        g_state != State::Recording)
    {
        g_status = "Start replaying/recording first";
        return false;
    }

    g_speedToggled = !g_speedToggled;

    const float normalSpeed =
        (g_state == State::Replaying)
            ? g_tas.ReplaySpeed
            : g_tas.RecordSpeed;

    const float alternateSpeed =
        (g_state == State::Replaying)
            ? g_tas.RecordSpeed
            : g_tas.ReplaySpeed;

    SetTimeDilation(
        pc,
        g_speedToggled ? alternateSpeed : normalSpeed);

    g_status =
        std::string("TAS speed: ") +
        std::to_string(
            g_speedToggled ? alternateSpeed : normalSpeed);

    return true;
}

void KingTAS::Tick(
    APlayerController_TA* playerController,
    float deltaTime)
{
    if (!playerController ||
        !playerController->PlayerInput)
    {
        return;
    }

    g_lastController = playerController;

    if (g_trainingResetPending)
    {
        if (!g_hasTas || !g_tas.StartReplayOnReset)
        {
            g_trainingResetPending = false;
            g_trainingResetStableTicks = 0;
        }
        else if (!IsSafeLocalSession(playerController))
        {
            g_trainingResetStableTicks = 0;
        }
        else
        {
            const bool ballReady = !g_tas.HasBall || GetBall(playerController) != nullptr;
            if (IsControllerUsable(playerController) && ballReady)
            {
                ++g_trainingResetStableTicks;
                if (g_trainingResetStableTicks >= 6)
                {
                    g_trainingResetPending = false;
                    g_trainingResetStableTicks = 0;

                                                                                  
                                                                               
                                                                                 
                                                                              
                    DisableInputOverride(playerController);
                    RestoreTimeDilation(playerController);
                    g_state = State::Stopped;
                    g_lastController = playerController;
                    Main.Execute([]()
                    {
                        if (!g_hasTas || !g_tas.StartReplayOnReset)
                            return;

                        APlayerController_TA* stableController = GetController();
                        const bool ballReady = !g_tas.HasBall || GetBall(stableController) != nullptr;
                        if (!IsSafeLocalSession(stableController) || !ballReady)
                        {
                            g_status = "TAS reset replay postponed: training objects are not stable";
                            return;
                        }

                        KingTAS::Start();
                    });
                }
            }
            else
            {
                g_trainingResetStableTicks = 0;
            }
        }

                                                                              
                                                 
        if (g_trainingResetPending)
            return;
    }

    if (g_state != State::Replaying &&
        g_state != State::Recording)
    {
        return;
    }

    if (!IsSafeLocalSession(playerController))
    {
        g_status = "TAS stopped because session is no longer local";
        Stop();
        return;
    }

    if (!playerController->Car ||
        playerController->Car->bDeleteMe)
    {
        g_status = "TAS stopped because local car is unavailable";
        Stop();
        return;
    }

    if (g_state == State::Replaying)
    {
        ReplayTick(playerController, deltaTime);
        return;
    }

    if (g_state == State::Recording)
    {
        DisableInputOverride(playerController);
        RecordFrame(playerController, deltaTime);
    }
}

void KingTAS::PrepareForTrainingReset()
{
                                                                                
                                                                                 
                                                                                
                                                           
    const bool tasWasDriving =
        g_state == State::Replaying ||
        g_state == State::Recording ||
        g_haveOriginalTimeDilation;

    if (tasWasDriving)
    {
        APlayerController_TA* pc = g_lastController;
        if (IsControllerUsable(pc))
        {
            DisableInputOverride(pc);
            RestoreTimeDilation(pc);
        }
        else
        {
                                                                                 
            g_haveOriginalTimeDilation = false;
            g_speedToggled = false;
        }
    }

    g_state = g_hasTas ? State::Stopped : State::Idle;
    g_lastController = nullptr;
    g_trainingResetPending = false;
    g_trainingResetStableTicks = 0;
}

void KingTAS::NotifyTrainingReset()
{
    if (!g_hasTas || !g_tas.StartReplayOnReset)
        return;

    g_lastController = nullptr;
    g_trainingResetPending = true;
    g_trainingResetStableTicks = 0;
}

void KingTAS::OnTrainingReset(
    APlayerController_TA* playerController)
{
                                                                               
                                                                              
    if (playerController)
        g_lastController = playerController;

    NotifyTrainingReset();
}

bool KingTAS::Save(const std::string& path)
{
    if (!g_hasTas)
    {
        g_status = "No TAS is loaded";
        return false;
    }

    if (g_state == State::Replaying ||
        g_state == State::Recording)
    {
        g_status = "Stop before saving the TAS";
        return false;
    }

    if (!g_pendingFrames.empty())
    {
        g_status = "Press Update before saving the new recording";
        return false;
    }

    const std::string target =
        path.empty() ? DefaultSavePath() : path;

    try
    {
        fs::path targetPath(target);

        if (targetPath.has_parent_path())
            fs::create_directories(targetPath.parent_path());

        std::ofstream output(targetPath, std::ios::trunc);
        if (!output.is_open())
        {
            g_status = "Could not open TAS file for writing";
            return false;
        }

        output << std::setw(2) << TASDataToJson();
        output.close();

        g_status = "Saved TAS: " + targetPath.string();
        return true;
    }
    catch (const std::exception& e)
    {
        g_status = std::string("Save failed: ") + e.what();
        return false;
    }
    catch (...)
    {
        g_status = "Save failed";
        return false;
    }
}

bool KingTAS::Load(const std::string& path)
{
    if (path.empty())
    {
        g_status = "TAS path is empty";
        return false;
    }

    if (g_state == State::Replaying ||
        g_state == State::Recording)
    {
        Stop();
    }

    try
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            g_status = "Could not open TAS file";
            return false;
        }

        json root;
        input >> root;

        TASData loaded{};
        if (!TASDataFromJson(root, loaded))
        {
            g_status = "Invalid or unsupported TAS file";
            return false;
        }

        g_tas = std::move(loaded);
        g_hasTas = true;
        g_pendingFrames.clear();
        g_branchFrame = g_tas.Frames.size();
        g_replayFrame = 0;
        g_replayFrameElapsed = 0.0f;
        g_state = State::Stopped;

        g_status =
            "Loaded TAS: " + g_tas.Name +
            " (" + std::to_string(g_tas.Frames.size()) +
            " frames)";

        return true;
    }
    catch (const std::exception& e)
    {
        g_status = std::string("Load failed: ") + e.what();
        return false;
    }
    catch (...)
    {
        g_status = "Load failed";
        return false;
    }
}

bool KingTAS::DeleteFile(const std::string& path)
{
    if (path.empty())
        return false;

    try
    {
        if (!fs::exists(path))
            return false;

        const bool removed = fs::remove(path);
        g_status = removed
            ? "Deleted TAS file"
            : "Could not delete TAS file";
        return removed;
    }
    catch (...)
    {
        g_status = "Could not delete TAS file";
        return false;
    }
}

std::vector<std::string> KingTAS::GetSavedFiles()
{
    std::vector<std::string> result;

    try
    {
        const fs::path directory(g_saveDirectory);
        fs::create_directories(directory);

        for (const fs::directory_entry& entry :
             fs::directory_iterator(directory))
        {
            if (!entry.is_regular_file())
                continue;

            std::string extension =
                entry.path().extension().string();

            std::transform(
                extension.begin(),
                extension.end(),
                extension.begin(),
                [](unsigned char c)
                {
                    return static_cast<char>(std::tolower(c));
                });

            if (extension == ".json")
                result.push_back(entry.path().string());
        }

        std::sort(result.begin(), result.end());
    }
    catch (...)
    {
    }

    return result;
}

void KingTAS::SetSaveDirectory(const std::string& path)
{
    if (!path.empty())
        g_saveDirectory = path;
}

const std::string& KingTAS::GetSaveDirectory()
{
    return g_saveDirectory;
}

void KingTAS::SetReplaySpeed(float speed)
{
    g_tas.ReplaySpeed = ClampSpeed(speed);

    if (g_state == State::Replaying && !g_speedToggled)
        SetTimeDilation(GetController(), g_tas.ReplaySpeed);
}

void KingTAS::SetRecordSpeed(float speed)
{
    g_tas.RecordSpeed = ClampSpeed(speed);

    if (g_state == State::Recording && !g_speedToggled)
        SetTimeDilation(GetController(), g_tas.RecordSpeed);
}

float KingTAS::GetReplaySpeed()
{
    return g_tas.ReplaySpeed;
}

float KingTAS::GetRecordSpeed()
{
    return g_tas.RecordSpeed;
}

void KingTAS::SetInterruptInputs(
    const InterruptInputs& inputs)
{
    g_tas.Interrupts = inputs;
}

KingTAS::InterruptInputs KingTAS::GetInterruptInputs()
{
    return g_tas.Interrupts;
}

void KingTAS::SetStartReplayOnReset(bool enabled)
{
    g_tas.StartReplayOnReset = enabled;
}

bool KingTAS::GetStartReplayOnReset()
{
    return g_tas.StartReplayOnReset;
}

void KingTAS::SetAllowListenServer(bool enabled)
{
    g_allowListenServer = enabled;
}

bool KingTAS::GetAllowListenServer()
{
    return g_allowListenServer;
}

void KingTAS::SetEnvironmentValidation(bool enabled)
{
    g_validateEnvironment = enabled;
}

bool KingTAS::GetEnvironmentValidation()
{
    return g_validateEnvironment;
}

KingTAS::State KingTAS::GetState()
{
    return g_state;
}

const char* KingTAS::GetStateName()
{
    switch (g_state)
    {
    case State::Idle:
        return "Idle";
    case State::Replaying:
        return "Replaying";
    case State::Recording:
        return "Recording";
    case State::Stopped:
        return "Stopped";
    default:
        return "Unknown";
    }
}

bool KingTAS::HasLoadedTAS()
{
    return g_hasTas;
}

bool KingTAS::HasPendingRecording()
{
    return !g_pendingFrames.empty();
}

KingTAS::TASInfo KingTAS::GetInfo()
{
    TASInfo info{};

    if (!g_hasTas)
        return info;

    info.Name = g_tas.Name;
    info.MapName = g_tas.MapName;
    info.ReplaySpeed = g_tas.ReplaySpeed;
    info.RecordSpeed = g_tas.RecordSpeed;

    info.ExpectedSteeringSensitivity =
        g_tas.ExpectedSteeringSensitivity;
    info.ExpectedAirSensitivity =
        g_tas.ExpectedAirSensitivity;
    info.ExpectedDodgeThreshold =
        g_tas.ExpectedDodgeThreshold;

    info.ExpectedHitboxExtent =
        g_tas.ExpectedHitboxExtent;
    info.ExpectedHitboxOffset =
        g_tas.ExpectedHitboxOffset;
    info.HasExpectedHitbox =
        g_tas.HasExpectedHitbox;

    info.SavedFrameCount = g_tas.Frames.size();
    info.PendingFrameCount = g_pendingFrames.size();

    return info;
}

const std::string& KingTAS::GetStatus()
{
    return g_status;
}

bool KingTAS::ExecuteBind(const std::string& command)
{
    if (command == "tas_start")
        return Start();

    if (command == "tas_stop")
    {
        Stop();
        return true;
    }

    if (command == "tas_update")
        return Update();

    if (command == "tas_stopandupdate")
        return StopAndUpdate();

    if (command == "tas_changespeed")
        return ChangeSpeed();

    return false;
}
