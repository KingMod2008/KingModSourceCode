#pragma once
#include "../Module.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../GamePacket.hpp"
#include "nlohmann/json.hpp"
#include <vector>
#include <string>
#include <array>
#include <functional>
#include <mutex>
#include <unordered_map>

struct OnlineWorkshopMap {
    int id = 0;
    std::string title;
    std::string author;
    std::string downloadUrl;
    std::string previewUrl;
    int downloads = 0;
    float rating = 0.0f;
};

struct CustomMatchPreset
{
    std::string name;
    FCustomMatchSettings settings;
};

class CustomMatchModule : public Module
{
public:
    CustomMatchModule();
    ~CustomMatchModule() override;

    void OnCreate();
    void OnDestroy();

                                                           
    static bool HostCustomMatch(const FCustomMatchSettings& settings, ECustomMatchSettingsType matchType);
    static bool HostLanMatch(const std::string& mapName, int gameModeIndex,
                             int maxPlayers, const std::string& password,
                             const std::string& gameTags);

                                                
    static bool JoinLanMatch();

                                          
    static bool JoinLanMatchByIP(const std::string& ip, const std::string& port,
                                 const std::string& password = "");
                                                                             
                                                                               
                                                                      
    static bool IsLanJoinPasswordSafe(const std::string& password);
    static bool NormalizeLanEndpoint(const std::string& inputHost,
                                     const std::string& inputPort,
                                     std::string& outputHost,
                                     std::string& outputPort);
    static bool StartLanStatusServer(const std::string& port,
                                     const std::string& password);
    static void StopLanStatusServer();
    static bool RequestLanServerStatus(const std::string& host,
                                       const std::string& port,
                                       const std::string& password);
    static void SetLanStatusMatchReady(bool ready);
    static void SynchronizeHostedLanPassword(class AGameEvent_TA* gameEvent);
    static void ApplyHostedLanLoginPassword(const class FString& options,
                                            class FString& errorMessage);
    static bool ShouldBlockHostedLanBots();
    static void EnforceHostedLanBotPolicy(class AGameEvent_TA* gameEvent);

                                           
    static bool JoinPrivateMatch(const FServerReservationData& reservation, const FJoinMatchSettings& joinSettings);

                                     
    static bool SetMutatorValue(const std::string& key, const std::string& value);

                                  
    static std::vector<FDownloadedWorkshopData> GetWorkshopMaps();

                                  
    static bool LoadWorkshopMap(const std::string& fullPath);

                                             
    static bool SetCustomMatchMap(const std::string& workshopMapPath);

                                                      
    static FCustomMatchSettings GetCurrentSettings();

                                             
    static bool ApplySettings(const FCustomMatchSettings& settings);

                             
    static bool StartCustomMatch();

                                 
    static void LeaveCustomMatch();

                                       
    static FUniqueNetId GetPrimaryPlayerID();

                                                   
    static std::string GetDetectedLocalIP();

                                           
    static UGameSettingPlaylist_X* GetPrivateMatchPlaylist();
    static UGameSettingPlaylist_X* GetLanMatchPlaylist();
    static UGameSettingPlaylist_X* GetPlaylistById(int32_t playlistId);
    static std::vector<UGameSettingPlaylist_X*> GetAllPlaylists();

             
    static void LoadConfig();
    static void SaveConfig();
    static std::string ConfigFilePath;

              
    static std::vector<CustomMatchPreset> Presets;
    static void AddPreset(const std::string& name, const FCustomMatchSettings& settings);
    static void RemovePreset(size_t index);
    static void SavePresets();
    static void LoadPresets();

            
    static bool IsInCustomMatch;
    static ECustomMatchSettingsType CurrentMatchType;

                 
    static void Initialize();

                           
    static int SelectedPlaylistIndex;
    static int SelectedGameMode;
    static int SelectedMapIndex;
    static int MaxPlayers;
    static bool PublicMatch;
    static bool ClubServer;
    static std::string ServerName;
    static std::string Password;
    static std::string HostPassword;
    static std::string JoinPassword;
    static std::string GameTags;
    static std::string Team0Name;
    static std::string Team1Name;
    static int Team0ColorPrimary;
    static int Team0ColorSecondary;
    static bool Team0CustomColor;
    static int Team1ColorPrimary;
    static int Team1ColorSecondary;
    static bool Team1CustomColor;
    static int BotDifficulty;
    static int BoostOption;
    static int GameLength;
    static int SeriesLength;

                                                     
    static std::string LanHostIP;
    static std::string LanHostPort;
    static std::string LanJoinIP;
    static std::string LanJoinPort;

    static int  WorkshopLocalMode;
    static int  ServerSessionMode;
    static bool WorkshopUseMap;
    static int  WorkshopArenaIndex;
    static int  WorkshopGameModeIndex;

                               
    static bool Mutator_BallSize;     static float Mutator_BallSizeVal;
    static bool Mutator_BallGravity;  static float Mutator_BallGravityVal;
    static bool Mutator_BallSpeed;    static float Mutator_BallSpeedVal;
    static bool Mutator_BallType;     static int   Mutator_BallTypeIdx;
    static bool Mutator_BallWeight;   static int   Mutator_BallWeightIdx;
    static bool Mutator_BoostAmount;  static int   Mutator_BoostAmountIdx;
    static bool Mutator_BoostStrength;static float Mutator_BoostStrengthVal;
    static bool Mutator_BoostType;    static int   Mutator_BoostTypeIdx;
    static bool Mutator_Demolish;     static int   Mutator_DemolishIdx;
    static bool Mutator_Gravity;      static float Mutator_GravityVal;
    static bool Mutator_GameSpeed;    static float Mutator_GameSpeedVal;
    static bool Mutator_Respawn;      static float Mutator_RespawnVal;
    static bool Mutator_MaxScore;     static int   Mutator_MaxScoreVal;
    static bool Mutator_TimeLimit;    static int   Mutator_TimeLimitVal;
    static bool Mutator_Rumble;       static int   Mutator_RumbleIdx;
    static bool Mutator_Cards;        static int   Mutator_CardsIdx;

                                         
    static std::vector<std::string> MapNames;
    static std::vector<int32_t>     MapGameModes;
    static std::vector<std::string> GameModeNames;
    static void RefreshMapList();
    static FString BuildGameTags();
    static std::string BuildGameTagsString(bool freePlay = false);

    enum HostMutator : size_t
    {
        MatchLength,
        MaxScore,
        Overtime,
        MaxTimeLimit,
        MatchSeries,
        GameSpeed,
        BallMaxSpeed,
        BallType,
        BallGravity,
        BallPhysics,
        BallSize,
        BallBounciness,
        BallCount,
        BoostAmount,
        Rumble,
        BoostStrength,
        WorldGravity,
        Demolish,
        RespawnTime,
        BotLoadouts,
        MatchAudio,
        GameEventRules,
        HostMutatorCount
    };
    static std::array<int, HostMutatorCount> HostMutatorSelections;

                                           
    static void FetchOnlineMapsAsync(int page, std::function<void(std::vector<OnlineWorkshopMap>, int)> callback);
    static void DownloadAndLoadMap(int mapId, const std::string& downloadUrl);
    static void* GetOrLoadTexture(const std::string& url);
    static void PreloadTextures(const std::vector<std::string>& urls);
    static void FetchTotalPagesAsync(std::function<void(int)> callback);

                    
    static std::unordered_map<std::string, void*> TextureCache;
    static std::mutex TextureCacheMutex;
};

extern class CustomMatchModule CustomMatch;
