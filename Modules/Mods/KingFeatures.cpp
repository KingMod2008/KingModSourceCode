#include "KingFeatures.hpp"

#include "GameEventHook.hpp"
#include "HostSync.hpp"
#include "MatchmakingShield.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Main.hpp"
#include "../../Components/Components/Notify.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <random>
#include <sstream>
#include <nlohmann/json.hpp>

namespace KingFeatures
{
    Settings Config{};
    SessionStats Stats{};

    namespace
    {
        namespace fs = std::filesystem;
        using json = nlohmann::json;

        Checkpoint g_checkpoint{};
        bool g_photoMode = false;
        bool g_photoHudToggled = false;
        bool g_prevGrounded = true;
        ULONGLONG g_sessionStart = 0;
        ULONGLONG g_lastTick = 0;
        int g_lastTouchArraySize = 0;
        int g_lastDodgeCount = 0;
        bool g_prevRoundActive = false;
        bool g_kickoffArmed = false;
        bool g_kickoffReached220 = false;
        ULONGLONG g_kickoffStartTick = 0;
        std::deque<float> g_shotHistory;
        std::deque<DebugEntry> g_debug;
        std::mutex g_debugMutex;
        std::vector<PlayerSnapshot> g_playerSnapshots;
        std::mutex g_playerSnapshotMutex;
        std::vector<CameraKeyframe> g_cameraKeys;
        std::mutex g_cameraMutex;
        bool g_cameraPathPlaying = false;
        ULONGLONG g_cameraPathStart = 0;
        float g_cameraPathDuration = 10.0f;
        constexpr size_t kMaxDebugEntries = 160;
        constexpr size_t kMaxShotHistory = 12;

        fs::path ConfigPath()
        {
            char exePath[MAX_PATH] = {};
            fs::path base = GetModuleFileNameA(nullptr, exePath, MAX_PATH)
                ? fs::path(exePath).parent_path()
                : fs::current_path();
            fs::path dir = base / "KingMod" / "resources";
            std::error_code ec;
            fs::create_directories(dir, ec);
            return dir / "v32_features.json";
        }

        APlayerController_TA* GetLocalPC()
        {
            UEngine* engine = UEngine::GetEngine();
            if (!engine || !engine->IsA<UGameEngine>())
                return nullptr;
            auto* gameEngine = static_cast<UGameEngine*>(engine);
            if (gameEngine->GamePlayers.empty() || !gameEngine->GamePlayers[0])
                return nullptr;
            APlayerController* actor = gameEngine->GamePlayers[0]->Actor;
            if (!actor || !actor->IsA<APlayerController_TA>())
                return nullptr;
            return static_cast<APlayerController_TA*>(actor);
        }

        APRI_TA* GetLocalPRI()
        {
            APlayerController_TA* pc = GetLocalPC();
            if (!pc || !pc->PlayerReplicationInfo || !pc->PlayerReplicationInfo->IsA<APRI_TA>())
                return nullptr;
            return static_cast<APRI_TA*>(pc->PlayerReplicationInfo);
        }

        ACar_TA* GetLocalCar()
        {
            APRI_TA* pri = GetLocalPRI();
            return pri ? pri->Car : nullptr;
        }

        AGameEvent_Soccar_TA* GetSoccar()
        {
            AGameEvent_Soccar_TA* game = GameEventHookModule::CurrentGameEvent;
            return game && !game->bDeleteMe ? game : nullptr;
        }

        ABall_TA* GetPrimaryBall()
        {
            AGameEvent_Soccar_TA* game = GetSoccar();
            if (!game || game->GameBalls.empty())
                return nullptr;
            for (int i = 0; i < game->GameBalls.size(); ++i)
            {
                ABall_TA* ball = game->GameBalls[i];
                if (ball && !ball->bDeleteMe)
                    return ball;
            }
            return nullptr;
        }

        float SpeedUUToKph(const FVector& v)
        {
            const float uuPerSecond = std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
                                                                                    
            return uuPerSecond * 0.036f;
        }

        bool IsGrounded(ACar_TA* car)
        {
            if (!car || car->bDeleteMe)
                return false;
            try { return car->AnyWheelTouchingGround(); }
            catch (...) { return false; }
        }

        float GetAddedCarBounceScale()
        {
                                                                           
                                                                               
                                                                           
            const float multiplier = Config.BallPinchStrengthEnabled
                ? (std::max)(0.25f, (std::min)(Config.BallPinchStrength, 5.0f))
                : 1.0f;
            return multiplier - 1.0f;
        }

        bool ApplyPinchToGameBalls(AGameEvent_Soccar_TA* game, bool force)
        {
            if (!game || game->bDeleteMe) return false;
            if (!Events.CanUseLocalServerFeatures() || HostSync::IsJoinGuardActive()) return false;

            const float addedScale = GetAddedCarBounceScale();
            bool any = false;
            try
            {
                const int count = (std::min)(game->GameBalls.size(), 8);
                for (int i = 0; i < count; ++i)
                {
                    ABall_TA* ball = game->GameBalls[i];
                    if (!ball || ball->bDeleteMe) continue;

                                                                            
                                                                               
                                                                           
                    float current = 0.0f;
                    try { current = ball->ReplicatedAddedCarBounceScale; }
                    catch (...) { continue; }
                    if (!force && std::isfinite(current) && std::fabs(current - addedScale) <= 0.005f)
                    {
                        any = true;
                        continue;
                    }

                    ball->SetCarBounceScale(addedScale);
                    ball->bForceNetUpdate = true;
                    any = true;
                }
            }
            catch (...) { return false; }
            return any;
        }

        void SaveConfig()
        {
            try
            {
                json j;
                j["speedometer"] = Config.Speedometer;
                j["ball_telemetry"] = Config.BallTelemetry;
                j["boost_telemetry"] = Config.BoostTelemetry;
                j["shot_history"] = Config.ShotHistory;
                j["cinematic_bars"] = Config.CinematicBars;
                j["session_panel"] = Config.SessionPanel;
                j["debug_panel"] = Config.DebugPanel;
                j["bar_size"] = Config.CinematicBarSize;
                j["auto_checkpoint"] = Config.AutoCheckpoint;
                j["unlimited_boost"] = Config.UnlimitedBoost;
                j["unlimited_dodge"] = Config.UnlimitedDodge;
                j["slow_motion"] = Config.SlowMotion;
                j["slow_motion_scale"] = Config.SlowMotionScale;
                j["launch_speed"] = Config.TrainingBallLaunchSpeed;
                j["launch_height"] = Config.TrainingBallLaunchHeight;
                j["host_game_speed"] = Config.HostGameSpeed;
                j["ball_scale"] = Config.BallScale;
                j["ball_gravity"] = Config.BallGravityScale;
                j["ball_max_speed"] = Config.BallMaxSpeedScale;
                j["ball_bounce"] = Config.BallBounceScale;
                j["ball_pinch_enabled"] = Config.BallPinchStrengthEnabled;
                j["ball_pinch_strength"] = Config.BallPinchStrength;
                j["host_car_scale"] = Config.HostCarScale;
                j["command_key"] = Config.CommandPaletteKey;
                j["command_ctrl"] = Config.CommandPaletteCtrl;
                std::ofstream out(ConfigPath(), std::ios::trunc);
                if (out.is_open()) out << j.dump(2);
            }
            catch (...) {}
        }

        void LoadConfig()
        {
            try
            {
                std::ifstream in(ConfigPath());
                if (!in.is_open()) return;
                json j; in >> j;
                Config.Speedometer = j.value("speedometer", Config.Speedometer);
                Config.BallTelemetry = j.value("ball_telemetry", Config.BallTelemetry);
                Config.BoostTelemetry = j.value("boost_telemetry", Config.BoostTelemetry);
                Config.ShotHistory = j.value("shot_history", Config.ShotHistory);
                Config.CinematicBars = j.value("cinematic_bars", Config.CinematicBars);
                Config.SessionPanel = j.value("session_panel", Config.SessionPanel);
                Config.DebugPanel = j.value("debug_panel", Config.DebugPanel);
                Config.CinematicBarSize = j.value("bar_size", Config.CinematicBarSize);
                Config.AutoCheckpoint = j.value("auto_checkpoint", Config.AutoCheckpoint);
                Config.UnlimitedBoost = j.value("unlimited_boost", Config.UnlimitedBoost);
                Config.UnlimitedDodge = j.value("unlimited_dodge", Config.UnlimitedDodge);
                Config.SlowMotion = j.value("slow_motion", Config.SlowMotion);
                Config.SlowMotionScale = j.value("slow_motion_scale", Config.SlowMotionScale);
                Config.TrainingBallLaunchSpeed = j.value("launch_speed", Config.TrainingBallLaunchSpeed);
                Config.TrainingBallLaunchHeight = j.value("launch_height", Config.TrainingBallLaunchHeight);
                Config.HostGameSpeed = j.value("host_game_speed", Config.HostGameSpeed);
                Config.BallScale = j.value("ball_scale", Config.BallScale);
                Config.BallGravityScale = j.value("ball_gravity", Config.BallGravityScale);
                Config.BallMaxSpeedScale = j.value("ball_max_speed", Config.BallMaxSpeedScale);
                Config.BallBounceScale = j.value("ball_bounce", Config.BallBounceScale);
                Config.BallPinchStrengthEnabled = j.value("ball_pinch_enabled", Config.BallPinchStrengthEnabled);
                Config.BallPinchStrength = (std::max)(0.25f, (std::min)(j.value("ball_pinch_strength", Config.BallPinchStrength), 5.0f));
                Config.HostCarScale = j.value("host_car_scale", Config.HostCarScale);
                Config.CommandPaletteKey = j.value("command_key", Config.CommandPaletteKey);
                Config.CommandPaletteCtrl = j.value("command_ctrl", Config.CommandPaletteCtrl);
            }
            catch (...) {}
        }

        APRI_TA* ResolvePRIByName(const std::string& playerName)
        {
            AGameEvent_Soccar_TA* game = GetSoccar();
            if (!game || playerName.empty()) return nullptr;
            try
            {
                const int count = (std::min)(game->PRIs.size(), 64);
                for (int i = 0; i < count; ++i)
                {
                    APRI_TA* pri = game->PRIs[i];
                    if (!pri || pri->bDeleteMe) continue;
                    if (pri->PlayerName.ToString() == playerName) return pri;
                }
            }
            catch (...) {}
            return nullptr;
        }

        AController* ControllerForPRI(APRI_TA* pri)
        {
            if (!pri || pri->bDeleteMe || !pri->Owner)
                return nullptr;
            if (!pri->Owner->IsA<AController>())
                return nullptr;
            return static_cast<AController*>(pri->Owner);
        }

        void DrawShadowText(ImDrawList* draw, const ImVec2& p, ImU32 color, const char* text)
        {
            draw->AddText(p + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 210), text);
            draw->AddText(p, color, text);
        }
    }

    void Initialize()
    {
        LoadConfig();
        ResetSession();
        Log("KingMod Features initialized");
    }

    void Shutdown()
    {
        if (g_photoMode)
            SetPhotoMode(false);
        SaveConfig();
        Log("KingMod Features shutdown");
    }

    void SaveSettings()
    {
        SaveConfig();
    }

    void ResetSession()
    {
        Stats = SessionStats{};
        g_sessionStart = GetTickCount64();
        g_lastTick = g_sessionStart;
        g_lastTouchArraySize = 0;
        g_lastDodgeCount = 0;
        g_prevGrounded = true;
        g_prevRoundActive = false;
        g_kickoffArmed = false;
        g_kickoffReached220 = false;
        g_kickoffStartTick = 0;
        g_shotHistory.clear();
    }

    bool IsHostSandboxAvailable()
    {
        AGameEvent_Soccar_TA* game = GetSoccar();
        if (!game) return false;
        return Events.CanUseLocalServerFeatures() && !HostSync::IsJoinGuardActive() &&
            (game->IsPlayingLan() || game->IsPlayingPrivate());
    }

    void Tick(AGameEvent_Soccar_TA* gameEvent, APlayerController_TA* localPC)
    {
        const auto perfStart = std::chrono::high_resolution_clock::now();
        if (!gameEvent || gameEvent->bDeleteMe || !localPC || localPC->bDeleteMe)
            return;

        const ULONGLONG now = GetTickCount64();
        if (g_sessionStart == 0) g_sessionStart = now;
        float dt = g_lastTick ? static_cast<float>(now - g_lastTick) / 1000.0f : 0.0f;
        dt = (std::max)(0.0f, (std::min)(dt, 0.25f));
        g_lastTick = now;
        Stats.SessionSeconds = static_cast<float>(now - g_sessionStart) / 1000.0f;

        if (gameEvent->bRoundActive && !g_prevRoundActive)
        {
            g_kickoffStartTick = now;
            g_kickoffArmed = true;
            g_kickoffReached220 = false;
        }
        g_prevRoundActive = gameEvent->bRoundActive;

        APRI_TA* pri = localPC->PRI;
        ACar_TA* car = pri ? pri->Car : nullptr;
        ABall_TA* ball = nullptr;
        if (!gameEvent->GameBalls.empty())
        {
            for (int i = 0; i < gameEvent->GameBalls.size(); ++i)
            {
                if (gameEvent->GameBalls[i] && !gameEvent->GameBalls[i]->bDeleteMe)
                {
                    ball = gameEvent->GameBalls[i];
                    break;
                }
            }
        }

                                                                          
                                                                          
                                                                             
                                                                      
        ApplyPinchToGameBalls(gameEvent, false);

        if (car && !car->bDeleteMe)
        {
            const FReplicatedRBState carState = car->GetCurrentRBState();
            Stats.CurrentCarSpeedKph = SpeedUUToKph(carState.LinearVelocity);
            Stats.MaxCarSpeedKph = (std::max)(Stats.MaxCarSpeedKph, Stats.CurrentCarSpeedKph);
            if (g_kickoffArmed && !g_kickoffReached220 && g_kickoffStartTick != 0 && Stats.CurrentCarSpeedKph >= 220.0f)
            {
                Stats.LastKickoffTimeTo220Ms = static_cast<float>(now - g_kickoffStartTick);
                g_kickoffReached220 = true;
            }

            const bool grounded = IsGrounded(car);
            if (!grounded) Stats.AirTimeSeconds += dt;
            g_prevGrounded = grounded;

            if (IsPointerReadable(car->BoostComponent) && !car->BoostComponent->bDeleteMe)
            {
                Stats.BoostPercent = car->BoostComponent->GetPercentBoostFull() * 100.0f;
                if (Config.UnlimitedBoost && (gameEvent->IsPlayingLan() || gameEvent->IsPlayingPrivate() || gameEvent->IsPlayingTraining()))
                    car->BoostComponent->SetUnlimitedBoost(true);
            }

            if (Config.UnlimitedDodge && (gameEvent->IsPlayingLan() || gameEvent->IsPlayingPrivate() || gameEvent->IsPlayingTraining()))
                car->SetUnlimitedTimeForDodgeEnabled(true);

            if (IsPointerReadable(car->DodgeComponent) && !car->DodgeComponent->bDeleteMe)
            {
                const int dodges = car->DodgeComponent->DodgesCount;
                if (dodges >= g_lastDodgeCount)
                    Stats.DodgeCount += dodges - g_lastDodgeCount;
                g_lastDodgeCount = dodges;
            }
        }

        {
            std::vector<PlayerSnapshot> snapshots;
            try
            {
                const int count = (std::min)(gameEvent->PRIs.size(), 32);
                snapshots.reserve(count);
                for (int i = 0; i < count; ++i)
                {
                    APRI_TA* p = gameEvent->PRIs[i];
                    if (!p || p->bDeleteMe) continue;
                    PlayerSnapshot snap;
                    snap.Name = p->PlayerName.ToString();
                    snap.TeamIndex = p->Team ? p->Team->TeamIndex : -1;
                    snap.Spectator = p->IsSpectator();
                    snap.Bot = p->bBot;
                    snapshots.push_back(std::move(snap));
                }
            }
            catch (...) {}
            std::lock_guard<std::mutex> lock(g_playerSnapshotMutex);
            g_playerSnapshots.swap(snapshots);
        }

        if (ball && !ball->bDeleteMe)
        {
            const FReplicatedRBState ballState = ball->GetCurrentRBState();
            const float previousMax = Stats.MaxBallSpeedKph;
            Stats.CurrentBallSpeedKph = SpeedUUToKph(ballState.LinearVelocity);
            Stats.MaxBallSpeedKph = (std::max)(Stats.MaxBallSpeedKph, Stats.CurrentBallSpeedKph);

            const int touches = ball->Touches.size();
            if (touches > g_lastTouchArraySize)
            {
                Stats.TouchCount += touches - g_lastTouchArraySize;
                if (g_kickoffArmed && g_kickoffStartTick != 0)
                {
                    Stats.LastKickoffTouchMs = static_cast<float>(now - g_kickoffStartTick);
                    Stats.LastKickoffTouchSpeedKph = Stats.CurrentCarSpeedKph;
                    if (Stats.BestKickoffTouchMs <= 0.0f || Stats.LastKickoffTouchMs < Stats.BestKickoffTouchMs)
                        Stats.BestKickoffTouchMs = Stats.LastKickoffTouchMs;
                    g_kickoffArmed = false;
                }
                if (Config.ShotHistory && Stats.CurrentBallSpeedKph > 15.0f)
                {
                    g_shotHistory.push_front(Stats.CurrentBallSpeedKph);
                    while (g_shotHistory.size() > kMaxShotHistory) g_shotHistory.pop_back();
                }
            }
            g_lastTouchArraySize = touches;

            if (Config.AutoCheckpoint && !g_checkpoint.Valid && car)
                SaveCheckpoint();

            (void)previousMax;
        }

        if (Config.SlowMotion && !g_photoMode)
            SetWorldTimeScale(Config.SlowMotionScale);

        if (g_cameraPathPlaying && localPC->PlayerCamera)
        {
            std::vector<CameraKeyframe> keys;
            {
                std::lock_guard<std::mutex> lock(g_cameraMutex);
                keys = g_cameraKeys;
            }
            if (keys.size() < 2)
            {
                g_cameraPathPlaying = false;
            }
            else
            {
                const float elapsed = static_cast<float>(now - g_cameraPathStart) / 1000.0f;
                const float duration = (std::max)(0.25f, g_cameraPathDuration);
                float t = elapsed / duration;
                if (t >= 1.0f)
                {
                    t = 1.0f;
                    g_cameraPathPlaying = false;
                }
                const float scaled = t * static_cast<float>(keys.size() - 1);
                const int index = (std::min)(static_cast<int>(keys.size()) - 2, (std::max)(0, static_cast<int>(scaled)));
                const float localT = scaled - static_cast<float>(index);
                const CameraKeyframe& a = keys[index];
                const CameraKeyframe& b = keys[index + 1];
                auto lerp = [localT](float x, float y) { return x + (y - x) * localT; };
                FVector loc{ lerp(a.Location.X,b.Location.X), lerp(a.Location.Y,b.Location.Y), lerp(a.Location.Z,b.Location.Z) };
                FRotator rot{};
                rot.Pitch = static_cast<int32_t>(lerp(static_cast<float>(a.Rotation.Pitch), static_cast<float>(b.Rotation.Pitch)));
                rot.Yaw   = static_cast<int32_t>(lerp(static_cast<float>(a.Rotation.Yaw),   static_cast<float>(b.Rotation.Yaw)));
                rot.Roll  = static_cast<int32_t>(lerp(static_cast<float>(a.Rotation.Roll),  static_cast<float>(b.Rotation.Roll)));
                localPC->PlayerCamera->SetLocation(loc);
                localPC->PlayerCamera->SetRotation(rot);
                localPC->SetFOV(lerp(a.FOV, b.FOV));
            }
        }

        const auto perfEnd = std::chrono::high_resolution_clock::now();
        Stats.LastTickCostMs = std::chrono::duration<float, std::milli>(perfEnd - perfStart).count();
        Stats.MaxTickCostMs = (std::max)(Stats.MaxTickCostMs, Stats.LastTickCostMs);
        if (Stats.LastTickCostMs > 8.0f)
        {
            ++Stats.SlowTickCount;
            static ULONGLONG lastSlowLog = 0;
            if (now - lastSlowLog > 2000)
            {
                lastSlowLog = now;
                Log("Feature tick watchdog: " + std::to_string(Stats.LastTickCostMs) + " ms");
            }
        }
    }

    void RenderOverlay()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* draw = ImGui::GetForegroundDrawList();
        if (!draw) return;

        const ImVec2 display = io.DisplaySize;

        if (Config.CinematicBars || g_photoMode)
        {
            const float bar = display.y * (std::max)(0.02f, (std::min)(Config.CinematicBarSize, 0.25f));
            draw->AddRectFilled(ImVec2(0, 0), ImVec2(display.x, bar), IM_COL32(0, 0, 0, 255));
            draw->AddRectFilled(ImVec2(0, display.y - bar), display, IM_COL32(0, 0, 0, 255));
        }

        float y = 24.0f;
        if (Config.Speedometer)
        {
            char buf[96];
            sprintf_s(buf, "CAR  %.0f km/h   MAX %.0f", Stats.CurrentCarSpeedKph, Stats.MaxCarSpeedKph);
            DrawShadowText(draw, ImVec2(24.0f, y), IM_COL32(245, 245, 245, 245), buf);
            y += 19.0f;
        }

        if (Config.BallTelemetry)
        {
            char buf[96];
            sprintf_s(buf, "BALL %.0f km/h   MAX %.0f   TOUCHES %d", Stats.CurrentBallSpeedKph, Stats.MaxBallSpeedKph, Stats.TouchCount);
            DrawShadowText(draw, ImVec2(24.0f, y), IM_COL32(255, 200, 90, 245), buf);
            y += 19.0f;
        }

        if (Config.BoostTelemetry)
        {
            char buf[64];
            sprintf_s(buf, "BOOST %.0f%%   AIR %.1fs", Stats.BoostPercent, Stats.AirTimeSeconds);
            DrawShadowText(draw, ImVec2(24.0f, y), IM_COL32(95, 210, 255, 245), buf);
            y += 19.0f;
        }

        if (Config.ShotHistory && !g_shotHistory.empty())
        {
            std::string line = "SHOTS ";
            int shown = 0;
            for (float s : g_shotHistory)
            {
                char tmp[24]; sprintf_s(tmp, "%.0f ", s);
                line += tmp;
                if (++shown >= 6) break;
            }
            DrawShadowText(draw, ImVec2(24.0f, y), IM_COL32(210, 210, 210, 230), line.c_str());
        }

        if (Config.SessionPanel)
        {
            const float w = 245.0f, h = 112.0f;
            const ImVec2 p0(display.x - w - 24.0f, 24.0f);
            const ImVec2 p1(display.x - 24.0f, 24.0f + h);
            draw->AddRectFilled(p0, p1, IM_COL32(12, 12, 16, 205), 8.0f);
            draw->AddRect(p0, p1, IM_COL32(255, 70, 80, 140), 8.0f);
            DrawShadowText(draw, p0 + ImVec2(12, 10), IM_COL32(255, 90, 100, 245), "KINGMOD SESSION");
            char a[96], b[96], c[96], d[96];
            sprintf_s(a, "Time %.0fs   Touches %d", Stats.SessionSeconds, Stats.TouchCount);
            sprintf_s(b, "Car max %.0f km/h", Stats.MaxCarSpeedKph);
            sprintf_s(c, "Ball max %.0f km/h", Stats.MaxBallSpeedKph);
            sprintf_s(d, "Air %.1fs   Dodges %d", Stats.AirTimeSeconds, Stats.DodgeCount);
            DrawShadowText(draw, p0 + ImVec2(12, 33), IM_COL32(225,225,225,235), a);
            DrawShadowText(draw, p0 + ImVec2(12, 51), IM_COL32(225,225,225,235), b);
            DrawShadowText(draw, p0 + ImVec2(12, 69), IM_COL32(225,225,225,235), c);
            DrawShadowText(draw, p0 + ImVec2(12, 87), IM_COL32(225,225,225,235), d);
        }

        if (Config.DebugPanel)
        {
            const std::vector<DebugEntry> entries = GetDebugLog();
            float debugY = display.y * 0.55f;
            int shown = 0;
            for (auto it = entries.rbegin(); it != entries.rend() && shown < 8; ++it, ++shown)
            {
                DrawShadowText(draw, ImVec2(24.0f, debugY), IM_COL32(170, 255, 170, 220), it->Text.c_str());
                debugY += 17.0f;
            }
        }
    }

    void ApplyProfile(Profile profile)
    {
        switch (profile)
        {
        case Profile::Competitive:
            Config.Speedometer = false;
            Config.BallTelemetry = false;
            Config.BoostTelemetry = false;
            Config.ShotHistory = false;
            Config.CinematicBars = false;
            Config.SessionPanel = false;
            Config.DebugPanel = false;
            Config.UnlimitedBoost = false;
            Config.UnlimitedDodge = false;
            Config.SlowMotion = false;
            MatchmakingShield::SetEnabled(true);
            break;
        case Profile::Training:
            Config.Speedometer = true;
            Config.BallTelemetry = true;
            Config.BoostTelemetry = true;
            Config.ShotHistory = true;
            Config.SessionPanel = true;
            Config.UnlimitedBoost = true;
            Config.UnlimitedDodge = true;
            Config.SlowMotion = false;
            GameEventHookModule::BallPredictionEnabled = true;
            break;
        case Profile::LANHost:
            Config.Speedometer = true;
            Config.BallTelemetry = true;
            Config.BoostTelemetry = true;
            Config.SessionPanel = true;
            Config.DebugPanel = false;
            MatchmakingShield::SetEnabled(false);
            break;
        case Profile::Cinematic:
            Config.Speedometer = false;
            Config.BallTelemetry = false;
            Config.BoostTelemetry = false;
            Config.ShotHistory = false;
            Config.CinematicBars = true;
            Config.SessionPanel = false;
            Config.DebugPanel = false;
            break;
        case Profile::Debug:
            Config.Speedometer = true;
            Config.BallTelemetry = true;
            Config.BoostTelemetry = true;
            Config.SessionPanel = true;
            Config.DebugPanel = true;
            break;
        }
        SaveConfig();
        Log(std::string("Applied profile: ") + GetProfileName(profile));
    }

    const char* GetProfileName(Profile profile)
    {
        switch (profile)
        {
        case Profile::Competitive: return "Competitive";
        case Profile::Training: return "Training";
        case Profile::LANHost: return "LAN Host";
        case Profile::Cinematic: return "Cinematic";
        case Profile::Debug: return "Debug";
        default: return "Unknown";
        }
    }

    bool SaveCheckpoint()
    {
        ACar_TA* car = GetLocalCar();
        ABall_TA* ball = GetPrimaryBall();
        if (!car || !ball) return false;
        try
        {
            g_checkpoint.Car = car->GetCurrentRBState();
            g_checkpoint.Ball = ball->GetCurrentRBState();
            g_checkpoint.BoostAmount = (IsPointerReadable(car->BoostComponent) && !car->BoostComponent->bDeleteMe)
                ? car->BoostComponent->CurrentBoostAmount : 0.0f;
            APRI_TA* pri = GetLocalPRI();
            g_checkpoint.TeamIndex = (pri && pri->Team) ? pri->Team->TeamIndex : -1;
            g_checkpoint.Valid = true;
            Log("Training checkpoint saved");
            return true;
        }
        catch (...) { return false; }
    }

    bool RestoreCheckpoint()
    {
        if (!g_checkpoint.Valid) return false;
        ACar_TA* car = GetLocalCar();
        ABall_TA* ball = GetPrimaryBall();
        if (!car || !ball) return false;
        try
        {
            FReplicatedRBState carState = g_checkpoint.Car;
            FReplicatedRBState ballState = g_checkpoint.Ball;
            carState.bNewData = true;
            ballState.bNewData = true;
            car->SetPhysicsState(carState);
            ball->SetPhysicsState(ballState);
            if (IsPointerReadable(car->BoostComponent) && !car->BoostComponent->bDeleteMe)
                car->BoostComponent->SetBoostAmount(g_checkpoint.BoostAmount);
            Log("Training checkpoint restored");
            return true;
        }
        catch (...) { return false; }
    }

    bool ClearCheckpoint()
    {
        g_checkpoint = Checkpoint{};
        Log("Training checkpoint cleared");
        return true;
    }

    bool CenterBall(bool stopVelocity)
    {
        ABall_TA* ball = GetPrimaryBall();
        if (!ball) return false;
        try
        {
            FReplicatedRBState state = ball->GetCurrentRBState();
            state.Location = FVector{ 0.0f, 0.0f, 120.0f };
            if (stopVelocity)
            {
                state.LinearVelocity = FVector{};
                state.AngularVelocity = FVector{};
            }
            state.bSleeping = false;
            state.bNewData = true;
            ball->SetPhysicsState(state);
            ball->RegisterTeleport();
            Log("Ball centered");
            return true;
        }
        catch (...) { return false; }
    }

    bool LaunchBallTowardGoal(int targetTeam, float speed, float height)
    {
        ABall_TA* ball = GetPrimaryBall();
        AGameEvent_Soccar_TA* game = GetSoccar();
        if (!ball || !game) return false;
        try
        {
            UGoal_TA* goal = game->GetGoalByTeamIndex(targetTeam == 0 ? 0 : 1);
            if (!goal) return false;
            FReplicatedRBState s = ball->GetCurrentRBState();
            FVector target = goal->Location;
            target.Z += height;
            FVector d{ target.X - s.Location.X, target.Y - s.Location.Y, target.Z - s.Location.Z };
            const float len = std::sqrt(d.X*d.X + d.Y*d.Y + d.Z*d.Z);
            if (len < 1.0f) return false;
            const float inv = 1.0f / len;
            s.LinearVelocity = FVector{ d.X * inv * speed, d.Y * inv * speed, d.Z * inv * speed };
            s.bSleeping = false;
            s.bNewData = true;
            ball->SetPhysicsState(s);
            Log(targetTeam == 0 ? "Ball launched toward Blue goal" : "Ball launched toward Orange goal");
            return true;
        }
        catch (...) { return false; }
    }

    bool LaunchBallAtLocalCar(float speed, float height)
    {
        ABall_TA* ball = GetPrimaryBall();
        ACar_TA* car = GetLocalCar();
        if (!ball || !car) return false;
        try
        {
            FReplicatedRBState bs = ball->GetCurrentRBState();
            const FReplicatedRBState cs = car->GetCurrentRBState();
            FVector target = cs.Location;
            target.Z += height;
            FVector d{ target.X-bs.Location.X, target.Y-bs.Location.Y, target.Z-bs.Location.Z };
            const float len = std::sqrt(d.X*d.X + d.Y*d.Y + d.Z*d.Z);
            if (len < 1.0f) return false;
            d.X /= len; d.Y /= len; d.Z /= len;
            bs.LinearVelocity = FVector{ d.X*speed, d.Y*speed, d.Z*speed };
            bs.bSleeping = false; bs.bNewData = true;
            ball->SetPhysicsState(bs);
            Log("Ball launched at local car");
            return true;
        }
        catch (...) { return false; }
    }

    bool RandomizeBall()
    {
        ABall_TA* ball = GetPrimaryBall();
        if (!ball) return false;
        try
        {
            static std::mt19937 rng(static_cast<unsigned int>(GetTickCount()));
            std::uniform_real_distribution<float> x(-3000.0f, 3000.0f);
            std::uniform_real_distribution<float> y(-4000.0f, 4000.0f);
            std::uniform_real_distribution<float> z(150.0f, 1600.0f);
            std::uniform_real_distribution<float> v(-1600.0f, 1600.0f);
            FReplicatedRBState s = ball->GetCurrentRBState();
            s.Location = FVector{ x(rng), y(rng), z(rng) };
            s.LinearVelocity = FVector{ v(rng), v(rng), v(rng) * 0.45f };
            s.AngularVelocity = FVector{};
            s.bSleeping = false; s.bNewData = true;
            ball->SetPhysicsState(s);
            ball->RegisterTeleport();
            Log("Ball randomized");
            return true;
        }
        catch (...) { return false; }
    }

    bool GiveLocalFullBoost()
    {
        ACar_TA* car = GetLocalCar();
        if (!car || !IsPointerReadable(car->BoostComponent)) return false;
        try { car->BoostComponent->GiveFullBoost(); return true; }
        catch (...) { return false; }
    }

    bool HostApplyScoreAndTime(bool restartRound)
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        APlayerController_TA* pc = GetLocalPC();
        if (!game || !pc) return false;
        try
        {
            game->SetScoreAndTime(pc,
                (std::max)(0, Config.HostScoreBlue),
                (std::max)(0, Config.HostScoreOrange),
                (std::max)(0, Config.HostSeconds),
                Config.HostOvertime,
                restartRound);
            game->bForceNetUpdate = true;
            Log("Host score/time applied");
            return true;
        }
        catch (...) { return false; }
    }

    bool HostPause(bool pause)
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        APlayerController_TA* pc = GetLocalPC();
        if (!game || !pc) return false;
        try
        {
            game->SetPaused(pc, pause);
            Config.HostPaused = pause;
            Log(pause ? "Host paused match" : "Host resumed match");
            return true;
        }
        catch (...) { return false; }
    }

    bool HostResetBall()
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        try { game->ResetBalls(); Log("Host reset balls"); return true; }
        catch (...) { return false; }
    }

    bool HostResetGame()
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        try { game->ResetGame(); Log("Host reset game"); return true; }
        catch (...) { return false; }
    }

    bool HostStartNewRound()
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        try { game->StartNewRound(); Log("Host started new round"); return true; }
        catch (...) { return false; }
    }

    bool HostForceOvertime()
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        try { game->ForceOvertime(); Log("Host forced overtime"); return true; }
        catch (...) { return false; }
    }

    bool HostSetGoalsEnabled(bool enabled)
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        try { game->SetGoalsEnabled(enabled); Config.HostGoalsEnabled = enabled; Log(enabled ? "Goals enabled" : "Goals disabled"); return true; }
        catch (...) { return false; }
    }

    bool HostSetTeamSize(int size)
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        if (!game) return false;
        try
        {
            const int clamped = (std::max)(1, (std::min)(size, 8));
            game->SetMaxTeamSize(clamped);
            game->bForceNetUpdate = true;
            Config.HostTeamSize = clamped;
            Log("Host max team size changed");
            return true;
        }
        catch (...) { return false; }
    }

    bool SetWorldTimeScale(float scale)
    {
        try
        {
            AWorldInfo* wi = AWorldInfo::GetWorldInfo();
            if (!wi) return false;
            const float clamped = (std::max)(0.05f, (std::min)(scale, 3.0f));
            wi->eventSetTimeDilation(clamped);
            return true;
        }
        catch (...) { return false; }
    }

    bool HostSetGameSpeed(float scale)
    {
        if (!IsHostSandboxAvailable()) return false;
        Config.HostGameSpeed = (std::max)(0.1f, (std::min)(scale, 3.0f));
        const bool ok = SetWorldTimeScale(Config.HostGameSpeed);
        if (ok) Log("Host game speed changed");
        return ok;
    }

    bool HostApplyBallPhysics()
    {
        if (!IsHostSandboxAvailable()) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        if (!game) return false;
        bool any = false;
        try
        {
            for (int i = 0; i < game->GameBalls.size(); ++i)
            {
                ABall_TA* ball = game->GameBalls[i];
                if (!ball || ball->bDeleteMe) continue;
                ball->SetBallScale((std::max)(0.25f, (std::min)(Config.BallScale, 4.0f)));
                ball->SetBallGravityScale((std::max)(0.0f, (std::min)(Config.BallGravityScale, 5.0f)));
                ball->SetBallMaxLinearSpeedScale((std::max)(0.25f, (std::min)(Config.BallMaxSpeedScale, 5.0f)));
                ball->SetWorldBounceScale((std::max)(0.0f, (std::min)(Config.BallBounceScale, 5.0f)));
                ball->SetCarBounceScale(GetAddedCarBounceScale());
                ball->bForceNetUpdate = true;
                any = true;
            }
            if (any) Log("Host ball physics applied");
        }
        catch (...) { return false; }
        return any;
    }

    bool ApplyBallPinchStrength()
    {
        AGameEvent_Soccar_TA* game = GetSoccar();
        const bool ok = ApplyPinchToGameBalls(game, true);
        if (ok)
        {
            std::ostringstream ss;
            ss << "Ball pinch strength "
               << (Config.BallPinchStrengthEnabled ? Config.BallPinchStrength : 1.0f)
               << "x";
            Log(ss.str());
        }
        return ok;
    }


    bool HostMovePlayerToTeam(APRI_TA* pri, int team)
    {
        if (!IsHostSandboxAvailable() || !pri || pri->bDeleteMe) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        AController* controller = ControllerForPRI(pri);
        if (!game || !controller) return false;
        try
        {
            game->SetPlayerTeam(controller, team == 0 ? 0 : 1);
            game->RestartPlayer(controller);
            Log("Host moved player team");
            return true;
        }
        catch (...) { return false; }
    }

    bool HostSpectatePlayer(APRI_TA* pri)
    {
        if (!IsHostSandboxAvailable() || !pri || pri->bDeleteMe) return false;
        try { pri->ServerSpectate(); Log("Host requested player spectate"); return true; }
        catch (...) { return false; }
    }

    bool HostRespawnPlayer(APRI_TA* pri)
    {
        if (!IsHostSandboxAvailable() || !pri || pri->bDeleteMe) return false;
        AGameEvent_Soccar_TA* game = GetSoccar();
        AController* controller = ControllerForPRI(pri);
        if (!game || !controller) return false;
        try { const bool ok = game->RestartPlayer(controller); if (ok) Log("Host respawned player"); return ok; }
        catch (...) { return false; }
    }

    bool HostMovePlayerByName(const std::string& playerName, int team)
    {
        APRI_TA* pri = ResolvePRIByName(playerName);
        return pri ? HostMovePlayerToTeam(pri, team) : false;
    }

    bool HostSpectatePlayerByName(const std::string& playerName)
    {
        APRI_TA* pri = ResolvePRIByName(playerName);
        return pri ? HostSpectatePlayer(pri) : false;
    }

    bool HostRespawnPlayerByName(const std::string& playerName)
    {
        APRI_TA* pri = ResolvePRIByName(playerName);
        return pri ? HostRespawnPlayer(pri) : false;
    }

    bool HostFreezePlayerByName(const std::string& playerName, bool frozen)
    {
        if (!IsHostSandboxAvailable()) return false;
        APRI_TA* pri = ResolvePRIByName(playerName);
        if (!pri || pri->bDeleteMe || !pri->Car || pri->Car->bDeleteMe) return false;
        try
        {
            pri->Car->SetFrozen(frozen);
            pri->Car->bForceNetUpdate = true;
            Log(std::string(frozen ? "Host froze player: " : "Host unfroze player: ") + playerName);
            return true;
        }
        catch (...) { return false; }
    }

    bool HostSetCarScaleByName(const std::string& playerName, float scale)
    {
        if (!IsHostSandboxAvailable()) return false;
        APRI_TA* pri = ResolvePRIByName(playerName);
        if (!pri || pri->bDeleteMe || !pri->Car || pri->Car->bDeleteMe) return false;
        try
        {
            const float safeScale = (std::max)(0.25f, (std::min)(scale, 3.0f));
            pri->Car->SetCarScale(safeScale);
            pri->Car->bForceNetUpdate = true;
            Log("Host set car scale for " + playerName + " to " + std::to_string(safeScale));
            return true;
        }
        catch (...) { return false; }
    }


    bool HostKickPlayerByName(const std::string& playerName)
    {
        if (!IsHostSandboxAvailable()) return false;
        APRI_TA* pri = ResolvePRIByName(playerName);
        AGameEvent_Soccar_TA* game = GetSoccar();
        AController* controller = ControllerForPRI(pri);
        if (!pri || !game || !controller) return false;
                                                         
        if (pri == GetLocalPRI()) return false;
        try
        {
            game->RemovePlayer(controller);
            Log("Host removed player: " + playerName);
            return true;
        }
        catch (...) { return false; }
    }

    bool ToggleGameHud()
    {
        APlayerController_TA* pc = GetLocalPC();
        if (!pc) return false;
        try
        {
            pc->ConsoleCommand(FString(L"ToggleHUD"), false);
            return true;
        }
        catch (...) { return false; }
    }

    bool SetPhotoMode(bool enabled)
    {
        if (g_photoMode == enabled) return true;
        g_photoMode = enabled;
        if (enabled)
        {
            if (Config.HideGameHudInPhotoMode)
            {
                g_photoHudToggled = ToggleGameHud();
            }
            SetWorldTimeScale(0.05f);
            Log("Photo mode enabled");
        }
        else
        {
            SetWorldTimeScale(Config.SlowMotion ? Config.SlowMotionScale : 1.0f);
            if (g_photoHudToggled)
                ToggleGameHud();
            g_photoHudToggled = false;
            Log("Photo mode disabled");
        }
        return true;
    }

    bool IsPhotoMode() { return g_photoMode; }

    bool FollowPlayer(APRI_TA* pri)
    {
        APlayerController_TA* pc = GetLocalPC();
        if (!pc || !pri || pri->bDeleteMe) return false;
        try { pc->FollowPlayer(pri); return true; }
        catch (...) { return false; }
    }

    bool FollowPlayerByName(const std::string& playerName)
    {
        APRI_TA* pri = ResolvePRIByName(playerName);
        return pri ? FollowPlayer(pri) : false;
    }

    bool UnfollowPlayer()
    {
        APlayerController_TA* pc = GetLocalPC();
        if (!pc || pc->bDeleteMe) return false;
        try
        {
                                                                         
                                                                           
                                                                
            pc->SetFollowTarget(nullptr);
            return true;
        }
        catch (...) { return false; }
    }

    bool ToggleFreeCam()
    {
        APlayerController_TA* pc = GetLocalPC();
        AGameEvent_Soccar_TA* game = GetSoccar();
        if (!pc || pc->bDeleteMe || !game || game->bDeleteMe) return false;
        if (!(game->IsPlayingLan() || game->IsPlayingPrivate() || game->IsPlayingTraining()))
            return false;

        try
        {
                                                                                  
                                                                                  
                                                                                 
                                                                              
            APRI_TA* pri = pc->PRI;
            bool currentlyUsing = false;

            if (pri && !pri->bDeleteMe)
            {
                currentlyUsing = pri->bUsingFreecam != 0;

                if (pri->Camera && !pri->Camera->bDeleteMe)
                    currentlyUsing = pri->Camera->bUsingFreecam != 0;
                else if (pri->PersistentCamera && !pri->PersistentCamera->bDeleteMe)
                    currentlyUsing = pri->PersistentCamera->bUsingFreecam != 0;
            }

            const bool enable = !currentlyUsing;

                                                                                
                                                                              
                                                                            
            pc->SetUsingFreecam(enable);

            Log(enable ? "Free camera enabled" : "Free camera disabled");
            return true;
        }
        catch (...) { return false; }
    }

    bool CaptureCameraKeyframe()
    {
        APlayerController_TA* pc = GetLocalPC();
        if (!pc || !pc->PlayerCamera) return false;
        try
        {
            CameraKeyframe key;
            key.Location = pc->PlayerCamera->Location;
            key.Rotation = pc->PlayerCamera->Rotation;
            key.FOV = pc->GetFOVAngle();
            std::lock_guard<std::mutex> lock(g_cameraMutex);
            if (g_cameraKeys.size() >= 32) g_cameraKeys.erase(g_cameraKeys.begin());
            g_cameraKeys.push_back(key);
            Log("Camera keyframe captured");
            return true;
        }
        catch (...) { return false; }
    }

    bool ClearCameraPath()
    {
        std::lock_guard<std::mutex> lock(g_cameraMutex);
        g_cameraKeys.clear();
        g_cameraPathPlaying = false;
        Log("Camera path cleared");
        return true;
    }

    bool StartCameraPathPlayback(float durationSeconds)
    {
        std::lock_guard<std::mutex> lock(g_cameraMutex);
        if (g_cameraKeys.size() < 2) return false;
        g_cameraPathDuration = (std::max)(0.25f, (std::min)(durationSeconds, 120.0f));
        g_cameraPathStart = GetTickCount64();
        g_cameraPathPlaying = true;
        Log("Camera path playback started");
        return true;
    }

    bool StopCameraPathPlayback()
    {
        g_cameraPathPlaying = false;
        Log("Camera path playback stopped");
        return true;
    }

    bool IsCameraPathPlaying() { return g_cameraPathPlaying; }

    std::vector<CameraKeyframe> GetCameraKeyframes()
    {
        std::lock_guard<std::mutex> lock(g_cameraMutex);
        return g_cameraKeys;
    }

    bool SaveCameraPathToDisk()
    {
        try
        {
            std::vector<CameraKeyframe> keys;
            {
                std::lock_guard<std::mutex> lock(g_cameraMutex);
                keys = g_cameraKeys;
            }
            if (keys.empty()) return false;
            json out = json::array();
            for (const CameraKeyframe& k : keys)
            {
                out.push_back({
                    {"x", k.Location.X}, {"y", k.Location.Y}, {"z", k.Location.Z},
                    {"pitch", k.Rotation.Pitch}, {"yaw", k.Rotation.Yaw}, {"roll", k.Rotation.Roll},
                    {"fov", k.FOV}
                });
            }
            std::ofstream file(ConfigPath().parent_path() / "camera_path.json", std::ios::trunc);
            if (!file.is_open()) return false;
            file << out.dump(2);
            Log("Camera path saved");
            return true;
        }
        catch (...) { return false; }
    }

    bool LoadCameraPathFromDisk()
    {
        try
        {
            std::ifstream file(ConfigPath().parent_path() / "camera_path.json");
            if (!file.is_open()) return false;
            json data; file >> data;
            if (!data.is_array()) return false;
            std::vector<CameraKeyframe> loaded;
            for (const auto& v : data)
            {
                CameraKeyframe k{};
                k.Location.X = v.value("x", 0.0f);
                k.Location.Y = v.value("y", 0.0f);
                k.Location.Z = v.value("z", 0.0f);
                k.Rotation.Pitch = v.value("pitch", 0);
                k.Rotation.Yaw = v.value("yaw", 0);
                k.Rotation.Roll = v.value("roll", 0);
                k.FOV = v.value("fov", 90.0f);
                loaded.push_back(k);
                if (loaded.size() >= 64) break;
            }
            if (loaded.empty()) return false;
            {
                std::lock_guard<std::mutex> lock(g_cameraMutex);
                g_cameraKeys.swap(loaded);
            }
            Log("Camera path loaded");
            return true;
        }
        catch (...) { return false; }
    }

    void ResetSessionStats()
    {
        ResetSession();
        Log("Session statistics reset");
    }

    bool SaveSessionStats()
    {
        try
        {
            json j;
            j["session_seconds"] = Stats.SessionSeconds;
            j["car_speed_kph"] = Stats.CurrentCarSpeedKph;
            j["max_car_speed_kph"] = Stats.MaxCarSpeedKph;
            j["ball_speed_kph"] = Stats.CurrentBallSpeedKph;
            j["max_ball_speed_kph"] = Stats.MaxBallSpeedKph;
            j["boost_percent"] = Stats.BoostPercent;
            j["touch_count"] = Stats.TouchCount;
            j["air_time_seconds"] = Stats.AirTimeSeconds;
            j["dodge_count"] = Stats.DodgeCount;
            j["kickoff_touch_ms"] = Stats.LastKickoffTouchMs;
            j["best_kickoff_touch_ms"] = Stats.BestKickoffTouchMs;
            j["kickoff_0_to_220_ms"] = Stats.LastKickoffTimeTo220Ms;
            j["tick_cost_ms"] = Stats.LastTickCostMs;
            j["max_tick_cost_ms"] = Stats.MaxTickCostMs;
            const fs::path path = ConfigPath().parent_path() /
                ("session_stats_" + std::to_string(GetTickCount64()) + ".json");
            std::ofstream out(path, std::ios::trunc);
            if (!out.is_open()) return false;
            out << j.dump(2);
            Log("Session statistics exported");
            return true;
        }
        catch (...) { return false; }
    }

    void Log(const std::string& text)
    {
        DebugEntry e{ GetTickCount64(), text };
        {
            std::lock_guard<std::mutex> lock(g_debugMutex);
            g_debug.push_back(e);
            while (g_debug.size() > kMaxDebugEntries) g_debug.pop_front();
        }
        try { Console.Write("[V32] " + text); }
        catch (...) {}
    }

    std::vector<DebugEntry> GetDebugLog()
    {
        std::lock_guard<std::mutex> lock(g_debugMutex);
        return std::vector<DebugEntry>(g_debug.begin(), g_debug.end());
    }

    std::vector<PlayerSnapshot> GetPlayerSnapshots()
    {
        std::lock_guard<std::mutex> lock(g_playerSnapshotMutex);
        return g_playerSnapshots;
    }

    std::string GetStatusLine()
    {
        std::ostringstream out;
        out << (GameEventHookModule::IsInGame ? "In match" : "Menu")
            << " | " << (IsHostSandboxAvailable() ? "LAN host" : "client")
            << " | car " << static_cast<int>(Stats.CurrentCarSpeedKph) << " km/h"
            << " | ball " << static_cast<int>(Stats.CurrentBallSpeedKph) << " km/h";
        return out.str();
    }

    std::string BuildDebugReport()
    {
        std::ostringstream out;
        out << "KingMod V32 Debug Report\n";
        out << "========================\n";
        out << "Status: " << GetStatusLine() << "\n";
        out << "HostSync: " << HostSync::GetStatusText() << "\n";
        out << "Host join guard: " << (HostSync::IsJoinGuardActive() ? "active" : "idle") << "\n";
        out << "Match shield: " << (MatchmakingShield::IsEnabled() ? "enabled" : "disabled") << "\n";
        out << "Car max km/h: " << Stats.MaxCarSpeedKph << "\n";
        out << "Ball max km/h: " << Stats.MaxBallSpeedKph << "\n";
        out << "Touches: " << Stats.TouchCount << "\n";
        out << "Air time: " << Stats.AirTimeSeconds << "\n";
        out << "Dodges: " << Stats.DodgeCount << "\n";
        out << "V32 tick last/max ms: " << Stats.LastTickCostMs << " / " << Stats.MaxTickCostMs << "\n";
        out << "Slow ticks: " << Stats.SlowTickCount << "\n";
        out << "\nRecent V32 events:\n";
        for (const auto& e : GetDebugLog())
            out << e.Tick << "  " << e.Text << "\n";
        return out.str();
    }

    bool SaveDebugReport()
    {
        try
        {
            fs::path path = ConfigPath().parent_path() / "KingMod_V32_DebugReport.txt";
            std::ofstream out(path, std::ios::trunc);
            if (!out.is_open()) return false;
            out << BuildDebugReport();
            Log("Debug report saved: " + path.string());
            return true;
        }
        catch (...) { return false; }
    }

    bool CopyDebugReportToClipboard()
    {
        const std::string text = BuildDebugReport();
        if (!OpenClipboard(nullptr)) return false;
        EmptyClipboard();
        HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        if (!memory) { CloseClipboard(); return false; }
        void* target = GlobalLock(memory);
        if (!target) { GlobalFree(memory); CloseClipboard(); return false; }
        memcpy(target, text.c_str(), text.size() + 1);
        GlobalUnlock(memory);
        if (!SetClipboardData(CF_TEXT, memory))
        {
            GlobalFree(memory);
            CloseClipboard();
            return false;
        }
        CloseClipboard();
        Log("Debug report copied to clipboard");
        return true;
    }

    Checkpoint GetCheckpoint() { return g_checkpoint; }
}
