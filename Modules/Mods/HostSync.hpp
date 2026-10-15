#pragma once

#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include <Windows.h>
#include <string>

           
           
                                              
  
                                                                                
                                                                                  
                                                                               
                      
namespace HostSync
{
    void Tick();

                                                                                 
                                                                       
    void NotifyLoginStarting();
    void NotifyPlayerJoined(APRI_TA* pri);
    void ResetSessionState();

    bool IsJoinGuardActive();
    int GetConnectedPlayerCount();
    ULONGLONG GetLastSuccessfulSyncTick();
    const char* GetStatusText();

                                        
    void SyncTitleNow();
    void SyncWheelsNow();
    void SyncAllNow();
    void SyncBotSkillNow();

                                
    bool SpawnBot(const std::string& name, int team, int skill);
    bool RemoveBotByName(const std::string& name);
    int RemoveAllBots();
    void SetBotSkillLevel(int skill);
    int GetActiveBotCount();
}
