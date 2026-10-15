#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

                                                                   
                                                                                
                                                                       
struct BoostMeterLayer
{
    std::string        layerName;
    fs::path           imgFile;
    UTexture2DDynamic* texture = nullptr;
};

                                                                
                                                                
                                                         
struct BoostMeterSkin
{
    std::string                  name;
    fs::path                     jsonFile;
    std::vector<BoostMeterLayer> layers;
    bool                         bLoaded = false;

    bool loadTextures();
    void clearLoadedTextures();
};

                                                                           
                                                                                 
                                                                                
                                                                      
class CustomBoostMeterModule : public Module
{
public:
    CustomBoostMeterModule();
    ~CustomBoostMeterModule() override;

    void OnCreate();
    void OnDestroy();

    static void Initialize();
    static void Hook();

    static void OnGameEventStart(PreEvent& event);
    static void OnGameEventDestroyed(PreEvent& event);

    static void SearchForSkins();
    static void ApplySelectedSkin();
    static void RestoreMeter();
    static void ReassertOverrides();
    static void ArmForNextTick();

                                                                               
                                                                    
    static void DumpTextureNames();

                                                                             
                                                                                
                                                   
    static std::string TargetForLayer(const std::string& layerName);

    static bool                                       IsEnabled;
    static bool                                       IsInGame;
    static fs::path                                   MeterFolder;
    static std::unordered_map<std::string, BoostMeterSkin> SavedSkins;
    static std::string                                SelectedSkinName;

    static bool                                       PendingApply;
};

extern class CustomBoostMeterModule CustomBoostMeter;
