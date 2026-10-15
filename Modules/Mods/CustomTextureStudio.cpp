#include "CustomTextureStudio.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Main.hpp"
#include <Windows.h>
#include <algorithm>
#include <atomic>
#include <cctype>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>

#pragma warning(disable: 4996)

using json = nlohmann::json;

bool CustomTextureStudioModule::IsInGame = false;
CustomTextureStudioModule CustomTextureStudio;

namespace
{
    enum FeatureIndex : size_t
    {
        CustomDecal = 0,
        CustomBanner = 1
    };

    constexpr ULONGLONG kResetReapplyDelayMs = 1500;
    constexpr ULONGLONG kVehicleReapplyDelayMs = 350;

    fs::path g_RootFolder;
    fs::path g_ConfigPath;
    std::array<TextureStudioFeatureState, CustomTextureStudioModule::FeatureCount> g_States{};
    std::array<std::vector<fs::path>, CustomTextureStudioModule::FeatureCount> g_Files{};
    std::array<int, CustomTextureStudioModule::FeatureCount> g_LastApplyCount{};
    std::mutex g_StateMutex;
    std::mutex g_FilesMutex;

    std::atomic<bool> g_ResetPaused{ false };
    std::atomic<ULONGLONG> g_ReapplyAt{ 0 };
    std::atomic<uint32_t> g_PendingMask{ 0 };
    bool g_Hooked = false;
    bool g_ApplyingDecal = false;
    bool g_ApplyingBanner = false;

    const std::array<TextureStudioFeatureDefinition, CustomTextureStudioModule::FeatureCount> g_Definitions{{
        { "Custom Decal", "custom_decal", "Replaces the equipped decal skin material texture on the local car and garage preview.", TextureStudioGroup::Car },
        { "Custom Banner", "custom_banner", "Replaces the local player banner image using the normal PlayerBanner data binding.", TextureStudioGroup::Menu },
    }};

    struct BannerOverride
    {
        UPlayerBanner_TA* banner = nullptr;
        UTexture* original = nullptr;
    };
    std::vector<BannerOverride> g_BannerOverrides;

    struct DecalMaterialOverride
    {
        UCarMeshComponentBase_TA* mesh = nullptr;
        int32_t materialIndex = -1;
        UMaterialInterface* originalMaterial = nullptr;
        UMaterialInstanceConstant* customMaterial = nullptr;
    };
    std::vector<DecalMaterialOverride> g_DecalOverrides;

    std::string LowerCopy(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return value;
    }

    bool SafeIsLiveObject(void* object)
    {
        const uintptr_t address = reinterpret_cast<uintptr_t>(object);
        if (address < 0x10000 || (address & 0x7) != 0)
            return false;
        __try
        {
            const uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(address);
            if (vtable < 0x10000 || (vtable & 0x7) != 0) return false;
            const uintptr_t firstFunction = *reinterpret_cast<volatile uintptr_t*>(vtable);
            if (firstFunction < 0x10000) return false;
            const uintptr_t klass = *reinterpret_cast<volatile uintptr_t*>(address + 0x50);
            return klass >= 0x10000 && (klass & 0x7) == 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    APRI_TA* SafeGetPRI(APlayerController_TA* controller)
    {
        if (!controller) return nullptr;
        __try { return controller->PRI; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UPlayerBanner_TA* SafeGetPlayerBanner(APRI_TA* pri)
    {
        if (!pri) return nullptr;
        __try { return pri->PlayerBanner; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UPlayerBanner_TA* SafeGetLastPreviewBanner(UGFxData_PlayerBanners_TA* data)
    {
        if (!data) return nullptr;
        __try { return data->LastPreviewBanner; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UTexture* SafeGetBannerTexture(UPlayerBanner_TA* banner)
    {
        if (!banner) return nullptr;
        __try { return banner->ToPlayer; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    bool SafeSetBannerTexture(UPlayerBanner_TA* banner, UTexture* texture)
    {
        if (!banner) return false;
        __try
        {
            banner->ToPlayer = texture;
            banner->bIsDirty = 1;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    UPlayerBanner_TA* SafeGetGFxRowBanner(UGFxData_PlayerBanner_TA* row)
    {
        if (!row) return nullptr;
        __try { return row->PlayerBanner; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    void SafeRefreshGFxBannerRow(UGFxData_PlayerBanner_TA* row, UPlayerBanner_TA* banner)
    {
        if (!row || !banner) return;
        __try { row->SetBanner(banner); }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    APRI_TA* SafeGetGFxPRI(UGFxData_PRI_TA* data)
    {
        if (!data) return nullptr;
        __try { return data->PRI; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UGFxData_PlayerBanner_TA* SafeGetGFxPRIBannerRow(UGFxData_PRI_TA* data)
    {
        if (!data) return nullptr;
        __try { return data->GFxPlayerBanner; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UGFxData_PlayerBanner_TA* SafeGetPlayerVanityBannerRow(UGFxData_PlayerVanity_TA* data)
    {
        if (!data) return nullptr;
        __try { return data->GFxPlayerBanner; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    APawn* SafeGetPawn(APlayerController* controller)
    {
        if (!controller) return nullptr;
        __try { return controller->Pawn; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UCarMeshComponentBase_TA* SafeGetLiveCarMesh(ACar_TA* car)
    {
        if (!car) return nullptr;
        __try { return car->CarMesh; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UProductAsset_Skin_TA* SafeGetSkinAsset(UCarMeshComponentBase_TA* mesh)
    {
        if (!mesh) return nullptr;
        __try { return mesh->SkinAsset; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    UProductAsset_Body_TA* SafeGetBodyAsset(UCarMeshComponentBase_TA* mesh)
    {
        if (!mesh) return nullptr;
        __try { return mesh->BodyAsset; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    int32_t SafeGetSkinMaterialIndex(UProductAsset_Body_TA* body)
    {
        if (!body) return -1;
        __try { return body->SkinMaterialIndex; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
    }

    UMaterialInterface* SafeGetMeshMaterial(UCarMeshComponentBase_TA* mesh, int32_t index)
    {
        if (!mesh || index < 0) return nullptr;
        __try { return mesh->GetMaterial(index); }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    bool SafeSetMeshMaterial(UCarMeshComponentBase_TA* mesh, int32_t index, UMaterialInterface* material)
    {
        if (!mesh || index < 0 || !material) return false;
        __try
        {
            mesh->SetMaterial(index, material);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    UMaterialInterface* SafeGetSkinMaterial(UProductAsset_Skin_TA* skinAsset)
    {
        if (!skinAsset) return nullptr;
        __try { return skinAsset->Skin; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
    }

    bool SafeSetSkinMaterial(UProductAsset_Skin_TA* skinAsset, UMaterialInterface* material)
    {
        if (!skinAsset) return false;
        __try
        {
            skinAsset->Skin = material;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeSetMaterialParent(UMaterialInstanceConstant* material, UMaterialInterface* parent)
    {
        if (!material || !parent) return false;
        __try
        {
            material->SetParent(parent);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SafeSetTextureParam(UMaterialInstanceConstant* material, const FName* name, UTexture* texture)
    {
        if (!material || !name || !texture) return false;
        __try
        {
            material->SetTextureParameterValue(*name, texture);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    void SafeRefreshSkin(UCarMeshComponentBase_TA* mesh, UProductAsset_Skin_TA* skinAsset)
    {
        if (!mesh || !skinAsset) return;
        __try
        {
            mesh->AddVisualAsset(skinAsset);
            mesh->InitMaterials();
            mesh->ApplyPaintSettings();
            mesh->OnPaintChanged();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    bool ReadFileBytes(const fs::path& filePath, std::vector<uint8_t>& bytes)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) return false;
        const std::streamsize size = file.tellg();
        if (size <= 0) return false;
        file.seekg(0, std::ios::beg);
        bytes.resize(static_cast<size_t>(size));
        return static_cast<bool>(file.read(reinterpret_cast<char*>(bytes.data()), size));
    }

    UTexture2DDynamic* LoadImageTexture(const fs::path& image)
    {
        if (image.empty() || !fs::exists(image)) return nullptr;
        std::vector<uint8_t> bytes;
        if (!ReadFileBytes(image, bytes)) return nullptr;

        UTexture2DDynamic* texture = Instances.CreateInstance<UTexture2DDynamic>();
        if (!texture) return nullptr;
        texture->CompressionFullDynamicRange = true;
        texture->CompressionSettings = ETextureCompressionSettings::TC_NormalmapUncompressed;
        texture->Init(1024, 1024, EPixelFormat::PF_A8R8G8B8, false);

        struct RawTArray { uint8_t* data; int32_t size; int32_t cap; };
        RawTArray raw{ bytes.data(), static_cast<int32_t>(bytes.size()), static_cast<int32_t>(bytes.size()) };
        TArray<uint8_t>& sdkBytes = *reinterpret_cast<TArray<uint8_t>*>(&raw);

        const std::string extension = LowerCopy(image.extension().string());
        if (extension == ".png") texture->UpdateMipFromPNG(0, sdkBytes);
        else if (extension == ".jpg" || extension == ".jpeg") texture->UpdateMipFromJPEG(0, sdkBytes);
        else
        {
            Instances.MarkForDestory(texture);
            return nullptr;
        }

        Instances.MarkInvincible(texture);
        return texture;
    }

    bool IsEnabled(size_t index)
    {
        std::lock_guard<std::mutex> lock(g_StateMutex);
        return index < g_States.size() && g_States[index].enabled;
    }

    uint32_t EnabledMask()
    {
        std::lock_guard<std::mutex> lock(g_StateMutex);
        uint32_t mask = 0;
        for (size_t i = 0; i < g_States.size(); ++i)
            if (g_States[i].enabled) mask |= (1u << static_cast<uint32_t>(i));
        return mask;
    }

    void ScheduleMask(uint32_t mask, ULONGLONG delayMs)
    {
        if (!mask) return;
        g_PendingMask.fetch_or(mask, std::memory_order_acq_rel);
        g_ReapplyAt.store(GetTickCount64() + delayMs, std::memory_order_release);
    }

    UTexture2DDynamic* EnsureLoadedTexture(size_t index)
    {
        if (index >= g_States.size()) return nullptr;
        TextureStudioFeatureState state;
        {
            std::lock_guard<std::mutex> lock(g_StateMutex);
            state = g_States[index];
        }
        if (!state.enabled) return nullptr;
        if (state.loadedTexture && SafeIsLiveObject(state.loadedTexture)) return state.loadedTexture;

        fs::path selectedPath;
        {
            std::lock_guard<std::mutex> lock(g_FilesMutex);
            if (state.selectedFileIndex < 0 || state.selectedFileIndex >= static_cast<int>(g_Files[index].size()))
                return nullptr;
            selectedPath = g_Files[index][state.selectedFileIndex];
        }

        UTexture2DDynamic* loaded = LoadImageTexture(selectedPath);
        if (!loaded) return nullptr;
        {
            std::lock_guard<std::mutex> lock(g_StateMutex);
            g_States[index].loadedTexture = loaded;
        }
        return loaded;
    }

    int SafeGetDefaultSkinProductID(UProductAsset_Body_TA* body)
    {
        if (!body) return 0;
        __try { return body->GetDefaultSkinProductID(); }
        __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
    }

    UProductAsset_Skin_TA* LoadDefaultSkinForMesh(UCarMeshComponentBase_TA* mesh)
    {
        UProductAsset_Body_TA* body = SafeGetBodyAsset(mesh);
        if (!body || !SafeIsLiveObject(body)) return nullptr;
        const int productId = SafeGetDefaultSkinProductID(body);
        if (productId <= 0) return nullptr;

        UProductAsset_TA* asset = nullptr;
        try
        {
            if (UProductDatabase_TA* db = Instances.GetInstanceOf<UProductDatabase_TA>())
                asset = db->LoadAsset(productId);
            if (!asset)
            {
                if (UProductAssetLoader_TA* loader = UProductAssetLoader_TA::GetInstance())
                    asset = loader->LoadAsset(productId);
            }
        }
        catch (...) { asset = nullptr; }

        if (!asset || !asset->IsA(UProductAsset_Skin_TA::StaticClass())) return nullptr;
        return static_cast<UProductAsset_Skin_TA*>(asset);
    }

    DecalMaterialOverride* FindDecalOverride(UCarMeshComponentBase_TA* mesh)
    {
        for (auto& entry : g_DecalOverrides)
            if (entry.mesh == mesh) return &entry;
        return nullptr;
    }

    void SetCommonDecalParameters(UMaterialInstanceConstant* material, UTexture* source)
    {
        static const FName names[] = {
            FName(L"Diffuse"), FName(L"Texture"), FName(L"Skin"), FName(L"SkinTexture"),
            FName(L"Decal"), FName(L"DecalTexture"), FName(L"BaseColor"),
            FName(L"BaseColorTexture"), FName(L"Albedo"), FName(L"ColorTexture")
        };
        for (const FName& name : names)
            SafeSetTextureParam(material, &name, source);
    }

    int ApplyCustomDecalToMesh(UCarMeshComponentBase_TA* mesh, UTexture2DDynamic* dynamicTexture)
    {
        if (!mesh || !dynamicTexture || !SafeIsLiveObject(mesh)) return 0;

                                                                       
                                                                              
                                                                            
                                                                               
                                               
        UProductAsset_Body_TA* body = SafeGetBodyAsset(mesh);
        const int32_t skinIndex = SafeGetSkinMaterialIndex(body);
        if (!body || skinIndex < 0) return 0;

        UProductAsset_Skin_TA* skinAsset = SafeGetSkinAsset(mesh);
        if (!skinAsset || !SafeIsLiveObject(skinAsset))
            skinAsset = LoadDefaultSkinForMesh(mesh);
        if (!skinAsset || !SafeIsLiveObject(skinAsset)) return 0;

        UTexture* source = static_cast<UTexture*>(dynamicTexture);
        DecalMaterialOverride* existing = FindDecalOverride(mesh);
        if (existing && existing->customMaterial && SafeIsLiveObject(existing->customMaterial))
        {
            SetCommonDecalParameters(existing->customMaterial, source);
            return SafeSetMeshMaterial(mesh, existing->materialIndex, existing->customMaterial) ? 1 : 0;
        }

                                                                               
                                                                    
        UMaterialInterface* skinMaterial = SafeGetSkinMaterial(skinAsset);
        UMaterialInterface* originalSlotMaterial = SafeGetMeshMaterial(mesh, skinIndex);
        UMaterialInterface* parent = (skinMaterial && SafeIsLiveObject(skinMaterial)) ? skinMaterial : originalSlotMaterial;
        if (!parent || !SafeIsLiveObject(parent)) return 0;

        UMaterialInstanceConstant* customMaterial = Instances.CreateInstance<UMaterialInstanceConstant>();
        if (!customMaterial) return 0;
        Instances.MarkInvincible(customMaterial);
        if (!SafeSetMaterialParent(customMaterial, parent))
        {
            Instances.MarkForDestory(customMaterial);
            return 0;
        }

                                                                             
                                                                                
                                                                     
        if (skinMaterial && skinMaterial->IsA(UMaterialInstanceConstant::StaticClass()))
        {
            auto* sourceMic = static_cast<UMaterialInstanceConstant*>(skinMaterial);
            try
            {
                for (int i = 0; i < sourceMic->TextureParameterValues.size() && i < 64; ++i)
                {
                    const FTextureParameterValue& param = sourceMic->TextureParameterValues[i];
                    const std::string low = LowerCopy(param.ParameterName.ToString());
                    if (low.find("normal") != std::string::npos || low.find("mask") != std::string::npos ||
                        low.find("spec") != std::string::npos || low.find("rough") != std::string::npos ||
                        low.find("metal") != std::string::npos || low.find("window") != std::string::npos ||
                        low.find("glass") != std::string::npos)
                        continue;
                    SafeSetTextureParam(customMaterial, &param.ParameterName, source);
                }
            }
            catch (...) {}
        }
        SetCommonDecalParameters(customMaterial, source);

        if (!SafeSetMeshMaterial(mesh, skinIndex, customMaterial))
        {
            Instances.MarkForDestory(customMaterial);
            return 0;
        }

        g_DecalOverrides.push_back({ mesh, skinIndex, originalSlotMaterial, customMaterial });
        return 1;
    }

    int ApplyCustomDecal(UTexture2DDynamic* source)
    {
        if (!source || g_ApplyingDecal || g_ResetPaused.load(std::memory_order_acquire) ||
            EventsComponent::IsTrainingResetQuarantined()) return 0;

        g_ApplyingDecal = true;
        int applied = 0;
        try
        {
            APlayerController* pc = Instances.IAPlayerController();
            APawn* pawn = SafeGetPawn(pc);
            if (pawn && SafeIsLiveObject(pawn) && pawn->IsA<ACar_TA>())
            {
                auto* car = static_cast<ACar_TA*>(pawn);
                applied += ApplyCustomDecalToMesh(SafeGetLiveCarMesh(car), source);
            }

            UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
            if (garage && SafeIsLiveObject(garage) && garage->PreviewActor && SafeIsLiveObject(garage->PreviewActor))
                applied += ApplyCustomDecalToMesh(garage->PreviewActor->CarMesh, source);
        }
        catch (...) {}
        g_ApplyingDecal = false;
        return applied;
    }

    int ApplyCustomBanner(UTexture* source)
    {
        if (!source || g_ApplyingBanner) return 0;
        g_ApplyingBanner = true;
        int count = 0;

        APRI_TA* localPri = nullptr;
        UPlayerBanner_TA* localBanner = nullptr;
        APlayerController* raw = Instances.IAPlayerController();
        if (raw && SafeIsLiveObject(raw) && raw->IsA<APlayerController_TA>())
        {
            localPri = SafeGetPRI(static_cast<APlayerController_TA*>(raw));
            localBanner = SafeGetPlayerBanner(localPri);
            if (localBanner && SafeIsLiveObject(localBanner))
            {
                bool tracked = false;
                for (const auto& entry : g_BannerOverrides) if (entry.banner == localBanner) { tracked = true; break; }
                if (!tracked) g_BannerOverrides.push_back({ localBanner, SafeGetBannerTexture(localBanner) });
                if (SafeSetBannerTexture(localBanner, source)) ++count;
            }
        }

                                                                             
                                                                               
                                                                   
        if (localPri && localBanner)
        {
            TArray<UObject*>* objects = UObject::GObjObjects();
            if (objects)
            {
                for (UObject* object : *objects)
                {
                    if (!object || !object->Class || object->Class->ClassDefaultObject == object)
                        continue;
                    if (object->IsA<UGFxData_PRI_TA>())
                    {
                        auto* data = static_cast<UGFxData_PRI_TA*>(object);
                        if (SafeGetGFxPRI(data) != localPri) continue;
                        UGFxData_PlayerBanner_TA* row = SafeGetGFxPRIBannerRow(data);
                        if (row && SafeIsLiveObject(row))
                        {
                            SafeRefreshGFxBannerRow(row, localBanner);
                            ++count;
                        }
                    }
                }
            }

            try
            {
                UGFxData_PlayerVanity_TA* vanityData = Instances.GetInstanceOf<UGFxData_PlayerVanity_TA>();
                UGFxData_PlayerBanner_TA* row = SafeGetPlayerVanityBannerRow(vanityData);
                if (row && SafeIsLiveObject(row))
                {
                    SafeRefreshGFxBannerRow(row, localBanner);
                    ++count;
                }
            }
            catch (...) {}
        }

                                                                                
                                      
        try
        {
            UGFxData_PlayerBanners_TA* data = Instances.GetInstanceOf<UGFxData_PlayerBanners_TA>();
            UPlayerBanner_TA* preview = SafeGetLastPreviewBanner(data);
            if (preview && SafeIsLiveObject(preview))
            {
                bool tracked = false;
                for (const auto& entry : g_BannerOverrides) if (entry.banner == preview) { tracked = true; break; }
                if (!tracked) g_BannerOverrides.push_back({ preview, SafeGetBannerTexture(preview) });
                if (SafeSetBannerTexture(preview, source)) ++count;
            }
        }
        catch (...) {}

        g_ApplyingBanner = false;
        return count;
    }

    void RestoreBanner()
    {
        for (const auto& entry : g_BannerOverrides)
            if (entry.banner && SafeIsLiveObject(entry.banner)) SafeSetBannerTexture(entry.banner, entry.original);
        g_BannerOverrides.clear();
    }

    void RestoreDecal()
    {
        g_ApplyingDecal = true;
        for (auto& entry : g_DecalOverrides)
        {
            if (entry.mesh && SafeIsLiveObject(entry.mesh) && entry.originalMaterial)
                SafeSetMeshMaterial(entry.mesh, entry.materialIndex, entry.originalMaterial);
            if (entry.customMaterial)
                Instances.MarkForDestory(entry.customMaterial);
        }
        g_DecalOverrides.clear();
        g_ApplyingDecal = false;
    }

    void EnsureFolders()
    {
        std::error_code ec;
        fs::create_directories(g_RootFolder, ec);
        for (const auto& definition : g_Definitions)
            fs::create_directories(g_RootFolder / definition.slug, ec);
    }

    void RestoreSelectionIndex(size_t index, const std::vector<fs::path>& files)
    {
        std::lock_guard<std::mutex> lock(g_StateMutex);
        if (index >= g_States.size()) return;
        auto& state = g_States[index];
        state.selectedFileIndex = -1;
        for (int i = 0; i < static_cast<int>(files.size()); ++i)
            if (files[i].filename().string() == state.selectedFileName) { state.selectedFileIndex = i; break; }
    }
}

CustomTextureStudioModule::CustomTextureStudioModule()
    : Module("CustomTextureStudio", "Custom decal and banner images", States::STATES_All) {}
CustomTextureStudioModule::~CustomTextureStudioModule() {}
void CustomTextureStudioModule::OnCreate() {}
void CustomTextureStudioModule::OnDestroy() {}

const std::array<TextureStudioFeatureDefinition, CustomTextureStudioModule::FeatureCount>& CustomTextureStudioModule::Definitions() { return g_Definitions; }
TextureStudioFeatureState CustomTextureStudioModule::StateForFeature(size_t index)
{
    std::lock_guard<std::mutex> lock(g_StateMutex);
    return index < g_States.size() ? g_States[index] : TextureStudioFeatureState{};
}
fs::path CustomTextureStudioModule::RootFolder() { return g_RootFolder; }
fs::path CustomTextureStudioModule::FolderForFeature(size_t index) { return index < g_Definitions.size() ? g_RootFolder / g_Definitions[index].slug : g_RootFolder; }
std::vector<fs::path> CustomTextureStudioModule::FilesForFeature(size_t index)
{
    std::lock_guard<std::mutex> lock(g_FilesMutex);
    return index < g_Files.size() ? g_Files[index] : std::vector<fs::path>{};
}
std::vector<std::string> CustomTextureStudioModule::TargetsForFeature(size_t) { return {}; }

void CustomTextureStudioModule::Initialize()
{
    wchar_t exePath[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) > 0)
        g_RootFolder = fs::path(exePath).parent_path() / "KingMod" / "Texture" / "Custom";
    else
        g_RootFolder = fs::current_path() / "KingMod" / "Texture" / "Custom";
    g_ConfigPath = g_RootFolder / "custom_images.json";
    EnsureFolders();
    LoadConfig();
    ScanFiles();
    Hook();
    ScheduleMask(EnabledMask(), 900);
    Console.Write("[CustomTexture] Initialized Custom Decal + Custom Banner");
}

void CustomTextureStudioModule::Shutdown()
{
    g_ResetPaused.store(true, std::memory_order_release);
    g_ReapplyAt.store(0, std::memory_order_release);
    g_PendingMask.store(0, std::memory_order_release);
    SaveConfig();
    RestoreAll();
    std::array<UTexture2DDynamic*, FeatureCount> loaded{};
    {
        std::lock_guard<std::mutex> lock(g_StateMutex);
        for (size_t i = 0; i < g_States.size(); ++i) { loaded[i] = g_States[i].loadedTexture; g_States[i].loadedTexture = nullptr; }
    }
    for (UTexture2DDynamic* texture : loaded) if (texture) Instances.MarkForDestory(texture);
}

void CustomTextureStudioModule::ScanFilesForFeature(size_t index)
{
    if (index >= FeatureCount) return;
    std::vector<fs::path> files;
    const fs::path folder = FolderForFeature(index);
    std::error_code ec;
    fs::create_directories(folder, ec);
    for (const auto& entry : fs::directory_iterator(folder, ec))
    {
        if (!entry.is_regular_file(ec)) continue;
        const std::string extension = LowerCopy(entry.path().extension().string());
        if (extension == ".png" || extension == ".jpg" || extension == ".jpeg") files.push_back(entry.path());
    }
    std::sort(files.begin(), files.end(), [](const fs::path& a, const fs::path& b) { return a.filename().string() < b.filename().string(); });
    { std::lock_guard<std::mutex> lock(g_FilesMutex); g_Files[index] = files; }
    RestoreSelectionIndex(index, files);
}
void CustomTextureStudioModule::ScanFiles() { EnsureFolders(); for (size_t i = 0; i < FeatureCount; ++i) ScanFilesForFeature(i); }
void CustomTextureStudioModule::RequestLiveTextureRescan(bool reapplyAfterScan) { if (reapplyAfterScan) ScheduleMask(EnabledMask(), 100); }
bool CustomTextureStudioModule::IsScanning() { return false; }
float CustomTextureStudioModule::ScanProgress() { return 1.0f; }
int CustomTextureStudioModule::MatchCount(size_t index)
{
    std::lock_guard<std::mutex> lock(g_StateMutex);
    return index < g_LastApplyCount.size() ? g_LastApplyCount[index] : 0;
}

void CustomTextureStudioModule::SetEnabled(size_t index, bool enabled)
{
    if (index >= FeatureCount) return;
    { std::lock_guard<std::mutex> lock(g_StateMutex); g_States[index].enabled = enabled; }
    if (enabled) ApplyFeature(index); else RestoreFeature(index);
    SaveConfig();
}

void CustomTextureStudioModule::SelectImage(size_t index, int fileIndex)
{
    if (index >= FeatureCount) return;
    fs::path selectedPath;
    {
        std::lock_guard<std::mutex> lock(g_FilesMutex);
        if (fileIndex < 0 || fileIndex >= static_cast<int>(g_Files[index].size())) return;
        selectedPath = g_Files[index][fileIndex];
    }
    RestoreFeature(index);
    UTexture2DDynamic* oldTexture = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_StateMutex);
        oldTexture = g_States[index].loadedTexture;
        g_States[index].loadedTexture = nullptr;
        g_States[index].selectedFileIndex = fileIndex;
        g_States[index].selectedFileName = selectedPath.filename().string();
        g_States[index].enabled = true;
    }
    if (oldTexture) Instances.MarkForDestory(oldTexture);
    SaveConfig();
    ApplyFeature(index);
}
void CustomTextureStudioModule::SetSelectedTarget(size_t, const std::string&) {}

void CustomTextureStudioModule::ApplyFeature(size_t index)
{
    if (index >= FeatureCount || g_ResetPaused.load(std::memory_order_acquire) || EventsComponent::IsTrainingResetQuarantined()) return;
    UTexture2DDynamic* texture = EnsureLoadedTexture(index);
    if (!texture) return;
    if (index == CustomDecal) RestoreDecal(); else if (index == CustomBanner) RestoreBanner();
    const int applied = index == CustomDecal ? ApplyCustomDecal(texture) : ApplyCustomBanner(static_cast<UTexture*>(texture));
    { std::lock_guard<std::mutex> lock(g_StateMutex); g_LastApplyCount[index] = applied; }
    if (applied > 0) Console.Write("[CustomTexture] " + std::string(g_Definitions[index].label) + ": " + std::to_string(applied) + " target(s)");
}

void CustomTextureStudioModule::ApplyAllEnabled()
{
    if (g_ResetPaused.load(std::memory_order_acquire) || EventsComponent::IsTrainingResetQuarantined()) return;
    for (size_t i = 0; i < FeatureCount; ++i) if (IsEnabled(i)) ApplyFeature(i);
}
void CustomTextureStudioModule::RestoreFeature(size_t index)
{
    if (index == CustomDecal) RestoreDecal();
    else if (index == CustomBanner) RestoreBanner();
    std::lock_guard<std::mutex> lock(g_StateMutex);
    if (index < g_LastApplyCount.size()) g_LastApplyCount[index] = 0;
}
void CustomTextureStudioModule::RestoreAll()
{
    RestoreDecal(); RestoreBanner();
    std::lock_guard<std::mutex> lock(g_StateMutex);
    g_LastApplyCount.fill(0);
}

void CustomTextureStudioModule::SaveConfig()
{
    if (g_ConfigPath.empty()) return;
    try
    {
        std::array<TextureStudioFeatureState, FeatureCount> states;
        { std::lock_guard<std::mutex> lock(g_StateMutex); states = g_States; }
        json root;
        for (size_t i = 0; i < FeatureCount; ++i)
            root[g_Definitions[i].slug] = { { "enabled", states[i].enabled }, { "file", states[i].selectedFileName } };
        std::error_code ec; fs::create_directories(g_ConfigPath.parent_path(), ec);
        std::ofstream file(g_ConfigPath); if (file.is_open()) file << root.dump(2);
    }
    catch (...) {}
}
void CustomTextureStudioModule::LoadConfig()
{
    if (g_ConfigPath.empty() || !fs::exists(g_ConfigPath)) return;
    try
    {
        std::ifstream file(g_ConfigPath); if (!file.is_open()) return;
        json root; file >> root;
        std::lock_guard<std::mutex> lock(g_StateMutex);
        for (size_t i = 0; i < FeatureCount; ++i)
        {
            const char* slug = g_Definitions[i].slug;
            if (!root.contains(slug) || !root[slug].is_object()) continue;
            g_States[i].enabled = root[slug].value("enabled", false);
            g_States[i].selectedFileName = root[slug].value("file", std::string());
        }
    }
    catch (...) {}
}

void CustomTextureStudioModule::PrepareForGameplayReset()
{
    g_ResetPaused.store(true, std::memory_order_release);
    g_ReapplyAt.store(0, std::memory_order_release);
    g_PendingMask.store(0, std::memory_order_release);
    RestoreDecal();
}
void CustomTextureStudioModule::NotifyGameplayReset()
{
    g_ResetPaused.store(true, std::memory_order_release);
    uint32_t mask = 0;
    if (IsEnabled(CustomDecal)) mask |= (1u << CustomDecal);
    if (IsEnabled(CustomBanner)) mask |= (1u << CustomBanner);
    ScheduleMask(mask, kResetReapplyDelayMs);
    if (!mask) g_ResetPaused.store(false, std::memory_order_release);
}

void CustomTextureStudioModule::Hook()
{
    if (g_Hooked) return;
    g_Hooked = true;

    Events.HookEventPost("Function TAGame.Car_TA.EventVehicleSetup", [](const PostEvent&)
    {
        if (IsEnabled(CustomDecal)) ScheduleMask(1u << CustomDecal, kVehicleReapplyDelayMs);
    });

    Events.HookEventPost("Function TAGame.CarMeshComponentBase_TA.AddVisualAsset", [](const PostEvent& event)
    {
        if (g_ApplyingDecal || !IsEnabled(CustomDecal)) return;
        auto* params = event.GetParams<UCarMeshComponentBase_TA_execAddVisualAsset_Params>();
        if (!params || !params->Asset || !params->Asset->IsA(UProductAsset_Skin_TA::StaticClass())) return;
        ScheduleMask(1u << CustomDecal, 100);
    });

    Events.HookEventPost("Function TAGame.CarMeshComponentBase_TA.ApplyPaintSettings", [](const PostEvent&)
    {
        if (g_ApplyingDecal || !IsEnabled(CustomDecal)) return;
        ScheduleMask(1u << CustomDecal, 60);
    });

    Events.HookEventPost("Function TAGame.PRI_TA.UpdatePlayerBanner", [](const PostEvent&)
    {
        if (IsEnabled(CustomBanner)) ScheduleMask(1u << CustomBanner, 100);
    });

    Events.HookEventPost("Function TAGame.PlayerBanner_TA.HandleLoaded", [](const PostEvent&)
    {
        if (!g_ApplyingBanner && IsEnabled(CustomBanner)) ScheduleMask(1u << CustomBanner, 40);
    });

    Events.HookEventPost("Function TAGame.GFxData_PRI_TA.UpdatePlayerBanner", [](const PostEvent&)
    {
        if (!g_ApplyingBanner && IsEnabled(CustomBanner)) ScheduleMask(1u << CustomBanner, 40);
    });

    Events.HookEventPost("Function TAGame.GFxData_PlayerBanners_TA.HandleBannerPreviewLoaded", [](const PostEvent&)
    {
        if (!g_ApplyingBanner && IsEnabled(CustomBanner)) ScheduleMask(1u << CustomBanner, 40);
    });

    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay", [](PreEvent&)
    {
        IsInGame = true;
        ScheduleMask(EnabledMask(), kResetReapplyDelayMs);
    });

    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed", [](PreEvent&)
    {
        IsInGame = false;
        RestoreDecal();
        g_ResetPaused.store(false, std::memory_order_release);
        uint32_t mask = IsEnabled(CustomBanner) ? (1u << CustomBanner) : 0;
        if (mask) ScheduleMask(mask, 700);
    });

    Events.HookEventPost("Function Engine.GameViewportClient.Tick", [](const PostEvent&)
    {
        if (EventsComponent::IsTrainingResetQuarantined()) return;
        const ULONGLONG at = g_ReapplyAt.load(std::memory_order_acquire);
        if (!at || GetTickCount64() < at) return;
        g_ReapplyAt.store(0, std::memory_order_release);
        g_ResetPaused.store(false, std::memory_order_release);
        const uint32_t mask = g_PendingMask.exchange(0, std::memory_order_acq_rel);
        for (size_t i = 0; i < CustomTextureStudioModule::FeatureCount; ++i)
            if ((mask & (1u << static_cast<uint32_t>(i))) && IsEnabled(i)) CustomTextureStudioModule::ApplyFeature(i);
    });
}
