#include "CustomMatch.hpp"
#include "GameEventHook.hpp"
#include "../../Components/Includes.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../RLSDK/RPC_DISCORD/KingModRPC.hpp"
#include <fstream>
#include <filesystem>
#include <curl/curl.h>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <atomic>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <d3d11.h>
#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../ImGui/blur.hpp"                                                             

                                                                     
                                                                            
#include "../../ImGui/stb_image.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

CustomMatchModule::CustomMatchModule() : Module("CustomMatch", "Custom match hosting and joining", 0xFFFFFFFF) { OnCreate(); }
CustomMatchModule::~CustomMatchModule() { OnDestroy(); }

std::string CustomMatchModule::ConfigFilePath = "KingMod/custom_match.json";
std::vector<CustomMatchPreset> CustomMatchModule::Presets;

                       
int CustomMatchModule::SelectedPlaylistIndex = 0;
int CustomMatchModule::SelectedGameMode = 0;
int CustomMatchModule::SelectedMapIndex = 0;
int CustomMatchModule::MaxPlayers = 8;
bool CustomMatchModule::PublicMatch = false;
bool CustomMatchModule::ClubServer = false;
std::string CustomMatchModule::ServerName = "KingMod Custom";
std::string CustomMatchModule::Password = "";
std::string CustomMatchModule::HostPassword = "";
std::string CustomMatchModule::JoinPassword = "";
std::string CustomMatchModule::GameTags = "";
std::string CustomMatchModule::Team0Name = "Orange";
std::string CustomMatchModule::Team1Name = "Blue";
int CustomMatchModule::Team0ColorPrimary = 0;
int CustomMatchModule::Team0ColorSecondary = 1;
bool CustomMatchModule::Team0CustomColor = false;
int CustomMatchModule::Team1ColorPrimary = 2;
int CustomMatchModule::Team1ColorSecondary = 3;
bool CustomMatchModule::Team1CustomColor = false;
int CustomMatchModule::BotDifficulty = 0;
int CustomMatchModule::BoostOption = 0;
int CustomMatchModule::GameLength = 5;
int CustomMatchModule::SeriesLength = 0;

                                                 
std::string CustomMatchModule::LanHostIP;
std::string CustomMatchModule::LanHostPort = "7777";
std::string CustomMatchModule::LanJoinIP;
std::string CustomMatchModule::LanJoinPort = "7777";
int  CustomMatchModule::WorkshopLocalMode = 0;
int  CustomMatchModule::ServerSessionMode = 0;
bool CustomMatchModule::WorkshopUseMap = true;
int  CustomMatchModule::WorkshopArenaIndex = 0;
int  CustomMatchModule::WorkshopGameModeIndex = 0;
std::array<int, CustomMatchModule::HostMutatorCount> CustomMatchModule::HostMutatorSelections{};

                             
bool CustomMatchModule::Mutator_BallSize = false;     float CustomMatchModule::Mutator_BallSizeVal = 1.0f;
bool CustomMatchModule::Mutator_BallGravity = false; float CustomMatchModule::Mutator_BallGravityVal = 1.0f;
bool CustomMatchModule::Mutator_BallSpeed = false;   float CustomMatchModule::Mutator_BallSpeedVal = 1.0f;
bool CustomMatchModule::Mutator_BallType = false;    int   CustomMatchModule::Mutator_BallTypeIdx = 0;
bool CustomMatchModule::Mutator_BallWeight = false; int   CustomMatchModule::Mutator_BallWeightIdx = 0;
bool CustomMatchModule::Mutator_BoostAmount = false; int   CustomMatchModule::Mutator_BoostAmountIdx = 0;
bool CustomMatchModule::Mutator_BoostStrength = false; float CustomMatchModule::Mutator_BoostStrengthVal = 1.0f;
bool CustomMatchModule::Mutator_BoostType = false;   int   CustomMatchModule::Mutator_BoostTypeIdx = 0;
bool CustomMatchModule::Mutator_Demolish = false;    int   CustomMatchModule::Mutator_DemolishIdx = 0;
bool CustomMatchModule::Mutator_Gravity = false;     float CustomMatchModule::Mutator_GravityVal = 1.0f;
bool CustomMatchModule::Mutator_GameSpeed = false;   float CustomMatchModule::Mutator_GameSpeedVal = 1.0f;
bool CustomMatchModule::Mutator_Respawn = false;     float CustomMatchModule::Mutator_RespawnVal = 3.0f;
bool CustomMatchModule::Mutator_MaxScore = false;    int   CustomMatchModule::Mutator_MaxScoreVal = 0;
bool CustomMatchModule::Mutator_TimeLimit = false;   int   CustomMatchModule::Mutator_TimeLimitVal = 5;
bool CustomMatchModule::Mutator_Rumble = false;      int   CustomMatchModule::Mutator_RumbleIdx = 0;
bool CustomMatchModule::Mutator_Cards = false;       int   CustomMatchModule::Mutator_CardsIdx = 0;

bool CustomMatchModule::IsInCustomMatch = false;
ECustomMatchSettingsType CustomMatchModule::CurrentMatchType = ECustomMatchSettingsType::CustomMatchSettingsType_PrivateMatch;

                                                    
std::vector<std::string> CustomMatchModule::MapNames;
std::vector<int32_t>     CustomMatchModule::MapGameModes;
std::vector<std::string> CustomMatchModule::GameModeNames;

void CustomMatchModule::OnCreate()
{
    LoadConfig();
    LoadPresets();
    Console.Write(GetNameFormatted() + "Initialized!");
}

void CustomMatchModule::Initialize()
{
    LoadConfig();
    LoadPresets();
}

void CustomMatchModule::OnDestroy()
{
    StopLanStatusServer();
    SaveConfig();
    SavePresets();
                                                
    for (auto& kv : TextureCache) {
        if (kv.second)
            reinterpret_cast<ID3D11ShaderResourceView*>(kv.second)->Release();
    }
    TextureCache.clear();
}

namespace
{
    std::atomic<bool> g_LanStatusStop{ false };
    std::atomic<bool> g_LanStatusRunning{ false };
    std::atomic<bool> g_LanStatusMatchReady{ false };
    std::atomic<bool> g_LanStatusPasswordSynchronized{ false };
    std::atomic<bool> g_LanStatusProbeRunning{ false };
    std::atomic<SOCKET> g_LanStatusSocket{ INVALID_SOCKET };
    std::atomic<SOCKET> g_LanStatusProbeSocket{ INVALID_SOCKET };
    std::mutex g_LanStatusPasswordMutex;
    std::string g_LanStatusPassword;
    std::thread g_LanStatusThread;
    std::thread g_LanStatusProbeThread;

                                                                             
    bool IsPtrReadable(const void* ptr, size_t size = sizeof(UObject))
    {
        if (!ptr) return false;
        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQuery(ptr, &mbi, sizeof(mbi)) != sizeof(mbi)) return false;
        if (mbi.State != MEM_COMMIT) return false;
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) return false;
        const uintptr_t begin = reinterpret_cast<uintptr_t>(ptr);
        const uintptr_t end = begin + size;
        const uintptr_t regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        return end >= begin && end <= regionEnd;
    }

                                                                                 
                                                                                  
                                                                             
                                                                                  
                                                                           
                                            
    std::string TrimPassword(const std::string& value)
    {
        size_t begin = 0;
        size_t end = value.size();
        while (begin < end && static_cast<unsigned char>(value[begin]) <= 0x20)
            ++begin;
        while (end > begin && static_cast<unsigned char>(value[end - 1]) <= 0x20)
            --end;
        return value.substr(begin, end - begin);
    }

    bool IsBotGameTag(const std::string& token)
    {
        if (token.size() < 4) return false;
        return std::tolower(static_cast<unsigned char>(token[0])) == 'b' &&
               std::tolower(static_cast<unsigned char>(token[1])) == 'o' &&
               std::tolower(static_cast<unsigned char>(token[2])) == 't' &&
               std::tolower(static_cast<unsigned char>(token[3])) == 's';
    }

    std::string NormalizeBotGameTags(const std::string& tags, int difficulty)
    {
        static const std::array<const char*, 6> botValues = {
            "BotsNone", "BotsIntro", "BotsEasy", "BotsMedium", "BotsHard", "BotsUnfair"
        };
        std::string normalized;
        std::string token;
        std::istringstream input(tags);
        while (std::getline(input, token, ','))
        {
            token.erase(std::remove_if(token.begin(), token.end(),
                [](unsigned char c) { return std::isspace(c); }), token.end());
            if (token.empty() || IsBotGameTag(token)) continue;
            if (!normalized.empty()) normalized += ',';
            normalized += token;
        }
        if (!normalized.empty()) normalized += ',';
        normalized += botValues[std::clamp(difficulty, 0, 5)];
        return normalized;
    }
}

APlayerControllerBase_TA* GetLocalController()
{
    if (auto* lp = Instances.IULocalPlayer()) {
        if (IsPtrReadable(lp) && lp->Actor && IsPtrReadable(lp->Actor) &&
            lp->Actor->Class && IsPtrReadable(lp->Actor->Class) &&
            lp->Actor->IsA<APlayerControllerBase_TA>())
            return static_cast<APlayerControllerBase_TA*>(lp->Actor);
    }

    if (auto* viewport = Instances.GetInstanceOf<UGameViewportClient_TA>()) {
        if (IsPtrReadable(viewport) && viewport->Class && IsPtrReadable(viewport->Class)) {
            if (auto* pc = viewport->GetPrimaryPlayerController())
                if (IsPtrReadable(pc) && pc->Class && IsPtrReadable(pc->Class) &&
                    pc->IsA<APlayerControllerBase_TA>())
                    return pc;
        }
    }

    if (auto* raw = Instances.IAPlayerController()) {
        if (IsPtrReadable(raw) && raw->Class && IsPtrReadable(raw->Class) &&
            raw->IsA<APlayerControllerBase_TA>())
            return static_cast<APlayerControllerBase_TA*>(raw);
    }

    if (auto* pc = Instances.GetInstanceOf<APlayerControllerBase_TA>())
        if (IsPtrReadable(pc) && pc->Class && IsPtrReadable(pc->Class) &&
            pc->IsA<APlayerControllerBase_TA>())
            return pc;

    return nullptr;
}

UGFxData_LanMatch_TA* GetLanMatchData()
{
    if (UGFxData_LanMatch_TA* existing =
            Instances.GetInstanceOf<UGFxData_LanMatch_TA>())
    {
        if (IsPtrReadable(existing) && existing->Class &&
            IsPtrReadable(existing->Class) &&
            existing->IsA<UGFxData_LanMatch_TA>())
            return existing;
    }

    UGFxShell_TA* shell = Instances.GetInstanceOf<UGFxShell_TA>();
    if (!shell || !IsPtrReadable(shell) || !shell->DataStore ||
        !IsPtrReadable(shell->DataStore))
    {
        try
        {
            if (ULocalPlayer* localPlayer = Instances.IULocalPlayer())
                shell = UGFxShell_TA::GetShell(
                    static_cast<ULocalPlayer_X*>(localPlayer));
        }
        catch (...) { shell = nullptr; }
    }
    if (!shell || !IsPtrReadable(shell) || !shell->DataStore ||
        !IsPtrReadable(shell->DataStore))
        return nullptr;

    try
    {
        int placedRow = -1;
        UGFxDataRow_X* row = shell->DataStore->GetObjectW(
            UGFxData_LanMatch_TA::StaticClass(), 0);
        if (!row || !IsPtrReadable(row) || !row->Class ||
            !IsPtrReadable(row->Class) ||
            !row->IsA<UGFxData_LanMatch_TA>())
            row = shell->DataStore->CreateObject(
                UGFxData_LanMatch_TA::StaticClass(), -1, placedRow);
        if (!row || !IsPtrReadable(row) || !row->Class ||
            !IsPtrReadable(row->Class) ||
            !row->IsA<UGFxData_LanMatch_TA>())
            return nullptr;

        UGFxData_LanMatch_TA* lanMatch =
            static_cast<UGFxData_LanMatch_TA*>(row);
        if (!lanMatch->Shell)
        {
            lanMatch->Shell = shell;
            lanMatch->eventOnShellSet();
        }
        return lanMatch;
    }
    catch (...) { return nullptr; }
}

UOnlineGameDedicatedServer_TA* GetDedicatedServer()
{
    if (auto* ge = Instances.GetInstanceOf<AGameEvent_TA>())
        if (IsPtrReadable(ge) && ge->Class && IsPtrReadable(ge->Class))
            return ge->GetOnlineGameDedicatedServer();
    auto* ds = Instances.GetInstanceOf<UOnlineGameDedicatedServer_TA>();
    if (ds && IsPtrReadable(ds) && ds->Class && IsPtrReadable(ds->Class))
        return ds;
    return nullptr;
}

FUniqueNetId CustomMatchModule::GetPrimaryPlayerID()
{
    FUniqueNetId result{};
    try {
        if (auto* ds = GetDedicatedServer())
            result = ds->GetCustomMatchOwner();
        if (result.Uid == 0 && result.EpicAccountId.ToString().empty()) {
            if (auto* online = UGFxShell_TA::GetOnlineGame())
                if (IsPtrReadable(online))
                    result = online->eventGetPrimaryPlayerID();
        }
    } catch (...) {}
    return result;
}

                                                                                  
static std::string DetectLocalIP()
{
    ULONG size = 0;
    GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER, nullptr, nullptr, &size);
    if (size == 0) return "";
    std::vector<uint8_t> buf(size);
    auto* adapters = reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buf.data());
    if (GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER, nullptr, adapters, &size) != NO_ERROR)
        return "";
    for (auto* a = adapters; a; a = a->Next) {
        if (a->OperStatus != IfOperStatusUp) continue;
        std::wstring desc = a->Description ? a->Description : L"";
        if (a->FriendlyName) {
            desc += L" ";
            desc += a->FriendlyName;
        }
        bool isVpn = desc.find(L"TAP") != std::wstring::npos ||
                     desc.find(L"ZeroTier") != std::wstring::npos ||
                     desc.find(L"Hamachi") != std::wstring::npos ||
                     desc.find(L"Tailscale") != std::wstring::npos ||
                     desc.find(L"Radmin") != std::wstring::npos ||
                     desc.find(L"WireGuard") != std::wstring::npos;
        for (auto* ua = a->FirstUnicastAddress; ua; ua = ua->Next) {
            sockaddr_in* sa = reinterpret_cast<sockaddr_in*>(ua->Address.lpSockaddr);
            if (sa->sin_family != AF_INET) continue;
            uint32_t ip = ntohl(sa->sin_addr.S_un.S_addr);
            if ((ip & 0xFF000000) == 0x7F000000) continue;
            if ((ip & 0xFFFF0000) == 0xA9FE0000) continue;
            std::string ipStr = std::to_string((ip >> 24) & 0xFF) + "." +
                               std::to_string((ip >> 16) & 0xFF) + "." +
                               std::to_string((ip >> 8) & 0xFF) + "." +
                               std::to_string(ip & 0xFF);
            if (isVpn) return ipStr;
        }
    }
    for (auto* a = adapters; a; a = a->Next) {
        if (a->OperStatus != IfOperStatusUp) continue;
        for (auto* ua = a->FirstUnicastAddress; ua; ua = ua->Next) {
            sockaddr_in* sa = reinterpret_cast<sockaddr_in*>(ua->Address.lpSockaddr);
            if (sa->sin_family != AF_INET) continue;
            uint32_t ip = ntohl(sa->sin_addr.S_un.S_addr);
            if ((ip & 0xFF000000) == 0x7F000000) continue;
            if ((ip & 0xFFFF0000) == 0xA9FE0000) continue;
            std::string ipStr = std::to_string((ip >> 24) & 0xFF) + "." +
                               std::to_string((ip >> 16) & 0xFF) + "." +
                               std::to_string((ip >> 8) & 0xFF) + "." +
                               std::to_string(ip & 0xFF);
            return ipStr;
        }
    }
    return "";
}

std::string CustomMatchModule::GetDetectedLocalIP()
{
    return DetectLocalIP();
}

                                                                        
std::string CustomMatchModule::BuildGameTagsString(bool freePlay)
{
    static const std::array<std::vector<std::string>, HostMutatorCount> values = {{
        { "", "10Minutes", "20Minutes", "UnlimitedTime" },
        { "", "Max1", "Max3", "Max5", "Max7", "UnlimitedScore" },
        { "", "Overtime5MinutesFirstScore", "Overtime5MinutesRandom" },
        { "", "MaxTime11Minutes" },
        { "", "3Games", "5Games", "7Games" },
        { "", "SloMoGameSpeed", "SloMoDistanceBall" },
        { "", "SlowBall", "FastBall", "SuperFastBall" },
        { "", "Ball_CubeBall", "Ball_Puck", "Ball_BasketBall", "Ball_BeachBall", "Ball_Anniversary", "Ball_Haunted" },
        { "", "LowGravityBall", "HighGravityBall", "SuperGravityBall" },
        { "", "LightBall", "HeavyBall", "SuperLightBall", "MagnusBall", "MagnusBeachBall" },
        { "", "SmallBall", "MediumBall", "BigBall", "GiantBall" },
        { "", "LowBounciness", "HighBounciness", "SuperBounciness" },
        { "", "TwoBalls", "FourBalls", "SixBalls" },
        { "", "NoBooster", "UnlimitedBooster", "SlowRecharge", "RapidRecharge" },
        { "", "ItemsMode", "ItemsModeSlow", "ItemsModeBallManipulators", "ItemsModeCarManipulators", "ItemsModeSprings", "ItemsModeSpikes", "ItemsModeRugby", "ItemsModeHauntedBallBeam", "ItemsModeSelection" },
        { "", "BoostMultiplier1_5x", "BoostMultiplier2x", "BoostMultiplier10x" },
        { "", "LowGravity", "HighGravity", "SuperGravity", "ReverseGravity" },
        { "", "NoDemolish", "DemolishAll", "AlwaysDemolishOpposing", "AlwaysDemolish" },
        { "", "TwoSecondsRespawn", "OneSecondsRespawn", "DisableGoalDelay" },
        { "", "RandomizedBotLoadouts" },
        { "", "HauntedAudio" },
        { "", "HauntedGameEventRules", "RugbyGameEventRules" }
    }};
    static const std::array<const char*, 6> botValues = {
        "BotsNone", "BotsIntro", "BotsEasy", "BotsMedium", "BotsHard", "BotsUnfair"
    };

    std::string tags;
    const auto append = [&tags](const std::string& value)
    {
        if (value.empty()) return;
        if (!tags.empty()) tags += ',';
        tags += value;
    };

    if (freePlay) append("FreePlay");

    if (!GameTags.empty())
    {
        std::string token;
        std::istringstream input(GameTags);
        while (std::getline(input, token, ','))
        {
            token.erase(std::remove_if(token.begin(), token.end(),
                [](unsigned char c) { return std::isspace(c); }), token.end());
            if (!token.empty() && !IsBotGameTag(token) &&
                std::all_of(token.begin(), token.end(),
                    [](unsigned char c) { return std::isalnum(c) || c == '_'; }))
                append(token);
        }
    }

    if (!freePlay)
    {
        for (size_t index = 0; index < values.size(); ++index)
        {
                                                                              
                                                                          
                                                                               
                                                
            const int selected = index == HostMutator::BallCount
                ? 0
                : std::clamp(
                    HostMutatorSelections[index], 0,
                    static_cast<int>(values[index].size()) - 1);
            append(values[index][selected]);
        }
    }

    append(freePlay ? botValues[0] : botValues[std::clamp(BotDifficulty, 0, 5)]);
    return tags;
}

FString CustomMatchModule::BuildGameTags()
{
    const std::string tags = BuildGameTagsString(false);
    return FString(tags.c_str());
}

                                                                 
bool CustomMatchModule::SetMutatorValue(const std::string& key, const std::string& value)
{
    if (key.empty())
        return false;

                                                                          
                                                                              
                          
    Main.Execute([key, value]() {
        try {
            if (auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>()) {
                if (auto* gt = mutators->GameTags) {
                    gt->SetValue(FString(key.c_str()), FString(value.c_str()));
                }
            }
        } catch (...) {}
    });
    return true;                                                              
}

bool CustomMatchModule::HostLanMatch(const std::string& mapName, int gameModeIndex,
                                     int maxPlayers, const std::string& password,
                                     const std::string& gameTags)
{
    if (mapName.empty())
        return false;

    FCustomMatchSettings settings{};
    const std::string normalizedGameTags = NormalizeBotGameTags(gameTags, BotDifficulty);
    settings.GameTags = FString(normalizedGameTags.c_str());
    settings.MapName = FName(mapName.c_str());
    settings.GameMode = static_cast<uint8_t>(std::clamp(gameModeIndex, 0, 6));
    settings.MaxPlayerCount = std::clamp(maxPlayers, 2, 8);
    settings.ServerName = FString(ServerName.empty() ? "KingMod LAN" : ServerName.c_str());
    settings.Password = FString(password.c_str());
    settings.bPublic = false;
    settings.bClubServer = ClubServer;
    settings.TeamSettings[0].Name = FString(Team0Name.c_str());
    settings.TeamSettings[1].Name = FString(Team1Name.c_str());
    settings.TeamSettings[0].Colors.TeamColorID = static_cast<uint8_t>(std::clamp(Team0ColorPrimary, 0, 255));
    settings.TeamSettings[0].Colors.CustomColorID = static_cast<uint8_t>(std::clamp(Team0ColorSecondary, 0, 255));
    settings.TeamSettings[0].Colors.bTeamColorSet = Team0CustomColor;
    settings.TeamSettings[0].Colors.bCustomColorSet = Team0CustomColor;
    settings.TeamSettings[1].Colors.TeamColorID = static_cast<uint8_t>(std::clamp(Team1ColorPrimary, 0, 255));
    settings.TeamSettings[1].Colors.CustomColorID = static_cast<uint8_t>(std::clamp(Team1ColorSecondary, 0, 255));
    settings.TeamSettings[1].Colors.bTeamColorSet = Team1CustomColor;
    settings.TeamSettings[1].Colors.bCustomColorSet = Team1CustomColor;
    return HostCustomMatch(settings, ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch);
}

bool CustomMatchModule::HostCustomMatch(const FCustomMatchSettings& settings, ECustomMatchSettingsType matchType)
{
    Main.Execute([settings, matchType]() {
        try {
            APlayerControllerBase_TA* pc = GetLocalController();
            if (!pc) {
                GameEventHookModule::WorkshopLoadStatus = "LAN host unavailable: no local player controller";
                Main.SpawnNotification("KingMod", "No local player controller", 3);
                return;
            }

            FCustomMatchSettings s = settings;

            auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>();
            if (mutators && IsPtrReadable(mutators)) {
                mutators->InitCustomGameSettings(true);
                mutators->InitMutators(matchType);
            }

                                                        
            if (mutators && IsPtrReadable(mutators)) {
                if (!s.MapName.ToString().empty())
                    mutators->SetSelectedMapName(s.MapName);
                mutators->SetSelectedGameMode((int32_t)s.GameMode);
                mutators->SetSelectedBotDifficulty(std::clamp(BotDifficulty, 0, 5));
                                                          
                if (BoostOption > 0)
                    mutators->SetSelectedBoostOption(BoostOption);
            }

                                                                
            if (mutators && IsPtrReadable(mutators) && mutators->GameTags && IsPtrReadable(mutators->GameTags)) {
                auto* gt = mutators->GameTags;
                auto apply = [&](const char* key, const std::string& val) {
                    gt->SetValue(FString(key), FString(val.c_str()));
                };
                if (Mutator_BallSize)    apply("GAMETAG_BALLSIZE", std::to_string(Mutator_BallSizeVal));
                if (Mutator_BallGravity) apply("GAMETAG_BALLGRAVITY", std::to_string(Mutator_BallGravityVal));
                if (Mutator_BallSpeed)   apply("GAMETAG_BALLSPEED", std::to_string(Mutator_BallSpeedVal));
                if (Mutator_BallType)    apply("GAMETAG_BALLTYPE", std::to_string(Mutator_BallTypeIdx));
                if (Mutator_BallWeight)  apply("GAMETAG_BALLWEIGHT", std::to_string(Mutator_BallWeightIdx));
                if (Mutator_BoostAmount) apply("GAMETAG_BOOSTAMOUNT", std::to_string(Mutator_BoostAmountIdx));
                if (Mutator_BoostStrength) apply("GAMETAG_BOOSTSTRENGTH", std::to_string(Mutator_BoostStrengthVal));
                if (Mutator_BoostType)   apply("GAMETAG_BOOSTTYPE", std::to_string(Mutator_BoostTypeIdx));
                if (Mutator_Demolish)    apply("GAMETAG_DEMOLISH", std::to_string(Mutator_DemolishIdx));
                if (Mutator_Gravity)     apply("GAMETAG_GRAVITY", std::to_string(Mutator_GravityVal));
                if (Mutator_GameSpeed)   apply("GAMETAG_GAMESPEED", std::to_string(Mutator_GameSpeedVal));
                if (Mutator_Respawn)     apply("GAMETAG_RESPAWN", std::to_string(Mutator_RespawnVal));
                if (Mutator_MaxScore)    apply("GAMETAG_GOALS", std::to_string(Mutator_MaxScoreVal));
                if (Mutator_TimeLimit)   apply("GAMETAG_TIME", std::to_string(Mutator_TimeLimitVal));
                if (Mutator_Rumble)      apply("GAMETAG_RUMBLE", std::to_string(Mutator_RumbleIdx));
                if (Mutator_Cards)       apply("GAMETAG_CARDS", std::to_string(Mutator_CardsIdx));

            }

                                                          
                                                                                    
                                                                                               
            if (matchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch) {
                GameEventHookModule::WorkshopLoadStatus = "Starting native LAN match...";
                UGFxData_LanMatch_TA* lanMatch = GetLanMatchData();
                if (!lanMatch || !IsPtrReadable(lanMatch)) {
                    GameEventHookModule::WorkshopLoadStatus =
                        "LAN host unavailable: match data is not ready";
                    Main.SpawnNotification("KingMod", "LAN match data is not ready", 4);
                    return;
                }
                lanMatch->SetCustomMatchSettings(s);
                lanMatch->SetServerName(s.ServerName);
                lanMatch->SetSelectedMaxPlayerCount(s.MaxPlayerCount);
                lanMatch->SetPassword(s.Password);
                lanMatch->CreateMatch();
            } else {
                if (auto* pm = Instances.GetInstanceOf<UGFxData_PrivateMatch_TA>())
                    if (IsPtrReadable(pm))
                        pm->StartSearchWithSettings(s);
                    else {
                        Main.SpawnNotification("KingMod", "Private match UI unavailable", 3);
                        return;
                    }
                else {
                    Main.SpawnNotification("KingMod", "Private match UI unavailable", 3);
                    return;
                }
            }

            CurrentMatchType = matchType;
            IsInCustomMatch = true;
            if (matchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch)
            {
                GameEventHookModule::WorkshopLoadStatus = "LAN host requested on UDP 7777";

                                                                               
                                                                                 
                                                                                 
                std::string rpcHost = LanHostIP.empty() ? GetDetectedLocalIP() : LanHostIP;
                std::string rpcPort = LanHostPort.empty() ? "7777" : LanHostPort;
                if (!rpcHost.empty())
                {
                    LanHostIP = rpcHost;
                    LanHostPort = rpcPort;
                    const std::string rpcServerName = s.ServerName.ToString().empty()
                        ? "KingMod Server" : s.ServerName.ToString();
                    const std::string rpcPassword = s.Password.ToString();
                    if (IsLanJoinPasswordSafe(rpcPassword))
                    {
                        KingModRPC::SetJoinableServer(
                            rpcHost + ":" + rpcPort,
                            rpcPassword,
                            1,
                            std::clamp(static_cast<int>(s.MaxPlayerCount), 2, 8),
                            "Hosting a Rocket League LAN Match",
                            rpcServerName);
                    }
                    else
                    {
                                                                                 
                                                                                 
                        KingModRPC::SetNotJoinable(
                            "Hosting a Rocket League LAN Match",
                            rpcServerName);
                    }
                }
                else
                {
                    KingModRPC::SetNotJoinable(
                        "Hosting a Rocket League LAN Match",
                        "KingMod Server");
                }
            }
            else
            {
                KingModRPC::SetNotJoinable("Playing a Private Match", "KingMod | Rocket League");
            }
            Main.SpawnNotification("KingMod",
                std::string("Custom match started (") +
                (matchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch ? "LAN" : "Private") + ")", 3);
        } catch (const std::exception& e) {
            GameEventHookModule::WorkshopLoadStatus =
                std::string(matchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch
                    ? "LAN host error: " : "Private match error: ") + e.what();
            Main.SpawnNotification("KingMod", std::string("Error: ") + e.what(), 4);
        } catch (...) {
            GameEventHookModule::WorkshopLoadStatus =
                matchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch
                    ? "Failed to start native LAN match"
                    : "Failed to start private match";
            Main.SpawnNotification("KingMod", "Failed to start custom match", 4);
        }
    });
    return true;                              
}

bool CustomMatchModule::JoinLanMatch()
{
    Main.Execute([]() {
        try {
            APlayerControllerBase_TA* pc = GetLocalController();
            if (!pc || !IsPtrReadable(pc)) {
                Main.SpawnNotification("KingMod", "No local player controller", 3);
                return;
            }
            FCustomMatchSettings s{};
            s.bPublic = false;
            pc->StartLanMatch(s);
            Main.SpawnNotification("KingMod", "Searching for LAN matches via VPN...", 3);
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to join LAN match", 4);
        }
    });
    return true;                              
}

bool CustomMatchModule::JoinPrivateMatch(const FServerReservationData& reservation, const FJoinMatchSettings& joinSettings)
{
    Main.Execute([reservation, joinSettings]() {
        try {
            UOnlineGame_X* online = UGFxShell_TA::GetOnlineGame();
            if (!online || !IsPtrReadable(online) || !online->JoinGame || !IsPtrReadable(online->JoinGame)) {
                Main.SpawnNotification("KingMod", "JoinGame system unavailable", 3);
                return;
            }
            FCustomMatchSettings outSettings{};
            if (online->JoinGame->StartJoinPrivateMatch(reservation, joinSettings, outSettings)) {
                IsInCustomMatch = true;
                CurrentMatchType = ECustomMatchSettingsType::CustomMatchSettingsType_PrivateMatch;
                Main.SpawnNotification("KingMod", "Joining private match...", 3);
            } else {
                Main.SpawnNotification("KingMod", "Failed to join private match", 3);
            }
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to join private match", 4);
        }
    });
    return true;                              
}

std::vector<FDownloadedWorkshopData> CustomMatchModule::GetWorkshopMaps()
{
    std::vector<FDownloadedWorkshopData> result;
    try {
        if (auto* workshop = Instances.GetInstanceOf<UGFxData_Workshop_TA>())
            if (IsPtrReadable(workshop)) {
                for (auto& item : workshop->Items)
                    result.push_back(item);
            }
    } catch (...) {}
    return result;
}

bool CustomMatchModule::LoadWorkshopMap(const std::string& fullPath)
{
    if (fullPath.empty())
        return false;

                                                                           
                                                                              
                                                                               
                                            
    Main.Execute([fullPath]() {
        try {
            strncpy_s(GameEventHookModule::WorkshopMapPath,
                      sizeof(GameEventHookModule::WorkshopMapPath),
                      fullPath.c_str(), _TRUNCATE);
            GameEventHookModule::LoadWorkshopMap(
                false, 0, 8, std::string(), std::string(),
                std::string(), std::string(), true);
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to load workshop map", 4);
        }
    });
    return true;                              
}

bool CustomMatchModule::SetCustomMatchMap(const std::string& workshopMapPath)
{
    if (workshopMapPath.empty())
        return false;

    Main.Execute([workshopMapPath]() {
        try {
            if (auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>())
                if (IsPtrReadable(mutators)) {
                    mutators->SetSelectedMapName(FName(workshopMapPath.c_str()));
                    Main.SpawnNotification("KingMod", "Map set to: " + workshopMapPath, 3);
                }
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to set map", 4);
        }
    });
    return true;                              
}

FCustomMatchSettings CustomMatchModule::GetCurrentSettings()
{
    FCustomMatchSettings settings{};
    try {
        if (auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>())
            if (IsPtrReadable(mutators))
                settings = mutators->GetCustomMatchSettings();
    } catch (...) {}
    return settings;
}

bool CustomMatchModule::ApplySettings(const FCustomMatchSettings& settings)
{
    Main.Execute([settings]() {
        try {
            if (auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>())
                if (IsPtrReadable(mutators)) {
                    mutators->SetCustomMatchSettings(const_cast<FCustomMatchSettings&>(settings));
                }
        } catch (...) {}
    });
    return true;                              
}

bool CustomMatchModule::StartCustomMatch()
{
    Main.Execute([]() {
        try {
            APlayerControllerBase_TA* pc = GetLocalController();
            if (!pc || !IsPtrReadable(pc)) return;
            FCustomMatchSettings s{};
            if (CurrentMatchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch) {
                pc->StartLanMatch(s);
            } else {
                if (auto* pm = Instances.GetInstanceOf<UGFxData_PrivateMatch_TA>()) {
                    if (IsPtrReadable(pm))
                        pm->StartSearchWithSettings(s);
                } else {
                    return;
                }
            }
            IsInCustomMatch = true;
            Main.SpawnNotification("KingMod", "Starting custom match...", 3);
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to start custom match", 4);
        }
    });
    return true;                              
}

void CustomMatchModule::LeaveCustomMatch()
{
    Main.Execute([]() {
        try {
            Main.LeaveMatch();
            IsInCustomMatch = false;
            KingModRPC::SetNotJoinable("In Main Menu", "KingMod | Rocket League");
            Main.SpawnNotification("KingMod", "Left custom match", 3);
        } catch (...) {}
    });
}

                                                                         
                                                                           
bool CustomMatchModule::NormalizeLanEndpoint(const std::string& inputHost,
                                              const std::string& inputPort,
                                              std::string& outputHost,
                                              std::string& outputPort)
{
    const auto trim = [](std::string value) {
        const auto first = std::find_if(value.begin(), value.end(), [](unsigned char c) {
            return !std::isspace(c);
        });
        const auto last = std::find_if(value.rbegin(), value.rend(), [](unsigned char c) {
            return !std::isspace(c);
        }).base();
        if (first >= last) return std::string();
        return std::string(first, last);
    };

    outputHost = trim(inputHost);
    outputPort = trim(inputPort);
    if (outputPort.empty()) outputPort = "7777";
    while (!outputHost.empty() && outputHost.back() == '/') outputHost.pop_back();

    if (!outputHost.empty() && outputHost.front() == '[')
    {
        const size_t close = outputHost.find(']');
        if (close == std::string::npos) return false;
        if (close + 1 < outputHost.size())
        {
            if (outputHost[close + 1] != ':') return false;
            outputPort = outputHost.substr(close + 2);
            outputHost.resize(close + 1);
        }
    }
    else
    {
        const size_t firstColon = outputHost.find(':');
        const size_t lastColon = outputHost.rfind(':');
        if (firstColon != std::string::npos && firstColon == lastColon)
        {
            const std::string embeddedPort = outputHost.substr(lastColon + 1);
            if (!embeddedPort.empty() && std::all_of(embeddedPort.begin(), embeddedPort.end(),
                    [](unsigned char c) { return std::isdigit(c); }))
            {
                outputHost.resize(lastColon);
                outputPort = embeddedPort;
            }
        }
        else if (firstColon != std::string::npos)
        {
            outputHost = '[' + outputHost + ']';
        }
    }

    const auto safeHost = [](const std::string& value) {
        if (value.empty() || value.size() > 255) return false;
        return std::all_of(value.begin(), value.end(), [](unsigned char c) {
            return std::isalnum(c) || c == '.' || c == '-' || c == ':' || c == '[' || c == ']';
        });
    };
    if (!safeHost(outputHost) || outputPort.empty() ||
        !std::all_of(outputPort.begin(), outputPort.end(), [](unsigned char c) { return std::isdigit(c); }))
        return false;

    int portNumber = 0;
    try { portNumber = std::stoi(outputPort); }
    catch (...) { return false; }
    return portNumber >= 1 && portNumber <= 65535;
}

void CustomMatchModule::SetLanStatusMatchReady(bool ready)
{
    g_LanStatusMatchReady.store(ready);
}

void CustomMatchModule::SynchronizeHostedLanPassword(AGameEvent_TA* gameEvent)
{
    if (!g_LanStatusRunning.load() || !gameEvent || !IsPtrReadable(gameEvent))
        return;

    try
    {
        g_LanStatusPasswordSynchronized.store(
            gameEvent->ListenServer && IsPtrReadable(gameEvent->ListenServer));
    }
    catch (...)
    {
        g_LanStatusPasswordSynchronized.store(false);
    }
}

void CustomMatchModule::ApplyHostedLanLoginPassword(
    const FString& options,
    FString& errorMessage)
{
    if (!g_LanStatusRunning.load() ||
        !g_LanStatusMatchReady.load())
    {
        return;
    }

    std::string expectedPassword;
    {
        std::lock_guard<std::mutex> lock(g_LanStatusPasswordMutex);
        expectedPassword = g_LanStatusPassword;
    }

    const std::string optionText = options.ToString();
    std::string lowerOptions = optionText;
    std::transform(
        lowerOptions.begin(),
        lowerOptions.end(),
        lowerOptions.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        }
    );

    const std::string key = "password=";
    size_t keyPosition = lowerOptions.find(key);
    bool passwordFound = false;
    bool anyEntryMatches = false;
    std::string suppliedPassword;
    const std::string expectedTrimmed = TrimPassword(expectedPassword);

                                                                           
                                                                          
                                                                           
                                                                       
                                                                
    while (keyPosition != std::string::npos)
    {
        const bool validBoundary =
            keyPosition == 0 ||
            lowerOptions[keyPosition - 1] == '?' ||
            lowerOptions[keyPosition - 1] == '&' ||
            lowerOptions[keyPosition - 1] == '\\';

        if (validBoundary)
        {
            const size_t valueStart = keyPosition + key.size();
            const size_t valueEnd = optionText.find_first_of("?&\\\r\n", valueStart);
            suppliedPassword = optionText.substr(
                valueStart,
                valueEnd == std::string::npos
                    ? std::string::npos
                    : valueEnd - valueStart
            );
            passwordFound = true;

            if (TrimPassword(suppliedPassword) == expectedTrimmed)
            {
                anyEntryMatches = true;
                break;
            }
        }
        keyPosition = lowerOptions.find(key, keyPosition + key.size());
    }

    const std::string suppliedTrimmed = TrimPassword(suppliedPassword);

                                                                              
                                                                         
                                                                            
                                                                                
                                                                                
                                                                               
                                                                                 
                                                                               
                                                                                
    const bool passwordMatches =
        expectedTrimmed.empty()
        ? true
        : (!passwordFound || anyEntryMatches);

    if (!passwordMatches)
    {
        Console.Write(std::string("[KingMod][LAN] AllowPlayerLogin rejected a join: expected '") +
                      expectedTrimmed + "' supplied '" + suppliedTrimmed +
                      "' options '" + optionText + "'");
        const std::string nativeError = errorMessage.ToString();
        if (nativeError.empty())
        {
            errorMessage = FString("Password does not match.");
        }
        return;
    }
}

bool CustomMatchModule::ShouldBlockHostedLanBots()
{
    return BotDifficulty == 0 &&
        (g_LanStatusRunning.load() ||
         (IsInCustomMatch && CurrentMatchType ==
            ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch));
}

void CustomMatchModule::EnforceHostedLanBotPolicy(AGameEvent_TA* gameEvent)
{
    if (!ShouldBlockHostedLanBots() || !gameEvent || !IsPtrReadable(gameEvent))
        return;
    gameEvent->bFillWithAI = false;
}

void CustomMatchModule::StopLanStatusServer()
{
    g_LanStatusStop.store(true);
    const SOCKET socketHandle = g_LanStatusSocket.exchange(INVALID_SOCKET);
    if (socketHandle != INVALID_SOCKET)
    {
        shutdown(socketHandle, SD_BOTH);
        closesocket(socketHandle);
    }
    const SOCKET probeSocket = g_LanStatusProbeSocket.exchange(INVALID_SOCKET);
    if (probeSocket != INVALID_SOCKET)
    {
        shutdown(probeSocket, SD_BOTH);
        closesocket(probeSocket);
    }
    if (g_LanStatusThread.joinable() &&
        g_LanStatusThread.get_id() != std::this_thread::get_id())
        g_LanStatusThread.join();
    if (g_LanStatusProbeThread.joinable() &&
        g_LanStatusProbeThread.get_id() != std::this_thread::get_id())
        g_LanStatusProbeThread.join();
    g_LanStatusMatchReady.store(false);
    g_LanStatusPasswordSynchronized.store(false);
}

bool CustomMatchModule::StartLanStatusServer(const std::string& port,
                                              const std::string& password)
{
    std::string normalizedHost;
    std::string normalizedPort;
    if (!NormalizeLanEndpoint("127.0.0.1", port, normalizedHost, normalizedPort))
        return false;

    int portNumber = 0;
    try { portNumber = std::stoi(normalizedPort); }
    catch (...) { return false; }

    StopLanStatusServer();
    {
        std::lock_guard<std::mutex> lock(g_LanStatusPasswordMutex);
        g_LanStatusPassword = password;
    }
    g_LanStatusStop.store(false);
    g_LanStatusMatchReady.store(false);
    g_LanStatusPasswordSynchronized.store(false);
    g_LanStatusRunning.store(true);

    try
    {
        g_LanStatusThread = std::thread([portNumber]()
        {
            WSADATA data{};
            if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
            {
                g_LanStatusRunning.store(false);
                return;
            }

            SOCKET listenSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
            if (listenSocket == INVALID_SOCKET)
                listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (listenSocket == INVALID_SOCKET)
            {
                WSACleanup();
                g_LanStatusRunning.store(false);
                return;
            }

            BOOL exclusive = TRUE;
            setsockopt(listenSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
                       reinterpret_cast<const char*>(&exclusive), sizeof(exclusive));

            bool bound = false;
            sockaddr_in6 address6{};
            address6.sin6_family = AF_INET6;
            address6.sin6_addr = in6addr_any;
            address6.sin6_port = htons(static_cast<u_short>(portNumber));
            DWORD dualStack = 0;
            setsockopt(listenSocket, IPPROTO_IPV6, IPV6_V6ONLY,
                       reinterpret_cast<const char*>(&dualStack), sizeof(dualStack));
            if (bind(listenSocket, reinterpret_cast<sockaddr*>(&address6), sizeof(address6)) == 0)
                bound = true;

            if (!bound)
            {
                closesocket(listenSocket);
                listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                if (listenSocket != INVALID_SOCKET)
                {
                    setsockopt(listenSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
                               reinterpret_cast<const char*>(&exclusive), sizeof(exclusive));
                    sockaddr_in address4{};
                    address4.sin_family = AF_INET;
                    address4.sin_addr.s_addr = htonl(INADDR_ANY);
                    address4.sin_port = htons(static_cast<u_short>(portNumber));
                    bound = bind(listenSocket, reinterpret_cast<sockaddr*>(&address4), sizeof(address4)) == 0;
                }
            }

            if (!bound || listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
            {
                if (listenSocket != INVALID_SOCKET) closesocket(listenSocket);
                WSACleanup();
                g_LanStatusRunning.store(false);
                if (!g_DllUnloading.load())
                    Main.Execute([]() {
                        Main.SpawnNotification("KingMod", "LAN match started, but TCP status port 7777 is unavailable", 4);
                    });
                return;
            }

            u_long nonBlocking = 1;
            ioctlsocket(listenSocket, FIONBIO, &nonBlocking);
            g_LanStatusSocket.store(listenSocket);

            while (!g_LanStatusStop.load() && !g_DllUnloading.load())
            {
                sockaddr_storage peerAddress{};
                int peerAddressLength = sizeof(peerAddress);
                SOCKET client = accept(listenSocket,
                    reinterpret_cast<sockaddr*>(&peerAddress), &peerAddressLength);
                if (client == INVALID_SOCKET)
                {
                    const int error = WSAGetLastError();
                    if (error == WSAEWOULDBLOCK || error == WSAEINTR)
                    {
                        Sleep(20);
                        continue;
                    }
                    break;
                }

                u_long blocking = 0;
                ioctlsocket(client, FIONBIO, &blocking);
                DWORD timeout = 1500;
                setsockopt(client, SOL_SOCKET, SO_RCVTIMEO,
                           reinterpret_cast<const char*>(&timeout), sizeof(timeout));
                setsockopt(client, SOL_SOCKET, SO_SNDTIMEO,
                           reinterpret_cast<const char*>(&timeout), sizeof(timeout));

                char requestBuffer[256]{};
                const int received = recv(client, requestBuffer,
                                          static_cast<int>(sizeof(requestBuffer) - 1), 0);
                std::string response = "KINGMOD|INVALID_REQUEST";
                if (received > 0)
                {
                    const std::string request(requestBuffer, static_cast<size_t>(received));
                    const std::string prefix = "KINGMOD_STATUS|";
                    if (request.rfind(prefix, 0) == 0)
                    {
                        const std::string suppliedPassword = request.substr(prefix.size());
                        std::string expectedPassword;
                        {
                            std::lock_guard<std::mutex> lock(g_LanStatusPasswordMutex);
                            expectedPassword = g_LanStatusPassword;
                        }
                        const bool passwordMatches =
                            TrimPassword(suppliedPassword) == TrimPassword(expectedPassword);
                        response = passwordMatches
                            ? (g_LanStatusMatchReady.load()
                                ? "KINGMOD|READY" : "KINGMOD|STARTING")
                            : "KINGMOD|PASSWORD_MISMATCH";

                        char peerHost[NI_MAXHOST]{};
                        std::string requester = "unknown address";
                        if (getnameinfo(reinterpret_cast<sockaddr*>(&peerAddress),
                                peerAddressLength, peerHost, sizeof(peerHost),
                                nullptr, 0, NI_NUMERICHOST) == 0)
                            requester = peerHost;
                        if (!g_DllUnloading.load())
                            Main.Execute([requester, passwordMatches]() {
                                Main.SpawnNotification("KingMod Server",
                                    "Status request from " + requester +
                                    (passwordMatches ? " (password matched)" : " (wrong password)"), 4);
                            });
                    }
                }
                send(client, response.data(), static_cast<int>(response.size()), 0);
                shutdown(client, SD_BOTH);
                closesocket(client);
            }

            SOCKET expected = listenSocket;
            if (g_LanStatusSocket.compare_exchange_strong(expected, INVALID_SOCKET))
                closesocket(listenSocket);
            WSACleanup();
            g_LanStatusRunning.store(false);
        });
    }
    catch (...)
    {
        g_LanStatusRunning.store(false);
        return false;
    }
    return true;
}

bool CustomMatchModule::RequestLanServerStatus(const std::string& host,
                                                const std::string& port,
                                                const std::string& password)
{
    std::string normalizedHost;
    std::string normalizedPort;
    if (!NormalizeLanEndpoint(host, port, normalizedHost, normalizedPort))
        return false;
    bool expected = false;
    if (!g_LanStatusProbeRunning.compare_exchange_strong(expected, true))
        return false;

    try
    {
        if (g_LanStatusProbeThread.joinable())
            g_LanStatusProbeThread.join();
        g_LanStatusProbeThread = std::thread([normalizedHost, normalizedPort, password]()
        {
            std::string resultMessage = "No KingMod status response; check the address and TCP port";
            WSADATA data{};
            if (WSAStartup(MAKEWORD(2, 2), &data) == 0)
            {
                std::string lookupHost = normalizedHost;
                if (lookupHost.size() > 2 && lookupHost.front() == '[' && lookupHost.back() == ']')
                    lookupHost = lookupHost.substr(1, lookupHost.size() - 2);

                addrinfo hints{};
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;
                addrinfo* addresses = nullptr;
                if (getaddrinfo(lookupHost.c_str(), normalizedPort.c_str(), &hints, &addresses) == 0)
                {
                    SOCKET connectedSocket = INVALID_SOCKET;
                    for (addrinfo* address = addresses;
                         address && connectedSocket == INVALID_SOCKET &&
                         !g_LanStatusStop.load() && !g_DllUnloading.load();
                         address = address->ai_next)
                    {
                        SOCKET candidate = socket(address->ai_family, address->ai_socktype,
                                                  address->ai_protocol);
                        if (candidate == INVALID_SOCKET) continue;
                        g_LanStatusProbeSocket.store(candidate);
                        u_long nonBlocking = 1;
                        ioctlsocket(candidate, FIONBIO, &nonBlocking);
                        const int connectResult = connect(candidate, address->ai_addr,
                                                          static_cast<int>(address->ai_addrlen));
                        if (connectResult == 0 || WSAGetLastError() == WSAEWOULDBLOCK)
                        {
                            fd_set writeSet;
                            fd_set errorSet;
                            FD_ZERO(&writeSet);
                            FD_ZERO(&errorSet);
                            FD_SET(candidate, &writeSet);
                            FD_SET(candidate, &errorSet);
                            timeval timeout{};
                            timeout.tv_sec = 2;
                            if (select(0, nullptr, &writeSet, &errorSet, &timeout) > 0 &&
                                FD_ISSET(candidate, &writeSet) && !FD_ISSET(candidate, &errorSet))
                            {
                                int socketError = 0;
                                int errorLength = sizeof(socketError);
                                if (getsockopt(candidate, SOL_SOCKET, SO_ERROR,
                                               reinterpret_cast<char*>(&socketError), &errorLength) == 0 &&
                                    socketError == 0)
                                    connectedSocket = candidate;
                            }
                        }
                        if (connectedSocket != candidate)
                        {
                            SOCKET expectedSocket = candidate;
                            if (g_LanStatusProbeSocket.compare_exchange_strong(
                                    expectedSocket, INVALID_SOCKET))
                                closesocket(candidate);
                        }
                    }
                    freeaddrinfo(addresses);

                    if (connectedSocket != INVALID_SOCKET)
                    {
                        u_long blocking = 0;
                        ioctlsocket(connectedSocket, FIONBIO, &blocking);
                        DWORD timeout = 2000;
                        setsockopt(connectedSocket, SOL_SOCKET, SO_RCVTIMEO,
                                   reinterpret_cast<const char*>(&timeout), sizeof(timeout));
                        const std::string request = "KINGMOD_STATUS|" + password;
                        if (send(connectedSocket, request.data(), static_cast<int>(request.size()), 0) > 0)
                        {
                            char responseBuffer[256]{};
                            const int received = recv(connectedSocket, responseBuffer,
                                                      static_cast<int>(sizeof(responseBuffer) - 1), 0);
                            if (received > 0)
                            {
                                const std::string response(responseBuffer, static_cast<size_t>(received));
                                if (response == "KINGMOD|READY")
                                    resultMessage = "Host is reachable, match is ready, and password matches";
                                else if (response == "KINGMOD|STARTING")
                                    resultMessage = "Host is reachable and password matches; match is still starting";
                                else if (response == "KINGMOD|PASSWORD_MISMATCH")
                                    resultMessage = "Host is reachable, but the password does not match";
                                else
                                    resultMessage = "A service answered, but it is not a KingMod LAN host";
                            }
                        }
                        SOCKET expectedSocket = connectedSocket;
                        if (g_LanStatusProbeSocket.compare_exchange_strong(
                                expectedSocket, INVALID_SOCKET))
                        {
                            shutdown(connectedSocket, SD_BOTH);
                            closesocket(connectedSocket);
                        }
                    }
                }
                WSACleanup();
            }

            if (!g_DllUnloading.load())
                Main.Execute([resultMessage]() {
                    Main.SpawnNotification("KingMod Server Test", resultMessage, 5);
                });
            g_LanStatusProbeRunning.store(false);
        });
    }
    catch (...)
    {
        g_LanStatusProbeRunning.store(false);
        return false;
    }
    return true;
}

bool CustomMatchModule::IsLanJoinPasswordSafe(const std::string& password)
{
    return password.size() <= 64 &&
        std::all_of(password.begin(), password.end(), [](unsigned char c) {
            return std::isalnum(c) || c == '_' || c == '-' || c == '.';
        });
}

bool CustomMatchModule::JoinLanMatchByIP(const std::string& ip, const std::string& port,
                                         const std::string& password)
{
    std::string normalizedHost;
    std::string normalizedPort;
    if (!NormalizeLanEndpoint(ip, port, normalizedHost, normalizedPort))
        return false;
    if (!IsLanJoinPasswordSafe(password))
        return false;

    KingModRPC::SetNotJoinable(
        "Connecting to " + normalizedHost + ":" + normalizedPort,
        "KingMod | LAN Join");

    Main.Execute([normalizedHost, normalizedPort, password]() {
        try {
            std::string command = "start " + normalizedHost + ":" + normalizedPort + "/?Lan";
            if (!password.empty())
                command += "?Password=" + password;

            bool sent = false;
            try {
                if (AActor* actor = Instances.GetDefaultInstanceOf<AActor>()) {
                    actor->ConsoleCommand(Format::ToFString(command), 0);
                    sent = true;
                }
            } catch (...) {}

            if (!sent) {
                try {
                    if (APlayerController* controller = Instances.IAPlayerController()) {
                        controller->ConsoleCommand(Format::ToFString(command), false);
                        sent = true;
                    }
                } catch (...) {}
            }

            if (!sent) {
                try {
                    if (UGameViewportClient_TA* viewport =
                            Instances.GetInstanceOf<UGameViewportClient_TA>()) {
                        viewport->ConsoleCommand(Format::ToFString(command));
                        sent = true;
                    }
                } catch (...) {}
            }

            Main.SpawnNotification("KingMod",
                sent ? "Connecting to " + normalizedHost + ":" + normalizedPort + "..."
                     : "No game console is available yet",
                sent ? 3 : 4);
        } catch (...) {
            Main.SpawnNotification("KingMod", "Failed to connect to LAN match", 4);
        }
    });
    return true;                              
}

                                                                           
void CustomMatchModule::RefreshMapList()
{
    MapNames.clear();
    MapGameModes.clear();
    GameModeNames.clear();
    try {
        if (auto* mutators = Instances.GetInstanceOf<UGFxData_Mutators_TA>())
            if (IsPtrReadable(mutators)) {
                for (auto& gm : mutators->GameModes) {
                    GameModeNames.push_back(gm.LocalizedName.ToString());
                }
                if (auto* online = UGFxShell_TA::GetOnlineGame())
                    if (IsPtrReadable(online) && online->Playlists && IsPtrReadable(online->Playlists)) {
                        for (auto* pl : online->Playlists->DownloadedPlaylists) {
                            if (!pl || !IsPtrReadable(pl)) continue;
                                                                                    
                            MapNames.push_back(pl->Title.ToString());
                            MapGameModes.push_back(0);
                        }
                    }
            }
    } catch (...) {}
}

UGameSettingPlaylist_X* CustomMatchModule::GetPrivateMatchPlaylist()
{
    try {
        if (auto* online = UGFxShell_TA::GetOnlineGame())
            if (IsPtrReadable(online) && online->Playlists && IsPtrReadable(online->Playlists))
                return online->Playlists->GetPrivateMatch();
    } catch (...) {}
    return nullptr;
}

UGameSettingPlaylist_X* CustomMatchModule::GetLanMatchPlaylist()
{
    try {
        if (auto* online = UGFxShell_TA::GetOnlineGame())
            if (IsPtrReadable(online) && online->Playlists && IsPtrReadable(online->Playlists))
                return online->Playlists->GetLanMatch();
    } catch (...) {}
    return nullptr;
}

UGameSettingPlaylist_X* CustomMatchModule::GetPlaylistById(int32_t playlistId)
{
    try {
        if (auto* online = UGFxShell_TA::GetOnlineGame())
            if (IsPtrReadable(online) && online->Playlists && IsPtrReadable(online->Playlists))
                return online->Playlists->GetPlaylistByID(playlistId);
    } catch (...) {}
    return nullptr;
}

std::vector<UGameSettingPlaylist_X*> CustomMatchModule::GetAllPlaylists()
{
    std::vector<UGameSettingPlaylist_X*> result;
    try {
        if (auto* online = UGFxShell_TA::GetOnlineGame())
            if (IsPtrReadable(online) && online->Playlists && IsPtrReadable(online->Playlists))
                for (auto* pl : online->Playlists->DownloadedPlaylists)
                    if (pl && IsPtrReadable(pl)) result.push_back(pl);
    } catch (...) {}
    return result;
}

void CustomMatchModule::LoadConfig()
{
    try {
        std::ifstream file(ConfigFilePath);
        if (file.is_open()) {
            nlohmann::json j;
            file >> j;
            ServerName = j.value("ServerName", "KingMod Custom");
            Password = j.value("Password", "");
            HostPassword = j.value("HostPassword", "");
            JoinPassword = j.value("JoinPassword", "");
            Password = HostPassword;
            GameTags = j.value("GameTags", "");
            MaxPlayers = j.value("MaxPlayers", 8);
            PublicMatch = j.value("PublicMatch", false);
            ClubServer = j.value("ClubServer", false);
            Team0Name = j.value("Team0Name", "Orange");
            Team1Name = j.value("Team1Name", "Blue");
            Team0ColorPrimary = j.value("Team0ColorPrimary", 0);
            Team0ColorSecondary = j.value("Team0ColorSecondary", 1);
            Team0CustomColor = j.value("Team0CustomColor", false);
            Team1ColorPrimary = j.value("Team1ColorPrimary", 2);
            Team1ColorSecondary = j.value("Team1ColorSecondary", 3);
            Team1CustomColor = j.value("Team1CustomColor", false);
            BotDifficulty = j.value("BotDifficulty", 0);
            BoostOption = j.value("BoostOption", 0);
            GameLength = j.value("GameLength", 5);
            SeriesLength = j.value("SeriesLength", 0);
            LanHostIP = j.value("LanHostIP", "");
            LanHostPort = j.value("LanHostPort", "7777");
            LanJoinIP = j.value("LanJoinIP", "");
            LanJoinPort = j.value("LanJoinPort", "7777");
            const int legacySessionMode = std::clamp(j.value("WorkshopSessionMode", 0), 0, 2);
            WorkshopLocalMode = std::clamp(j.value("WorkshopLaunchMode", 0), 0, 1);
            ServerSessionMode = std::clamp(j.value("ServerSessionMode", legacySessionMode == 2 ? 1 : 0), 0, 1);
            WorkshopUseMap = j.value("WorkshopUseMap", true);
            WorkshopArenaIndex = std::clamp(j.value("WorkshopArenaIndex", 0), 0, 64);
            WorkshopGameModeIndex = std::clamp(j.value("WorkshopGameModeIndex", 0), 0, 6);
            if (j.contains("HostMutatorSelections") && j["HostMutatorSelections"].is_array()) {
                const auto& savedMutators = j["HostMutatorSelections"];
                const size_t count = (std::min)(savedMutators.size(), HostMutatorSelections.size());
                for (size_t index = 0; index < count; ++index)
                    HostMutatorSelections[index] = savedMutators[index].get<int>();
            }
                                                                  
            HostMutatorSelections[HostMutator::BallCount] = 0;
            MaxPlayers = std::clamp(MaxPlayers, 2, 8);
            if (LanHostPort.empty()) LanHostPort = "7777";
            if (LanJoinPort.empty()) LanJoinPort = "7777";
            Mutator_BallSize = j.value("Mutator_BallSize", false);
            Mutator_BallSizeVal = j.value("Mutator_BallSizeVal", 1.0f);
            Mutator_BallGravity = j.value("Mutator_BallGravity", false);
            Mutator_BallGravityVal = j.value("Mutator_BallGravityVal", 1.0f);
            Mutator_BallSpeed = j.value("Mutator_BallSpeed", false);
            Mutator_BallSpeedVal = j.value("Mutator_BallSpeedVal", 1.0f);
            Mutator_BallType = j.value("Mutator_BallType", false);
            Mutator_BallTypeIdx = j.value("Mutator_BallTypeIdx", 0);
            Mutator_BallWeight = j.value("Mutator_BallWeight", false);
            Mutator_BallWeightIdx = j.value("Mutator_BallWeightIdx", 0);
            Mutator_BoostAmount = j.value("Mutator_BoostAmount", false);
            Mutator_BoostAmountIdx = j.value("Mutator_BoostAmountIdx", 0);
            Mutator_BoostStrength = j.value("Mutator_BoostStrength", false);
            Mutator_BoostStrengthVal = j.value("Mutator_BoostStrengthVal", 1.0f);
            Mutator_BoostType = j.value("Mutator_BoostType", false);
            Mutator_BoostTypeIdx = j.value("Mutator_BoostTypeIdx", 0);
            Mutator_Demolish = j.value("Mutator_Demolish", false);
            Mutator_DemolishIdx = j.value("Mutator_DemolishIdx", 0);
            Mutator_Gravity = j.value("Mutator_Gravity", false);
            Mutator_GravityVal = j.value("Mutator_GravityVal", 1.0f);
            Mutator_GameSpeed = j.value("Mutator_GameSpeed", false);
            Mutator_GameSpeedVal = j.value("Mutator_GameSpeedVal", 1.0f);
            Mutator_Respawn = j.value("Mutator_Respawn", false);
            Mutator_RespawnVal = j.value("Mutator_RespawnVal", 3.0f);
            Mutator_MaxScore = j.value("Mutator_MaxScore", false);
            Mutator_MaxScoreVal = j.value("Mutator_MaxScoreVal", 0);
            Mutator_TimeLimit = j.value("Mutator_TimeLimit", false);
            Mutator_TimeLimitVal = j.value("Mutator_TimeLimitVal", 5);
            Mutator_Rumble = j.value("Mutator_Rumble", false);
            Mutator_RumbleIdx = j.value("Mutator_RumbleIdx", 0);
            Mutator_Cards = j.value("Mutator_Cards", false);
            Mutator_CardsIdx = j.value("Mutator_CardsIdx", 0);
            file.close();
        }
    } catch (...) {}
}

void CustomMatchModule::SaveConfig()
{
    try {
        std::filesystem::create_directories("KingMod");
        nlohmann::json j;
        Password = HostPassword;
        j["ServerName"] = ServerName;
        j["Password"] = HostPassword;
        j["HostPassword"] = HostPassword;
        j["JoinPassword"] = JoinPassword;
        j["GameTags"] = GameTags;
        j["MaxPlayers"] = MaxPlayers;
        j["PublicMatch"] = PublicMatch;
        j["ClubServer"] = ClubServer;
        j["Team0Name"] = Team0Name;
        j["Team1Name"] = Team1Name;
        j["Team0ColorPrimary"] = Team0ColorPrimary;
        j["Team0ColorSecondary"] = Team0ColorSecondary;
        j["Team0CustomColor"] = Team0CustomColor;
        j["Team1ColorPrimary"] = Team1ColorPrimary;
        j["Team1ColorSecondary"] = Team1ColorSecondary;
        j["Team1CustomColor"] = Team1CustomColor;
        j["BotDifficulty"] = BotDifficulty;
        j["BoostOption"] = BoostOption;
        j["GameLength"] = GameLength;
        j["SeriesLength"] = SeriesLength;
        j["LanHostIP"] = LanHostIP;
        j["LanHostPort"] = LanHostPort;
        j["LanJoinIP"] = LanJoinIP;
        j["LanJoinPort"] = LanJoinPort;
        j["WorkshopLocalMode"] = WorkshopLocalMode;
        j["WorkshopLaunchMode"] = WorkshopLocalMode;
        j["ServerSessionMode"] = ServerSessionMode;
        j["WorkshopUseMap"] = WorkshopUseMap;
        j["WorkshopArenaIndex"] = WorkshopArenaIndex;
        j["WorkshopGameModeIndex"] = WorkshopGameModeIndex;
        HostMutatorSelections[HostMutator::BallCount] = 0;
        j["HostMutatorSelections"] = HostMutatorSelections;
        j["Mutator_BallSize"] = Mutator_BallSize;
        j["Mutator_BallSizeVal"] = Mutator_BallSizeVal;
        j["Mutator_BallGravity"] = Mutator_BallGravity;
        j["Mutator_BallGravityVal"] = Mutator_BallGravityVal;
        j["Mutator_BallSpeed"] = Mutator_BallSpeed;
        j["Mutator_BallSpeedVal"] = Mutator_BallSpeedVal;
        j["Mutator_BallType"] = Mutator_BallType;
        j["Mutator_BallTypeIdx"] = Mutator_BallTypeIdx;
        j["Mutator_BallWeight"] = Mutator_BallWeight;
        j["Mutator_BallWeightIdx"] = Mutator_BallWeightIdx;
        j["Mutator_BoostAmount"] = Mutator_BoostAmount;
        j["Mutator_BoostAmountIdx"] = Mutator_BoostAmountIdx;
        j["Mutator_BoostStrength"] = Mutator_BoostStrength;
        j["Mutator_BoostStrengthVal"] = Mutator_BoostStrengthVal;
        j["Mutator_BoostType"] = Mutator_BoostType;
        j["Mutator_BoostTypeIdx"] = Mutator_BoostTypeIdx;
        j["Mutator_Demolish"] = Mutator_Demolish;
        j["Mutator_DemolishIdx"] = Mutator_DemolishIdx;
        j["Mutator_Gravity"] = Mutator_Gravity;
        j["Mutator_GravityVal"] = Mutator_GravityVal;
        j["Mutator_GameSpeed"] = Mutator_GameSpeed;
        j["Mutator_GameSpeedVal"] = Mutator_GameSpeedVal;
        j["Mutator_Respawn"] = Mutator_Respawn;
        j["Mutator_RespawnVal"] = Mutator_RespawnVal;
        j["Mutator_MaxScore"] = Mutator_MaxScore;
        j["Mutator_MaxScoreVal"] = Mutator_MaxScoreVal;
        j["Mutator_TimeLimit"] = Mutator_TimeLimit;
        j["Mutator_TimeLimitVal"] = Mutator_TimeLimitVal;
        j["Mutator_Rumble"] = Mutator_Rumble;
        j["Mutator_RumbleIdx"] = Mutator_RumbleIdx;
        j["Mutator_Cards"] = Mutator_Cards;
        j["Mutator_CardsIdx"] = Mutator_CardsIdx;
        std::ofstream file(ConfigFilePath);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        }
    } catch (...) {}
}

void CustomMatchModule::AddPreset(const std::string& name, const FCustomMatchSettings& settings)
{
    Presets.push_back({ name, settings });
    SavePresets();
}

void CustomMatchModule::RemovePreset(size_t index)
{
    if (index < Presets.size()) {
        Presets.erase(Presets.begin() + index);
        SavePresets();
    }
}

void CustomMatchModule::SavePresets()
{
    try {
        std::filesystem::create_directories("KingMod");
        nlohmann::json j = nlohmann::json::array();
        for (auto& preset : Presets) {
            nlohmann::json p;
            p["name"] = preset.name;
            p["GameTags"] = preset.settings.GameTags.ToString();
            p["MapName"] = preset.settings.MapName.ToString();
            p["GameMode"] = (int)preset.settings.GameMode;
            p["MaxPlayerCount"] = preset.settings.MaxPlayerCount;
            p["ServerName"] = preset.settings.ServerName.ToString();
            p["Password"] = preset.settings.Password.ToString();
            p["bPublic"] = (bool)preset.settings.bPublic;
            p["bClubServer"] = (bool)preset.settings.bClubServer;
            p["Team0Name"] = preset.settings.TeamSettings[0].Name.ToString();
            p["Team1Name"] = preset.settings.TeamSettings[1].Name.ToString();
            j.push_back(p);
        }
        std::ofstream file("KingMod/custom_match_presets.json");
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        }
    } catch (...) {}
}

void CustomMatchModule::LoadPresets()
{
    try {
        std::ifstream file("KingMod/custom_match_presets.json");
        if (file.is_open()) {
            nlohmann::json j;
            file >> j;
            Presets.clear();
            for (auto& p : j) {
                CustomMatchPreset preset;
                preset.name = p.value("name", "Preset");
                preset.settings.GameTags = FString(p.value("GameTags", "").c_str());
                preset.settings.MapName = FName(p.value("MapName", "").c_str());
                preset.settings.GameMode = (uint8_t)p.value("GameMode", 0);
                preset.settings.MaxPlayerCount = p.value("MaxPlayerCount", 8);
                preset.settings.ServerName = FString(p.value("ServerName", "KingMod Custom").c_str());
                preset.settings.Password = FString(p.value("Password", "").c_str());
                preset.settings.bPublic = p.value("bPublic", false);
                preset.settings.bClubServer = p.value("bClubServer", false);
                preset.settings.TeamSettings[0].Name = FString(p.value("Team0Name", "Orange").c_str());
                preset.settings.TeamSettings[1].Name = FString(p.value("Team1Name", "Blue").c_str());
                Presets.push_back(preset);
            }
            file.close();
        }
    } catch (...) {}
}

                                               
                         
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

                                                
static int FetchTotalPages() {
    CURL* curl = curl_easy_init();
    if (!curl) return 0;

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://bakkesplugins.com/api/maps?page=1");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "KingMod/1.0");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) return 0;

    try {
        auto j = nlohmann::json::parse(response);
        return j.value("last_page", 1);
    } catch (...) {
        return 1;
    }
}

                              
static std::vector<OnlineWorkshopMap> FetchOnlineMapsPage(int page, int& outTotalPages) {
    std::vector<OnlineWorkshopMap> result;
    CURL* curl = curl_easy_init();
    if (!curl) return result;

    std::string url = "https://bakkesplugins.com/api/maps?page=" + std::to_string(page);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "KingMod/1.0");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) return result;

    try {
        auto j = nlohmann::json::parse(response);
        outTotalPages = j.value("last_page", 1);
        auto data = j.value("data", nlohmann::json::array());

        for (auto& item : data) {
            OnlineWorkshopMap map;
            map.id = item.value("id", 0);
            map.title = item.value("name", "Unknown");
            map.author = item.value("author", "Unknown");
            map.downloads = item.value("downloads", 0);
            map.rating = item.value("rating", 0.0f);

                           
            if (item.contains("download_url")) {
                map.downloadUrl = item["download_url"].get<std::string>();
            } else {
                map.downloadUrl = "https://bakkesplugins.com/maps/" + std::to_string(map.id) + "/download";
            }

                            
            if (item.contains("preview_image")) {
                map.previewUrl = item["preview_image"].get<std::string>();
            }

            if (map.id > 0) result.push_back(std::move(map));
        }
    } catch (...) {}

    return result;
}

              
void CustomMatchModule::FetchOnlineMapsAsync(int page, std::function<void(std::vector<OnlineWorkshopMap>, int)> callback) {
    std::thread([page, callback]() {
        if (g_DllUnloading.load()) return;
        int totalPages = 0;
        auto maps = FetchOnlineMapsPage(page, totalPages);
        if (g_DllUnloading.load()) return;
        Main.Execute([maps = std::move(maps), totalPages, callback]() mutable {
            callback(std::move(maps), totalPages);
        });
    }).detach();
}

void CustomMatchModule::FetchTotalPagesAsync(std::function<void(int)> callback) {
    std::thread([callback]() {
        if (g_DllUnloading.load()) return;
        int pages = FetchTotalPages();
        if (g_DllUnloading.load()) return;
        Main.Execute([pages, callback]() {
            callback(pages);
        });
    }).detach();
}

                          
void CustomMatchModule::DownloadAndLoadMap(int mapId, const std::string& downloadUrl) {
    Main.SpawnNotification("KingMod", "Downloading map " + std::to_string(mapId) + "...", 3);

    std::thread([mapId, downloadUrl]() {
        if (g_DllUnloading.load()) return;
        CURL* curl = curl_easy_init();
        if (!curl) {
            if (!g_DllUnloading.load()) Main.Execute([]() {
                Main.SpawnNotification("KingMod", "Download failed: curl init failed", 4);
            });
            return;
        }

        std::string savePath = "KingMod/workshop_maps/map_" + std::to_string(mapId) + ".zip";
        std::filesystem::create_directories("KingMod/workshop_maps");

        FILE* fp = nullptr;
        errno_t err = fopen_s(&fp, savePath.c_str(), "wb");
        if (err != 0 || !fp) {
            curl_easy_cleanup(curl);
            if (!g_DllUnloading.load()) Main.Execute([]() {
                Main.SpawnNotification("KingMod", "Download failed: cannot create file", 4);
            });
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, downloadUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "KingMod/1.0");

        CURLcode res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            if (!g_DllUnloading.load()) Main.Execute([]() {
                Main.SpawnNotification("KingMod", "Download failed: network error", 4);
            });
            return;
        }

        if (g_DllUnloading.load()) return;

                      
        Main.Execute([savePath, mapId]() {
            try {
                                                                             
                std::string extractDir = "KingMod/workshop_maps/map_" + std::to_string(mapId);
                std::filesystem::create_directories(extractDir);

                std::string cmd = "powershell -Command \"Expand-Archive -Path '" + savePath + "' -DestinationPath '" + extractDir + "' -Force\"";
                system(cmd.c_str());

                                     
                for (auto& entry : std::filesystem::recursive_directory_iterator(extractDir)) {
                    if (entry.path().extension() == ".upk" || entry.path().extension() == ".udk") {
                        CustomMatchModule::LoadWorkshopMap(entry.path().string());
                        CustomMatchModule::SetCustomMatchMap(entry.path().string());
                        if (!g_DllUnloading.load())
                            Main.SpawnNotification("KingMod", "Map loaded successfully!", 3);
                        return;
                    }
                }
                if (!g_DllUnloading.load())
                    Main.SpawnNotification("KingMod", "Map downloaded but no .upk found", 4);
            } catch (...) {
                if (!g_DllUnloading.load())
                    Main.SpawnNotification("KingMod", "Failed to extract/load map", 4);
            }
        });
    }).detach();
}

                                                                                         
static void* BuildMapTexture(ID3D11Device* dev, const std::vector<uint8_t>& rgba, uint32_t w, uint32_t h)
{
    if (!dev || w == 0 || h == 0 || rgba.size() < static_cast<size_t>(w) * h * 4)
        return nullptr;

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = w;
    td.Height = h;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = rgba.data();
    sd.SysMemPitch = w * 4;

    ID3D11Texture2D* tex = nullptr;
    if (FAILED(dev->CreateTexture2D(&td, &sd, &tex)))
        return nullptr;

    ID3D11ShaderResourceView* srv = nullptr;
    if (FAILED(dev->CreateShaderResourceView(tex, nullptr, &srv))) {
        tex->Release();
        return nullptr;
    }
    tex->Release();
    return srv;
}

                                                                            
                                                           
void* CustomMatchModule::GetOrLoadTexture(const std::string& url) {
    std::lock_guard<std::mutex> lock(TextureCacheMutex);
    auto it = TextureCache.find(url);
    if (it != TextureCache.end())
        return it->second;
    return nullptr;                                                           
}

                                                                               
void CustomMatchModule::PreloadTextures(const std::vector<std::string>& urls) {
    for (const auto& url : urls) {
        {
            std::lock_guard<std::mutex> lock(TextureCacheMutex);
            if (TextureCache.find(url) != TextureCache.end())
                continue;                               
            TextureCache[url] = nullptr;                                           
        }
        std::thread([url]() {
            if (g_DllUnloading.load()) return;
            CURL* curl = curl_easy_init();
            if (!curl) return;

            std::string response;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "KingMod/1.0");

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK || response.empty() || g_DllUnloading.load()) return;

            int w = 0, h = 0, comp = 0;
            stbi_uc* pixels = stbi_load_from_memory(
                reinterpret_cast<const stbi_uc*>(response.data()),
                static_cast<int>(response.size()), &w, &h, &comp, 4);
            if (!pixels || g_DllUnloading.load()) return;

                                                                                     
            std::vector<uint8_t> rgba(pixels, pixels + static_cast<size_t>(w) * h * 4);
            stbi_image_free(pixels);

            Main.Execute([url, rgba = std::move(rgba), w, h]() {
                try {
                    if (g_DllUnloading.load()) return;
                    ID3D11Device* dev = nullptr;
                    if (!blur::device) return;
                    blur::device->GetDevice(&dev);
                    if (!dev) return;
                    if (void* srv = BuildMapTexture(dev, rgba, (uint32_t)w, (uint32_t)h)) {
                        std::lock_guard<std::mutex> lock(TextureCacheMutex);
                        TextureCache[url] = srv;
                    }
                    dev->Release();
                } catch (...) {}
            });
        }).detach();
    }
}

                                             
std::unordered_map<std::string, void*> CustomMatchModule::TextureCache;
std::mutex CustomMatchModule::TextureCacheMutex;

class CustomMatchModule CustomMatch;
