#include "CustomBorder.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Events.hpp"
#include <Windows.h>
#include <algorithm>
#include <chrono>
#include <cctype>
#include <fstream>

#pragma warning(disable: 4996)

bool                         CustomBorderModule::IsEnabled          = false;
bool                         CustomBorderModule::IsInGame           = false;
fs::path                     CustomBorderModule::BorderFolder;
std::vector<fs::path>        CustomBorderModule::AvailableFiles;
int                          CustomBorderModule::SelectedFileIndex  = -1;
UTexture2DDynamic*           CustomBorderModule::LoadedTexture      = nullptr;
bool                         CustomBorderModule::ApplyToAdverts     = true;
bool                         CustomBorderModule::ApplyToTerrain     = true;
bool                         CustomBorderModule::ApplyToSkyCurves   = true;
bool                         CustomBorderModule::PendingApply       = false;

CustomBorderModule::CustomBorderModule() : Module("CustomBorder", "Stadium texture override", States::STATES_All) {}
CustomBorderModule::~CustomBorderModule() {}
void CustomBorderModule::OnCreate() {}
void CustomBorderModule::OnDestroy() {}
CustomBorderModule CustomBorder;

namespace
{
    enum BorderCategory : uint8_t
    {
        BorderCategory_Advert  = 1 << 0,
        BorderCategory_Terrain = 1 << 1,
        BorderCategory_Sky     = 1 << 2
    };

    struct BorderBinding
    {
        UMaterialInstanceConstant* mic = nullptr;
        FName parameterName{};
        uint8_t categories = 0;
    };

    struct BorderTextureOverride
    {
        UMaterialInstanceConstant* mic = nullptr;
        FName parameterName{};
        UTexture* originalTexture = nullptr;
    };

    std::vector<BorderBinding> g_Bindings;
    std::vector<BorderTextureOverride> g_OriginalOverrides;
    bool g_CacheBuilding = false;
    bool g_CacheReady = false;
    size_t g_CacheScanIndex = 0;
    size_t g_CacheTotalSnapshot = 0;
    bool g_Hooked = false;
    std::string g_SelectedFileNameHint;

                                                                            
                                                      
    constexpr double kCacheBudgetMs = 0.75;
    constexpr size_t kMaxObjectsPerTick = 1800;

    std::string LowerCopy(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return value;
    }

    bool BorderGetFileBytes(const fs::path& filePath, std::vector<uint8_t>& outBytes)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) return false;
        const std::streamsize size = file.tellg();
        if (size <= 0) return false;
        file.seekg(0, std::ios::beg);
        outBytes.resize(static_cast<size_t>(size));
        return static_cast<bool>(file.read(reinterpret_cast<char*>(outBytes.data()), size));
    }

                                                                    
    void UnsafeAssignObjectName(UObject* object, std::string* outName)
    {
        *outName = object->GetName();
    }

    bool SafeGetObjectName(UObject* object, std::string* outName)
    {
        if (!object || !outName) return false;
        __try
        {
            UnsafeAssignObjectName(object, outName);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeSetMICTextureInner(UMaterialInstanceConstant* mic, const FName* name, UTexture* tex)
    {
        if (!mic || !name || !tex) return false;
        __try
        {
            UTexture* current = nullptr;
            if (mic->GetTextureParameterValue(*name, current))
            {
                mic->SetTextureParameterValue(*name, tex);
                return true;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
        return false;
    }

    bool SafeGetMICTextureInner(UMaterialInstanceConstant* mic, const FName* name, UTexture** outTexture)
    {
        if (!mic || !name || !outTexture) return false;
        __try
        {
            UTexture* current = nullptr;
            if (mic->GetTextureParameterValue(*name, current))
            {
                *outTexture = current;
                return true;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
        return false;
    }

    bool SameFName(const FName& a, const FName& b)
    {
        return memcmp(&a, &b, sizeof(FName)) == 0;
    }

    void AddBinding(UMaterialInstanceConstant* mic, const FName& parameterName, uint8_t category)
    {
        if (!mic || category == 0) return;
        for (BorderBinding& binding : g_Bindings)
        {
            if (binding.mic == mic && SameFName(binding.parameterName, parameterName))
            {
                binding.categories |= category;
                return;
            }
        }
        g_Bindings.push_back({ mic, parameterName, category });
    }

    void RememberOriginal(UMaterialInstanceConstant* mic, const FName& parameterName, UTexture* original)
    {
        if (!mic) return;
        for (const BorderTextureOverride& entry : g_OriginalOverrides)
            if (entry.mic == mic && SameFName(entry.parameterName, parameterName))
                return;
        g_OriginalOverrides.push_back({ mic, parameterName, original });
    }

    bool ApplyTracked(UMaterialInstanceConstant* mic, const FName& parameterName, UTexture* replacement)
    {
        UTexture* current = nullptr;
        if (!SafeGetMICTextureInner(mic, &parameterName, &current))
            return false;
        RememberOriginal(mic, parameterName, current);
        return SafeSetMICTextureInner(mic, &parameterName, replacement);
    }

    void RestoreMaterialOverrides()
    {
        for (const BorderTextureOverride& entry : g_OriginalOverrides)
        {
            if (entry.mic && entry.originalTexture)
                SafeSetMICTextureInner(entry.mic, &entry.parameterName, entry.originalTexture);
        }
        g_OriginalOverrides.clear();
    }

    void BeginCacheBuild()
    {
        g_Bindings.clear();
        g_CacheScanIndex = 0;
        g_CacheTotalSnapshot = 0;
        g_CacheReady = false;
        g_CacheBuilding = true;
    }

    void InspectMIC(UMaterialInstanceConstant* mic)
    {
        if (!mic) return;

        std::string micName;
        SafeGetObjectName(mic, &micName);
        const std::string lowerMicName = LowerCopy(micName);

                                                                              
                                                                               
        if (lowerMicName.find("advert") != std::string::npos)
        {
            FName adTexture{ L"AdTexture" };
            UTexture* current = nullptr;
            if (SafeGetMICTextureInner(mic, &adTexture, &current))
                AddBinding(mic, adTexture, BorderCategory_Advert);
        }

                                                                               
                                                                                 
                                                
        for (const FTextureParameterValue& textureParam : mic->TextureParameterValues)
        {
            UTexture* referenced = textureParam.ParameterValue;
            if (!referenced) continue;

            std::string textureName;
            if (!SafeGetObjectName(referenced, &textureName)) continue;
            const std::string lowerTextureName = LowerCopy(textureName);

            if (lowerTextureName.find("terrain_textures") != std::string::npos ||
                lowerTextureName.find("terrain") != std::string::npos && lowerTextureName.find("texture") != std::string::npos)
            {
                AddBinding(mic, textureParam.ParameterName, BorderCategory_Terrain);
            }

            if (lowerTextureName.find("skycurves") != std::string::npos ||
                lowerTextureName.find("sky_curve") != std::string::npos)
            {
                AddBinding(mic, textureParam.ParameterName, BorderCategory_Sky);
            }
        }
    }

    void ProcessCacheBuildSlice()
    {
        if (!g_CacheBuilding) return;
        TArray<UObject*>* objects = UObject::GObjObjects();
        if (!objects)
        {
            g_CacheBuilding = false;
            return;
        }

        const size_t count = static_cast<size_t>(objects->size());
        g_CacheTotalSnapshot = (std::max)(g_CacheTotalSnapshot, count);
        const auto start = std::chrono::steady_clock::now();
        size_t processed = 0;

        while (g_CacheScanIndex < count && processed < kMaxObjectsPerTick)
        {
            UObject* object = objects->at(static_cast<int32_t>(g_CacheScanIndex++));
            ++processed;
            if (object && object->Class && object->IsA<UMaterialInstanceConstant>())
                InspectMIC(static_cast<UMaterialInstanceConstant*>(object));

            const double elapsed = std::chrono::duration<double, std::milli>(
                std::chrono::steady_clock::now() - start).count();
            if (elapsed >= kCacheBudgetMs)
                break;
        }

        if (g_CacheScanIndex >= count)
        {
            g_CacheBuilding = false;
            g_CacheReady = true;
        }
    }

    uint8_t EnabledCategoryMask()
    {
        uint8_t mask = 0;
        if (CustomBorderModule::ApplyToAdverts)   mask |= BorderCategory_Advert;
        if (CustomBorderModule::ApplyToTerrain)   mask |= BorderCategory_Terrain;
        if (CustomBorderModule::ApplyToSkyCurves) mask |= BorderCategory_Sky;
        return mask;
    }
}

void CustomBorderModule::Initialize()
{
    wchar_t exePath[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) > 0)
        BorderFolder = fs::path(exePath).parent_path() / "KingMod" / "Texture" / "Border";
    else
        BorderFolder = fs::current_path() / "KingMod" / "Texture" / "Border";

    std::error_code ec;
    fs::create_directories(BorderFolder, ec);
    ScanBorderFiles();
                                                                               
                                                                            
    if (IsEnabled && SelectedFileIndex >= 0)
        LoadedTexture = LoadSelectedTexture();
    Hook();
    Console.Write("[CustomBorder] Ready (kickoff-safe incremental target cache)");
}

void CustomBorderModule::ScanBorderFiles()
{
    const std::string previous = SelectedFileName();
    AvailableFiles.clear();
    if (!fs::exists(BorderFolder)) return;

    std::error_code ec;
    for (const auto& entry : fs::directory_iterator(BorderFolder, ec))
    {
        if (!entry.is_regular_file(ec)) continue;
        const std::string ext = LowerCopy(entry.path().extension().string());
        if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
            AvailableFiles.push_back(entry.path());
    }
    std::sort(AvailableFiles.begin(), AvailableFiles.end(),
        [](const fs::path& a, const fs::path& b) { return a.filename().string() < b.filename().string(); });

    SelectedFileIndex = -1;
    if (!previous.empty())
        SelectFileByName(previous);
}

UTexture2DDynamic* CustomBorderModule::LoadSelectedTexture()
{
    if (SelectedFileIndex < 0 || SelectedFileIndex >= static_cast<int>(AvailableFiles.size()))
        return nullptr;

    const fs::path& imgPath = AvailableFiles[SelectedFileIndex];
    if (!fs::exists(imgPath)) return nullptr;

    std::vector<uint8_t> bytes;
    if (!BorderGetFileBytes(imgPath, bytes)) return nullptr;

    UTexture2DDynamic* tex = Instances.CreateInstance<UTexture2DDynamic>();
    if (!tex) return nullptr;

    tex->CompressionFullDynamicRange = true;
    tex->CompressionSettings = ETextureCompressionSettings::TC_NormalmapUncompressed;
    tex->Init(512, 512, EPixelFormat::PF_A8R8G8B8, false);

    struct RawTArray { uint8_t* data; int32_t size; int32_t cap; };
    RawTArray raw{ bytes.data(), static_cast<int32_t>(bytes.size()), static_cast<int32_t>(bytes.size()) };
    TArray<uint8_t>& sdkBytes = *reinterpret_cast<TArray<uint8_t>*>(&raw);

    const std::string ext = LowerCopy(imgPath.extension().string());
    if (ext == ".png")
        tex->UpdateMipFromPNG(0, sdkBytes);
    else if (ext == ".jpg" || ext == ".jpeg")
        tex->UpdateMipFromJPEG(0, sdkBytes);
    else
    {
        Instances.MarkForDestory(tex);
        return nullptr;
    }

    Instances.MarkInvincible(tex);
    return tex;
}

void CustomBorderModule::RestoreStadium()
{
    RestoreMaterialOverrides();
    PendingApply = false;
}

void CustomBorderModule::ApplyToStadium()
{
    if (!IsEnabled) return;
    if (!IsInGame)
    {
        PendingApply = true;
        return;
    }

    if (!g_CacheReady)
    {
        PendingApply = true;
        if (!g_CacheBuilding) BeginCacheBuild();
        return;
    }

    if (!LoadedTexture)
    {
        LoadedTexture = LoadSelectedTexture();
        if (!LoadedTexture)
        {
            Console.Error("[CustomBorder] No stadium texture selected");
            return;
        }
    }

    UTexture* source = static_cast<UTexture*>(static_cast<UObject*>(LoadedTexture));
    if (!source) return;

    RestoreMaterialOverrides();
    const uint8_t enabledMask = EnabledCategoryMask();
    int applied = 0;
    for (const BorderBinding& binding : g_Bindings)
    {
        if ((binding.categories & enabledMask) == 0) continue;
        if (ApplyTracked(binding.mic, binding.parameterName, source))
            ++applied;
    }

    PendingApply = false;
    Console.Write("[CustomBorder] Applied " + std::to_string(applied) + " cached stadium material target(s)");
}

void CustomBorderModule::ArmForNextTick()
{
    PendingApply = true;
    if (!IsInGame && IsEnabled && !LoadedTexture && SelectedFileIndex >= 0)
        LoadedTexture = LoadSelectedTexture();
    if (IsInGame && !g_CacheReady && !g_CacheBuilding)
        BeginCacheBuild();
}

std::string CustomBorderModule::SelectedFileName()
{
    if (SelectedFileIndex >= 0 && SelectedFileIndex < static_cast<int>(AvailableFiles.size()))
        return AvailableFiles[SelectedFileIndex].filename().string();
    return g_SelectedFileNameHint;
}

void CustomBorderModule::SelectFileByName(const std::string& name)
{
    g_SelectedFileNameHint = name;
    if (name.empty())
    {
        SelectedFileIndex = -1;
        return;
    }

    for (int i = 0; i < static_cast<int>(AvailableFiles.size()); ++i)
    {
        if (AvailableFiles[i].filename().string() == name)
        {
            SelectedFileIndex = i;
            return;
        }
    }
    SelectedFileIndex = -1;
}

void CustomBorderModule::OnGameEventStart(PreEvent& event)
{
    if (!event.Caller() || !event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
        return;

    IsInGame = true;
    RestoreMaterialOverrides();
    PendingApply = IsEnabled && SelectedFileIndex >= 0;
    if (PendingApply)
        BeginCacheBuild();
    else
    {
        g_Bindings.clear();
        g_CacheBuilding = false;
        g_CacheReady = false;
        g_CacheScanIndex = 0;
        g_CacheTotalSnapshot = 0;
    }
}

void CustomBorderModule::OnGameEventDestroyed(PreEvent&)
{
                                                                               
                                                                                     
    RestoreMaterialOverrides();
    IsInGame = false;
    PendingApply = false;
    g_Bindings.clear();
    g_CacheBuilding = false;
    g_CacheReady = false;
    g_CacheScanIndex = 0;
    g_CacheTotalSnapshot = 0;
                                                                              
                                                                              
}

void CustomBorderModule::Hook()
{
    if (g_Hooked) return;
    g_Hooked = true;

    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay", OnGameEventStart);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed", OnGameEventDestroyed);

    Events.HookEventPost("Function TAGame.PlayerController_TA.PlayerTick",
        [](const PostEvent&)
        {
            if (!IsInGame) return;

            if (g_CacheBuilding)
                ProcessCacheBuildSlice();

            if (PendingApply && g_CacheReady)
                ApplyToStadium();
        });
}
