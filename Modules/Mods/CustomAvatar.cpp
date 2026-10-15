#include "CustomAvatar.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Main.hpp"
#include "../../Modules/Mods/GameEventHook.hpp"
#include <fstream>
#include <algorithm>
#include <array>
#include <unordered_map>
#pragma warning(disable: 4996)

bool                         CustomAvatarModule::IsEnabled         = true;
bool                         CustomAvatarModule::IsInGame          = false;
AGameEvent_Soccar_TA*        CustomAvatarModule::CurrentGameEvent  = nullptr;
fs::path                     CustomAvatarModule::AvatarsFolder;
std::vector<fs::path>        CustomAvatarModule::AvailableFiles;
int                          CustomAvatarModule::SelectedFileIndex = -1;
bool                         CustomAvatarModule::ApplyToAllPlayers = false;
UTexture2DDynamic*           CustomAvatarModule::LoadedTexture     = nullptr;

                                           

                       
static bool ShouldSkipApplication();
static int ApplyPlatformIconsToMatch();

namespace
{
    std::unordered_map<std::string, UTexture2DDynamic*> g_PlatformTextureCache;
    ULONGLONG g_LastPlatformRefreshMs = 0;
}

                                                               
                
                                                               

static bool AvatarGetFileBytes(const fs::path& filePath, std::vector<uint8_t>& outBytes)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        Console.Error("[CustomAvatar] Failed to open: " + filePath.string());
        return false;
    }
    std::streamsize size = file.tellg();
    if (size <= 0)
    {
        Console.Error("[CustomAvatar] File empty: " + filePath.string());
        return false;
    }
    file.seekg(0, std::ios::beg);
    outBytes.resize(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(outBytes.data()), size))
    {
        Console.Error("[CustomAvatar] Read failed: " + filePath.string());
        return false;
    }
    return true;
}

                                                               
                   
                                                               

UTexture2DDynamic* CustomAvatarModule::LoadTextureFromPath(const fs::path& imgPath)
{
    if (!fs::exists(imgPath))
    {
        Console.Error("[CustomAvatar] Image does not exist: " + imgPath.string());
        return nullptr;
    }

    std::vector<uint8_t> bytes;
    if (!AvatarGetFileBytes(imgPath, bytes))
        return nullptr;

    UTexture2DDynamic* tex = Instances.CreateInstance<UTexture2DDynamic>();
    if (!tex)
    {
        Console.Error("[CustomAvatar] Failed to create UTexture2DDynamic");
        return nullptr;
    }

    tex->CompressionFullDynamicRange = true;
    tex->CompressionSettings         = ETextureCompressionSettings::TC_NormalmapUncompressed;
    tex->Init(256, 256, EPixelFormat::PF_A8R8G8B8, false);

    struct RawTArray { uint8_t* data; int32_t size; int32_t cap; };
    RawTArray raw{ bytes.data(), static_cast<int32_t>(bytes.size()), static_cast<int32_t>(bytes.size()) };
    TArray<uint8_t>& sdkBytes = *reinterpret_cast<TArray<uint8_t>*>(&raw);

    std::string ext = imgPath.extension().string();
    for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    if (ext == ".png")
        tex->UpdateMipFromPNG(0, sdkBytes);
    else if (ext == ".jpg" || ext == ".jpeg")
        tex->UpdateMipFromJPEG(0, sdkBytes);
    else
    {
        Console.Error("[CustomAvatar] Unsupported format: " + ext + " (use .png or .jpg)");
        Instances.MarkForDestory(tex);
        return nullptr;
    }

    Instances.MarkInvincible(tex);
    Console.Write("[CustomAvatar] Loaded texture: " + imgPath.filename().string());
    return tex;
}

UTexture2DDynamic* CustomAvatarModule::LoadSelectedTexture()
{
    if (AvailableFiles.empty() || SelectedFileIndex < 0 || SelectedFileIndex >= static_cast<int>(AvailableFiles.size()))
        return nullptr;

    return LoadTextureFromPath(AvailableFiles[SelectedFileIndex]);
}

void CustomAvatarModule::ApplyTextureFromPath(const fs::path& imgPath)
{
    if (!IsEnabled) return;
    
    UTexture2DDynamic* tex = LoadTextureFromPath(imgPath);
    if (tex)
    {
        LoadedTexture = tex;
        ApplyToAll();
    }
}

                                                               
                 
                                                               

void CustomAvatarModule::ScanAvatarFiles()
{
    AvailableFiles.clear();

    if (!fs::exists(AvatarsFolder))
    {
        Console.Error("[CustomAvatar] Folder not found: " + AvatarsFolder.string());
        return;
    }

    try
    {
        for (const auto& entry : fs::directory_iterator(AvatarsFolder))
        {
            if (!entry.is_regular_file()) continue;
            std::string ext = entry.path().extension().string();
            for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
                AvailableFiles.push_back(entry.path());
        }
    }
    catch (...) { Console.Error("[CustomAvatar] Exception scanning avatar folder"); }

    Console.Write("[CustomAvatar] Found " + std::to_string(AvailableFiles.size()) + " image(s)");
    if (!AvailableFiles.empty() && SelectedFileIndex < 0)
        SelectedFileIndex = 0;
    else if (SelectedFileIndex >= static_cast<int>(AvailableFiles.size()))
        SelectedFileIndex = AvailableFiles.empty() ? -1 : 0;
}

                                                               
                                                               
  
                                        
                                                     
                                                     
                                                     
                                                     
                                                                        
                                                     
                                                     
                                                     
                                                               

                                                                                       
static bool SafeReadPtrRaw(uintptr_t address, void** outPtr)
{
    __try {
        *outPtr = *reinterpret_cast<void**>(address);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        *outPtr = nullptr;
        return false;
    }
}

static bool SafeReadFName(void* base, size_t off, FName& out)
{
    __try {
        out = *reinterpret_cast<FName*>(reinterpret_cast<uint8_t*>(base) + off);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static bool SafeReadInt32(void* base, size_t off, int32_t& out)
{
    __try {
        out = *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(base) + off);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

                                                                                   
                                                                                    
                                                                                   
                                                                                     
static UVanitySetManager_TA* SafeReadVanityMgr(APlayerController_TA* pc)
{
    __try { return pc->VanityMgr; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static UPlayerAvatar_TA* SafeReadPCPlayerAvatar(APlayerController_TA* pc)
{
    __try { return pc->PlayerAvatar; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static APRI_TA* SafeReadPCPRI(APlayerController_TA* pc)
{
    __try { return pc->PRI; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static UPlayerAvatar_TA* SafeReadPRIPlayerAvatar(APRI_TA* pri)
{
    __try { return pri->PlayerAvatar; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static bool SafeCallHandleUpdateTexture(UPlayerAvatar_TA* avatar, UTexture2DDynamic* tex)
{
    __try {
        avatar->HandleUpdateTexture(tex);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static bool SafeCallHandleLoadedAvatarAsset(UVanitySetManager_TA* mgr, UPlayerAvatar_TA* avatar)
{
    __try {
        mgr->HandleLoadedAvatarAsset(avatar);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static bool SafeCallSetTextureValue(UGFxDataStore_X* store, const FName* table, int32_t row, const FName* col, UTexture2DDynamic* tex)
{
    __try {
        store->SetTextureValue(*table, row, *col, tex);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static bool SafeWritePlayerAvatarTexture(UGFxData_LocalPlayer_TA* lp, UTexture2DDynamic* tex)
{
    __try {
        lp->PlayerAvatarTexture = tex;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

                                                                                                             
                                                                                      
                                                                                       
static bool IsValidUserPtr(void* ptr)
{
    uintptr_t v = reinterpret_cast<uintptr_t>(ptr);
    return v > 0x10000ULL && v < 0x0007FFFFFFFFFFFULL && (v & 0x7) == 0;
}

template<typename T>
static T* OffsetPtr(void* base, size_t off)
{
    if (!base) return nullptr;
    void* result = nullptr;
    uintptr_t addr = reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(base) + off);
    SafeReadPtrRaw(addr, &result);
    return IsValidUserPtr(result) ? static_cast<T*>(result) : nullptr;
}

static UPlayerAvatar_TA* SafeReadAnyPRIPlayerAvatar(APRI_TA* pri)
{
    __try { return pri ? pri->PlayerAvatar : nullptr; }
    __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static bool SafeGetPRIPlatformId(APRI_TA* pri, uint8_t& outPlatform)
{
    outPlatform = 0;
    __try
    {
        if (!pri)
            return false;
        outPlatform = static_cast<uint8_t>(pri->UniqueId.Platform);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        outPlatform = 0;
        return false;
    }
}

static std::string PlatformIdToAvatarStem(uint8_t platformId)
{
    switch (platformId)
    {
    case 1:  return "steam";
    case 2:  return "psn";
    case 4:  return "xbox";
    case 6:  return "switch";
    case 7:  return "psynet";
    case 11: return "epic";
    default: return "unknown";
    }
}

static fs::path FindPlatformAvatarPath(const std::string& stem)
{
    const std::array<std::string, 10> candidates = {
        stem + ".png", stem + ".jpg", stem + ".jpeg",
        (stem == "psn" ? "playstation.png" : ""),
        (stem == "psn" ? "ps4.png" : ""),
        (stem == "psn" ? "ps5.png" : ""),
        (stem == "epic" ? "egs.png" : ""),
        (stem == "epic" ? "epicgames.png" : ""),
        (stem == "psynet" ? "psyonix.png" : ""),
        (stem == "unknown" ? "default.png" : "")
    };
    for (const auto& name : candidates)
    {
        if (name.empty())
            continue;
        const fs::path p = CustomAvatarModule::AvatarsFolder / name;
        if (fs::exists(p))
            return p;
    }
    return {};
}

static UTexture2DDynamic* GetOrLoadPlatformTexture(const std::string& stem)
{
    const auto it = g_PlatformTextureCache.find(stem);
    if (it != g_PlatformTextureCache.end() && it->second)
        return it->second;

    const fs::path p = FindPlatformAvatarPath(stem);
    if (p.empty())
        return nullptr;

    UTexture2DDynamic* tex = CustomAvatarModule::LoadTextureFromPath(p);
    if (tex)
        g_PlatformTextureCache[stem] = tex;
    return tex;
}

static UTexture* SafeGetNativeAvatarTexture(UPlayerAvatar_TA* avatar)
{
    __try
    {
        if (!avatar || !avatar->Asset) return nullptr;
        return avatar->Asset->ToPlayer;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return nullptr;
    }
}

static bool SafeCallHandleUpdateAnyTexture(UPlayerAvatar_TA* avatar, UTexture* tex)
{
    __try
    {
        if (!avatar || !tex) return false;
        avatar->HandleUpdateTexture(tex);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}

static int RestorePlatformIconsInMatch()
{
    AGameEvent_Soccar_TA* game = CustomAvatarModule::CurrentGameEvent;
    if (!game)
        game = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();
    if (!game)
        return 0;

    int restored = 0;
    const int count = (std::min)(game->PRIs.size(), 64);
    for (int i = 0; i < count; ++i)
    {
        APRI_TA* pri = game->PRIs[i];
        if (!pri || !IsValidUserPtr(pri)) continue;
        UPlayerAvatar_TA* avatar = SafeReadAnyPRIPlayerAvatar(pri);
        if (!avatar || !IsValidUserPtr(avatar)) continue;
        UTexture* nativeTexture = SafeGetNativeAvatarTexture(avatar);
        if (nativeTexture && SafeCallHandleUpdateAnyTexture(avatar, nativeTexture))
            ++restored;
    }
    return restored;
}



static int ApplyPlatformIconsToMatch()
{
    if (!GameEventHookModule::ShowPlatformOnScoreboard)
        return 0;

    AGameEvent_Soccar_TA* game = CustomAvatarModule::CurrentGameEvent;
    if (!game)
        game = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();
    if (!game)
        return 0;

    int applied = 0;
    const int count = (std::min)(game->PRIs.size(), 64);
    for (int i = 0; i < count; ++i)
    {
        APRI_TA* pri = game->PRIs[i];
        if (!pri || !IsValidUserPtr(pri))
            continue;

        uint8_t platformId = 0;
        if (!SafeGetPRIPlatformId(pri, platformId))
            continue;

        UPlayerAvatar_TA* avatar = SafeReadAnyPRIPlayerAvatar(pri);
        if (!avatar || !IsValidUserPtr(avatar))
            continue;

        UTexture2DDynamic* tex = GetOrLoadPlatformTexture(PlatformIdToAvatarStem(platformId));
        if (!tex)
            continue;

        if (SafeCallHandleUpdateTexture(avatar, tex))
            ++applied;
    }

    return applied;
}

static bool ResolveLocalAvatar(UPlayerAvatar_TA*& outAvatar, UVanitySetManager_TA*& outVanityMgr)
{
    outAvatar = nullptr;
    outVanityMgr = nullptr;

    try
    {
        const FUniqueNetId localId = Instances.GetUniqueID();

        auto* rawPC = Instances.IAPlayerController();
        auto* pc = (rawPC && IsValidUserPtr(rawPC)) ? static_cast<APlayerController_TA*>(rawPC) : nullptr;

        if (!pc)
        {
            auto* found = Instances.GetInstanceOf<APlayerController_TA>();
            if (found && IsValidUserPtr(found))
                pc = found;
        }

        if (!pc)
            return false;

                                                                                 
                                                                                
                                                                                
        outVanityMgr = SafeReadVanityMgr(pc);
        if (outVanityMgr && !IsValidUserPtr(outVanityMgr))
            outVanityMgr = nullptr;

        UPlayerAvatar_TA* avatar = SafeReadPCPlayerAvatar(pc);
        if (avatar && IsValidUserPtr(avatar))
            outAvatar = avatar;

        if (!outAvatar)
        {
            APRI_TA* pri = SafeReadPCPRI(pc);
                                                                              
                                                                              
            if (pri && IsValidUserPtr(pri))
            {
                UPlayerAvatar_TA* priAvatar = SafeReadPRIPlayerAvatar(pri);
                if (priAvatar && IsValidUserPtr(priAvatar))
                    outAvatar = priAvatar;
            }
        }
    }
    catch (...)
    {
        Console.Error("[CustomAvatar] Exception resolving local avatar");
    }

    return outAvatar != nullptr && IsValidUserPtr(outAvatar);
}

void CustomAvatarModule::ApplyPlatformIcons()
{
    ApplyPlatformIconsToMatch();
}

void CustomAvatarModule::RestorePlatformIcons()
{
    RestorePlatformIconsInMatch();
    if (IsEnabled && SelectedFileIndex >= 0 && SelectedFileIndex < static_cast<int>(AvailableFiles.size()))
    {
        if (!LoadedTexture)
            LoadedTexture = LoadSelectedTexture();
        if (LoadedTexture)
        {
                                                                           
                                             
            UPlayerAvatar_TA* localAvatar = nullptr;
            UVanitySetManager_TA* vanityMgr = nullptr;
            if (ResolveLocalAvatar(localAvatar, vanityMgr))
            {
                SafeCallHandleUpdateTexture(localAvatar, LoadedTexture);
                if (vanityMgr) SafeCallHandleLoadedAvatarAsset(vanityMgr, localAvatar);
            }
        }
    }
}

void CustomAvatarModule::ApplyToAll()
{
    if (GameEventHookModule::ShowPlatformOnScoreboard)
    {
        const int platformApplied = ApplyPlatformIconsToMatch();
        Console.Write("[CustomAvatar] Applied platform avatar icons (" + std::to_string(platformApplied) + " player(s))");
        return;
    }

    if (ShouldSkipApplication())
        return;

    if (!LoadedTexture)
        return;

    int applied = 0;

                                                                             
    UPlayerAvatar_TA*     localAvatar = nullptr;
    UVanitySetManager_TA* vanityMgr   = nullptr;

    if (!ResolveLocalAvatar(localAvatar, vanityMgr))
    {
        Console.Error("[CustomAvatar] Failed to resolve local avatar");
        return;
    }

    ApplyToAllPlayers = false;

                                                                              
    if (SafeCallHandleUpdateTexture(localAvatar, LoadedTexture))
    {
        applied++;
        Console.Write("[CustomAvatar] Updated local avatar texture");
    }
    else
    {
        Console.Error("[CustomAvatar] AV in HandleUpdateTexture (local avatar)");
    }

    if (vanityMgr && localAvatar)
    {
        if (!SafeCallHandleLoadedAvatarAsset(vanityMgr, localAvatar))
            Console.Error("[CustomAvatar] AV in HandleLoadedAvatarAsset (stale vanityMgr)");
    }

    Console.Write("[CustomAvatar] Applied custom avatar locally (" + std::to_string(applied) + " updates)");
}

                                                               
                    
                                                               

void CustomAvatarModule::OnGameEventDestroyed(PreEvent& event)
{
    try {
        if (event.Caller() && event.Caller() == CurrentGameEvent) {
            CurrentGameEvent = nullptr;
            IsInGame = false;
            LoadedTexture = nullptr;
        }
    }
    catch (...) { Console.Error("[CustomAvatar] Exception in OnGameEventDestroyed"); }
}

void CustomAvatarModule::OnGameEventStart(PreEvent& event)
{
    try
    {
        if (event.Caller() && event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
        {
            CurrentGameEvent = static_cast<AGameEvent_Soccar_TA*>(event.Caller());
            IsInGame = true;

            if (GameEventHookModule::ShowPlatformOnScoreboard)
            {
                ApplyPlatformIconsToMatch();
            }
            else if (IsEnabled)
            {
                if (SelectedFileIndex >= 0 && SelectedFileIndex < static_cast<int>(AvailableFiles.size()) && !LoadedTexture)
                    LoadedTexture = LoadSelectedTexture();
                ApplyToAll();
            }
        }
    }
    catch (...) { Console.Error("[CustomAvatar] Exception in OnGameEventStart"); }
}

void CustomAvatarModule::Hook()
{
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay",        OnGameEventStart);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed",            OnGameEventDestroyed);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Active.BeginState",    OnGameEventStart);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Countdown.BeginState", OnGameEventStart);
    
                                                      
    Events.HookEventPost("Function TAGame.PlayerController_TA.PlayerTick",          [](const PostEvent&) { CustomAvatar.OnTick(); });
}

                                                               
                    
                                                               

void CustomAvatarModule::Initialize()
{
    ApplyToAllPlayers = false;

    wchar_t exePath[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH))
    {
        fs::path basePath = fs::path(exePath).parent_path();
        AvatarsFolder = basePath / "KingMod" / "Texture" / "Avatar";
    }
    else
    {
        AvatarsFolder = fs::current_path() / "KingMod" / "Texture" / "Avatar";
    }

    if (!fs::exists(AvatarsFolder))
    {
        std::error_code ec;
        if (fs::create_directories(AvatarsFolder, ec))
            Console.Write("[CustomAvatar] Created folder: " + AvatarsFolder.string());
        else
            Console.Error("[CustomAvatar] Failed to create folder: " + ec.message());
    }

    Console.Write("[CustomAvatar] Using folder: " + AvatarsFolder.string());
    ScanAvatarFiles();
    Hook();

                                                                             
    AGameEvent_Soccar_TA* existingGame = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();
    if (existingGame)
    {
        CurrentGameEvent = existingGame;
        IsInGame = true;
        Console.Write("[CustomAvatar] Already in-game at inject time, applying queued avatar.");
        if (GameEventHookModule::ShowPlatformOnScoreboard)
        {
            ApplyPlatformIconsToMatch();
        }
        else if (IsEnabled)
        {
            if (SelectedFileIndex >= 0 && SelectedFileIndex < static_cast<int>(AvailableFiles.size()))
                LoadedTexture = LoadSelectedTexture();
            ApplyToAll();
        }
    }

    Console.Write("[CustomAvatar] Initialized.");
}

CustomAvatarModule::CustomAvatarModule() : Module("CustomAvatar", "Client-side avatar replacement", States::STATES_All) 
{ 
    OnCreate();
}
CustomAvatarModule::~CustomAvatarModule() { OnDestroy(); }
void CustomAvatarModule::OnCreate() {}
void CustomAvatarModule::OnDestroy() {}

                                                               
                    
                                                               

static bool ShouldSkipApplication()
{
    if (!CustomAvatarModule::IsEnabled || !CustomAvatarModule::LoadedTexture)
        return true;
    
                                           
    if (!CustomAvatarModule::CurrentGameEvent)
        CustomAvatarModule::CurrentGameEvent = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();

    if (!CustomAvatarModule::IsInGame && !CustomAvatarModule::CurrentGameEvent)
        return true;
    
                                                              
    if (CustomAvatarModule::SelectedFileIndex < 0 ||
         CustomAvatarModule::SelectedFileIndex >= static_cast<int>(CustomAvatarModule::AvailableFiles.size()))
        return true;
    
    return false;
}

void CustomAvatarModule::OnTick()
{
    if (!GameEventHookModule::ShowPlatformOnScoreboard || !IsInGame || EventsComponent::IsTrainingResetQuarantined())
        return;

    const ULONGLONG now = GetTickCount64();
    if (now - g_LastPlatformRefreshMs < 1500ULL)
        return;
    g_LastPlatformRefreshMs = now;

    ApplyPlatformIconsToMatch();
}

CustomAvatarModule CustomAvatar;
