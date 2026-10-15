#include "Main.hpp"
#include "../Includes.hpp"
#include "Fun.hpp"
#include "../Modules/Includes.hpp"
#include "../Modules/Mods/CustomAvatar.hpp"
#include "../Modules/Mods/BallTextures.hpp"
#include "../Modules/Mods/CustomBorder.hpp"
#include "../Modules/Mods/CustomBoostMeter.hpp"
#include "../Modules/Mods/CustomTextureStudio.hpp"
#include "../Modules/Mods/TAS.hpp"
#include <set>
#include <filesystem>
#include <Windows.h>

                                          
extern void InitializePsyNetDump();

static bool TryReadMemoryRaw(uintptr_t address, void* result, size_t size) {
    __try {
        memcpy(result, reinterpret_cast<const void*>(address), size);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

template<typename T>
bool TryReadMemory(uintptr_t address, T* result) {
    return TryReadMemoryRaw(address, result, sizeof(T));
}

                                                     
template <typename T>
T SafeRead(uintptr_t address) {
    T result = T{};
    TryReadMemory(address, &result);
    return result;
}


template <typename T>
bool SafeWrite(uintptr_t address, T value)
{
                                           
    if (address == 0)
    {
        return false;
    }

    __try
    {
                                          
        *reinterpret_cast<T*>(address) = value;
        return true;            
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
                            
        return false;
    }
}


MainComponent::MainComponent() : Component("Main", "Interface to game interacton") { OnCreate(); }

MainComponent::~MainComponent() { OnDestroy(); }

void MainComponent::OnCreate()
{
	Console.Write(GetNameFormatted() + "Initialized!");
	
	                                  
	Fun::ShowWelcomeModal();
	
    Main.Execute([]() {
        GameEventHook.Initialize();
    });

                                  
    Main.Execute([]() {
        CustomCar::Initialize();
    });

                                     
    Main.Execute([]() {
        CustomAvatarModule::Initialize();
    });

                                     
    Main.Execute([]() {
        BallTexturesModule::Initialize();
    });

                                                                               
                                                               
    Main.Execute([]() {
        CustomBoostMeterModule::Initialize();
    });

                                                
                                                                                  
    Main.Execute([]() {
        CustomTextureStudioModule::Initialize();
    });

                       
    Main.Execute([]() {
        Titles.LoadAllTitle();
        });

                                                                              
                                                                            
    Main.Execute([]() {
        std::filesystem::path tasDir;
        wchar_t exePath[MAX_PATH] = {};
        if (GetModuleFileNameW(nullptr, exePath, MAX_PATH))
            tasDir = std::filesystem::path(exePath).parent_path() / "KingMod" / "TAS";
        else
            tasDir = std::filesystem::current_path() / "KingMod" / "TAS";
        KingTAS::SetSaveDirectory(tasDir.string());
        KingTAS::InstallHooks();
    });
    
                                   
                                                               
                                                   
    Main.Execute([]() {
        extern void InitializePsyNetDump();
        InitializePsyNetDump();
        Console.Write("[PsyNet] Dump system ready. Call PsyNetDumper::Enable() to start");
    });
}

void MainComponent::OnDestroy()
{
    CustomTextureStudioModule::Shutdown();

                                                                             
    std::lock_guard<std::mutex> lock(GameFunctionsMutex);
    GameFunctions.clear();
}

void MainComponent::Initialize() {
    Main.Execute([]() {
        GameEventHook.Initialize();
    });
}

                                                    
   
                      
                                     
    

UNotification_TA* MainComponent::SpawnNotification(const std::string& Title, const std::string& Content, int Duration, UClass* NotificationClass)
{
                                                            
    UNotificationManager_TA* NotificationManager = Instances.GetInstanceOf<UNotificationManager_TA>();
    if (!NotificationManager) {
        Console.Error("Could not get NotificationManager instance.");
        return nullptr;
    }

                                                    
    static UFunction* PopUp_UFunc = nullptr;
    if (!PopUp_UFunc) {
        PopUp_UFunc = UObject::FindObject<UFunction>("Function TAGame.NotificationManager_TA.PopUpOnlyNotification");
    }

    if (!PopUp_UFunc) {
        Console.Error("UObject::FindObject failed for PopUpOnlyNotification.");
        return nullptr;
    }

    if (!NotificationClass) {
        NotificationClass = UGenericNotification_TA::StaticClass();
    }

    if (!NotificationClass) {
        Console.Error("NotificationClass is null.");
        return nullptr;
    }

                                            
    struct UNotificationManager_TA_execPopUpOnlyNotification_Params {
        UClass* NotificationClass;
        UNotification_TA* ReturnValue;
    } params = {};
    params.NotificationClass = NotificationClass;

    NotificationManager->ProcessEvent(PopUp_UFunc, &params,nullptr);

    UNotification_TA* Notification = params.ReturnValue;
    if (Notification) {
        Notification->PopUpDuration = Duration;

                                                 
        static UFunction* SetTitle_UFunc = nullptr;
        if (!SetTitle_UFunc) {
            SetTitle_UFunc = UObject::FindObject<UFunction>("Function TAGame.Notification_TA.SetTitle");
        }

        if (SetTitle_UFunc) {
            struct UNotification_TA_execSetTitle_Params { FString NewTitle; };
            UNotification_TA_execSetTitle_Params titleParams = {};
            titleParams.NewTitle = Format::ToFString(Title);
            Notification->ProcessEvent(SetTitle_UFunc, &titleParams,nullptr);
        }

        static UFunction* SetBody_UFunc = nullptr;
        if (!SetBody_UFunc) {
            SetBody_UFunc = UObject::FindObject<UFunction>("Function TAGame.Notification_TA.SetBody");
        }

        if (SetBody_UFunc) {
            struct UNotification_TA_execSetBody_Params { FString NewBody; };
            UNotification_TA_execSetBody_Params bodyParams = {};
            bodyParams.NewBody = Format::ToFString(Content);
            Notification->ProcessEvent(SetBody_UFunc, &bodyParams);
        }
	}

	return Notification;
}

void MainComponent::SpawnItemShopToast(const std::string& Title, const std::string& Content, int Duration)
{
	                                                                           
	                                                                          
	                                                                             
	                                                                             
	SpawnNotification(Title, Content, Duration);
}

void MainComponent::SendChatMessage(const std::string& message, bool isTeamChat)
{
    if (!GameEventHookModule::CurrentGameEvent) { return; }
                                                                                           
                                                                        
                                                                                           
    UGFxData_Chat_TA* chatData = Instances.GetInstanceOf<UGFxData_Chat_TA>();
    if (!chatData) {
        Console.Error("SendChatMessage: Could not get GFxData_Chat_TA instance.");
        return;
    }

                                                                                           
                                                       
                                                                                           
    static UFunction* SendChat_UFunc = nullptr;
    if (!SendChat_UFunc) {
        SendChat_UFunc = UObject::FindObject<UFunction>("Function TAGame.GFxData_Chat_TA.SendChatMessage");
    }

    if (!SendChat_UFunc) {
        Console.Error("SendChatMessage: UObject::FindObject failed for SendChatMessage.");
        return;
    }

                                                                                           
                                                             
                                                                                           
    UGFxData_Chat_TA_execSendChatMessage_Params params = {};
    params.Message = Format::ToFString(message);
    params.bTeamMessage = isTeamChat;

                                                                                           
                                                        
                                                                                           
    chatData->ProcessEvent(SendChat_UFunc, &params);

    Console.Notify("Sent chat message: " + message);
}

void MainComponent::SendQuickChatMessage(const FName& MessageId, bool isTeamChat)
{
    if (!GameEventHookModule::CurrentGameEvent) { return; }
                                                                                           
                                                                        
                                                         
                                                                                           
    UGFxData_Chat_TA* chatData = Instances.GetInstanceOf<UGFxData_Chat_TA>();
    if (!chatData) {
        Console.Error("SendQuickChatMessage: Could not get GFxData_Chat_TA instance.");
        return;
    }

                                                                                           
                                                             
                                                                     
                                                                                           
    static UFunction* SendQuickChat_UFunc = nullptr;
    if (!SendQuickChat_UFunc) {
        SendQuickChat_UFunc = UObject::FindObject<UFunction>("Function TAGame.GFxData_Chat_TA.SendChatPresetMessage");
    }

    if (!SendQuickChat_UFunc) {
        Console.Error("SendQuickChatMessage: UObject::FindObject failed for SendChatPresetMessage.");
        return;
    }

                                                                                           
                                                                                  
                                                                                           
    struct UGFxData_Chat_TA_execSendChatPresetMessage_Params {
        FName MessageId;
        bool bTeam;
    };

    UGFxData_Chat_TA_execSendChatPresetMessage_Params params = {};
    params.MessageId = MessageId;
    params.bTeam = isTeamChat;

                                                                                           
                                                                                         
                                                                                
                                                                                           
    chatData->ProcessEvent(SendQuickChat_UFunc, &params);

    Console.Notify("Sent quick chat: " + MessageId.ToString());
}

void MainComponent::AddSplitscreenPlayer() {
    UGameViewportClient_TA* viewportClient = Instances.GetInstanceOf<UGameViewportClient_TA>();
    viewportClient->AddSplitScreenPlayer();
}

bool MainComponent::SpawnItem(int productId, int seriesId, int tradeHold, std::string spawnMsg, bool doAnim) {
    Console.Write("Before");
    UOnlineProduct_TA* item = Items.SpawnProduct(productId, seriesId, tradeHold, true, spawnMsg, doAnim);

    Console.Write("lol");

    if (item) 
    {
        Console.Write("Spawned da item like a boss 💔🙏");
    }
        
    else {
        Console.Write("spawn failed... im cryin rn 😭💔");
    }

    
    return item;
}

void MainComponent::ReadyUp() {
    if (!GameEventHookModule::CurrentGameEvent) {
        Console.Error("ReadyUp: No current game event");
        return;
    }

                            
    TArray<APlayerController_TA*> localPlayers = GameEventHookModule::getLocalPlayers(GameEventHookModule::CurrentGameEvent);

    if (localPlayers.empty()) {
        Console.Error("ReadyUp: No local players found");
        return;
    }

                                                          
    for (APlayerController_TA* controller : localPlayers) {
        if (!controller) continue;

                                    
        static UFunction* ReadyUp_UFunc = nullptr;
        if (!ReadyUp_UFunc) {
            ReadyUp_UFunc = UObject::FindObject<UFunction>("Function TAGame.PlayerController_TA.ReadyUp");
        }

        if (ReadyUp_UFunc) {
                                              
            controller->ProcessEvent(ReadyUp_UFunc, nullptr);
            Console.Write("ReadyUp called on player controller");
        }
        else {
            Console.Error("ReadyUp: Could not find ReadyUp function");
        }
    }
}

void MainComponent::Forfeit() {
    if (!GameEventHookModule::CurrentGameEvent) {
        Console.Error("Forfeit: No current game event");
        return;
    }

    TArray<APlayerController_TA*> localPlayers = GameEventHookModule::getLocalPlayers(GameEventHookModule::CurrentGameEvent);
    if (localPlayers.empty()) {
        Console.Error("Forfeit: No local players found");
        return;
    }

    Console.Write("Attempting forfeit for " + std::to_string(localPlayers.size()) + " local players...");

    bool anyVoteSuccessful = false;
    int votesSuccessful = 0;

                                                                     
    for (APlayerController_TA* controller : localPlayers) {
        if (!controller) continue;

        APRI_TA* pri = controller->PRI;
        if (pri) {
                                                  
            bool forfeitDisabled = pri->bStartVoteToForfeitDisabled;

            if (forfeitDisabled) {
                Console.Write("Forfeit voting is disabled for player " + std::to_string(votesSuccessful + 1));
                continue;
            }

                                          
            std::string playerName = pri->PlayerName.ToString();

                                                       
            static UFunction* ServerVoteToForfeit_UFunc = nullptr;
            if (!ServerVoteToForfeit_UFunc) {
                ServerVoteToForfeit_UFunc = UObject::FindObject<UFunction>("Function TAGame.PRI_TA.ServerVoteToForfeit");
            }

            if (ServerVoteToForfeit_UFunc) {
                pri->ProcessEvent(ServerVoteToForfeit_UFunc, nullptr);
                Console.Write("Forfeit vote cast for player: " + playerName);
                anyVoteSuccessful = true;
                votesSuccessful++;
            }
        }
    }

                                                               
    if (anyVoteSuccessful) {
        Console.Notify("Forfeit votes cast for " + std::to_string(votesSuccessful) + " player(s)!");
        return;
    }

                                                             
    AGameEvent_Team_TA* teamGameEvent = static_cast<AGameEvent_Team_TA*>(GameEventHookModule::CurrentGameEvent);
    TArray<ATeam_TA*> teams = teamGameEvent->Teams;

    for (APlayerController_TA* controller : localPlayers) {
        if (!controller) continue;

        APRI_TA* pri = controller->PRI;
        if (!pri) continue;

                            
        ATeamInfo* teamInfo = pri->Team;
        if (!teamInfo) continue;

        int teamIndex = teamInfo->TeamIndex;

        if (teamIndex >= 0 && teamIndex < teams.size()) {
            ATeam_TA* team = teams[teamIndex];
            if (team) {
                std::string playerName = pri->PlayerName.ToString();

                                            
                static UFunction* VoteToForfeit_UFunc = nullptr;
                if (!VoteToForfeit_UFunc) {
                    VoteToForfeit_UFunc = UObject::FindObject<UFunction>("Function TAGame.Team_TA.VoteToForfeit");
                }

                if (VoteToForfeit_UFunc) {
                    struct VoteToForfeitParams {
                        APRI_TA* PRI;
                    };
                    VoteToForfeitParams params = { pri };

                    team->ProcessEvent(VoteToForfeit_UFunc, &params);
                    Console.Write("Team forfeit vote cast for player: " + playerName);
                    anyVoteSuccessful = true;
                    votesSuccessful++;
                    continue;                   
                }

                                                                          
                static std::set<ATeam_TA*> teamsAlreadyForfeited;
                if (teamsAlreadyForfeited.find(team) == teamsAlreadyForfeited.end()) {
                    static UFunction* Forfeit_UFunc = nullptr;
                    if (!Forfeit_UFunc) {
                        Forfeit_UFunc = UObject::FindObject<UFunction>("Function TAGame.Team_TA.Forfeit");
                    }

                    if (Forfeit_UFunc) {
                        team->ProcessEvent(Forfeit_UFunc, nullptr);
                        Console.Write("Direct forfeit executed for team " + std::to_string(teamIndex));
                        teamsAlreadyForfeited.insert(team);
                        anyVoteSuccessful = true;
                        votesSuccessful++;
                    }
                }
            }
        }
    }

    if (anyVoteSuccessful) {
        Console.Notify("Forfeit initiated for " + std::to_string(votesSuccessful) + " player(s)/team(s)!");
    }
    else {
        Console.Error("Forfeit: Could not find any working forfeit functions");
    }
}


std::vector<std::function<void()>> MainComponent::GameFunctions;
std::mutex MainComponent::GameFunctionsMutex;

class MainComponent Main {};

void MainComponent::StartMatchmaking() {
                                                                     
    if (UGFxData_Matchmaking_TA* uiMatch = Instances.GetInstanceOf<UGFxData_Matchmaking_TA>()) {
        bool ok = uiMatch->StartMatchmaking(-1);
        Console.Write(std::string("StartMatchmaking(UI): ") + (ok ? "requested" : "failed"));
        if (ok) return;
    }

    if (UGFxData_MenuTree_TA* menuTree = Instances.GetInstanceOf<UGFxData_MenuTree_TA>()) {
        menuTree->StartMatchmaking();
        Console.Write("StartMatchmaking(MenuTree): requested");
        return;
    }

                                                     
    UOnlineGame_X* online = nullptr;
                                                   
    online = UGFxShell_TA::GetOnlineGame();
    if (!online) {
        online = Instances.GetInstanceOf<UOnlineGame_X>();
    }

    if (!online) {
        Console.Error("StartMatchmaking: OnlineGame instance not found");
        return;
    }

    UOnlineGameMatchmaking_X* matchmaker = online->Matchmaking;
    if (!matchmaker) {
        Console.Error("StartMatchmaking: Matchmaking instance not available on OnlineGame");
        return;
    }

    matchmaker->RecordStart(true);
    matchmaker->AddRecommendedServers(80.f, 20.f, 180.f);
    matchmaker->StartMatchmaking();
    Console.Write("StartMatchmaking(Fallback): invoked StartMatchmaking()");
}

void MainComponent::LeaveMatch() {
                                                                                
                                                           
    TArray<APlayerController_TA*> locals;
    if (GameEventHookModule::CurrentGameEvent) {
        locals = GameEventHookModule::getLocalPlayers(GameEventHookModule::CurrentGameEvent);
    }
    if (!locals.empty() && locals[0]) {
        APlayerController_TA* pc = locals[0];
        pc->ConsoleCommand(Format::ToFString("Open MainMenu"), false);
        pc->ConsoleCommand(Format::ToFString("disconnect"), false);
        pc->ConsoleCommand(Format::ToFString("unreal_command disconnect"), false);
        Console.Write("LeaveMatch(ConsoleCommand via PlayerController): requested");
                 
    }

                                                     
    if (UGameViewportClient_TA* gvc = Instances.GetInstanceOf<UGameViewportClient_TA>()) {
        gvc->ConsoleCommand(Format::ToFString("Open MainMenu"));
        gvc->ConsoleCommand(Format::ToFString("disconnect"));
        gvc->ConsoleCommand(Format::ToFString("unreal_command disconnect"));
        Console.Write("LeaveMatch(ConsoleCommand via Viewport): requested");
                 
    }

                                      
    if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
        ULocalPlayer_X* lpx = static_cast<ULocalPlayer_X*>(lp);
        if (lpx) {
            if (UGFxShell_TA* shell = UGFxShell_TA::GetShell(lpx)) {
                shell->ExitToMainMenu();
                shell->LeaveMatch();
                Console.Write("LeaveMatch(GFxShell with LocalPlayer): requested");
                return;
            } else {
                Console.Write("LeaveMatch: GetShell(LocalPlayer_X) returned null");
            }
        }
    }

                                          
    if (UGFxShell_TA* shellInst = Instances.GetInstanceOf<UGFxShell_TA>()) {
        shellInst->ExitToMainMenu();
        shellInst->LeaveMatch();
        Console.Write("LeaveMatch(GFxShell via Instances): requested");
        return;
    }

    Console.Error("LeaveMatch: no route to issue disconnect");
}
