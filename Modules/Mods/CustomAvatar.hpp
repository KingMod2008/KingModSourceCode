#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class CustomAvatarModule : public Module
{
public:
    CustomAvatarModule();
    ~CustomAvatarModule() override;

    void OnCreate();
    void OnDestroy();

    static void Initialize();
    static void Hook();

    static void OnGameEventStart(PreEvent& event);
    static void OnGameEventDestroyed(PreEvent& event);
    static void OnTick();                                         

    static void ApplyToAll();
    static void ApplyPlatformIcons();
    static void RestorePlatformIcons();
    static void ScanAvatarFiles();
    static UTexture2DDynamic* LoadSelectedTexture();
    static UTexture2DDynamic* LoadTextureFromPath(const fs::path& imgPath);
    static void ApplyTextureFromPath(const fs::path& imgPath);

    static bool               IsEnabled;
    static bool               IsInGame;
    static AGameEvent_Soccar_TA* CurrentGameEvent;
    static fs::path           AvatarsFolder;
    static std::vector<fs::path> AvailableFiles;
    static int                SelectedFileIndex;
    static bool               ApplyToAllPlayers;
    static UTexture2DDynamic* LoadedTexture;
};

extern class CustomAvatarModule CustomAvatar;
