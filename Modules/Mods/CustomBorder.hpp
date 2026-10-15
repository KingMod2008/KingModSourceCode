#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

                                                                              
class CustomBorderModule : public Module
{
public:
    CustomBorderModule();
    ~CustomBorderModule() override;

    void OnCreate();
    void OnDestroy();

    static void Initialize();
    static void Hook();

    static void OnGameEventStart(PreEvent& event);
    static void OnGameEventDestroyed(PreEvent& event);

    static void ScanBorderFiles();
    static UTexture2DDynamic* LoadSelectedTexture();
    static void ApplyToStadium();
    static void RestoreStadium();
    static void ArmForNextTick();                                            

                                                                                
    static std::string SelectedFileName();
    static void        SelectFileByName(const std::string& name);

    static bool               IsEnabled;
    static bool               IsInGame;
    static fs::path           BorderFolder;
    static std::vector<fs::path> AvailableFiles;
    static int                SelectedFileIndex;
    static UTexture2DDynamic* LoadedTexture;

                                                                               
    static bool               ApplyToAdverts;
    static bool               ApplyToTerrain;
    static bool               ApplyToSkyCurves;

                                                                  
    static bool               PendingApply;
};

extern class CustomBorderModule CustomBorder;
