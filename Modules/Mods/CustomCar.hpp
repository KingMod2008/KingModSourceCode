#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <optional>
#include <unordered_map>
#include <vector>
#include <string>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace CustomCar
{
                                            
    struct ProductData
    {
        int32_t id = -1;
        std::string name;
    };

                                            
    extern std::unordered_map<int32_t, ProductData> s_allBodyProducts;

                                     
    struct CustomBodyData
    {
        std::string name;
        std::string assetPath;
        int32_t productId = -1;
        std::optional<int32_t> chassisMatIndex;
        std::optional<int32_t> skinMatIndex;
        std::optional<int32_t> brakelightMatIndex;
        std::optional<float> suspensionStiffnessScale;
        std::optional<float> wheelScaleFront;
        std::optional<float> wheelScaleBack;
        bool hideWheels = false;
        bool hideTrails = false;
    };

                                                   
    struct BodyCustomization
    {
        std::vector<CustomBodyData> bodies;
        std::optional<size_t> selectedBodyIdx;
    };

                                   
    struct WheelBoneNames
    {
        FName frontLeft;
        FName frontRight;
        FName backLeft;
        FName backRight;
    };

    struct WheelBoneInfo
    {
        bool front = false;
        bool left = false;
    };

                                                       
    extern std::unordered_map<int, std::string> g_baseHitboxIds;

                           
    struct CustomCarConfig
    {
        bool enabled = true;
        bool autoRefresh = true;
    };

                           
    CustomCarConfig& GetConfig();

                     
    void Initialize();
    void Shutdown();
    bool IsEnabled();

                           
    void LoadCustomBodies();
    void SaveConfiguration();
    void LoadConfiguration();
    std::optional<CustomBodyData> ParseBodyFromJson(const json& j);
    CustomBodyData* GetCustomBodyData(UCarMeshComponent_TA* cmc);
    CustomBodyData* GetCustomBodyDataFromProdId(int32_t productId);

                                 
    void ApplyCustomBody(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData);
    void HideTrails(ACar_TA* car);
    void HideTrails(UCarMeshComponent_TA* cmc);
    void HideWheels(UCarMeshComponent_TA* cmc);
    void ScaleWheels(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData);
    void FixBodyFX(UCarMeshComponent_TA* cmc, CustomBodyData* bodyData);
    std::optional<WheelBoneInfo> GetWheelBoneInfo(const FName& boneName);

                        
    void RefreshCarModel();

                                                                           
    std::unordered_map<int32_t, BodyCustomization>& GetBodyCustomizations();
    size_t GetCachedAssetCount();
    const fs::path& GetCustomCarsFolder();
    fs::path GetCookedPCConsoleFolder();
    bool CreateExampleJson();

                               
    void CacheCustomBodyAsset(int32_t productId, UProductAsset_Body_TA* asset);
    UProductAsset_Body_TA* GetCachedBodyAsset(int32_t productId);
    void ClearCachedAssets();

                                  
    void InitProductData();

                    
    void InitCachedFNames();
}
