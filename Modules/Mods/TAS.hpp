#pragma once

#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace KingTAS
{
    enum class State : uint8_t
    {
        Idle,
        Replaying,
        Recording,
        Stopped
    };

    struct InterruptInputs
    {
        bool Throttle   = false;
        bool Steer      = false;
        bool AirRoll    = false;
        bool Powerslide = false;
        bool Jump       = false;
        bool Boost      = true;
    };

    struct TASInfo
    {
        std::string Name;
        std::string MapName;

        float ReplaySpeed = 1.0f;
        float RecordSpeed = 1.0f;

        float ExpectedSteeringSensitivity = 0.0f;
        float ExpectedAirSensitivity = 0.0f;
        float ExpectedDodgeThreshold = 0.0f;

        FVector ExpectedHitboxExtent{};
        FVector ExpectedHitboxOffset{};
        bool HasExpectedHitbox = false;

        std::size_t SavedFrameCount = 0;
        std::size_t PendingFrameCount = 0;
    };

                                                                          
      
                                                                
    void InstallHooks();

                                                                
                                                                             
                                                     
    bool NewTAS(const std::string& name);

                                                
      
                                 
                                               
    bool Start();

                                                                              
                          
    void Stop();

                                    
                                                                              
                       
    bool Update();

                                                   
    bool StopAndUpdate();

                                                                              
                          
    bool ChangeSpeed();

                                                             
                                                                           
    void Tick(APlayerController_TA* playerController, float deltaTime);

                                                                           
                                                                         
    void PrepareForTrainingReset();

                                                                              
                                                                                 
                                                                                
                                                                                
    void NotifyTrainingReset();
    void OnTrainingReset(APlayerController_TA* playerController);

                                                                                
                                         
    bool Save(const std::string& path = std::string());
    bool Load(const std::string& path);
    bool DeleteFile(const std::string& path);
    std::vector<std::string> GetSavedFiles();

    void SetSaveDirectory(const std::string& path);
    const std::string& GetSaveDirectory();

    void SetReplaySpeed(float speed);
    void SetRecordSpeed(float speed);
    float GetReplaySpeed();
    float GetRecordSpeed();

    void SetInterruptInputs(const InterruptInputs& inputs);
    InterruptInputs GetInterruptInputs();

    void SetStartReplayOnReset(bool enabled);
    bool GetStartReplayOnReset();

                                                                               
                                                                                  
                          
    void SetAllowListenServer(bool enabled);
    bool GetAllowListenServer();

    void SetEnvironmentValidation(bool enabled);
    bool GetEnvironmentValidation();

    State GetState();
    const char* GetStateName();

    bool HasLoadedTAS();
    bool HasPendingRecording();

    TASInfo GetInfo();
    const std::string& GetStatus();

                                                                      
                                                                           
    bool ExecuteBind(const std::string& command);
}
