#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../GamePacket.hpp"
#include "nlohmann/json.hpp"
#include <memory>
#include <vector>
#include <atomic>

#include "../../ImGui/imgui.h"

struct PrivBallInfo {
    FVector Location;
    FVector Velocity;
    FVector AngularVelocity;
    bool IsValid;
    float Radius = 91.25f;
};

struct CameraData {
    FVector Location;
    FRotator Rotation;
    float FOV;
};

struct PlayerControllerData {
    class APlayerController_TA* Controller;
    class ACamera* Camera;
    class APRI_TA* PRI;
    class ACar_TA* Car;
};

struct Player {
    std::string PlayerName;
    FVector Location;
    FVector Velocity;
    ACarComponent_Boost_TA* BoostComponent;
    APRI_TA* PRI;
    float BoostAmount;
};

struct Players {
    std::vector<Player> players;
    bool Valid;
};

struct PlayerController_ChatMessage_Params
{
    uintptr_t InPRI_ptr;
    FString   Message;
    uint8_t   ChatChannel;
    uint8_t   padding[3];
    union {
        uint32_t BitfieldData;
        struct {
            uint32_t bPreset : 1;
        };
    };
    int32_t   TimeStamp;
};
class Field;

class GameEventHookModule : public Module
{
public:
    GameEventHookModule();
    ~GameEventHookModule() override;

    void OnCreate();
    void OnDestroy();


    static void HookGameEvents();


    static void HookAdditionalFunctions();


    static void GameViewportKeyPress(const PostEvent& event);
    static void OnSendChatPresetMessageHook(PreEvent& event);
    static void OnChatMessageHook(PreEvent& event);
    static void on_boost_picked_up(PreEvent& event);
    static void on_boost_respawned(PreEvent& event);
    static void on_reset_pickups(PreEvent& event);
    static void CacheSkillCalled(PreEvent& event);
    static void PlayerTickCalled(const PostEvent& event);
    static void OnGameEventStart(PreEvent& event);
    static void OnGameEventDestroyed(PreEvent& event);
    static void SkipReplay(PreEvent& event);
    static void OnReplayPlaybackEnd(PreEvent& event);


    static void OnBoostPickedUp(PreEvent& event);
    static void OnChatMessage(PreEvent& event);


    static void UpdateBallInfo(bool shouldLog = false);
    static void UpdatePlayers();
    static PrivBallInfo GetBallInfo();
    static Players GetPlayers();


    struct PredictionPoint {
        FVector Location;
        FVector Velocity;
        float Time;
    };
    static std::vector<PredictionPoint> PredictedPath;
    static void PredictBallPath();
    static void DrawBallPrediction();


    static PlayerControllerData GetPlayerControllerData();
    static CameraData GetCameraData();


    static bool WorldToScreen(const FVector& WorldLocation, FVector2D& ScreenLocation, float& Depth);


    static void DrawCarHitboxes();
    static void DrawFlipIndicator();
    void DrawBallSpeedDisplay();
    static bool CanDodgeFlip(ACar_TA* car);
                                                                             
                                                                                  
                                                                                 
                                                                                 
                                                                              
                                                                             
                                                                              
                                      
    static bool HasFlipAvailable(ACar_TA* car, bool authoritative);

    static int HitboxMode;

    static bool ResolveEpicIdViaWeb(const std::string& steam64, std::string& outEpicId);

    struct FavoriteEntry { int platform; std::string id; std::string title; };
    static std::vector<FavoriteEntry> FavoritePartyIds;
    static std::vector<std::pair<int, std::string>> RecentPartyIds;

    static int LastSelectedTab;

                        
    static void DrawPlayerBoosts();
    static void DrawBoostTimers();
    static void DrawControllerOverlay();
    static void DrawKeyboardOverlay();
    static TArray<APlayerController_TA*> getLocalPlayers(AGameEvent_Soccar_TA* gameEvent);


    static void DrawShoulderButton(ImDrawList* draw_list, float x, float y, const char* label, float value);
    static void DrawCompactStick(ImDrawList* draw_list, float x, float y, float x_axis, float y_axis);
    static void DrawFaceButton(ImDrawList* draw_list, float x, float y, const char* label, bool pressed, ImU32 color);
    static void DrawToggleStatusIndicator();
    static void UpdateBodyColor();
    static void UpdateUnderglowColor();
    static void UpdateLicensePlates();
    static bool BallSpeedDisplayEnabled;
    static float BallSpeedDisplayX;
    static float BallSpeedDisplayY;
    static float BallSpeedDisplaySize;
    static float LastBallSpeed;

    static void OnRender();


    static void Initialize();


    static PrivBallInfo CurrentBall;
    static Players players;
    static Field field;


    static bool IsInGame;
    static bool IsInReplayPlayback;
    static bool IsInitialized;
    static bool Debug;
    static bool SuperSonicAnnoyerEnabled;


    static AGameEvent_Soccar_TA* CurrentGameEvent;
    static FieldInfoPacket CurrentFieldInfo;
    static GameTickPacket CurrentGameTickPacket;


    static bool BallSpawnedFlag;

    static bool BoostPadTimers;
    static bool Hitboxes;
    static bool ControllerOverlay;
    static bool KeyboardOverlay;
    static ImVec2 ControllerOverlayPos;
    static ImVec2 KeyboardOverlayPos;
    static float ControllerOverlayAlpha;
    static float KeyboardOverlayAlpha;
    static bool TracersEnabled;
    static bool VelocityArrowsEnabled;
    static bool PlayerDistanceTextEnabled;
    static bool OpponentBoostEnabled;
    static bool UseTeamColorsForTracers;
    static bool Ball3DSphereEnabled;
    static bool BallPredictionEnabled;
    static ImVec4 BallPredictionColor;
    static float BallPredictionLineWidth;
    static bool FlipIndicatorEnabled;


    static ImVec4 TracersColor;
    static ImVec4 VelocityArrowBallColor;
    static ImVec4 VelocityArrowCarColor;
    static ImVec4 PlayerDistanceTextColor;
    static ImVec4 OpponentBoostColor;

    static float OpponentBoostScale;
    static float BoostPadMarkerScale;
    static ImVec4 HitboxColor;
    static ImVec4 Ball3DSphereColor;
    static ImVec4 FlipIndicatorColor;
    static float FlipIndicatorSize;
    static ImVec2 FlipIndicatorPos;
    static ImVec4 FlipAvailableColor;
    static ImVec4 FlipUnavailableColor;

    static void OnBallExplode(PreEvent& event);
    static void OnBallHitGoal(PreEvent& event);
    static void OnCarFinishDemo(PreEvent& event);
    static void OnExplosionPostBeginPlay(PreEvent& event);
    static void RemoveVisualEffects();

    static bool SkipReplays;

    static bool RemoveDemoSmoke;
    static bool RemoveGoalExplosion;

    static bool AutoQueueEnabled;
    static int AutoQueueDelaySeconds;
    static bool AutoQueueTriggered;
    static double AutoQueueReadyAt;
    static bool AutoLeaveEnabled;
    static int AutoLeaveDelaySeconds;
    static bool AutoLeaveTriggered;
    static double AutoLeaveReadyAt;
    static bool AutoQueueDone;
    static bool AutoLeaveDone;
    static bool AutoQueuePolling;
    static bool AutoLeavePolling;
    static bool AutoQueueThreadRunning;





    static bool ToggleStatusIndicatorEnabled;
    static ImVec2 ToggleStatusIndicatorPos;
    static bool ToggleStatusIndicatorDragging;
    static ImVec2 ToggleStatusIndicatorDragOffset;

    static bool DiscordWebhookEnabled;
    static char DiscordWebhookURL[512];
    static bool MatchStartedLogged;
    static bool MatchEndedLogged;
    static std::string CurrentMatchStartTime;
    static std::string CurrentMatchMap;
    static std::string CurrentMatchPlaylist;
    static bool GameEventActive;
    static std::string MenuToggleKey;
    static std::string ModuleVersion;

                                                                              
                                                                                     
                                                                                
    static ImVec4 UIAccentColor;
    static bool   UIAccentRainbow;
    static float  UIAccentRainbowSpeed;                               
    static ImVec4 UIBackgroundColor;
    static bool   UIBackgroundRainbow;
    static float  UIBackgroundRainbowSpeed;                           
    static bool   UIBlurEnabled;


    static bool MinimapEnabled;
    static ImVec2 MinimapPos;
    static float MinimapSize;
    static float MinimapAlpha;
    static bool MinimapShowBall;
    static bool MinimapShowBoosts;
    static bool MinimapShowPlayers;
    static bool MinimapTeamColors;
    static ImVec4 MinimapBallColor;
    static ImVec4 MinimapBoostColor;
    static ImVec4 MinimapPlayerColor;
    static ImVec4 MinimapMyTeamColor;
    static ImVec4 MinimapOpponentColor;
    static bool MinimapShowGoals;
    static bool MinimapShowDirection;
    static void DrawMinimap();

    static bool ShowPlayerMMR;
    static void DrawPlayerMMR();


    static bool IsKickoffPause;
    static double LastKickoffTime;
    static std::string LastGameState;



    static void SendDiscordWebhook(const std::string& content, const std::string& title = "", const std::string& description = "", int color = 0x00ff00);
    static void LogMatchStart();
    static void LogMatchEnd();
    static std::string GetCurrentRankInfo();


    static std::string ConfigFilePath;

                                                                            
                                                                              
                                                                               
                                             
                                                                            

                                                                              
                                                                                 
                                                                                
                                                                                
                                                                                
                                
    static bool UsernameChangerEnabled;
    static bool UsernameInvisible;
    static char UsernameChangeText[64];
    static void ApplyUsernameChange();
    static void SetLocalUsername(class APRI_TA* optionalLocalPri, const std::string& name);

                                                                 
    static std::string UsernameChangeStatus;

                                                                             
                                                                    
                                                                 
                                                                         
                                                                         
                                                             
                            
    static void ApplySteamUsername();

                                                                            
                                                                                 
                                                                                
                                                                               
                                                           
    static bool EnemyResetIndicatorEnabled;
    static void DrawEnemyResetIndicators();

                                                             
                                                           

                                                                              
    static int BallSpeedUnit;                                        

                                                                              
                                                                          
                                                                 
                                                     
    static bool BoostSoundDefaultOverride;
    static void ApplyBoostSound();

                                                 
      
                                              
                                                                                
                                                                        
                                                                              
                                                                             
                                                                               
                                                                                
                                                                          
                                                                              
                                 
    static bool AlphaBoostSoundEnabled;
    static std::string AlphaBoostSoundStatus;
    static void ApplyAlphaBoostSound();

                                                                              
                                                                               
                                                                           
                                                                             
    static bool UnlimitedJumpsEnabled;
    static bool ScoredMessageEnabled;
    static void ApplyFreeplayTweaks();
                                                                           
                                                                          
    static bool SendLocalChatMessage(const std::string& message);

                                                                        
    static bool IsInFreeplay();

                                                                               
                                                                          
                                       
                                                                            
                                 
    static bool ScoredMessageShowSpeed;
                                                                            
                                                                           
                                                               
    static std::string ScoredMessageStatus;

                                                                             
                                                                             
                                                                            
                                                           
    static char WorkshopMapPath[512];
    static void LoadWorkshopMap(bool hostLan = false, int gameModeIndex = 0,
                                int maxPlayers = 8,
                                const std::string& password = std::string(),
                                const std::string& gameTags = std::string(),
                                const std::string& joinHost = std::string(),
                                const std::string& joinPort = std::string(),
                                bool localTraining = true);
    static void LaunchStandardMap(const std::string& arenaPackage, bool hostLan,
                                  int gameModeIndex = 0, int maxPlayers = 8,
                                  const std::string& password = std::string(),
                                  const std::string& gameTags = std::string(),
                                  bool localTraining = true);
    static void OpenCustomMapsFolder();
    static void OpenWorkshopFolder();
    static std::vector<std::string> WorkshopMapList;
    static void RefreshWorkshopMapList();

                                                                             
                                                                                 
                                               
    static std::string GetWorkshopDirectory();
    static bool DownloadWorkshopMap(uint64_t workshopId);
    static float GetWorkshopDownloadProgress(uint64_t workshopId);
    static bool IsWorkshopMapInstalled(uint64_t workshopId);
    static bool GetWorkshopInstallPath(uint64_t workshopId, std::string& path);

                                                                             
                                                                             
                                                                          
                                                                           
                                                                          
                                                                                
                                                                       
    struct WorkshopItem
    {
        std::string id;                                 
        std::string title;
        std::string previewUrl;
        std::string fileUrl;                                                      
        std::string fileName;                                                   
        std::string description;
        std::string author;                                                   
        std::string pageUrl;                                               
        int         source = 0;                                         
        long long   fileSize = 0;
        int         subscriptions = 0;
        void*       previewTexture = nullptr;                               
        bool        previewRequested = false;
        int         previewRetries = 0;                                                                  
        bool        installed = false;
        bool        playable = false;
        std::string installPath;
        std::string mapPath;
        int         progress = -1;                                                                
        std::string status;
    };

    static std::vector<WorkshopItem> WorkshopBrowse;
    static bool        WorkshopBrowseLoading;
    static std::string WorkshopBrowseError;
    static int         WorkshopBrowsePage;
    static int         WorkshopBrowseSort;                                         
    static char        WorkshopBrowseSearch[128];

                                                                              
                                                                                
                                                                          
                                                                              
                                                                                
                                                                                
                                                                              
                                                                      
      
                                                                               
                                                                          
                                                                               
                                       
    static int  WorkshopSource;                                                        
    static int  WorkshopBpMaxId;
    static void OpenWorkshopItemPage(int index);

                                                                            
    static void RefreshWorkshopBrowse(int page);

                                                                              
                                                                                 
                                                                                
                                                                                 
    struct WorkshopInstalledEntry
    {
        std::string path;                           
        std::string name;                         
        std::string mapFile;                                              
        std::string innerMap;                                  
        int         kind = 0;                                      
        long long   size = 0;
        std::string status;
    };
    static std::vector<WorkshopInstalledEntry> WorkshopInstalled;
    static std::string WorkshopInstalledStatus;
                                                                         
                                                                        
    static std::string WorkshopLoadStatus;
    static void RefreshWorkshopInstalled();
    static void ExtractWorkshopInstalled(int index);
    static void DeleteWorkshopInstalled(int index);
                                                                              
                                                              
    static void UpdateWorkshopBrowse();
    static void DownloadWorkshopItem(int index);
                                                                                
                                                                      
    static bool LoadWorkshopItem(int index);
    static void ReleaseWorkshopPreviews();

                                                                             
    static bool ShowPlatformOnScoreboard;
    static bool PovInReplay;
    static void ApplyPovInReplay();

                                                                             
                                                                              
                                             
    static char MatchmakingShieldKeyName[32];
    static int  KeyNameToVk(const std::string& name);
    static void DrawMatchmakingShieldOverlay();

                                                                             
                                                                              
                                                                                
                                                                          
                                                                                 
                                                                                 
                                           
    static std::atomic<int> BackgroundWorkers;

    struct ScopedWorker
    {
        ScopedWorker()  { GameEventHookModule::BackgroundWorkers.fetch_add(1); }
        ~ScopedWorker() { GameEventHookModule::BackgroundWorkers.fetch_sub(1); }
        ScopedWorker(const ScopedWorker&) = delete;
        ScopedWorker& operator=(const ScopedWorker&) = delete;
    };

                                                                              
    static void OpenKingModFolder();
    static std::string GetOperatingSystemName();
    static std::string GetLocalPlatformName();


    static void LoadConfig();
    static void SaveConfig();


private:
    static int findPlayerIndexInGameTickPacket(APlayerController_TA* playerController, const GameTickPacket& gameTickPacket);

};

inline std::vector<UMaterialInstanceConstant*> cachedBodyMICs;
inline std::vector<UMaterialInstanceConstant*> cachedWheelMICs;
inline std::vector<UMaterialInstanceConstant*> cachedBoostMICs;

extern class GameEventHookModule GameEventHook;

                                                                             
                                                                               
                                                                                    
                                             
namespace UITheme
{
    std::vector<std::string> ListPresets();
    bool        SavePreset(const std::string& name);
    bool        LoadPreset(const std::string& name);
    bool        DeletePreset(const std::string& name);
    void        SetFavorite(const std::string& name);
    std::string GetFavorite();
    void        ApplyFavoriteOnStartup();
}

                                                                                        
  
                                                                               
                                                                                
                                                                                
                                                                       
                                                                                
                               
  
               
                                                                                    
namespace ModPresets
{
                                                                           
                                                                     
                                                                            
                                                                   
    enum class FieldType { Bool, Int, Float, Color4, Text, Str };

    struct Field
    {
        const char* key;
        FieldType   type;
        void*       ptr;
        int         textCapacity;               
    };

                                                                             
                                                          
    std::vector<std::string> PageNames();
    std::vector<Field>       PageFields(const std::string& page);

    std::vector<std::string> List(const std::string& page);
    bool        Save(const std::string& page, const std::string& name);
    bool        Load(const std::string& page, const std::string& name);
    bool        Delete(const std::string& page, const std::string& name);
    void        SetFavorite(const std::string& page, const std::string& name);
    std::string GetFavorite(const std::string& page);
    void        ApplyFavoritesOnStartup();
}


