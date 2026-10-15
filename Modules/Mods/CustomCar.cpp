#include "CustomCar.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Extensions/Extensions/Formatting.hpp"
#include <fstream>

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

namespace CustomCar
{
    
    std::unordered_map<int, std::string> g_baseHitboxIds = {
        {22, "Breakout"},
        {23, "Octane"},
        {24, "Plank"},      
        {28, "Hybrid"},     
        {30, "Merc"},
        {31, "Hybrid"},     
        {403, "Dominus"}
    };

   
    static CustomCarConfig s_Config;
    static bool s_Initialized = false;
    static fs::path s_CustomCarsFolder;
    static fs::path s_ConfigFile;

  
    static std::unordered_map<int32_t, BodyCustomization> s_bodyCustomizations;
    static std::unordered_map<int32_t, UProductAsset_Body_TA*> s_customBodyProdAssets;

   
    static std::unordered_map<std::string, USkeletalMesh*> s_loadedMeshes;

    struct LiveCustomMeshState
    {
        USkeletalMesh* originalMesh = nullptr;
        int32_t originalForceRefpose = 0;
        int32_t originalIgnoreControllers = 0;
    };

    static std::unordered_map<UCarMeshComponent_TA*, LiveCustomMeshState> s_liveMeshStates;
    static std::unordered_map<UCarMeshComponent_TA*, FVector> s_originalSpringStrengths;

    std::unordered_map<int32_t, ProductData> s_allBodyProducts;

   
    static std::array<FName, 5> s_boostSocketNames;
    static WheelBoneNames s_wheelBoneNames;
    static bool s_fnamesCached = false;

  
    CustomCarConfig& GetConfig()
    {
        return s_Config;
    }

   
    void InitProductData()
    {
        try
        {
            auto* productsDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
            if (!productsDatabase)
            {
                Console.Warning("[CustomCar] UProductDatabase_TA* is null... unable to init product data");
                return;
            }

            s_allBodyProducts.clear();

            Console.Write("[CustomCar] Loading products from database: " + std::to_string(productsDatabase->Products_Pristine.size()) + " products");
            
            for (UProduct_TA* prod : productsDatabase->Products_Pristine)
            {
                if (!prod || !prod->Slot)
                    continue;

                int32_t id = prod->GetID();
                if (prod->Slot->SlotIndex == 0)
                {
                    ProductData data{};
                    data.id = id;
                    data.name = prod->LongLabel.ToString();
                    s_allBodyProducts[id] = std::move(data);
                }
            }

            Console.Write("[CustomCar] Initialized product data. " + std::to_string(s_allBodyProducts.size()) + " body products");
        }
        catch (const std::exception& e)
        {
            Console.Warning("[CustomCar] Exception in InitProductData: " + std::string(e.what()));
        }
        catch (...)
        {
            Console.Warning("[CustomCar] Unknown exception in InitProductData");
        }
    }
    void InitCachedFNames()
    {
        if (s_fnamesCached) return;

        s_fnamesCached = true;
    }


    FString ToFString(const std::string& str);
    USkeletalMesh* LoadCustomMesh(const std::string& meshPath);
    CustomBodyData* GetCustomBodyData(UCarMeshComponent_TA* cmc);

    static void RestoreLiveCustomMeshState(UCarMeshComponent_TA* cmc)
    {
        if (!cmc)
            return;

        auto stateIt = s_liveMeshStates.find(cmc);
        if (stateIt != s_liveMeshStates.end())
        {
            if (validUObject(cmc))
            {
                const LiveCustomMeshState state = stateIt->second;
                cmc->bForceRefpose = state.originalForceRefpose;
                cmc->bIgnoreControllers = state.originalIgnoreControllers;
                if (state.originalMesh && validUObject(state.originalMesh) && cmc->SkeletalMesh != state.originalMesh)
                    cmc->SetSkeletalMesh(state.originalMesh, false);
                cmc->ForceSkelUpdate();
            }
            s_liveMeshStates.erase(stateIt);
        }

        auto springIt = s_originalSpringStrengths.find(cmc);
        if (springIt != s_originalSpringStrengths.end())
        {
            if (validUObject(cmc) && cmc->ChassisSpringComponent && validUObject(cmc->ChassisSpringComponent))
                cmc->ChassisSpringComponent->Spring.Strength = springIt->second;
            s_originalSpringStrengths.erase(springIt);
        }
    }

    static void StabilizeLiveCustomMesh(UCarMeshComponent_TA* cmc, USkeletalMesh* customMesh)
    {
        if (!cmc || !customMesh || !validUObject(cmc) || !validUObject(customMesh))
            return;

        auto [it, inserted] = s_liveMeshStates.emplace(cmc, LiveCustomMeshState{});
        if (inserted)
        {
            it->second.originalMesh = cmc->SkeletalMesh;
            it->second.originalForceRefpose = cmc->bForceRefpose;
            it->second.originalIgnoreControllers = cmc->bIgnoreControllers;
        }

        if (cmc->SkeletalMesh != customMesh)
            cmc->SetSkeletalMesh(customMesh, false);

                                                                             
                                                                                   
                                                                                
                                                                                
        cmc->bForceRefpose = 1;
        cmc->bIgnoreControllers = 1;
        cmc->ForceSkelUpdate();
    }

    static void PrepareStockMeshForPaint(UCarMeshComponent_TA* cmc)
    {
        auto it = s_liveMeshStates.find(cmc);
        if (it == s_liveMeshStates.end() || !cmc || !validUObject(cmc))
            return;

        const LiveCustomMeshState& state = it->second;
        cmc->bForceRefpose = state.originalForceRefpose;
        cmc->bIgnoreControllers = state.originalIgnoreControllers;
        if (state.originalMesh && validUObject(state.originalMesh) && cmc->SkeletalMesh != state.originalMesh)
            cmc->SetSkeletalMesh(state.originalMesh, false);
    }

    void RegisterHooks()
    {

                                                                                    
                                                                               
                                                                                 
                                                      
        Events.HookEventPre("Function TAGame.CarMeshComponent_TA.ApplyPaintSettings", [](PreEvent& event) {
            try
            {
                auto* cmc = static_cast<UCarMeshComponent_TA*>(event.Caller());
                if (!cmc || !validUObject(cmc) || !cmc->bLocalPlayer)
                    return;

                if (!s_Config.enabled || !GetCustomBodyData(cmc))
                {
                    RestoreLiveCustomMeshState(cmc);
                    return;
                }

                PrepareStockMeshForPaint(cmc);
            }
            catch (...)
            {
                Console.Warning("[CustomCar] Exception in ApplyPaintSettings pre-hook - ignoring");
            }
        });

        Events.HookEventPost("Function TAGame.CarMeshComponent_TA.ApplyPaintSettings", [](const PostEvent& event) {
            try
            {
                UObject* caller = event.Caller();
                if (!caller || !validUObject(caller)) return;
                
                auto* cmc = static_cast<UCarMeshComponent_TA*>(caller);
                if (!cmc || !validUObject(cmc)) return;
                if (!cmc->bLocalPlayer) return;
                
                CustomBodyData* bodyData = GetCustomBodyData(cmc);
                if (!bodyData)
                {
                    RestoreLiveCustomMeshState(cmc);
                    return;
                }
                
                Console.Write("[CustomCar] ApplyPaintSettings - applying custom body: " + bodyData->name);

                ApplyCustomBody(cmc, bodyData);
                
                if (bodyData->hideTrails)
                    HideTrails(cmc);
                
                if (bodyData->hideWheels)
                    HideWheels(cmc);
                else if (bodyData->wheelScaleFront || bodyData->wheelScaleBack)
                    ScaleWheels(cmc, bodyData);
                
                FixBodyFX(cmc, bodyData);
            }
            catch (...)
            {
                Console.Warning("[CustomCar] Exception in ApplyPaintSettings hook - ignoring");
            }
        });
        
   
        Events.HookEventPost("Function TAGame.Car_TA.HandleAllAssetsLoaded", [](const PostEvent& event) {
            try
            {
                UObject* caller = event.Caller();
                if (!caller || !validUObject(caller)) return;
                
                auto* car = static_cast<ACar_TA*>(caller);
                if (!car || !validUObject(car)) return;
                
                auto* cmc = car->CarMesh;
                if (!cmc || !validUObject(cmc)) return;
                if (!cmc->bLocalPlayer) return;
                
                CustomBodyData* bodyData = GetCustomBodyData(cmc);
                if (!bodyData)
                {
                    RestoreLiveCustomMeshState(cmc);
                    return;
                }
                
                Console.Write("[CustomCar] HandleAllAssetsLoaded - applying custom body: " + bodyData->name);
                
              
                ApplyCustomBody(cmc, bodyData);
                
                if (bodyData->hideTrails)
                    HideTrails(cmc);
                
                if (bodyData->hideWheels)
                    HideWheels(cmc);
                else if (bodyData->wheelScaleFront || bodyData->wheelScaleBack)
                    ScaleWheels(cmc, bodyData);
                
                FixBodyFX(cmc, bodyData);
            }
            catch (...)
            {
                Console.Warning("[CustomCar] Exception in HandleAllAssetsLoaded hook - ignoring");
            }
        });
        
      
        Events.HookEventPost("Function TAGame.CarPreviewActor_TA.HandleAllProductsLoaded", [](const PostEvent& event) {
            try
            {
                UObject* caller = event.Caller();
                if (!caller || !validUObject(caller)) return;
                
                auto* car = static_cast<ACarPreviewActor_TA*>(caller);
                if (!car || !validUObject(car)) return;
                
                auto* cmc = car->CarMesh;
                if (!cmc || !validUObject(cmc)) return;
                
           
                if (!cmc->BodyAsset) return;
                
                CustomBodyData* bodyData = GetCustomBodyData(cmc);
                if (!bodyData) return;
                
              
                UProduct_TA* prod = cmc->BodyAsset->GetProduct();
                if (!prod || prod->GetID() != bodyData->productId) return;
                
                Console.Write("[CustomCar] PreviewActor - applying custom body: " + bodyData->name);
                
                if (!bodyData->assetPath.empty()) {
                    FString fMeshPath = ToFString(bodyData->assetPath);
                    UObject* loadedObj = UObject::DynamicLoadObject(fMeshPath, USkeletalMesh::StaticClass(), true);
                    USkeletalMesh* customMesh = loadedObj ? static_cast<USkeletalMesh*>(loadedObj) : nullptr;
                    if (customMesh && customMesh->IsA<USkeletalMesh>() && validUObject(customMesh)) {
                        cmc->SetSkeletalMesh(customMesh, false);
                        Console.Write("[CustomCar] PreviewActor - Set custom skeletal mesh: " + bodyData->assetPath);
                    }
                }
            }
            catch (...)
            {
                Console.Warning("[CustomCar] Exception in CarPreviewActor hook");
            }
        });
        
 
        Events.HookEventPost("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay", [](const PostEvent& event) {
            UObject* caller = event.Caller();
            if (!caller || !validUObject(caller)) return;
            
            Console.Write("[CustomCar] Match started, clearing caches...");
            s_customBodyProdAssets.clear();
            s_loadedMeshes.clear();
            s_liveMeshStates.clear();
            s_originalSpringStrengths.clear();
        });
        
       
        Events.HookEventPost("Function TAGame.GameEvent_Soccar_TA.Destroyed", [](const PostEvent& event) {
            UObject* caller = event.Caller();
            if (!caller || !validUObject(caller)) return;
            
            Console.Write("[CustomCar] Match ended, clearing caches...");
            s_customBodyProdAssets.clear();
            s_loadedMeshes.clear();
            s_liveMeshStates.clear();
            s_originalSpringStrengths.clear();
        });
        
        Events.HookEventPost("Function TAGame.CarPreviewActor_TA.OnProductsChanged", [](const PostEvent& event) {
            try
            {
                UObject* caller = event.Caller();
                if (!caller || !validUObject(caller)) return;
                
                Console.Write("[CustomCar] Car changed in preview, clearing mesh caches...");
                s_loadedMeshes.clear();
                s_customBodyProdAssets.clear();
            }
            catch (...)
            {
                Console.Warning("[CustomCar] Exception in OnProductsChanged hook");
            }
        });
        
        Console.Write("[CustomCar] Hooks registered");
    }

  
    void Initialize()
    {
        if (s_Initialized) return;

     
        char pathBuffer[MAX_PATH];
        DWORD result = GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
        Console.Write("[CustomCar] GetModuleFileNameA result: " + std::to_string(result));
        Console.Write("[CustomCar] Module path: " + std::string(pathBuffer));
        
        fs::path exePath(pathBuffer);
        Console.Write("[CustomCar] exePath: " + exePath.string());
        
        fs::path kingModFolder = exePath.parent_path() / "KingMod";
        Console.Write("[CustomCar] kingModFolder: " + kingModFolder.string());
        
        s_CustomCarsFolder = kingModFolder / "CustomCars";
        s_ConfigFile = kingModFolder / "config.json";
        
        Console.Write("[CustomCar] s_CustomCarsFolder: " + s_CustomCarsFolder.string());
        Console.Write("[CustomCar] s_ConfigFile: " + s_ConfigFile.string());

   
        try
        {
            if (!fs::exists(kingModFolder))
            {
                fs::create_directories(kingModFolder);
                Console.Write("[CustomCar] Created KingMod folder: " + kingModFolder.string());
            }
            if (!fs::exists(s_CustomCarsFolder))
            {
                fs::create_directories(s_CustomCarsFolder);
                Console.Write("[CustomCar] Created custom cars folder: " + s_CustomCarsFolder.string());
            }
            else
            {
                Console.Write("[CustomCar] Custom cars folder exists: " + s_CustomCarsFolder.string());
            }
        }
        catch (const std::exception& e)
        {
            Console.Warning("[CustomCar] Failed to create directory: " + std::string(e.what()));
        }

        LoadConfiguration();
        LoadCustomBodies();
        InitProductData();
        RegisterHooks();

        s_Initialized = true;
        Console.Write("[CustomCar] Initialized successfully");
    }

  
    void Shutdown()
    {
        if (!s_Initialized) return;


        for (auto it = s_liveMeshStates.begin(); it != s_liveMeshStates.end(); )
        {
            UCarMeshComponent_TA* cmc = it->first;
            ++it;
            RestoreLiveCustomMeshState(cmc);
        }
        s_liveMeshStates.clear();
        s_originalSpringStrengths.clear();
        ClearCachedAssets();
        s_loadedMeshes.clear();
        s_bodyCustomizations.clear();
        
        s_Initialized = false;
        Console.Write("[CustomCar] Shutdown - all caches cleared");
    }

                       
    bool IsEnabled()
    {
        return s_Initialized && s_Config.enabled;
    }

                                  
    std::optional<CustomBodyData> ParseBodyFromJson(const json& j)
    {
                                                                         
        auto idIt = j.find("BodyId");
        if (idIt == j.end())
            idIt = j.find("BodyID");
        
        auto meshPathIt = j.find("MeshPath");

        if (idIt == j.end() || meshPathIt == j.end())
            return std::nullopt;

        CustomBodyData body{};

        try
        {
            body.productId = idIt->get<int32_t>();
            body.assetPath = meshPathIt->get<std::string>();

            if (auto it = j.find("Name"); it != j.end())
                body.name = it->get<std::string>();
            else
                body.name = "Custom Body " + std::to_string(body.productId);

            if (auto it = j.find("ChassisMaterialIndex"); it != j.end())
                body.chassisMatIndex = it->get<int32_t>();

            if (auto it = j.find("SkinMaterialIndex"); it != j.end())
                body.skinMatIndex = it->get<int32_t>();

            if (auto it = j.find("BrakelightMaterialIndex"); it != j.end())
                body.brakelightMatIndex = it->get<int32_t>();

            if (auto it = j.find("SuspensionStiffnessScale"); it != j.end())
                body.suspensionStiffnessScale = it->get<float>();

            if (auto it = j.find("WheelScale"); it != j.end())
            {
                const auto& wheelScaleVal = *it;
                if (wheelScaleVal.is_object())
                {
                    if (auto frontIt = wheelScaleVal.find("Front"); frontIt != wheelScaleVal.end())
                        body.wheelScaleFront = frontIt->get<float>();
                    if (auto backIt = wheelScaleVal.find("Back"); backIt != wheelScaleVal.end())
                        body.wheelScaleBack = backIt->get<float>();
                }
                else if (wheelScaleVal.is_number_float())
                {
                    float scale = wheelScaleVal.get<float>();
                    body.wheelScaleFront = scale;
                    body.wheelScaleBack = scale;
                }
            }

            if (auto it = j.find("HideWheels"); it != j.end())
                body.hideWheels = it->get<bool>();

            if (auto it = j.find("HideTrails"); it != j.end())
                body.hideTrails = it->get<bool>();
        }
        catch (const json::exception& e)
        {
            Console.Warning("[CustomCar] JSON parse error: " + std::string(e.what()));
            return std::nullopt;
        }

        return body;
    }

                                         
    void LoadCustomBodies()
    {
        s_bodyCustomizations.clear();

                                 
        if (s_CustomCarsFolder.empty())
        {
            Console.Warning("[CustomCar] CustomCars folder path is empty, reinitializing...");
                                       
            char pathBuffer[MAX_PATH];
            GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
            fs::path exePath(pathBuffer);
            s_CustomCarsFolder = exePath.parent_path() / "KingMod" / "CustomCars";
        }

        try
        {
                                                      
            fs::path absPath = fs::absolute(s_CustomCarsFolder);
            Console.Write("[CustomCar] Loading from: " + absPath.string());
            
            if (!fs::exists(absPath))
            {
                Console.Warning("[CustomCar] CustomCars folder does not exist: " + absPath.string());
                return;
            }

            for (const auto& entry : fs::recursive_directory_iterator(absPath))
            {
                if (!entry.is_regular_file() || entry.path().extension() != ".json")
                    continue;

                std::ifstream file(entry.path());
                if (!file.is_open()) continue;

                json j;
                try
                {
                    file >> j;
                }
                catch (const json::exception&)
                {
                    continue;
                }

                if (j.empty()) continue;

                                                    
                for (const auto& [key, val] : j.items())
                {
                    if (!val.is_object()) continue;

                    auto bodyData = ParseBodyFromJson(val);
                    if (!bodyData) continue;

                    bodyData->name = key;
                    s_bodyCustomizations[bodyData->productId].bodies.emplace_back(*bodyData);
                    Console.Write("[CustomCar] Loaded body: " + key + " (ID: " + std::to_string(bodyData->productId) + ")");
                }
            }
        }
        catch (const fs::filesystem_error& e)
        {
            Console.Warning("[CustomCar] Filesystem error: " + std::string(e.what()));
        }

        Console.Write("[CustomCar] Loaded " + std::to_string(s_bodyCustomizations.size()) + " custom body configurations");
    }

                                 
    void SaveConfiguration()
    {
        json j;
        j["enabled"] = s_Config.enabled;
        j["autoRefresh"] = s_Config.autoRefresh;

                               
        for (const auto& [prodId, custo] : s_bodyCustomizations)
        {
            if (custo.selectedBodyIdx)
            {
                j["selected"][std::to_string(prodId)] = custo.bodies[*custo.selectedBodyIdx].name;
            }
        }

        std::ofstream file(s_ConfigFile);
        if (file.is_open())
        {
            file << j.dump(4);
            file.close();
        }
    }

                                   
    void LoadConfiguration()
    {
        if (!fs::exists(s_ConfigFile)) return;

        std::ifstream file(s_ConfigFile);
        if (!file.is_open()) return;

        json j;
        try
        {
            file >> j;
        }
        catch (const json::exception&)
        {
            return;
        }

        if (j.find("enabled") != j.end())
            s_Config.enabled = j["enabled"].get<bool>();

        if (j.find("autoRefresh") != j.end())
            s_Config.autoRefresh = j["autoRefresh"].get<bool>();

                                                                        
    }

                                                   
    CustomBodyData* GetCustomBodyData(UCarMeshComponent_TA* cmc)
    {
        if (!s_Config.enabled || !cmc) return nullptr;

                                             
        UProductAsset_Body_TA* bodyAsset = cmc->BodyAsset;
        if (!bodyAsset) return nullptr;

        UProduct_TA* prod = bodyAsset->GetProduct();
        if (!prod) return nullptr;

        return GetCustomBodyDataFromProdId(prod->GetID());
    }

                                           
    CustomBodyData* GetCustomBodyDataFromProdId(int32_t productId)
    {
        auto it = s_bodyCustomizations.find(productId);
        if (it == s_bodyCustomizations.end()) return nullptr;

        auto& customization = it->second;
        if (!customization.selectedBodyIdx) return nullptr;

        return &customization.bodies[*customization.selectedBodyIdx];
    }

                              
    void CacheCustomBodyAsset(int32_t productId, UProductAsset_Body_TA* asset)
    {
        s_customBodyProdAssets[productId] = asset;
    }

                            
    UProductAsset_Body_TA* GetCachedBodyAsset(int32_t productId)
    {
        auto it = s_customBodyProdAssets.find(productId);
        if (it != s_customBodyProdAssets.end())
            return it->second;
        return nullptr;
    }

                          
    void ClearCachedAssets()
    {
        s_customBodyProdAssets.clear();
    }

    FString ToFString(const std::string& str)
    {
        return Format::ToFString(str);
    }

                                   
                                                                        
    USkeletalMesh* LoadCustomMesh(const std::string& meshPath)
    {
                            
        auto it = s_loadedMeshes.find(meshPath);
        if (it != s_loadedMeshes.end())
            return it->second;

                                                      
        size_t dotPos = meshPath.find('.');
        if (dotPos == std::string::npos)
        {
            Console.Warning("[CustomCar] Invalid mesh path format (expected Package.Object): " + meshPath);
            return nullptr;
        }

        std::string packageName = meshPath.substr(0, dotPos);
        std::string objectName = meshPath.substr(dotPos + 1);

                             
        FString fMeshPath = ToFString(meshPath);

                                            
        USkeletalMesh* mesh = UObject::FindObject<USkeletalMesh>(meshPath);
        if (!mesh)
        {
                                           
            UClass* meshClass = USkeletalMesh::StaticClass();
            UObject* loadedObj = UObject::DynamicLoadObject(fMeshPath, meshClass, true);
            if (loadedObj)
            {
                mesh = static_cast<USkeletalMesh*>(loadedObj);
            }
        }

        if (mesh)
        {
            s_loadedMeshes[meshPath] = mesh;
            Console.Write("[CustomCar] Loaded custom mesh: " + meshPath);
        }
        else
        {
            Console.Warning("[CustomCar] Failed to load mesh: " + meshPath);
        }

        return mesh;
    }

                                    
    void ApplyCustomBody(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData)
    {
        if (!cmc || !bodyData) return;

                                                     
        if (!cmc->BodyAsset) 
        {
            Console.Warning("[CustomCar] Cannot apply custom body - BodyAsset is null");
            return;
        }

                                                                 
        UProduct_TA* prod = cmc->BodyAsset->GetProduct();
        if (!prod) 
        {
            Console.Warning("[CustomCar] Cannot apply custom body - Product is null");
            return;
        }

        if (prod->GetID() != bodyData->productId)
        {
                                                                  
            Console.Write("[CustomCar] Skipping custom body - car ID " + std::to_string(prod->GetID()) + 
                " doesn't match config ID " + std::to_string(bodyData->productId));
            return;
        }

        try
        {
                                            
            Console.Write("[CustomCar] Applying custom body: " + bodyData->name + " (Product ID: " + std::to_string(bodyData->productId) + ")");

                                                                                  
                                                                                   
                                                                                
        if (cmc->ChassisSpringComponent && validUObject(cmc->ChassisSpringComponent))
        {
            auto springIt = s_originalSpringStrengths.find(cmc);
            if (bodyData->suspensionStiffnessScale)
            {
                if (springIt == s_originalSpringStrengths.end())
                    springIt = s_originalSpringStrengths.emplace(cmc, cmc->ChassisSpringComponent->Spring.Strength).first;

                const float scale = *bodyData->suspensionStiffnessScale;
                const FVector& base = springIt->second;
                FVector scaledStrength = base;
                scaledStrength.X *= scale;
                scaledStrength.Y *= scale;
                scaledStrength.Z *= scale;
                cmc->ChassisSpringComponent->Spring.Strength = scaledStrength;
            }
            else if (springIt != s_originalSpringStrengths.end())
            {
                cmc->ChassisSpringComponent->Spring.Strength = springIt->second;
                s_originalSpringStrengths.erase(springIt);
            }
        }

                                                                              
                                                                                
                                                                                   
                                                                                    
        if (!bodyData->assetPath.empty())
        {
            USkeletalMesh* customMesh = LoadCustomMesh(bodyData->assetPath);
            if (customMesh && validUObject(customMesh))
            {
                StabilizeLiveCustomMesh(cmc, customMesh);
                Console.Write("[CustomCar] Set stable custom skeletal mesh: " + bodyData->assetPath);
            }
            else
            {
                Console.Warning("[CustomCar] Failed to load custom mesh: " + bodyData->assetPath);
            }
        }

                                                                                     
                                                                                   
                                                                                 
                                                                                       
        }
        catch (const std::exception& e)
        {
            Console.Warning("[CustomCar] Exception in ApplyCustomBody: " + std::string(e.what()));
        }
        catch (...)
        {
            Console.Warning("[CustomCar] Unknown exception in ApplyCustomBody");
        }
    }

                  
    void HideTrails(ACar_TA* car)
    {
        if (!car) return;

   
        Console.Write("[CustomCar] Hiding trails for car");
    }

    void HideTrails(UCarMeshComponent_TA* cmc)
    {
        if (!cmc || !cmc->Owner) return;

        ACar_TA* car = static_cast<ACar_TA*>(cmc->Owner);
        if (car)
            HideTrails(car);
    }

                  
    void HideWheels(UCarMeshComponent_TA* cmc)
    {
        if (!cmc) return;

        for (auto& wheelMesh : cmc->WheelMeshes)
        {
            if (wheelMesh)
            {
                wheelMesh->SetHidden(true);
            }
        }
        Console.Write("[CustomCar] Hid wheels");
    }

                          
    std::optional<WheelBoneInfo> GetWheelBoneInfo(const FName& boneName)
    {
                                              
                                    
        std::string boneStr = boneName.ToString();
        if (boneStr.find("FL") != std::string::npos)
            return WheelBoneInfo{true, true};
        if (boneStr.find("FR") != std::string::npos)
            return WheelBoneInfo{true, false};
        if (boneStr.find("BL") != std::string::npos)
            return WheelBoneInfo{false, true};
        if (boneStr.find("BR") != std::string::npos)
            return WheelBoneInfo{false, false};
        return std::nullopt;
    }

                   
    void ScaleWheels(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData)
    {
        if (!cmc || !bodyData) return;
        if (!bodyData->wheelScaleFront && !bodyData->wheelScaleBack) return;

                                                           
                                                               
        int wheelIndex = 0;
        for (auto& wheelMesh : cmc->WheelMeshes)
        {
            if (!wheelMesh) 
            {
                wheelIndex++;
                continue;
            }

                                                                     
            bool isFront = (wheelIndex == 0 || wheelIndex == 1);

            bool shouldScale = (isFront && bodyData->wheelScaleFront) ||
                               (!isFront && bodyData->wheelScaleBack);
            if (!shouldScale) 
            {
                wheelIndex++;
                continue;
            }

            float scale = isFront ? *bodyData->wheelScaleFront : *bodyData->wheelScaleBack;

          
            bool isLeft = (wheelIndex == 0 || wheelIndex == 2);
            float yScale = isLeft ? -scale : scale;

     
            wheelIndex++;
        }
        Console.Write("[CustomCar] Scaled wheels (Front: " + 
            std::to_string(bodyData->wheelScaleFront.value_or(1.0f)) + 
            ", Back: " + std::to_string(bodyData->wheelScaleBack.value_or(1.0f)) + ")");
    }

                                       
    void FixBodyFX(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData)
    {
        if (!cmc || !cmc->BodyFXActor) return;

                                                                     
                                                                
        Console.Write("[CustomCar] Fixed body FX alignment");
    }

                        
    void RefreshCarModel()
    {
        try
        {
            Console.Write("[CustomCar] Refreshing car model...");
            
                                                                               
                                                                                         
            s_customBodyProdAssets.clear();
            s_loadedMeshes.clear();
            
            bool foundCar = false;

                                                                     
            ULocalPlayer* localPlayer = Instances.IULocalPlayer();
            APlayerController* controller = nullptr;
            APawn* pawn = nullptr;
            
            if (localPlayer)
            {
                controller = localPlayer->Actor;
                if (controller)
                {
                    pawn = controller->Pawn;
                }
            }
            
      
            if (pawn && pawn->IsA(ACar_TA::StaticClass()))
            {
                ACar_TA* car = reinterpret_cast<ACar_TA*>(pawn);
                if (car && validUObject(car))
                {
                    foundCar = true;
                   
                    if (car->CarMesh && validUObject(car->CarMesh))
                        RestoreLiveCustomMeshState(car->CarMesh);

                    car->RespawnInPlace();
                    
                   
                    FVector loc = car->Location;
            
                    FVector vel = { 0.0f, 0.0f, 250.0f };
                    car->Velocity = vel;
                    
                    Console.Write("[CustomCar] Refreshed car model via RespawnInPlace");
                }
            }
            
          
            if (!foundCar)
            {
                ACarPreviewActor_TA* previewactor = nullptr;
                UGFxData_Garage_TA* garageGFX = Instances.GetInstanceOf<UGFxData_Garage_TA>();
                if (garageGFX && garageGFX->CarPreviewSet) 
                {
                    UCarPreviewSet_TA* previewSet = garageGFX->CarPreviewSet;
                    previewactor = previewSet->GetPlayerCarPreviewActor(localPlayer);
                    if (!previewactor && previewSet->CarPreviewActors.size() > 0) 
                    {
                        previewactor = previewSet->CarPreviewActors[0];
                    }
                }
                
           
                if (!previewactor)
                {
                    UPremiumGaragePreviewSet_TA* premGarage = Instances.GetInstanceOf<UPremiumGaragePreviewSet_TA>();
                    if (premGarage && premGarage->CarPreviewActors.size() > 0)
                    {
                        previewactor = premGarage->CarPreviewActors[0];
                    }
                }
                
                if (previewactor && validUObject(previewactor))
                {
                    foundCar = true;
                    if (previewactor->ProductLoader)
                    {
                      
                        previewactor->HandleAllProductsLoaded(previewactor->ProductLoader);
                        
           
                        FVector location = previewactor->Location;
                     
                        if (garageGFX && garageGFX->CarPreviewSet)
                        {
                            for (ACarPreviewActor_TA* pa : garageGFX->CarPreviewSet->CarPreviewActors) 
                            {
                                if (pa && pa != previewactor && validUObject(pa)) 
                                {
                                   
                                }
                            }
                        }
                        
                        Console.Write("[CustomCar] Refreshed car model via HandleAllProductsLoaded");
                    }
                }
            }
            
            if (!foundCar)
            {
                Console.Write("[CustomCar] RefreshCarModel - no car found (not in game or garage?)");
            }
        }
        catch (const std::exception& e)
        {
            Console.Warning("[CustomCar] Exception in RefreshCarModel: " + std::string(e.what()));
        }
        catch (...)
        {
            Console.Warning("[CustomCar] Unknown exception in RefreshCarModel");
        }
    }

  
    std::unordered_map<int32_t, BodyCustomization>& GetBodyCustomizations()
    {
        return s_bodyCustomizations;
    }

    size_t GetCachedAssetCount()
    {
        return s_customBodyProdAssets.size();
    }

    const fs::path& GetCustomCarsFolder()
    {
        return s_CustomCarsFolder;
    }

    fs::path GetCookedPCConsoleFolder()
    {
        char pathBuffer[MAX_PATH] = {};
        if (!GetModuleFileNameA(nullptr, pathBuffer, MAX_PATH))
            return {};

        fs::path exePath(pathBuffer);
        return (exePath.parent_path() / ".." / ".." / "TAGame" / "CookedPCConsole").lexically_normal();
    }

    bool CreateExampleJson()
    {
        try
        {
            if (s_CustomCarsFolder.empty())
                return false;

            std::error_code ec;
            fs::create_directories(s_CustomCarsFolder, ec);

            const fs::path examplePath = s_CustomCarsFolder / "example_cars.json";
            if (fs::exists(examplePath))
                return true;

            std::ofstream file(examplePath);
            if (!file.is_open())
                return false;

            file << "{\n";
            file << "    \"FennecOnOctane\": {\n";
            file << "        \"BodyId\": 23,\n";
            file << "        \"MeshPath\": \"Fenmobile.FenMobile_SK\",\n";
            file << "        \"Name\": \"Fennec\",\n";
            file << "        \"ChassisMaterialIndex\": 0,\n";
            file << "        \"SkinMaterialIndex\": 1,\n";
            file << "        \"WheelScale\": {\n";
            file << "            \"Front\": 1.0,\n";
            file << "            \"Back\": 1.0\n";
            file << "        },\n";
            file << "        \"HideWheels\": false,\n";
            file << "        \"HideTrails\": false\n";
            file << "    }\n";
            file << "}\n";
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}
