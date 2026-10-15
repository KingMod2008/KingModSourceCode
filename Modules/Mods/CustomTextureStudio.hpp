#pragma once

#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include <array>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

enum class TextureStudioGroup : int
{
    Car  = 0,
    Menu = 1
};

struct TextureStudioFeatureDefinition
{
    const char* label;
    const char* slug;
    const char* description;
    TextureStudioGroup group;
};

struct TextureStudioFeatureState
{
    bool enabled = false;
    int selectedFileIndex = -1;
    std::string selectedFileName;
    std::string selectedTarget;                                                 
    UTexture2DDynamic* loadedTexture = nullptr;
};

class CustomTextureStudioModule : public Module
{
public:
                                                                            
                                                                                    
    static constexpr size_t FeatureCount = 2;

    CustomTextureStudioModule();
    ~CustomTextureStudioModule() override;

    void OnCreate();
    void OnDestroy();

    static void Initialize();
    static void Shutdown();
    static void Hook();

    static void PrepareForGameplayReset();
    static void NotifyGameplayReset();

    static const std::array<TextureStudioFeatureDefinition, FeatureCount>& Definitions();
    static TextureStudioFeatureState StateForFeature(size_t index);

    static fs::path RootFolder();
    static fs::path FolderForFeature(size_t index);
    static std::vector<fs::path> FilesForFeature(size_t index);
    static std::vector<std::string> TargetsForFeature(size_t index);

    static void ScanFiles();
    static void ScanFilesForFeature(size_t index);
    static void RequestLiveTextureRescan(bool reapplyAfterScan = true);
    static bool IsScanning();
    static float ScanProgress();
    static int MatchCount(size_t index);

    static void SetEnabled(size_t index, bool enabled);
    static void SelectImage(size_t index, int fileIndex);
    static void SetSelectedTarget(size_t index, const std::string& fullName);

    static void ApplyFeature(size_t index);
    static void ApplyAllEnabled();
    static void RestoreFeature(size_t index);
    static void RestoreAll();

    static void SaveConfig();
    static void LoadConfig();

    static bool IsInGame;
};

extern CustomTextureStudioModule CustomTextureStudio;
