#include "HostSync.hpp"

#include "GameEventHook.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Extensions/Extensions/Formatting.hpp"
#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <vector>

namespace HostSync
{
    namespace
    {
        ULONGLONG s_lastSyncTick = 0;
        ULONGLONG s_pauseUntilTick = 0;
        ULONGLONG s_lastPlayerJoinTick = 0;
        ULONGLONG s_lastSuccessfulSyncTick = 0;
        constexpr ULONGLONG SYNC_INTERVAL_MS = 2000;
        constexpr ULONGLONG JOIN_SETTLE_MS = 6000;

        bool s_forceHostRefresh = false;
        int s_desiredBotSkill = 4;
        int s_lastObservedPriCount = -1;

        APlayerControllerBase_TA* GetLocalPC()
        {
            UEngine* eng = UEngine::GetEngine();
            if (!eng || !eng->IsA<UGameEngine>())
                return nullptr;

            auto* ge = static_cast<UGameEngine*>(eng);
            if (ge->GamePlayers.empty() || !ge->GamePlayers[0])
                return nullptr;

            APlayerController* actor = ge->GamePlayers[0]->Actor;
            if (!actor || !actor->IsA<APlayerControllerBase_TA>())
                return nullptr;

            return static_cast<APlayerControllerBase_TA*>(actor);
        }

        std::string LowerStr(const std::string& s)
        {
            std::string out = s;
            std::transform(out.begin(), out.end(), out.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return out;
        }

        float SkillToFloat(int skill)
        {
            switch (skill)
            {
            case 0: return 0.0f;
            case 1: return 0.25f;
            case 2: return 0.5f;
            case 3: return 0.75f;
            default: return 1.0f;
            }
        }

        void PauseForJoinTransition()
        {
            const ULONGLONG now = GetTickCount64();
            s_lastPlayerJoinTick = now;
            s_pauseUntilTick = now + JOIN_SETTLE_MS;
        }
    }

    void NotifyLoginStarting()
    {
        PauseForJoinTransition();
        s_forceHostRefresh = true;
    }

    void NotifyPlayerJoined(APRI_TA* pri)
    {
        if (!pri)
            return;

                                                                            
                                                                                 
                                                                                
                                             
        PauseForJoinTransition();
        s_forceHostRefresh = true;
    }

    void ResetSessionState()
    {
        s_lastSyncTick = 0;
        s_pauseUntilTick = 0;
        s_lastPlayerJoinTick = 0;
        s_lastSuccessfulSyncTick = 0;
        s_lastObservedPriCount = -1;
        s_forceHostRefresh = false;
    }

    bool IsJoinGuardActive()
    {
        return GetTickCount64() < s_pauseUntilTick;
    }

    int GetConnectedPlayerCount()
    {
        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe)
            return 0;

        const int count = ge->PRIs.size();
        return (count >= 0 && count <= 64) ? count : 0;
    }

    ULONGLONG GetLastSuccessfulSyncTick()
    {
        return s_lastSuccessfulSyncTick;
    }

    const char* GetStatusText()
    {
        if (!GameEventHookModule::IsInGame)
            return "Idle";
        if (!Events.CanUseLocalServerFeatures())
            return "Client / public match";
        if (IsJoinGuardActive())
            return "Waiting for player join to settle";
        return "Host replication healthy";
    }

    void Tick()
    {
        if (!Events.CanUseLocalServerFeatures() || !GameEventHookModule::IsInitialized)
            return;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe)
            return;

                                                                                
                                                                            
        const int priCount = ge->PRIs.size();
        if (priCount >= 0 && priCount <= 64)
        {
            if (s_lastObservedPriCount >= 0 && priCount != s_lastObservedPriCount)
                PauseForJoinTransition();
            s_lastObservedPriCount = priCount;
        }

        const ULONGLONG now = GetTickCount64();
        if (now < s_pauseUntilTick)
            return;

        if (!s_forceHostRefresh && now - s_lastSyncTick < SYNC_INTERVAL_MS)
            return;
        s_lastSyncTick = now;

        APlayerControllerBase_TA* localPC = GetLocalPC();
        if (!localPC || !localPC->PlayerReplicationInfo)
            return;

        APRI_TA* hostPRI = static_cast<APRI_TA*>(localPC->PlayerReplicationInfo);
        if (!hostPRI || hostPRI->bDeleteMe)
            return;

                                   
                                                                               
                                                                                 
                                                                              
                                                                              
                                                                          
        if (s_forceHostRefresh)
        {
            hostPRI->bForceNetUpdate = true;
            s_forceHostRefresh = false;
        }

                                                                           
                                     
        const float targetSkill = SkillToFloat(s_desiredBotSkill);
        if (ge->BotSkill != targetSkill)
        {
            ge->SetBotSkill(targetSkill);
            ge->bForceNetUpdate = true;
        }

        s_lastSuccessfulSyncTick = now;
    }

    void SyncTitleNow()
    {
                                                                              
                                                                           
                                                                        
    }

    void SyncWheelsNow()
    {
        s_forceHostRefresh = true;
        s_lastSyncTick = 0;
    }

    void SyncAllNow()
    {
        s_forceHostRefresh = true;
        s_lastSyncTick = 0;
        SyncBotSkillNow();
    }

    void SyncBotSkillNow()
    {
        if (!Events.CanUseLocalServerFeatures() || IsJoinGuardActive())
            return;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe)
            return;

        const float targetSkill = SkillToFloat(s_desiredBotSkill);
        if (ge->BotSkill != targetSkill)
        {
            ge->SetBotSkill(targetSkill);
            ge->bForceNetUpdate = true;
        }
    }

    bool SpawnBot(const std::string& name, int team, int skill)
    {
        if (!Events.CanUseLocalServerFeatures() || IsJoinGuardActive())
            return false;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe)
            return false;

        URLBot_Util_TA* util = URLBot_Util_TA::GetInstance();
        if (!util)
            return false;

        FString fName = Format::ToFString(name.empty() ? std::string("Bot") : name);
        const uint8_t uTeam = (team == 0 || team == 1) ? static_cast<uint8_t>(team) : 255;
        const float skillFloat = SkillToFloat(skill);

        FBotLoadout emptyLoadout{};
        emptyLoadout.PrimaryColor = FColor{ 255, 255, 255, 255 };
        emptyLoadout.SecondaryColor = FColor{ 255, 255, 255, 255 };

        AAIController_TA* bot = util->eventSpawnClassicBot(
            ge, fName, uTeam, skillFloat, emptyLoadout);

        return bot && !bot->bDeleteMe;
    }

    bool RemoveBotByName(const std::string& name)
    {
        if (!Events.CanUseLocalServerFeatures() || IsJoinGuardActive())
            return false;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe || !ge->AIManager || ge->AIManager->bDeleteMe)
            return false;

        AAIManager_TA* aiMgr = ge->AIManager;
        const std::string needleLower = LowerStr(name);

        for (int i = 0; i < aiMgr->Bots.size(); ++i)
        {
            AAIController_TA* bot = aiMgr->Bots[i];
            if (!bot || bot->bDeleteMe)
                continue;

            APRI_TA* pri = static_cast<APRI_TA*>(bot->PlayerReplicationInfo);
            if (!pri || pri->bDeleteMe)
                continue;

            if (LowerStr(pri->PlayerName.ToString()).find(needleLower) == std::string::npos)
                continue;

            aiMgr->RemoveBot(bot);
            if (bot->Pawn && !bot->Pawn->bDeleteMe)
                bot->Pawn->Destroy();
            if (!bot->bDeleteMe)
                bot->Destroy();
            return true;
        }
        return false;
    }

    int RemoveAllBots()
    {
        if (!Events.CanUseLocalServerFeatures() || IsJoinGuardActive())
            return 0;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe || !ge->AIManager || ge->AIManager->bDeleteMe)
            return 0;

        AAIManager_TA* aiMgr = ge->AIManager;
        std::vector<AAIController_TA*> toRemove;
        toRemove.reserve(aiMgr->Bots.size());

        for (int i = 0; i < aiMgr->Bots.size(); ++i)
        {
            AAIController_TA* bot = aiMgr->Bots[i];
            if (bot && !bot->bDeleteMe)
                toRemove.push_back(bot);
        }

        int count = 0;
        for (AAIController_TA* bot : toRemove)
        {
            if (!bot || bot->bDeleteMe)
                continue;
            aiMgr->RemoveBot(bot);
            if (bot->Pawn && !bot->Pawn->bDeleteMe)
                bot->Pawn->Destroy();
            if (!bot->bDeleteMe)
                bot->Destroy();
            ++count;
        }
        return count;
    }

    void SetBotSkillLevel(int skill)
    {
        s_desiredBotSkill = std::clamp(skill, 0, 4);
        SyncBotSkillNow();
    }

    int GetActiveBotCount()
    {
        if (!GameEventHookModule::IsInGame)
            return 0;

        AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
        if (!ge || ge->bDeleteMe || !ge->AIManager || ge->AIManager->bDeleteMe)
            return 0;

        const int count = ge->AIManager->Bots.size();
        return (count >= 0 && count <= 64) ? count : 0;
    }
}
