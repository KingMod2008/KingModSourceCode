#pragma once

#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../ImGui/imgui.h"
#include <array>
#include <deque>
#include <string>
#include <vector>

inline bool IsPointerReadable(const void* ptr)
{
    if (!ptr) return false;
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(ptr, &mbi, sizeof(mbi)))
        return false;
    if (!(mbi.State & MEM_COMMIT))
        return false;
    if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
        return false;
    return true;
}

                       
                         
                                                                                        
                                                                               
                                                                         
namespace KingFeatures
{
    enum class Profile
    {
        Competitive = 0,
        Training,
        LANHost,
        Cinematic,
        Debug
    };

    struct Settings
    {
                          
        bool Speedometer = true;
        bool BallTelemetry = true;
        bool BoostTelemetry = true;
        bool ShotHistory = true;
        bool CinematicBars = false;
        bool SessionPanel = false;
        bool DebugPanel = false;
        bool HideGameHudInPhotoMode = true;
        float CinematicBarSize = 0.105f;

                   
        bool AutoCheckpoint = false;
        bool UnlimitedBoost = false;
        bool UnlimitedDodge = false;
        bool SlowMotion = false;
        float SlowMotionScale = 0.35f;
        float TrainingBallLaunchSpeed = 1800.0f;
        float TrainingBallLaunchHeight = 600.0f;

                                   
        int HostScoreBlue = 0;
        int HostScoreOrange = 0;
        int HostSeconds = 300;
        bool HostOvertime = false;
        bool HostGoalsEnabled = true;
        bool HostPaused = false;
        int HostTeamSize = 3;
        float HostGameSpeed = 1.0f;
        float BallScale = 1.0f;
        float BallGravityScale = 1.0f;
        float BallMaxSpeedScale = 1.0f;
        float BallBounceScale = 1.0f;
                                                                           
                                                                            
                                                                              
        bool BallPinchStrengthEnabled = false;
        float BallPinchStrength = 1.0f;
        float HostCarScale = 1.0f;

                                             
        int CommandPaletteKey = 'K';
        bool CommandPaletteCtrl = true;
    };

    struct SessionStats
    {
        float CurrentCarSpeedKph = 0.0f;
        float MaxCarSpeedKph = 0.0f;
        float CurrentBallSpeedKph = 0.0f;
        float MaxBallSpeedKph = 0.0f;
        float BoostPercent = 0.0f;
        int TouchCount = 0;
        float AirTimeSeconds = 0.0f;
        float SessionSeconds = 0.0f;
        int DodgeCount = 0;
        float LastTickCostMs = 0.0f;
        float MaxTickCostMs = 0.0f;
        int SlowTickCount = 0;
        float LastKickoffTouchMs = 0.0f;
        float BestKickoffTouchMs = 0.0f;
        float LastKickoffTouchSpeedKph = 0.0f;
        float LastKickoffTimeTo220Ms = 0.0f;
    };

    struct Checkpoint
    {
        bool Valid = false;
        FReplicatedRBState Car{};
        FReplicatedRBState Ball{};
        float BoostAmount = 0.0f;
        int TeamIndex = -1;
    };



    struct CameraKeyframe
    {
        FVector Location{};
        FRotator Rotation{};
        float FOV = 90.0f;
    };

    struct PlayerSnapshot
    {
        std::string Name;
        int TeamIndex = -1;
        bool Spectator = false;
        bool Bot = false;
    };

    struct DebugEntry
    {
        ULONGLONG Tick = 0;
        std::string Text;
    };

    extern Settings Config;
    extern SessionStats Stats;

    void Initialize();
    void Shutdown();
    void SaveSettings();
    void ResetSession();

                                                         
    void Tick(AGameEvent_Soccar_TA* gameEvent, APlayerController_TA* localPC);

                                   
    void RenderOverlay();

                                 
    void ApplyProfile(Profile profile);
    const char* GetProfileName(Profile profile);

                                          
    bool SaveCheckpoint();
    bool RestoreCheckpoint();
    bool ClearCheckpoint();
    bool CenterBall(bool stopVelocity = true);
    bool LaunchBallTowardGoal(int targetTeam, float speed, float height);
    bool LaunchBallAtLocalCar(float speed, float height);
    bool RandomizeBall();
    bool GiveLocalFullBoost();

                                                                                 
    bool HostApplyScoreAndTime(bool restartRound = false);
    bool HostPause(bool pause);
    bool HostResetBall();
    bool HostResetGame();
    bool HostStartNewRound();
    bool HostForceOvertime();
    bool HostSetGoalsEnabled(bool enabled);
    bool HostSetTeamSize(int size);
    bool HostSetGameSpeed(float scale);
    bool HostApplyBallPhysics();
                                                                         
                                                            
    bool ApplyBallPinchStrength();
    bool HostMovePlayerToTeam(APRI_TA* pri, int team);
    bool HostSpectatePlayer(APRI_TA* pri);
    bool HostRespawnPlayer(APRI_TA* pri);
    bool HostMovePlayerByName(const std::string& playerName, int team);
    bool HostSpectatePlayerByName(const std::string& playerName);
    bool HostRespawnPlayerByName(const std::string& playerName);
    bool HostFreezePlayerByName(const std::string& playerName, bool frozen);
    bool HostSetCarScaleByName(const std::string& playerName, float scale);
    bool HostKickPlayerByName(const std::string& playerName);

                            
    bool SetPhotoMode(bool enabled);
    bool IsPhotoMode();
    bool SetWorldTimeScale(float scale);
    bool ToggleGameHud();
    bool FollowPlayer(APRI_TA* pri);
    bool FollowPlayerByName(const std::string& playerName);
    bool UnfollowPlayer();
    bool ToggleFreeCam();
    bool CaptureCameraKeyframe();
    bool ClearCameraPath();
    bool StartCameraPathPlayback(float durationSeconds);
    bool StopCameraPathPlayback();
    bool IsCameraPathPlaying();
    std::vector<CameraKeyframe> GetCameraKeyframes();
    bool SaveCameraPathToDisk();
    bool LoadCameraPathFromDisk();

                                 
    void ResetSessionStats();
    bool SaveSessionStats();

                      
    void Log(const std::string& text);
    std::vector<DebugEntry> GetDebugLog();
    std::vector<PlayerSnapshot> GetPlayerSnapshots();
    std::string GetStatusLine();
    std::string BuildDebugReport();
    bool SaveDebugReport();
    bool CopyDebugReportToClipboard();
    bool IsHostSandboxAvailable();
    Checkpoint GetCheckpoint();
}
