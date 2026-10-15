#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../ImGui/gui_widget.hpp"
#include "../../ImGui/hashes.hpp"
#include "../../ImGui/bytes.hpp"
#include "../../ImGui/Fonts.h"
#include "GUI.hpp"
#include "Watermark.hpp"

#include "DevConsole.hpp"
#include "Notify.hpp"
#include "RankChanger.hpp"
#include "../Includes.hpp"
#include "../../Modules/Mods/GameEventHook.hpp"
#include "../../Modules/Mods/MatchmakingShield.hpp"
#include "../../Modules/Mods/BallPrediction.hpp"
#include "../../Modules/Mods/BallTextures.hpp"
#include "../../Modules/Mods/CustomAvatar.hpp"
#include "../../Modules/Mods/CustomBorder.hpp"
#include "../../Modules/Mods/CustomBoostMeter.hpp"
#include "../../Modules/Mods/CustomTextureStudio.hpp"
#include "../../Modules/Mods/CustomCar.hpp"
#include "../../Modules/Mods/CustomMatch.hpp"
#include "../../Modules/Mods/HostSync.hpp"
#include "../../Modules/Mods/KingFeatures.hpp"
#include "../../Modules/Mods/KingSync.hpp"
#include "../../Modules/Mods/TAS.hpp"
#include "../../RLSDK/RPC_DISCORD/KingModRPC.hpp"
#include "../../ImGui/SimpleImGuiFileBrowser.hpp"
#include "../../resource.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <cmath>
#include <nlohmann/json.hpp>
#include <random>
#include <set>
#include <system_error>
#include <unordered_map>
#include <wincodec.h>
#include <thread>
#include <mutex>
#include <process.h>
#include <chrono>
#include <functional>
#include <shellapi.h>
#include <ShlObj.h>
#pragma comment(lib, "windowscodecs.lib")

extern class GameEventHookModule GameEventHook;

                                                                

bool GUIComponent::showFPSCounter = true;
float GUIComponent::fpsCounterSize = 1.0f;
ImVec2 GUIComponent::fpsCounterPos = {10, 10};
int GUIComponent::lowFPScounter = 30;
int GUIComponent::midFPScounter = 60;
HINSTANCE GUIComponent::DllModule = NULL;
static int seriesId = 0;
static int tradeHold = 0;
static char spawnMessage[256] = "";
static bool showAnimation = true;
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <sstream>
#include "../ImGui/Kiero/kiero.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_stdlib.h"
#include "../ImGui/blur.hpp"
#include "../../ImGui/menu_avatar.hpp"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

                                                     
namespace CustomTitleWheel {
    void SpawnCustomTitle(const char* Text);
}

                                                                  
extern bool EnablePsyNetLogging;
extern bool EnableDropUnlockBypass;
extern bool DisableSyncData;
extern std::vector<std::string> PsyNetLogMessages;
extern std::vector<std::string> PsyNetLogHeaders;
extern std::vector<std::string> PsyNetLogBodies;
extern std::string PsyNetStatusSummary;
extern bool PsyNetHasCachedDropTable;
extern int PsyNetPendingRequestCount;

namespace
{
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    struct LocalPsyNetPluginEditorState
    {
        std::vector<fs::path> Files;
        int SelectedIndex = -1;
        std::string Buffer;
        std::string Status = "No local plugin JSON file selected yet.";
        fs::file_time_type LastWriteTime{};
        std::chrono::steady_clock::time_point LastScanTime{};
        bool AutoRefresh = true;
        bool PauseWhenDirty = true;
        bool Dirty = false;
    };

    LocalPsyNetPluginEditorState g_LocalPsyNetPluginEditor;

    struct GuiWindowLayoutState
    {
        bool Loaded = false;
        bool HasSavedRect = false;
        ImVec2 Pos = ImVec2(0.0f, 0.0f);
        ImVec2 Size = ImVec2(920.0f, 580.0f);
    };

    struct LocalTradeUpEntry
    {
        uint64_t EntryId = 0;
        int ItemId = 0;
        int Quality = -1;
        std::string DisplayName;
        std::string Category;
        std::string Source;
        bool Selected = false;
    };

    struct LocalModalEditorState
    {
        int ModalType = 0;
        ImVec4 Color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        std::string Title = "Title";
        std::string Body = "Body";
        std::vector<std::string> Citations;
        std::vector<std::string> Buttons = { "OK" };
        std::string AddCitation;
        std::string AddButton;
    };

    GuiWindowLayoutState g_GuiWindowLayout;
    std::vector<LocalTradeUpEntry> g_LocalTradeUpEntries;
    uint64_t g_LocalTradeUpNextEntryId = 1;
    bool g_LocalTradeUpSpawnRewardItem = true;
    LocalModalEditorState g_LocalModalEditor;

    bool WriteTextFile(const fs::path& filePath, const std::string& text);
    bool FormatJsonText(const std::string& input, std::string& outFormatted, std::string& outError);

    bool OpenFolderInExplorer(const fs::path& folderPath)
    {
        if (folderPath.empty())
            return false;

        std::error_code fsError;
        fs::create_directories(folderPath, fsError);

        const std::wstring widePath = folderPath.wstring();
        HINSTANCE openResult = ShellExecuteW(nullptr, L"open", widePath.c_str(), nullptr, nullptr, SW_SHOWDEFAULT);
        if (reinterpret_cast<intptr_t>(openResult) > 32)
            return true;

        HINSTANCE exploreResult = ShellExecuteW(nullptr, L"explore", widePath.c_str(), nullptr, nullptr, SW_SHOWDEFAULT);
        return reinterpret_cast<intptr_t>(exploreResult) > 32;
    }


    bool SendActorConsoleCommand(const std::string& command)
    {
        try
        {
            if (APlayerController* playerController = Instances.IAPlayerController())
            {
                std::wstring wideCommand(command.begin(), command.end());
                playerController->ConsoleCommand(FString(wideCommand.c_str()), false);
                return true;
            }
        }
        catch (...)
        {
        }

        return false;
    }


    fs::path GetKingModResourcesDirectoryPath()
    {
                                                                               
                                                              
        char exePath[MAX_PATH] = {};
        fs::path dir = GetModuleFileNameA(NULL, exePath, MAX_PATH)
            ? fs::path(exePath).parent_path() / "KingMod" / "resources"
            : fs::current_path() / "KingMod" / "resources";
        std::error_code fsError;
        fs::create_directories(dir, fsError);
        return dir;
    }

    fs::path GetGuiLayoutSettingsPath()
    {
        return GetKingModResourcesDirectoryPath() / "KingMod.gui.json";
    }

    void LoadGuiWindowLayout()
    {
        if (g_GuiWindowLayout.Loaded)
            return;

        g_GuiWindowLayout.Loaded = true;

        const fs::path settingsPath = GetGuiLayoutSettingsPath();
        std::ifstream in(settingsPath);
        if (!in.is_open())
            return;

        try
        {
            json j;
            in >> j;
            g_GuiWindowLayout.Size.x = j.value("window_width", g_GuiWindowLayout.Size.x);
            g_GuiWindowLayout.Size.y = j.value("window_height", g_GuiWindowLayout.Size.y);

                                                                             
            if (g_GuiWindowLayout.Size.x < 880.0f || g_GuiWindowLayout.Size.y < 560.0f)
                g_GuiWindowLayout.Size = ImVec2(920.0f, 580.0f);

            if (j.contains("window_pos_x") && j.contains("window_pos_y"))
            {
                g_GuiWindowLayout.Pos.x = j.value("window_pos_x", 0.0f);
                g_GuiWindowLayout.Pos.y = j.value("window_pos_y", 0.0f);
                g_GuiWindowLayout.HasSavedRect = true;
            }
        }
        catch (...)
        {
        }
    }

    void SaveGuiWindowLayout(const ImVec2& pos, const ImVec2& size)
    {
        g_GuiWindowLayout.Pos = pos;
        g_GuiWindowLayout.Size = size;
        g_GuiWindowLayout.HasSavedRect = true;

        json j;
        j["window_pos_x"] = pos.x;
        j["window_pos_y"] = pos.y;
        j["window_width"] = size.x;
        j["window_height"] = size.y;

        WriteTextFile(GetGuiLayoutSettingsPath(), j.dump(4));
    }

    std::string GetQualityLabel(int quality)
    {
        switch (quality)
        {
        case 0: return "Common";
        case 1: return "Uncommon";
        case 2: return "Rare";
        case 3: return "Very Rare";
        case 4: return "Import";
        case 5: return "Exotic";
        case 6: return "Black Market";
        case 7: return "Premium";
        case 8: return "Limited";
        case 9: return "Legacy";
        default: return "Unknown";
        }
    }

    std::string FormatItemCategoryLabel(const std::string& category)
    {
        if (category == "RocketBoost" || category == "Rocket Boost") return "Rocket Boost";
        if (category == "GoalExplosion" || category == "Goal Explosion") return "Goal Explosion";
        if (category == "PlayerBanner" || category == "Player Banner") return "Player Banner";
        if (category == "PlayerAvatarBorder" || category == "Avatar Border") return "Avatar Border";
        if (category == "EngineAudio" || category == "Engine Audio") return "Engine Audio";
        if (category == "PaintFinish" || category == "Paint Finish") return "Paint Finish";
        if (category == "PaintFinish2" || category == "Paint Finish 2") return "Paint Finish 2";
        if (category == "PlayerTitle" || category == "Player Title") return "Player Title";
        return category;
    }

    std::string NormalizeCategoryKey(std::string category)
    {
        std::string normalized;
        normalized.reserve(category.size());
        for (unsigned char ch : category)
        {
            if (std::isalnum(ch))
            {
                normalized.push_back(static_cast<char>(std::tolower(ch)));
            }
        }
        return normalized;
    }

    std::vector<int> CollectItemIdsByCategory(const std::string& category)
    {
        std::vector<int> ids;
        const std::string targetKey = NormalizeCategoryKey(category);
        Items.EnsureItemsLoaded();
        for (const auto& item : Items.allItems)
        {
            if (NormalizeCategoryKey(item.category) == targetKey)
            {
                ids.push_back(item.id);
            }
        }
        return ids;
    }

    std::vector<int> CollectItemIdsByQuality(int quality)
    {
        std::vector<int> ids;
        Items.EnsureItemsLoaded();
        for (const auto& item : Items.allItems)
        {
            if (item.quality == quality)
            {
                ids.push_back(item.id);
            }
        }
        return ids;
    }

    std::vector<std::pair<std::string, std::vector<int>>> CollectExtraItemGroups()
    {
        static const std::set<std::string> primarySlotCategories = {
            "body", "decal", "wheels", "rocketboost", "topper", "antenna", "trail", "goalexplosion"
        };

        std::unordered_map<std::string, std::vector<int>> groupedIds;
        Items.EnsureItemsLoaded();
        for (const auto& item : Items.allItems)
        {
            if (item.category.empty())
                continue;
            if (primarySlotCategories.find(NormalizeCategoryKey(item.category)) != primarySlotCategories.end())
                continue;

            groupedIds[item.category].push_back(item.id);
        }

        std::vector<std::pair<std::string, std::vector<int>>> groups;
        groups.reserve(groupedIds.size());
        for (auto& entry : groupedIds)
        {
            groups.push_back({ entry.first, entry.second });
        }

        std::sort(groups.begin(), groups.end(), [](const auto& lhs, const auto& rhs) {
            return FormatItemCategoryLabel(lhs.first) < FormatItemCategoryLabel(rhs.first);
        });
        return groups;
    }

    void SpawnItemBatch(const std::vector<int>& itemIds, const std::string& notificationLabel)
    {
        if (itemIds.empty())
        {
            Main.SpawnNotification("KingMod", "No items found for " + notificationLabel, 3);
            return;
        }

        Main.Execute([itemIds, notificationLabel]() {
            int spawnedCount = 0;
            for (int itemId : itemIds)
            {
                try
                {
                    Items.SpawnProduct(itemId, 0, 0, false, "", false);
                    spawnedCount++;
                }
                catch (...)
                {
                }
            }

            Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " " + notificationLabel, 5);
        });
    }

    const GameItem* FindGameItemById(int itemId)
    {
        Items.EnsureItemsLoaded();
        for (const auto& item : Items.allItems)
        {
            if (item.id == itemId)
                return &item;
        }

        return nullptr;
    }

    bool IsTradeUpQualitySupported(int quality)
    {
        return quality >= 1 && quality <= 5;
    }

    int GetTradeUpResultQuality(int quality)
    {
        return IsTradeUpQualitySupported(quality) ? (quality + 1) : -1;
    }

    void ClearLocalTradeUpSelection()
    {
        for (auto& entry : g_LocalTradeUpEntries)
        {
            entry.Selected = false;
        }
    }

    void AddLocalTradeUpItems(int itemId, int quantity, const std::string& source)
    {
        if (quantity <= 0)
            return;

        const GameItem* item = FindGameItemById(itemId);
        if (!item || item->displayName.empty() || item->quality < 1 || item->quality > 6)
            return;

        for (int i = 0; i < quantity; ++i)
        {
            LocalTradeUpEntry entry;
            entry.EntryId = g_LocalTradeUpNextEntryId++;
            entry.ItemId = item->id;
            entry.Quality = item->quality;
            entry.DisplayName = item->displayName;
            entry.Category = item->category;
            entry.Source = source;
            g_LocalTradeUpEntries.push_back(entry);
        }

        constexpr size_t kMaxLocalTradeUpEntries = 600;
        if (g_LocalTradeUpEntries.size() > kMaxLocalTradeUpEntries)
        {
            const size_t overflow = g_LocalTradeUpEntries.size() - kMaxLocalTradeUpEntries;
            g_LocalTradeUpEntries.erase(g_LocalTradeUpEntries.begin(), g_LocalTradeUpEntries.begin() + overflow);
        }
    }

    int GetSelectedTradeUpQuality()
    {
        for (const auto& entry : g_LocalTradeUpEntries)
        {
            if (entry.Selected)
                return entry.Quality;
        }

        return -1;
    }

    int GetSelectedTradeUpCount()
    {
        int count = 0;
        for (const auto& entry : g_LocalTradeUpEntries)
        {
            if (entry.Selected)
                ++count;
        }

        return count;
    }

    bool TrySimulateLocalTradeUp(std::string& outMessage)
    {
        const int selectedQuality = GetSelectedTradeUpQuality();
        const int selectedCount = GetSelectedTradeUpCount();
        if (!IsTradeUpQualitySupported(selectedQuality) || selectedCount != 5)
        {
            outMessage = "Select exactly 5 items of the same supported quality.";
            return false;
        }

        const int rewardQuality = GetTradeUpResultQuality(selectedQuality);
        if (rewardQuality < 0)
        {
            outMessage = "This quality cannot be traded up.";
            return false;
        }

        std::vector<GameItem> rewardCandidates;
        Items.EnsureItemsLoaded();
        for (const auto& item : Items.allItems)
        {
            if (item.quality == rewardQuality && !item.displayName.empty())
            {
                rewardCandidates.push_back(item);
            }
        }

        if (rewardCandidates.empty())
        {
            outMessage = "No local reward candidates were found for that quality.";
            return false;
        }

        static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<size_t> rewardDist(0, rewardCandidates.size() - 1);
        const GameItem rewardItem = rewardCandidates[rewardDist(rng)];

        int removeCount = 5;
        g_LocalTradeUpEntries.erase(
            std::remove_if(g_LocalTradeUpEntries.begin(), g_LocalTradeUpEntries.end(), [&](const LocalTradeUpEntry& entry) {
                if (!entry.Selected || entry.Quality != selectedQuality || removeCount <= 0)
                    return false;
                --removeCount;
                return true;
            }),
            g_LocalTradeUpEntries.end());

        ClearLocalTradeUpSelection();
        AddLocalTradeUpItems(rewardItem.id, 1, "Trade-Up Reward");

        if (g_LocalTradeUpSpawnRewardItem)
        {
            Main.Execute([rewardId = rewardItem.id]() {
                try
                {
                    Items.SpawnProduct(rewardId, 0, 0, false, "Trade-Up Reward", true);
                }
                catch (...)
                {
                }
            });
        }

        outMessage = "Trade-up reward: " + rewardItem.displayName;
        return true;
    }

    std::string GetFormattedJsonPreview(const std::string& input)
    {
        std::string formatted;
        std::string error;
        if (FormatJsonText(input, formatted, error))
            return formatted;
        return input;
    }

    fs::path GetKingModPluginsDirectoryPath()
    {
        char exePath[MAX_PATH] = {};
        fs::path baseDir;

        if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
        {
            baseDir = fs::path(exePath).parent_path() / "KingMod" / "Plugins";
        }
        else
        {
            baseDir = fs::current_path() / "KingMod" / "Plugins";
        }

        std::error_code fsError;
        fs::create_directories(baseDir, fsError);
        return baseDir;
    }

    std::string ToLowerCopy(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return value;
    }

    std::vector<std::string> GetFallbackRankPlaylists()
    {
        return {
            "Duel (Comp)",
            "Doubles (Comp)",
            "Standard (Comp)",
            "Hoops (Comp)",
            "Rumble (Comp)",
            "Dropshot (Comp)",
            "Snow Day (Comp)"
        };
    }

    int GetBaseTierForRankSelection(int rankItem)
    {
        switch (rankItem)
        {
        case 0: return 1;
        case 1: return 4;
        case 2: return 7;
        case 3: return 10;
        case 4: return 13;
        case 5: return 16;
        case 6: return 19;
        case 7: return 22;
        case 8: return 69;
        default: return 1;
        }
    }

    void RefreshRankPlaylistsForGui(bool forceRefresh = false)
    {
        if (!forceRefresh && !RankChanger.PlaylistsForRankEditing.empty())
            return;

        RankChanger.PlaylistsForRankEditing.clear();

        UOnlineGamePlaylists_TA* playlistManager = Instances.GetInstanceOf<UOnlineGamePlaylists_TA>();
        if (playlistManager)
        {
            const int playlistCount = playlistManager->DownloadedPlaylists.size();
            for (int i = 0; i < playlistCount; ++i)
            {
                UGameSettingPlaylist_X* playlist = playlistManager->DownloadedPlaylists[i];
                if (!playlist)
                    continue;

                const std::string titleStr = playlist->Title.ToString();
                if (titleStr.empty() || titleStr == "null" || titleStr == "NULL")
                    continue;

                RankChanger.PlaylistsForRankEditing.push_back(
                    titleStr + " (" + (playlist->bRanked ? "Comp" : "Casual") + ")");
            }
        }

        if (RankChanger.PlaylistsForRankEditing.empty())
        {
            RankChanger.PlaylistsForRankEditing = GetFallbackRankPlaylists();
        }

        if (RankChanger.selectedplaylisttoedit.empty() ||
            std::find(RankChanger.PlaylistsForRankEditing.begin(),
                RankChanger.PlaylistsForRankEditing.end(),
                RankChanger.selectedplaylisttoedit) == RankChanger.PlaylistsForRankEditing.end())
        {
            RankChanger.selectedplaylisttoedit = RankChanger.PlaylistsForRankEditing.empty()
                ? std::string()
                : RankChanger.PlaylistsForRankEditing.front();
        }
    }

    void RefreshLocalPsyNetPluginFiles(bool keepSelection = true)
    {
        const std::string previousSelection = (keepSelection &&
            g_LocalPsyNetPluginEditor.SelectedIndex >= 0 &&
            g_LocalPsyNetPluginEditor.SelectedIndex < static_cast<int>(g_LocalPsyNetPluginEditor.Files.size()))
            ? g_LocalPsyNetPluginEditor.Files[g_LocalPsyNetPluginEditor.SelectedIndex].string()
            : std::string();

        g_LocalPsyNetPluginEditor.Files.clear();

        const fs::path pluginsDir = GetKingModPluginsDirectoryPath();
        std::error_code fsError;
        if (!fs::exists(pluginsDir, fsError))
        {
            g_LocalPsyNetPluginEditor.SelectedIndex = -1;
            return;
        }

        for (const auto& entry : fs::recursive_directory_iterator(pluginsDir, fs::directory_options::skip_permission_denied, fsError))
        {
            if (fsError)
                break;

            if (!entry.is_regular_file())
                continue;

            if (ToLowerCopy(entry.path().extension().string()) == ".json")
            {
                g_LocalPsyNetPluginEditor.Files.push_back(entry.path());
            }
        }

        std::sort(g_LocalPsyNetPluginEditor.Files.begin(), g_LocalPsyNetPluginEditor.Files.end(), [](const fs::path& lhs, const fs::path& rhs) {
            return lhs.filename().string() < rhs.filename().string();
        });

        if (g_LocalPsyNetPluginEditor.Files.empty())
        {
            g_LocalPsyNetPluginEditor.SelectedIndex = -1;
            return;
        }

        g_LocalPsyNetPluginEditor.SelectedIndex = 0;
        if (!previousSelection.empty())
        {
            for (int i = 0; i < static_cast<int>(g_LocalPsyNetPluginEditor.Files.size()); ++i)
            {
                if (g_LocalPsyNetPluginEditor.Files[i].string() == previousSelection)
                {
                    g_LocalPsyNetPluginEditor.SelectedIndex = i;
                    break;
                }
            }
        }
    }

    bool ReadTextFile(const fs::path& filePath, std::string& outText)
    {
        std::ifstream in(filePath, std::ios::binary);
        if (!in.is_open())
            return false;

        outText.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        return true;
    }

    bool WriteTextFile(const fs::path& filePath, const std::string& text)
    {
        std::error_code fsError;
        fs::create_directories(filePath.parent_path(), fsError);

        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
        if (!out.is_open())
            return false;

        out.write(text.data(), static_cast<std::streamsize>(text.size()));
        return out.good();
    }

    bool LoadSelectedLocalPsyNetPluginFile(bool forceReload = false)
    {
        if (g_LocalPsyNetPluginEditor.SelectedIndex < 0 ||
            g_LocalPsyNetPluginEditor.SelectedIndex >= static_cast<int>(g_LocalPsyNetPluginEditor.Files.size()))
        {
            return false;
        }

        if (!forceReload && g_LocalPsyNetPluginEditor.Dirty && g_LocalPsyNetPluginEditor.PauseWhenDirty)
        {
            return false;
        }

        const fs::path& selectedPath = g_LocalPsyNetPluginEditor.Files[g_LocalPsyNetPluginEditor.SelectedIndex];
        std::string fileText;
        if (!ReadTextFile(selectedPath, fileText))
        {
            g_LocalPsyNetPluginEditor.Status = "Failed to read " + selectedPath.filename().string();
            return false;
        }

        g_LocalPsyNetPluginEditor.Buffer = std::move(fileText);
        g_LocalPsyNetPluginEditor.Dirty = false;

        std::error_code fsError;
        g_LocalPsyNetPluginEditor.LastWriteTime = fs::last_write_time(selectedPath, fsError);
        g_LocalPsyNetPluginEditor.Status = "Loaded " + selectedPath.filename().string();
        return true;
    }

    void AutoRefreshLocalPsyNetPluginEditor()
    {
        const auto now = std::chrono::steady_clock::now();
        if (g_LocalPsyNetPluginEditor.LastScanTime != std::chrono::steady_clock::time_point{})
        {
            const auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_LocalPsyNetPluginEditor.LastScanTime).count();
            if (elapsedMs < 750)
                return;
        }
        g_LocalPsyNetPluginEditor.LastScanTime = now;

        const int previousSelection = g_LocalPsyNetPluginEditor.SelectedIndex;
        RefreshLocalPsyNetPluginFiles(true);

        if (g_LocalPsyNetPluginEditor.SelectedIndex < 0)
            return;

        if ((g_LocalPsyNetPluginEditor.Buffer.empty() && !g_LocalPsyNetPluginEditor.Dirty) ||
            previousSelection != g_LocalPsyNetPluginEditor.SelectedIndex)
        {
            LoadSelectedLocalPsyNetPluginFile(true);
            return;
        }

        if (!g_LocalPsyNetPluginEditor.AutoRefresh)
            return;

        if (g_LocalPsyNetPluginEditor.Dirty && g_LocalPsyNetPluginEditor.PauseWhenDirty)
            return;

        const fs::path& selectedPath = g_LocalPsyNetPluginEditor.Files[g_LocalPsyNetPluginEditor.SelectedIndex];
        std::error_code fsError;
        const fs::file_time_type currentWriteTime = fs::last_write_time(selectedPath, fsError);
        if (!fsError && currentWriteTime != g_LocalPsyNetPluginEditor.LastWriteTime)
        {
            LoadSelectedLocalPsyNetPluginFile(true);
        }
    }

    bool ValidateJsonText(const std::string& input, std::string& outError)
    {
        try
        {
            json::parse(input);
            outError.clear();
            return true;
        }
        catch (const std::exception& e)
        {
            outError = e.what();
            return false;
        }
    }

    bool FormatJsonText(const std::string& input, std::string& outFormatted, std::string& outError)
    {
        try
        {
            outFormatted = json::parse(input).dump(4);
            outError.clear();
            return true;
        }
        catch (const std::exception& e)
        {
            outError = e.what();
            return false;
        }
    }

    ImVec4 GetPsyNetEntryColor(const std::string& summary)
    {
        const std::string lower = ToLowerCopy(summary);
        if (lower.find("blocked") != std::string::npos)
            return ImVec4(0.92f, 0.76f, 0.18f, 1.0f);
        if (lower.find("edited") != std::string::npos)
            return ImVec4(0.45f, 0.88f, 0.54f, 1.0f);
        if (lower.find("response") != std::string::npos)
            return ImVec4(0.37f, 0.78f, 0.96f, 1.0f);
        if (lower.find("request") != std::string::npos)
            return ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        return ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
    }
}

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
static std::atomic<bool> unloading{ false };
static std::atomic<int> g_activePresentCalls{ 0 };
std::atomic<bool> g_DllUnloading{false};

namespace
{
    struct LocalTexturePreview
    {
        ID3D11ShaderResourceView* View = nullptr;
        fs::file_time_type Stamp{};
        std::chrono::steady_clock::time_point LastProbe{};
        int Width = 0;
        int Height = 0;
    };

    std::unordered_map<std::string, LocalTexturePreview> g_LocalTexturePreviewCache;

    void ReleaseLocalTexturePreviews()
    {
        for (auto& [key, preview] : g_LocalTexturePreviewCache)
        {
            if (preview.View)
            {
                preview.View->Release();
                preview.View = nullptr;
            }
        }
        g_LocalTexturePreviewCache.clear();
    }

    ID3D11ShaderResourceView* GetLocalTexturePreview(const fs::path& filePath, int& outWidth, int& outHeight)
    {
        outWidth = 0;
        outHeight = 0;
        if (filePath.empty())
            return nullptr;

        std::error_code ec;
        if (!fs::is_regular_file(filePath, ec) || ec)
            return nullptr;

        const std::string cacheKey = filePath.lexically_normal().string();
        auto existing = g_LocalTexturePreviewCache.find(cacheKey);
        const auto now = std::chrono::steady_clock::now();
        if (existing != g_LocalTexturePreviewCache.end() && existing->second.View &&
            existing->second.LastProbe.time_since_epoch().count() != 0 &&
            now - existing->second.LastProbe < std::chrono::seconds(1))
        {
            outWidth = existing->second.Width;
            outHeight = existing->second.Height;
            return existing->second.View;
        }

        const fs::file_time_type stamp = fs::last_write_time(filePath, ec);
        if (ec)
            return nullptr;

        if (existing != g_LocalTexturePreviewCache.end() && existing->second.Stamp == stamp && existing->second.View)
        {
            existing->second.LastProbe = now;
            outWidth = existing->second.Width;
            outHeight = existing->second.Height;
            return existing->second.View;
        }

        if (existing != g_LocalTexturePreviewCache.end())
        {
            if (existing->second.View)
                existing->second.View->Release();
            g_LocalTexturePreviewCache.erase(existing);
        }

        std::ifstream input(filePath, std::ios::binary | std::ios::ate);
        if (!input.is_open())
            return nullptr;
        const std::streamsize size = input.tellg();
        if (size <= 0 || size > (32ll * 1024ll * 1024ll))
            return nullptr;
        input.seekg(0, std::ios::beg);
        std::vector<uint8_t> bytes(static_cast<size_t>(size));
        if (!input.read(reinterpret_cast<char*>(bytes.data()), size))
            return nullptr;

        LocalTexturePreview preview;
        preview.Stamp = stamp;
        preview.LastProbe = now;
        preview.View = menu_avatar::CreateTextureFromMemory(bytes.data(), bytes.size(), &preview.Width, &preview.Height);
        if (!preview.View)
            return nullptr;

        outWidth = preview.Width;
        outHeight = preview.Height;
        auto [it, inserted] = g_LocalTexturePreviewCache.emplace(cacheKey, preview);
        return it->second.View;
    }

                                                                         
                                                                              
                                                                               
    void DrawLocalTextureHoverPreview(const fs::path& filePath, const char* label = nullptr, float maxWidth = 300.0f, float maxHeight = 260.0f)
    {
        if (!ImGui::IsItemHovered() || filePath.empty())
            return;

        int width = 0, height = 0;
        ID3D11ShaderResourceView* view = GetLocalTexturePreview(filePath, width, height);
        if (!view || width <= 0 || height <= 0)
            return;

        const float scale = (std::min)(maxWidth / static_cast<float>(width), maxHeight / static_cast<float>(height));
        const ImVec2 size(
            (std::max)(1.0f, static_cast<float>(width) * scale),
            (std::max)(1.0f, static_cast<float>(height) * scale));

        ImGui::BeginTooltip();
        if (label && *label)
        {
            ImGui::TextUnformatted(label);
            ImGui::Separator();
        }
        ImGui::Image(reinterpret_cast<ImTextureID>(view), size);
        ImGui::EndTooltip();
    }
}

                                                                            
                                                                           
                                                                         
                                                                             
                                                                            
                                                                             
                                                                               
                                                                         
                                                                             
                                                            
namespace {
    ImVec2 g_fitPos;
    float  g_fitW = 0.f;

    void BeginFitSection(float& heightStore) {
        g_fitPos = ImGui::GetCursorScreenPos();
        g_fitW   = ImGui::GetContentRegionAvail().x;
        if (heightStore > 1.f) {
            ImDrawList* dl = ImGui::GetWindowDrawList();
            const ImVec2 mn = g_fitPos;
            const ImVec2 mx = ImVec2(g_fitPos.x + g_fitW, g_fitPos.y + heightStore);
            dl->AddRectFilled(mn, mx, gui.group_box_bg.to_im_color(), 6.0f);
            dl->AddRect(mn, mx, gui.border.to_im_color(), 6.0f);
        }
        ImGui::BeginGroup();
        ImGui::Dummy(ImVec2(g_fitW, 10.0f));                                               
        ImGui::Indent(14.0f);
    }
    void EndFitSection(float& heightStore) {
        ImGui::Unindent(14.0f);
        ImGui::Dummy(ImVec2(0.0f, 10.0f));                  
        ImGui::EndGroup();
        heightStore = ImGui::GetItemRectMax().y - g_fitPos.y;
    }

                                                                                
                                                                                   
                                                                                 
                                                                                 
                                                                    
    bool SectionHeader(const char* label) {
        ImGui::Spacing();
        ImDrawList* dl = ImGui::GetWindowDrawList();
        const ImVec2 p = ImGui::GetCursorScreenPos();
        const float  th = ImGui::GetTextLineHeight();
        dl->AddRectFilled(ImVec2(p.x, p.y + 1.0f),
                          ImVec2(p.x + 3.0f, p.y + th - 1.0f),
                          gui.accent_color.to_im_color(), 1.5f);
        ImGui::Indent(11.0f);
        ImGui::TextColored(gui.accent_color.to_vec4(), "%s", label);
        ImGui::Unindent(11.0f);
        const ImVec2 a = ImGui::GetCursorScreenPos();
        const float  w = ImGui::GetContentRegionAvail().x;
        dl->AddLine(ImVec2(a.x, a.y + 2.0f), ImVec2(a.x + w, a.y + 2.0f),
                    IM_COL32(255, 255, 255, 20));
        ImGui::Dummy(ImVec2(0.0f, 7.0f));
        return true;
    }
}

GUIComponent::GUIComponent() : Component("UserInterface", "Displays an interface") { OnCreate(); }
GUIComponent::~GUIComponent() { OnDestroy(); }

char GUIComponent::notificationTitle[128] = "Test Title";
char GUIComponent::notificationContent[256] = "This is a test from ImGui!";
int  GUIComponent::notificationDuration = 10;
char GUIComponent::chatMessage[128] = "Hello world!";
bool GUIComponent::isTeamChat = false;
int GUIComponent::selectedQuickChatIndex = 0;

                                
std::atomic<bool> init{ false };

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (unloading.load(std::memory_order_acquire))
        return oPresent(pSwapChain, SyncInterval, Flags);

    g_activePresentCalls.fetch_add(1, std::memory_order_acq_rel);
    const auto leavePresent = []() {
        g_activePresentCalls.fetch_sub(1, std::memory_order_acq_rel);
    };

    if (!init.load(std::memory_order_acquire))
    {
        if (unloading.load(std::memory_order_acquire))
        {
            leavePresent();
            return oPresent(pSwapChain, SyncInterval, Flags);
        }

        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            blur::device = pContext;
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)GUIComponent::WndProc);
            GUIComponent::InitImGui();
            init.store(true, std::memory_order_release);
        }
        else
        {
            leavePresent();
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    if (unloading.load(std::memory_order_acquire) || !pContext || !mainRenderTargetView)
    {
        leavePresent();
        return oPresent(pSwapChain, SyncInterval, Flags);
    }

    GUIComponent::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    leavePresent();
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread()
{
    bool init_hook = false;
    while (!unloading.load(std::memory_order_acquire) && !init_hook)
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
        else
        {
            Sleep(10);
        }
    }
    return TRUE;
}

void GUIComponent::OnCreate() {
                                                                  
}
void GUIComponent::OnDestroy() {
                                            
}

void GUIComponent::NotifyTradeUpSimulatorItemSpawned(int itemId, int quantity, const std::string& source)
{
    if (quantity <= 0)
        return;

    if (source.find("Trade-Up Reward") != std::string::npos)
        return;

    AddLocalTradeUpItems(itemId, quantity, source.empty() ? "Spawned Item" : source);
}

void GUIComponent::Unload()
{
    unloading.store(true, std::memory_order_release);

                                                                             
                                                                            
                                                                   
    for (int elapsed = 0; elapsed < 2000 && g_activePresentCalls.load(std::memory_order_acquire) != 0; elapsed += 5)
        Sleep(5);

    if (init.exchange(false, std::memory_order_acq_rel))
    {
        if (window && oWndProc)
            SetWindowLongPtrW(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
        if (pContext) pContext->Flush();
        ReleaseLocalTexturePreviews();
        menu_avatar::Shutdown();
        blur::Shutdown();
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
        if (pContext) { pContext->Release(); pContext = NULL; }
        if (pDevice) { pDevice->Release(); pDevice = NULL; }
    }

                                                                             
                                                                                
                                                                               
                
    kiero::shutdown();

    if (InterfaceThread)
    {
        WaitForSingleObject(InterfaceThread, 1000);
        CloseHandle(InterfaceThread);
        InterfaceThread = NULL;
    }
}

void GUIComponent::RequestUnload()
{
                                                                              
                                                                               
                                                                           
    static std::atomic<bool> unloading_started{ false };
    bool expected = false;
    if (!unloading_started.compare_exchange_strong(expected, true))
        return;

    struct UnloadHelper {
                                                                         
                                                                          
                                                                              
                                                                           
                                                                           
                                                                                
                                                               
        static void Step(void (*fn)())
        {
            __try { fn(); }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        static DWORD WINAPI Run(LPVOID)
        {
            g_DllUnloading.store(true);


                                                                                 
                                                                                  
                                                                
            Step([] { KingModRPC::Shutdown(); });
                                                                           
                                                                           
                                                                            
            Step([] { EventsComponent::DetachDetour(); });
            Sleep(50);                                         
                                                                              
                                                                            
                                                                               
                                                  
            Step([] {
                std::lock_guard<std::mutex> lock(MainComponent::GameFunctionsMutex);
                MainComponent::GameFunctions.clear();
            });
                                                                       
                                                                         
                                                                            
                                                              
            Step([] { CustomBoostMeterModule::RestoreMeter(); });
            Step([] { GUIComponent::Unload(); });

                                                                              
                                                                              
                                                                              
                                                                           
            for (int waited = 0; waited < 5000; waited += 25) {
                if (GameEventHookModule::BackgroundWorkers.load() <= 0)
                    break;
                Sleep(25);
            }
            Sleep(250);

                                                                               
                                                                            
                                                                           
                                                                              
                                                                                
                                                                             
                                                                               
                                               
            HMODULE self = nullptr;
            GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                               reinterpret_cast<LPCSTR>(&UnloadHelper::Run), &self);
            if (!self)
                self = GUIComponent::DllModule;
            if (self)
                FreeLibraryAndExitThread(self, 0);                     

            ExitThread(0);
            return 0;
        }
    };
    CreateThread(nullptr, 0, UnloadHelper::Run, nullptr, 0, nullptr);
}

void GUIComponent::RenderFPSCounter()
{
    ImGuiIO& io = ImGui::GetIO();
    float fps = io.Framerate;
    char fpsText[32];
    sprintf_s(fpsText, "FPS: %.1f", fps);

    ImVec4 color;
    if (fps < lowFPScounter) {
        color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);       
    } else if (fps < midFPScounter) {
        color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);          
    } else {
        color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);         
    }

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize() * fpsCounterSize, FLT_MAX, 0.0f, fpsText);
    ImVec2 padding = ImVec2(6.0f, 3.0f);
    ImVec2 bgMin = ImVec2(fpsCounterPos.x - padding.x, fpsCounterPos.y - padding.y);
    ImVec2 bgMax = ImVec2(fpsCounterPos.x + textSize.x + padding.x, fpsCounterPos.y + textSize.y + padding.y);
    dl->AddRectFilled(bgMin, bgMax, IM_COL32(0, 0, 0, 160), 4.0f);
    dl->AddText(ImGui::GetFont(), ImGui::GetFontSize() * fpsCounterSize, fpsCounterPos, ImGui::GetColorU32(color), fpsText);
}

HANDLE GUIComponent::InterfaceThread = NULL;
bool GUIComponent::IsOpen = true;
ImFont* GUIComponent::FontKingRegular = nullptr;
ImFont* GUIComponent::FontKingMedium = nullptr;
ImFont* GUIComponent::FontKingItalic = nullptr;
ImFont* GUIComponent::FontKingMono = nullptr;

void GUIComponent::Initialize() {
    InterfaceThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), nullptr, 0, nullptr);
}

static void DefaultImGuiStyle();

void GUIComponent::InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
    DefaultImGuiStyle();

    io.Fonts->Clear();

                                                                                       
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false;
    FontKingRegular = io.Fonts->AddFontFromMemoryTTF(RudaBold, sizeof(RudaBold), 15.0f, &fontConfig);
    if (FontKingRegular) io.FontDefault = FontKingRegular;

    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;
    io.Fonts->AddFontFromMemoryTTF((void*)font_awesome_binary, sizeof(font_awesome_binary), 14.0f, &icons_config, icon_ranges);

                                                           
    ImFontConfig mediumConfig;
    mediumConfig.FontDataOwnedByAtlas = false;
    FontKingMedium = io.Fonts->AddFontFromMemoryTTF(RudaBold, sizeof(RudaBold), 18.0f, &mediumConfig);

                                           
    ImFontConfig titleConfig;
    titleConfig.FontDataOwnedByAtlas = false;
    FontKingItalic = io.Fonts->AddFontFromMemoryTTF(RudaBold, sizeof(RudaBold), 28.0f, &titleConfig);

                                                                               
                                                                               
                                                                               
    FontKingMono = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\consola.ttf", 15.0f);
    if (!FontKingMono)
        FontKingMono = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\cour.ttf", 15.0f);

    io.Fonts->Build();
}

                                                                                
                                                                          
static int MenuToggleVK() {
    const std::string& name = GameEventHookModule::MenuToggleKey;
    if (name.size() == 1) {
        const char c = name[0];
        if (c >= 'A' && c <= 'Z') return c;
        if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
        if (c >= '0' && c <= '9') return c;
    }
    if (name.size() >= 2 && (name[0] == 'F' || name[0] == 'f')) {
        const int number = std::atoi(name.c_str() + 1);
        if (number >= 1 && number <= 24) return VK_F1 + number - 1;
    }
    static const std::map<std::string, int> keys = {
        { "Mouse1", VK_LBUTTON }, { "Mouse2", VK_RBUTTON }, { "Mouse3", VK_MBUTTON },
        { "Mouse4", VK_XBUTTON1 }, { "Mouse5", VK_XBUTTON2 },
        { "Insert", VK_INSERT }, { "Delete", VK_DELETE }, { "Home", VK_HOME },
        { "End", VK_END }, { "PageUp", VK_PRIOR }, { "PageDown", VK_NEXT },
        { "Tab", VK_TAB }, { "CapsLock", VK_CAPITAL }, { "Space", VK_SPACE },
        { "Enter", VK_RETURN }, { "Backspace", VK_BACK }, { "Escape", VK_ESCAPE },
        { "Shift", VK_SHIFT }, { "Ctrl", VK_CONTROL }, { "Alt", VK_MENU },
        { "Left", VK_LEFT }, { "Right", VK_RIGHT }, { "Up", VK_UP }, { "Down", VK_DOWN },
        { "Pause", VK_PAUSE }, { "PrintScreen", VK_SNAPSHOT },
        { "NumLock", VK_NUMLOCK }, { "ScrollLock", VK_SCROLL },
        { "Numpad0", VK_NUMPAD0 }, { "Numpad1", VK_NUMPAD1 }, { "Numpad2", VK_NUMPAD2 },
        { "Numpad3", VK_NUMPAD3 }, { "Numpad4", VK_NUMPAD4 }, { "Numpad5", VK_NUMPAD5 },
        { "Numpad6", VK_NUMPAD6 }, { "Numpad7", VK_NUMPAD7 }, { "Numpad8", VK_NUMPAD8 },
        { "Numpad9", VK_NUMPAD9 }, { "Numpad+", VK_ADD }, { "Numpad-", VK_SUBTRACT },
        { "Numpad*", VK_MULTIPLY }, { "Numpad/", VK_DIVIDE }, { "Numpad.", VK_DECIMAL }
    };
    const auto it = keys.find(name);
    return it == keys.end() ? 0 : it->second;
}

static void KingModResetInputCaptureState()
{
    ReleaseCapture();
    ClipCursor(nullptr);

    if (ImGui::GetCurrentContext())
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[0] = io.MouseDown[1] = io.MouseDown[2] = io.MouseDown[3] = io.MouseDown[4] = false;
    }
}

                                                                       
                                                                        
                                                                          
                                                                             
                                                                    
                                       
static bool KingImGuiInputActive()
{

    return GUIComponent::IsOpen || KingConsole::IsOpen()

        || Notify::HasPopup();
}

LRESULT __stdcall GUIComponent::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ImGuiIO& io = ImGui::GetIO();
    const bool imguiInput = KingImGuiInputActive();
    if (imguiInput)
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

                                                                               
                                                                          
                                                                               
                                                                             
                                                                           
                                                                              
                                                                           
    if (imguiInput && uMsg == WM_INPUT)
    {
        RAWINPUT raw{};
        UINT rawSize = sizeof(raw);
        const UINT copied = GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT,
                                            &raw, &rawSize, sizeof(RAWINPUTHEADER));
        if (copied != static_cast<UINT>(-1) && raw.header.dwType == RIM_TYPEMOUSE)
        {
            const RAWMOUSE& rm = raw.data.mouse;
            const USHORT f = rm.usButtonFlags;
            if (f & RI_MOUSE_LEFT_BUTTON_DOWN)   io.AddMouseButtonEvent(0, true);
            if (f & RI_MOUSE_LEFT_BUTTON_UP)     io.AddMouseButtonEvent(0, false);
            if (f & RI_MOUSE_RIGHT_BUTTON_DOWN)  io.AddMouseButtonEvent(1, true);
            if (f & RI_MOUSE_RIGHT_BUTTON_UP)    io.AddMouseButtonEvent(1, false);
            if (f & RI_MOUSE_MIDDLE_BUTTON_DOWN) io.AddMouseButtonEvent(2, true);
            if (f & RI_MOUSE_MIDDLE_BUTTON_UP)   io.AddMouseButtonEvent(2, false);
            if (f & RI_MOUSE_BUTTON_4_DOWN)      io.AddMouseButtonEvent(3, true);
            if (f & RI_MOUSE_BUTTON_4_UP)        io.AddMouseButtonEvent(3, false);
            if (f & RI_MOUSE_BUTTON_5_DOWN)      io.AddMouseButtonEvent(4, true);
            if (f & RI_MOUSE_BUTTON_5_UP)        io.AddMouseButtonEvent(4, false);
            if (f & RI_MOUSE_WHEEL)
                io.AddMouseWheelEvent(0.0f, static_cast<float>(static_cast<short>(rm.usButtonData)) / (float)WHEEL_DELTA);
            if (f & RI_MOUSE_HWHEEL)
                io.AddMouseWheelEvent(static_cast<float>(static_cast<short>(rm.usButtonData)) / (float)WHEEL_DELTA, 0.0f);
        }
    }

                                                                              
                                                                              
                                                                                 
                                                                                 
                                                                                
                                                                                 
    if (!io.WantTextInput) {
        const int tvk = MenuToggleVK();
        const bool keyboard = uMsg == WM_KEYUP && tvk != 0 && static_cast<int>(wParam) == tvk;
        const bool mouse =
            (uMsg == WM_LBUTTONUP && tvk == VK_LBUTTON) ||
            (uMsg == WM_RBUTTONUP && tvk == VK_RBUTTON) ||
            (uMsg == WM_MBUTTONUP && tvk == VK_MBUTTON) ||
            (uMsg == WM_XBUTTONUP &&
                ((GET_XBUTTON_WPARAM(wParam) == XBUTTON1 && tvk == VK_XBUTTON1) ||
                 (GET_XBUTTON_WPARAM(wParam) == XBUTTON2 && tvk == VK_XBUTTON2)));
        if (keyboard || mouse)
        {
            GUIComponent::IsOpen = !GUIComponent::IsOpen;
            KingModResetInputCaptureState();
            return TRUE;
        }
    }

                                                                                
                                                                               
                                                                         
    if (!io.WantTextInput || KingConsole::IsOpen()) {
        if (uMsg == WM_KEYUP && wParam == VK_F6)
            KingConsole::Toggle();
    }

    if (GUIComponent::IsOpen && io.WantCaptureMouse && (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEMOVE))
    {
        return TRUE;
    }

                                                                            
                                                                              
                                                                             
                                                                                
                                                                     
    if ((GUIComponent::IsOpen || KingConsole::IsOpen()) && io.WantCaptureKeyboard &&
        (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_CHAR ||
         uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP || uMsg == WM_SYSCHAR))
    {
        return TRUE;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

                                                                                     
                                                                            
ImVec4 g_RedThemeColor = ImVec4(0.30f, 0.49f, 1.00f, 1.00f);
ImVec4 g_LightRedColor = ImVec4(0.38f, 0.57f, 1.00f, 1.00f);
ImVec4 g_DarkRedColor = ImVec4(0.012f, 0.012f, 0.012f, 1.00f);

static bool KingSliderFloat(const char* label, float* v, float v_min, float v_max, const char* fmt = "%.2f")
{
    ImGui::PushID(label);
    bool changed = false;

    float totalWidth = ImGui::GetContentRegionAvail().x;
    float labelWidth = totalWidth * 0.30f;
    float valueBoxWidth = 60.0f;
    float sliderWidth = totalWidth - labelWidth - valueBoxWidth - 12.0f;
    float height = 20.0f;

    ImGui::TextUnformatted(label);
    ImGui::SameLine(labelWidth);

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();

    ImVec2 trackMin(pos.x, pos.y + height * 0.30f);
    ImVec2 trackMax(pos.x + sliderWidth, pos.y + height * 0.70f);
    dl->AddRectFilled(trackMin, trackMax, IM_COL32(30, 32, 38, 255), 3.0f);

    float t = (v_max > v_min) ? ((*v - v_min) / (v_max - v_min)) : 0.0f;
    t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);

    ImVec2 fillMax(pos.x + t * sliderWidth, trackMax.y);
    dl->AddRectFilled(trackMin, fillMax, ImGui::GetColorU32(ImVec4(g_RedThemeColor.x, g_RedThemeColor.y, g_RedThemeColor.z, 0.6f)), 3.0f);

    float grabX = pos.x + t * sliderWidth;
    float grabY = pos.y + height * 0.5f;
    dl->AddCircleFilled(ImVec2(grabX, grabY), 6.0f, ImGui::GetColorU32(g_RedThemeColor));

    ImGui::SetCursorScreenPos(pos);
    ImGui::InvisibleButton("##slider", ImVec2(sliderWidth, height));
    if (ImGui::IsItemActive()) {
        float mouseX = ImGui::GetIO().MousePos.x;
        float newT = (mouseX - pos.x) / sliderWidth;
        newT = newT < 0.0f ? 0.0f : (newT > 1.0f ? 1.0f : newT);
        *v = v_min + newT * (v_max - v_min);
        changed = true;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), fmt, *v);

    ImGui::SameLine(0.0f, 8.0f);
    ImVec2 boxPos = ImGui::GetCursorScreenPos();

                                                                          
                                                                        
                                                                       
                                                                               
    static ImGuiID s_editing = 0;
    const ImGuiID boxId = ImGui::GetID("##boxEdit");

    if (s_editing == boxId) {
        ImGui::SetNextItemWidth(valueBoxWidth);
                                                                              
        if (ImGui::InputFloat("##boxInput", v, 0.0f, 0.0f, fmt,
                              ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue)) {
            changed = true;
            s_editing = 0;
        }
        if (*v < v_min) *v = v_min;
        if (*v > v_max) *v = v_max;
                                                                          
        if (!ImGui::IsItemActive() && !ImGui::IsItemFocused() && s_editing == boxId)
            s_editing = 0;
    } else {
        ImVec2 boxMin(boxPos.x, boxPos.y);
        ImVec2 boxMax(boxPos.x + valueBoxWidth, boxPos.y + height);
        dl->AddRectFilled(boxMin, boxMax, IM_COL32(20, 22, 28, 255), 3.0f);
        dl->AddRect(boxMin, boxMax, IM_COL32(50, 55, 65, 255), 3.0f, 0, 1.0f);

        ImVec2 textSize = ImGui::CalcTextSize(buf);
        dl->AddText(ImVec2(boxMin.x + (valueBoxWidth - textSize.x) * 0.5f, boxMin.y + (height - textSize.y) * 0.5f),
            IM_COL32(200, 200, 210, 255), buf);
        ImGui::SetCursorScreenPos(boxPos);
        ImGui::InvisibleButton("##box", ImVec2(valueBoxWidth, height));
        if (ImGui::IsItemHovered())
            ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
        if (ImGui::IsItemClicked())
            s_editing = boxId;
    }

    ImGui::PopID();
    return changed;
}

static bool KingSliderInt(const char* label, int* v, int v_min, int v_max)
{
    float fv = static_cast<float>(*v);
    bool changed = KingSliderFloat(label, &fv, static_cast<float>(v_min), static_cast<float>(v_max), "%.0f");
    if (changed) *v = static_cast<int>(fv);
    return changed;
}

void DefaultImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.TouchExtraPadding = ImVec2(2.0f, 2.0f);

                                                                        
                                                                               
                                                             
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.PopupBorderSize = 1.0f;

                                                                                  
    style.WindowPadding = ImVec2(0, 0);
    style.FramePadding = ImVec2(12, 8);
    style.ItemSpacing = ImVec2(12, 11);
    style.ItemInnerSpacing = ImVec2(10, 7);
    style.CellPadding = ImVec2(10, 8);
    style.ScrollbarSize = 10.0f;
    style.GrabMinSize = 12.0f;
                                                                              
                                                                                
                                                                               
                                                                                  
                                                               
    style.IndentSpacing = 15.0f;

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.51f, 0.52f, 0.56f, 1.0f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.012f, 0.012f, 0.012f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.012f, 0.012f, 0.012f, 0.0f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.019f, 0.035f, 0.062f, 0.98f);

    colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 0.03f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.023f, 0.039f, 0.070f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.043f, 0.070f, 0.137f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.055f, 0.085f, 0.160f, 1.0f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.012f, 0.012f, 0.012f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.019f, 0.035f, 0.062f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.012f, 0.012f, 0.012f, 0.8f);

    colors[ImGuiCol_MenuBarBg] = ImVec4(0.023f, 0.039f, 0.07f, 1.0f);
                                                                           
                                                                              
                                                                       
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.020f, 0.024f, 0.036f, 0.90f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.28f, 0.40f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.34f, 0.40f, 0.58f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.42f, 0.52f, 0.85f, 1.0f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.043f, 0.07f, 0.137f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.031f, 0.035f, 0.058f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.050f, 0.054f, 0.078f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.070f, 0.074f, 0.098f, 1.0f);

    colors[ImGuiCol_Header] = ImVec4(0.043f, 0.07f, 0.137f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.06f, 0.09f, 0.17f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.08f, 0.11f, 0.20f, 1.0f);

    colors[ImGuiCol_Separator] = ImVec4(0.043f, 0.07f, 0.137f, 0.70f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.49f, 1.0f, 0.70f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);

    colors[ImGuiCol_ResizeGrip] = ImVec4(0.32f, 0.56f, 1.0f, 0.0f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.42f, 0.64f, 1.0f, 0.0f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.32f, 0.56f, 1.0f, 0.0f);

    colors[ImGuiCol_Tab] = ImVec4(0.023f, 0.039f, 0.07f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.050f, 0.054f, 0.078f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.043f, 0.07f, 0.137f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.019f, 0.035f, 0.062f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.043f, 0.07f, 0.137f, 1.0f);

    colors[ImGuiCol_PlotLines] = ImVec4(0.42f, 0.64f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.42f, 0.64f, 1.0f, 1.0f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.49f, 1.0f, 0.35f);

    colors[ImGuiCol_DragDropTarget] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.30f, 0.49f, 1.0f, 1.0f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.012f, 0.012f, 0.012f, 0.60f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.012f, 0.012f, 0.012f, 0.60f);
}

                                                                              
              
                                                                              
                                                                               
                                                                             
                                                                              
                                                                              
                                                                            
extern char  g_KingSearchTarget[128];
extern float g_KingSearchUntil;
extern int   g_KingSearchScroll;

namespace {

struct MenuSearchEntry { unsigned char tab, sub; const char* label; };

                                                                              
                                                                          
                                                           
static const MenuSearchEntry kSearchIndex[] = {
                                                                             
    { 0, 0, "RANK SELECTION" },
    { 0, 0, "RANK SETTINGS" },
    { 0, 0, "PLAYLIST" },
    { 0, 0, "REWARDS & OVERLAY" },
    { 0, 0, "Show Player MMR Overlay" },
                                                                             
    { 1, 0, "SPAWN BY CATEGORY" },
    { 1, 0, "QUALITY SETS" },
    { 1, 0, "EXTRA" },
    { 1, 1, "TRADE-UP SIMULATOR" },
    { 1, 1, "Spawn Reward Item" },
    { 1, 1, "CREDIT SPAWNER" },
    { 1, 1, "Credit Amount:" },
    { 1, 1, "Special Credit Types:" },
    { 1, 2, "EQUIPPED ITEMS" },
    { 1, 2, "Enable Equip Overrides" },
    { 1, 2, "LOADOUT PRESET" },
    { 1, 2, "PAINTED ITEM SELECTOR" },
                                                                             
    { 2, 0, "BLACK CAR" },
    { 2, 0, "CUSTOM PAINT (Trim Only)" },
    { 2, 0, "Enable Custom Paint Trim" },
    { 2, 0, "Rainbow Trim" },
    { 2, 0, "ALPHA BOOST COLOR" },
    { 2, 0, "Enable Alpha Boost Color" },
    { 2, 0, "Rainbow Boost Color" },
    { 2, 0, "WHEEL COLOR" },
    { 2, 0, "Enable Wheel Color" },
    { 2, 0, "Rainbow Wheel Color" },
    { 2, 0, "UNDERGLOW" },
    { 2, 0, "Enable Underglow" },
    { 2, 0, "Rainbow Underglow" },
    { 2, 1, "HUD Colors" },
    { 2, 1, "Enable HUD Colors" },
    { 2, 1, "Rainbow HUD Colors" },
    { 2, 1, "Blue Team HUD" },
    { 2, 1, "Orange Team HUD" },
    { 2, 1, "Stadium Colors" },
    { 2, 1, "Enable Stadium Colors" },
    { 2, 1, "Rainbow Stadium Colors" },
    { 2, 1, "Blue Team Stadium" },
    { 2, 1, "Orange Team Stadium" },
    { 2, 1, "CUSTOM MODALS" },
                                                                             
    { 3, 0, "PSYNET" },
    { 3, 0, "Enable PsyNet Logging" },
    { 3, 0, "Enable Drop / Crate Edit" },
    { 3, 0, "HEADERS" },
    { 3, 0, "BODY" },
                                                                             
    { 4, 1, "FAVORITES" },
    { 4, 1, "RECENT" },
                                                                             
    { 5, 0, "Enable Camera Override" },
                                                                             
    { 6, 0, "PRESETS MANAGER" },
    { 6, 0, "BALL PREDICTION" },
    { 6, 0, "Enable Prediction" },
    { 6, 0, "BALL PREDICTION IN GOAL" },
    { 6, 0, "CROSSHAIR IN GOAL" },
    { 6, 0, "BALL PREDICTION SETTINGS" },
    { 6, 0, "Speed Color" },
    { 6, 0, "Smoothing" },
    { 6, 0, "Show Line" },
    { 6, 0, "Landing Marker" },
    { 6, 0, "Bounce Markers" },
    { 6, 0, "Time-to-Goal" },
    { 6, 1, "MINIMAP" },
    { 6, 1, "Enable Minimap" },
    { 6, 1, "Show Ball" },
    { 6, 1, "Show Players" },
    { 6, 1, "Team Colors" },
                                                                             
    { 7, 0, "DATA MANAGEMENT" },
    { 7, 0, "Skip Replays" },
    { 7, 0, "Auto Queue" },
    { 7, 0, "Auto Leave Match" },
    { 7, 2, "PLAYER VISUALS" },
    { 7, 2, "Draw Tracers" },
    { 7, 2, "Use Team Colors" },
    { 7, 2, "Draw Car Hitboxes" },
    { 7, 2, "Player Distance" },
    { 7, 2, "Opponent Boost" },
    { 7, 2, "Velocity Arrows" },
    { 7, 2, "GENERAL & OVERLAYS" },
    { 7, 2, "Flip Indicator" },
    { 7, 2, "BoostPad Timers" },
    { 7, 2, "Ball Speed" },
    { 7, 2, "Controller" },
    { 7, 2, "Keyboard Overlay" },
                                                                             
    { 7, 1, "CUSTOM TITLE" },
    { 7, 1, "Show Title Animation" },
                                                                             
    { 10, 0, "CAR" },
    { 10, 0, "Premium Garage" },
    { 10, 0, "CAR POSITION(Lobby)" },
    { 10, 0, "Rotation" },
    { 10, 0, "CAR SCALE" },
    { 10, 1, "WHEEL CUSTOMIZATION" },
    { 10, 1, "Size" },
    { 10, 1, "Translation & Camber" },
    { 10, 1, "Configs" },
    { 10, 2, "LICENSE PLATES" },
                                                                             
    { 11, 0, "Ball Textures" },
    { 11, 1, "Avatar Textures" },
    { 11, 2, "Custom Decal" },
    { 11, 3, "Custom Banner" },
    { 11, 4, "Boost Meter Textures" },
                                                                             
    { 12, 0, "LOCAL SERVER SETTINGS" },
    { 12, 1, "EFFECTS" },
    { 12, 1, "Remove Demo Smoke" },
    { 12, 1, "Remove Goal Explosion" },
                                                                             
    { 13, 0, "ROCKET PASS" },
    { 13, 0, "Tier Level" },
    { 13, 0, "XP Multiplier" },
    { 13, 0, "Premium Pass" },
    { 13, 1, "ONLINE STATUS" },
    { 13, 1, "Enable Custom Online Status" },
    { 13, 1, "NETWORK" },
    { 13, 1, "Enable Ping Spoofer" },
                                                                             
    { 6, 2, "BALL VISUALS" },
    { 6, 2, "3D Ball Sphere" },
    { 6, 2, "See Players Through Ball" },
    { 6, 2, "BALL SPEED" },
    { 6, 2, "Show Ball Speed" },
                                                                             
    { 14, 0, "TAS CONTROLS" },
    { 14, 0, "Start" },
    { 14, 0, "Stop" },
    { 14, 0, "Update" },
    { 14, 0, "New TAS" },
    { 14, 0, "Replaying Speed" },
    { 14, 0, "Recording Speed" },
    { 14, 1, "GENERAL" },
    { 14, 1, "Start Replay On Reset" },
    { 14, 1, "START RECORDING OPTIONS" },
    { 14, 1, "Popup Settings" },
    { 14, 1, "ADVANCED" },
    { 14, 1, "Validate Map / Sensitivities / Hitbox" },
    { 14, 1, "Allow Listen Server / Host (on by default)" },
    { 14, 2, "LOADED TAS" },
    { 14, 2, "Save TAS" },
    { 14, 2, "Stop + Update" },
    { 14, 3, "TAS FILES" },
    { 14, 3, "Load" },
    { 14, 3, "Delete" },
    { 14, 3, "Refresh" },
                                                                             
    { 9, 0, "DASHBOARD" },
    { 9, 0, "MATCH SHIELD" },
    { 9, 0, "Local Bot Detection" },
    { 9, 0, "Auto Scan Matches" },
    { 9, 0, "Mark Match Key" },
    { 9, 0, "Leave On Game Bot" },
    { 9, 0, "FILES" },
    { 9, 1, "LOCAL NAME" },
    { 9, 1, "Blank Local Name" },
    { 9, 1, "Local Username" },
    { 9, 1, "VISIBILITY" },
    { 9, 1, "Enemy Reset (Flip) Indicator" },
    { 9, 1, "Platform Avatar Icons" },
    { 9, 1, "Show MMR On Scoreboard" },
    { 9, 1, "POV Camera In Replays" },
    { 9, 1, "AUDIO" },
    { 9, 1, "Force Default Boost Sound" },
    { 9, 1, "Alpha Boost Sound" },
    { 9, 1, "All Boosts Sound Like Alpha Boost" },
    { 9, 2, "FREEPLAY" },
    { 9, 2, "Unlimited Flips / Jumps" },
    { 9, 2, "Ball Pinch Strength" },
    { 9, 2, "Pinch Strength" },
    { 9, 2, "Scored Message" },
    { 9, 2, "Show Ball Speed" },
    { 9, 2, "Speed Unit" },
    { 9, 2, "Test Local Message" },
    { 9, 2, "INSTALLED MAPS" },
    { 9, 2, "Load Method" },
    { 9, 3, "WORKSHOP" },
    { 9, 3, "Download" },
    { 9, 3, "Installed" },
    { 9, 3, "Extract" },
    { 9, 3, "Installed Maps" },
    { 9, 3, "Load Method" },
    { 9, 3, "Source" },
    { 9, 3, "Steam Workshop" },
    { 9, 3, "Community Maps" },
    { 9, 3, "LOCAL PLAY" },
    { 9, 3, "Training" },
    { 9, 3, "Local Match" },
    { 9, 4, "SERVER" },
    { 9, 4, "Host LAN Match" },
    { 9, 4, "Join LAN Match" },
    { 9, 4, "Host / Domain" },
    { 9, 4, "Advanced Match Settings" },
    { 9, 5, "PRESETS MANAGER" },
                                                                             
    { 16, 0, "TRAINING LAB" },
    { 16, 0, "Checkpoint" },
    { 16, 0, "Shot Launcher" },
    { 16, 0, "Unlimited Boost" },
    { 16, 0, "Unlimited Dodge" },
    { 16, 0, "Kickoff Timer" },
    { 17, 0, "HOST CONTROL" },
    { 17, 0, "Score & Time" },
    { 17, 0, "Ball Physics" },
    { 17, 0, "Ball Pinch Strength" },
    { 17, 0, "Pinch Strength" },
    { 17, 0, "Bot Manager" },
    { 17, 1, "PLAYER MANAGER" },
    { 17, 1, "Freeze Player" },
    { 17, 1, "Respawn Player" },
    { 17, 1, "Move Team" },
    { 17, 1, "Follow" },
    { 17, 1, "Unfollow" },
    { 18, 0, "CINEMATIC" },
    { 18, 0, "Photo Mode" },
    { 18, 0, "Slow Motion" },
    { 18, 0, "Freecam" },
    { 18, 0, "Camera Path" },
    { 19, 0, "KING SYNC" },
    { 19, 0, "LAN Peer Sync" },
    { 21, 0, "PROFILES" },
    { 21, 0, "Competitive Profile" },
    { 21, 0, "Training Profile" },
    { 21, 0, "LAN Host Profile" },
    { 21, 0, "Cinematic Profile" },
    { 22, 0, "MATCH SHIELD" },
    { 22, 0, "Auto Accept" },
    { 22, 0, "Hold Timeout" },
    { 24, 0, "AUTOMATION" },
    { 24, 0, "Skip Replays" },
    { 24, 0, "Auto Queue" },
    { 24, 0, "Auto Leave Match" },
    { 24, 0, "Quick Actions" },
    { 25, 0, "SESSION HUD" },
    { 25, 0, "Session Telemetry" },
    { 25, 0, "Export Session Stats" },
                                                                             
    { 8, 0, "PRESETS MANAGER" },
    { 8, 0, "UI COLORS" },
    { 8, 0, "OTHERS" },
    { 8, 1, "OVERLAY" },
    { 8, 1, "Show FPS Counter" },
    { 8, 2, "MENU TOGGLE KEY" },
    { 8, 3, "KINGMOD" },
};

static const char* const kSearchTabNames[26] = {
    "Rank", "Items", "Paint / HUD", "PsyNet", "Party", "Camera", "Ball", "Gameplay",
    "Settings", "Extras", "Car", "Textures", "World", "Account", "TAS", "",
    "Training Lab", "Host Center", "Cinematic", "King Sync", "", "Profiles",
    "Match Shield", "", "Automation", "Session HUD"
};
static const char* const kSearchSubNames[26][6] = {
    { "General", "", "", "", "", "" },
    { "Item Spawner", "Trade-Up", "Equipped Items", "", "", "" },
    { "Paint", "HUD", "Custom Car", "", "", "" },
    { "Log", "", "", "", "", "" },
    { "Invites", "Favorites", "", "", "", "" },
    { "Camera", "", "", "", "", "" },
    { "Prediction", "Minimap", "Ball", "", "", "" },
    { "Features", "Titles", "Overlays", "", "", "" },
    { "Customize", "Overlay", "Key", "KingMod", "", "" },
    { "Info", "Player", "Freeplay", "Workshop", "Server", "Presets" },
    { "Body", "Wheels", "Plates", "", "", "" },
    { "Ball", "Avatar", "Decal", "Banner", "Boost", "" },
    { "Local Server", "Effects", "", "", "", "" },
    { "Rocket Pass", "Online Status", "", "", "", "" },
    { "Controls", "Settings", "Loaded TAS", "Files", "", "" },
    { "", "", "", "", "", "" },
    { "Training Lab", "", "", "", "", "" },
    { "Host Control", "Players", "", "", "", "" },
    { "Cinematic", "", "", "", "", "" },
    { "King Sync", "", "", "", "", "" },
    { "", "", "", "", "", "" },
    { "Profiles", "", "", "", "", "" },
    { "Match Shield", "", "", "", "", "" },
    { "", "", "", "", "", "" },
    { "Automation", "", "", "", "", "" },
    { "Session HUD", "", "", "", "", "" },
};

static bool  g_MenuSearchOpen = false;
static bool  g_MenuSearchFocus = false;
static bool  g_MenuSearchWasActive = false;
static char  g_MenuSearchBuf[64] = "";

                                                                              
static bool SearchCiContains(const char* hay, const char* needle) {
    if (!needle || !*needle) return false;
    for (const char* s = hay; *s; ++s) {
        const char* h = s; const char* n = needle;
        while (*h && *n) {
            char ca = *h, cb = *n;
            if (ca >= 'A' && ca <= 'Z') ca += 32;
            if (cb >= 'A' && cb <= 'Z') cb += 32;
            if (ca != cb) break;
            ++h; ++n;
        }
        if (*n == '\0') return true;
    }
    return false;
}

static const char* const kBindKeys[] = {
    "Mouse1", "Mouse2", "Mouse3", "Mouse4", "Mouse5",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
    "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
    "Insert", "Delete", "Home", "End", "PageUp", "PageDown",
    "Up", "Down", "Left", "Right", "Space", "Enter", "Tab", "Backspace", "Escape",
    "Shift", "Ctrl", "Alt", "CapsLock", "Pause", "PrintScreen", "NumLock", "ScrollLock",
    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5",
    "Numpad6", "Numpad7", "Numpad8", "Numpad9", "Numpad+", "Numpad-", "Numpad*", "Numpad/", "Numpad."
};

static int RenderBindSelector(const char* id, const char* current) {
    static char filter[48] = "";
    int selectedIndex = -1;
    if (ImGui::BeginCombo(id, current && current[0] ? current : "Select a key")) {
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputTextWithHint("##bind_filter", ICON_FA_SEARCH "  Search keys...", filter, sizeof(filter));
        ImGui::Separator();
        for (int index = 0; index < IM_ARRAYSIZE(kBindKeys); ++index) {
            if (filter[0] != '\0' && !SearchCiContains(kBindKeys[index], filter))
                continue;
            const bool selected = current && strcmp(current, kBindKeys[index]) == 0;
            if (ImGui::Selectable(kBindKeys[index], selected)) {
                selectedIndex = index;
                filter[0] = '\0';
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    return selectedIndex;
}

static void MenuSearchJumpTo(const MenuSearchEntry& e) {
    gui.m_tab = e.tab;
    gui.m_active_subtab[e.tab] = e.sub;
    gui.m_anim = 0.f;
    GameEventHookModule::LastSelectedTab = e.tab;

    strncpy_s(g_KingSearchTarget, sizeof(g_KingSearchTarget), e.label, _TRUNCATE);
    g_KingSearchUntil = (float)ImGui::GetTime() + 6.0f;
    g_KingSearchScroll = 1;

    g_MenuSearchOpen = false;
    g_MenuSearchWasActive = false;
    g_MenuSearchBuf[0] = '\0';
}

                                                                              
static void RenderMenuSearchBar(float x, float y, float maxW) {
    ImGui::SetCursorPos(ImVec2(x, y));
    if (!g_MenuSearchOpen) {
                                                
        if (ImGui::Button(ICON_FA_SEARCH "##menusearch", ImVec2(25, 25))) {
            g_MenuSearchOpen = true;
            g_MenuSearchFocus = true;
            g_MenuSearchWasActive = false;
        }
        return;
    }

                                                                          
                                       
    const float fw = ImMax(120.0f, ImMin(260.0f, maxW));
    if (g_MenuSearchFocus) { ImGui::SetKeyboardFocusHere(); g_MenuSearchFocus = false; }
    ImGui::SetNextItemWidth(fw);
    ImGui::InputTextWithHint("##menusearchbox", ICON_FA_SEARCH "  Search anything...",
        g_MenuSearchBuf, sizeof(g_MenuSearchBuf));
    const bool active = ImGui::IsItemActive();
                                                                             
                                                                               
                                                                              
    if (active && ImGui::IsKeyPressed(ImGuiKey_Escape)) {
        g_MenuSearchOpen = false;
        g_MenuSearchBuf[0] = '\0';
        g_MenuSearchWasActive = false;
    }
    else if (g_MenuSearchWasActive && !active && g_MenuSearchBuf[0] == '\0') {
        g_MenuSearchOpen = false;
        g_MenuSearchWasActive = false;
    }
    else if (active) {
        g_MenuSearchWasActive = true;
    }
}

                                                                               
static bool RenderMenuSearchResults() {
    if (!g_MenuSearchOpen || g_MenuSearchBuf[0] == '\0')
        return false;

    ImGui::TextColored(g_RedThemeColor, ICON_FA_SEARCH "  SEARCH RESULTS");
    ImGui::Spacing();

    int shown = 0;
    for (int i = 0; i < IM_ARRAYSIZE(kSearchIndex); ++i) {
        const MenuSearchEntry& e = kSearchIndex[i];
        if (!SearchCiContains(e.label, g_MenuSearchBuf))
            continue;

        const char* sub = kSearchSubNames[e.tab][e.sub];
                                                                                 
                                                                        
        char row[224];
        if (sub && sub[0])
            sprintf_s(row, sizeof(row), ICON_FA_CHEVRON_RIGHT "  %s      %s " ICON_FA_ANGLE_RIGHT " %s##sr%d",
                e.label, kSearchTabNames[e.tab], sub, i);
        else
            sprintf_s(row, sizeof(row), ICON_FA_CHEVRON_RIGHT "  %s      %s##sr%d",
                e.label, kSearchTabNames[e.tab], i);
        if (ImGui::Button(row, ImVec2(-1.0f, 26.0f)))
            MenuSearchJumpTo(e);

        if (++shown >= 40)
            break;
    }

    if (shown == 0) {
        ImGui::Spacing();
        ImGui::TextDisabled(ICON_FA_TIMES_CIRCLE "  No option matches \"%s\".", g_MenuSearchBuf);
    }
    return true;
}

}             

                                                                              
                                                                            
                                                                         
                                                                           
                                                                              
                                                     
static void KingPollMouseInput()
{
    if (!ImGui::GetCurrentContext())
        return;

    static bool prevDown[5] = {};
    static const int vk[5] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

    bool nowDown[5];
    for (int i = 0; i < 5; ++i)
        nowDown[i] = (GetAsyncKeyState(vk[i]) & 0x8000) != 0;

    const bool active = KingImGuiInputActive();
    if (active)
    {
        ImGuiIO& io = ImGui::GetIO();

        for (int i = 0; i < 5; ++i)
            if (nowDown[i] != prevDown[i])
                io.AddMouseButtonEvent(i, nowDown[i]);

                                                                           
                                                    
        if (window)
        {
            POINT pt;
            if (GetCursorPos(&pt) && ScreenToClient(window, &pt))
                io.AddMousePosEvent((float)pt.x, (float)pt.y);
        }

                                                                          
                                                                            
        ClipCursor(nullptr);
    }

    memcpy(prevDown, nowDown, sizeof(prevDown));
}

void GUIComponent::Render()
{
    KingPollMouseInput();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& IO = ImGui::GetIO();
    GUI.DisplayX = IO.DisplaySize.x;
    GUI.DisplayY = IO.DisplaySize.y;

                                             
    if (GameEventHook.IsInitialized) {
        GameEventHook.OnRender();
    }

                                                                       
                                                                             
    Items.QueueAutoApplyLoadoutPreset();

    IO.MouseDrawCursor = IsOpen || KingConsole::IsOpen() || Notify::HasPopup();

    if (showFPSCounter) {
        RenderFPSCounter();
    }

                                          
    SilverModUI::RenderWatermark();

                                                                              
                                                                            
                                                                              
    KingConsole::Render();

                                                                          



                                
                                     
    LoadGuiWindowLayout();
    static bool firstTime = true;
    static bool wasMenuOpen = false;
    if (firstTime)
    {
        ImGui::SetNextWindowSize(g_GuiWindowLayout.Size, ImGuiCond_Always);

        if (g_GuiWindowLayout.HasSavedRect) {
            ImGui::SetNextWindowPos(g_GuiWindowLayout.Pos, ImGuiCond_Always);
        } else {
            RECT screen_rect;
            GetWindowRect(GetDesktopWindow(), &screen_rect);
            int pos_x = (screen_rect.right - static_cast<int>(g_GuiWindowLayout.Size.x)) / 2;
            int pos_y = (screen_rect.bottom - static_cast<int>(g_GuiWindowLayout.Size.y)) / 2;
            ImGui::SetNextWindowPos(ImVec2((float)pos_x, (float)pos_y), ImGuiCond_Always);
        }
        
        firstTime = false;
    }
    
                                                                         
    bool isMenuOpen = IsOpen;
    static bool tabsInitialized = false;
    if (!tabsInitialized)
    {
        gui.m_tab = std::clamp(GameEventHookModule::LastSelectedTab, 0, 25);

                                                                              
                                                                             
        if (gui.m_tab == 15)
        {
            gui.m_tab = 3;
            GameEventHookModule::LastSelectedTab = gui.m_tab;
        }
        tabsInitialized = true;
    }
    wasMenuOpen = isMenuOpen;

    if (IsOpen) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                                                                            
                                                                           
        ImGui::SetNextWindowSize(ImVec2(1050.0f, 680.0f), ImGuiCond_Always);
        ImGui::Begin("KingMod", &IsOpen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground); {

            auto window = ImGui::GetCurrentWindow();
            auto draw = window->DrawList;
            auto pos = window->Pos;
            auto size = window->Size;

            gui.m_anim = ImLerp(gui.m_anim, 1.f, 0.045f);

                                                                                  
                                                                                
                                                                             
                                                                          
            auto rainbowAt = [](float speed, float sat) -> ImVec4 {
                float hue = ImFmod((float)ImGui::GetTime() * (speed / 100.0f) * 0.20f, 1.0f);
                if (hue < 0.0f) hue += 1.0f;
                ImVec4 c = (ImVec4)ImColor::HSV(hue, sat, 1.0f);
                return c;
            };
            ImVec4 themeAccent = GameEventHookModule::UIAccentRainbow
                ? rainbowAt(GameEventHookModule::UIAccentRainbowSpeed, 0.70f)
                : GameEventHookModule::UIAccentColor;
            ImVec4 themeBg = GameEventHookModule::UIBackgroundRainbow
                ? rainbowAt(GameEventHookModule::UIBackgroundRainbowSpeed, 0.55f)
                : GameEventHookModule::UIBackgroundColor;
            if (GameEventHookModule::UIBackgroundRainbow)
                themeBg.w = GameEventHookModule::UIBackgroundColor.w;                       
            gui.accent_color.r = themeAccent.x; gui.accent_color.g = themeAccent.y;
            gui.accent_color.b = themeAccent.z; gui.accent_color.a = themeAccent.w;
            g_RedThemeColor = themeAccent;
            g_LightRedColor = ImVec4(ImMin(themeAccent.x + 0.08f, 1.0f),
                                     ImMin(themeAccent.y + 0.08f, 1.0f),
                                     ImMin(themeAccent.z + 0.08f, 1.0f), 1.0f);
            blur::enabled = GameEventHookModule::UIBlurEnabled;

                                                                               
                                                                            
                                                                                
                                                                            
                                                                                
                                                                              
              
                                                                                  
                                                                                
                                                                          
                                                                                  
                                                                              
                                                             
            const ImVec4 kNeutral(0.043f, 0.047f, 0.063f, 1.0f);
            const float  kTintMix = 0.16f;
            const ImVec4 baseBg(kNeutral.x + (themeBg.x - kNeutral.x) * kTintMix,
                                kNeutral.y + (themeBg.y - kNeutral.y) * kTintMix,
                                kNeutral.z + (themeBg.z - kNeutral.z) * kTintMix,
                                themeBg.w);
            const ImVec4 kLift(0.82f, 0.87f, 1.00f, 1.00f);
            auto lift = [&](float k, float a) -> ImVec4 {
                return ImVec4(baseBg.x + (kLift.x - baseBg.x) * k,
                              baseBg.y + (kLift.y - baseBg.y) * k,
                              baseBg.z + (kLift.z - baseBg.z) * k, a);
            };
            auto sink = [&](float k, float a) -> ImVec4 {
                return ImVec4(baseBg.x * (1.0f - k), baseBg.y * (1.0f - k),
                              baseBg.z * (1.0f - k), a);
            };
                                                                                
                                                                                 
                                                                              
                                                                  
            const bool  frost  = blur::enabled;
            const float aCard  = frost ? 0.45f : 1.00f;
            const float aFrame = frost ? 0.50f : 1.00f;
            const float aPopup = frost ? 0.90f : 0.98f;                                  
            const float aSide  = frost ? 0.55f : 0.98f;
            const ImVec4 bgCard   = lift(0.055f, aCard);                              
            const ImVec4 bgFrame  = lift(0.085f, aFrame);                           
            const ImVec4 bgFrameH = lift(0.150f, aFrame);
            const ImVec4 bgFrameA = lift(0.200f, aFrame);
            const ImVec4 bgPopup  = lift(0.030f, aPopup);                           
            const ImVec4 bgSide   = sink(0.45f,  aSide);                          
            {
                ImGuiStyle& s = ImGui::GetStyle();
                s.Colors[ImGuiCol_FrameBg]        = bgFrame;
                s.Colors[ImGuiCol_FrameBgHovered] = bgFrameH;
                s.Colors[ImGuiCol_FrameBgActive]  = bgFrameA;
                s.Colors[ImGuiCol_PopupBg]        = bgPopup;
                s.Colors[ImGuiCol_Header]         = bgFrame;
                s.Colors[ImGuiCol_HeaderHovered]  = bgFrameH;
                s.Colors[ImGuiCol_HeaderActive]   = bgFrameA;
                s.Colors[ImGuiCol_TitleBgActive]  = bgCard;
            }
            gui.group_box_bg.r = bgCard.x; gui.group_box_bg.g = bgCard.y;
            gui.group_box_bg.b = bgCard.z; gui.group_box_bg.a = bgCard.w;

                                                                                  
                                                                                   
                                                                                
                                                                            
                                                                                 
                                                                                 
                                                                   
            const float aSolid = frost ? 0.72f : 1.00f;
            const ImVec4 bgBtn  = lift(0.030f, aSolid);
            const ImVec4 bgBtnH = lift(0.075f, aSolid);
            const ImVec4 bgBtnA = lift(0.120f, aSolid);
            gui.button.r = bgBtn.x;  gui.button.g = bgBtn.y;  gui.button.b = bgBtn.z;  gui.button.a = bgBtn.w;
            gui.button_hovered.r = bgBtnH.x; gui.button_hovered.g = bgBtnH.y;
            gui.button_hovered.b = bgBtnH.z; gui.button_hovered.a = bgBtnH.w;
            gui.button_active.r = bgBtnA.x;  gui.button_active.g = bgBtnA.y;
            gui.button_active.b = bgBtnA.z;  gui.button_active.a = bgBtnA.w;
            const ImVec4 fiCol = sink(0.30f, frost ? 0.85f : 1.00f);
            const ImVec4 faCol = lift(0.100f, frost ? 0.85f : 1.00f);
            gui.frame_inactive.r = fiCol.x; gui.frame_inactive.g = fiCol.y;
            gui.frame_inactive.b = fiCol.z; gui.frame_inactive.a = fiCol.w;
            gui.frame_active.r = faCol.x;   gui.frame_active.g = faCol.y;
            gui.frame_active.b = faCol.z;   gui.frame_active.a = faCol.w;

                                                                            
                                                                            
                                                                      
            draw_blur(draw);

                                                                             
                                                                             
                                                                    
                                                                                
                                                                                  
                                                                             
                                                                     
            const float sidebarWidth = 170.0f;
            ImVec4 canvasBg = baseBg;
            canvasBg.w = blur::enabled ? ImClamp(themeBg.w * 0.40f, 0.14f, 0.45f) : 0.94f;
            draw->AddRectFilled(pos, pos + size, ImGui::GetColorU32(canvasBg), 6.0f);
            draw->AddRectFilled(pos, pos + ImVec2(sidebarWidth, size.y), ImGui::GetColorU32(bgSide), 6.0f,
                ImDrawFlags_RoundCornersLeft);
            draw->AddLine(pos + ImVec2(sidebarWidth, 0.0f), pos + ImVec2(sidebarWidth, size.y),
                IM_COL32(255, 255, 255, 10));
            draw->AddRect(pos, pos + size, IM_COL32(255, 255, 255, 18), 6.0f);

                                                                              
                                                                               
            menu_avatar::Update();

            const char* playerName = menu_avatar::Name();
            static char nameBuf[32];
            const size_t nameLen = strlen(playerName);
            const size_t shown = nameLen > 16 ? 16 : nameLen;
            memcpy(nameBuf, playerName, shown);
            nameBuf[shown] = '\0';
            const char* shortName = (shown == nameLen) ? playerName : nameBuf;

            ImFont* brandFont = GUIComponent::FontKingItalic ? GUIComponent::FontKingItalic : ImGui::GetFont();
            const float brandSize = brandFont->FontSize;
            const ImVec2 brandTextSize = brandFont->CalcTextSizeA(brandSize, FLT_MAX, 0.0f, "KINGMOD");
            const ImVec2 brandPos = pos + ImVec2((sidebarWidth - brandTextSize.x) * 0.5f, 20.0f);
            draw->AddText(brandFont, brandSize, brandPos + ImVec2(1.0f, 0.0f), ImGui::GetColorU32(g_RedThemeColor), "KINGMOD");
            draw->AddText(brandFont, brandSize, brandPos, IM_COL32(246, 248, 255, 255), "KINGMOD");

            const float avatarR = 15.0f;
            const ImVec2 avatarC = pos + ImVec2(30.0f, size.y - 25.0f);
            if (ImTextureID avatarTex = menu_avatar::Texture()) {
                draw->AddImageRounded(avatarTex, avatarC - ImVec2(avatarR, avatarR), avatarC + ImVec2(avatarR, avatarR),
                    ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255), avatarR, ImDrawFlags_None);
                draw->AddCircle(avatarC, avatarR, gui.accent_color.to_im_color(), 40, 2.0f);
            }
            else {
                draw->AddCircleFilled(avatarC, avatarR, IM_COL32(18, 22, 32, 255));
                draw->AddCircle(avatarC, avatarR, gui.accent_color.to_im_color(), 40, 2.0f);
                const char initial[2] = { playerName[0] ? playerName[0] : '?', '\0' };
                if (ImFont* defFont = ImGui::GetIO().Fonts->Fonts.Size > 0 ? ImGui::GetIO().Fonts->Fonts[0] : nullptr) {
                    const ImVec2 ts = defFont->CalcTextSizeA(defFont->FontSize, FLT_MAX, 0, initial);
                    draw->AddText(defFont, defFont->FontSize, avatarC - ImVec2(ts.x * 0.5f, ts.y * 0.5f), IM_COL32(255, 255, 255, 235), initial);
                }
            }

            draw->AddLine(pos + ImVec2(0, size.y - 50), pos + ImVec2(sidebarWidth, size.y - 50), IM_COL32(255, 255, 255, 10));
            draw->AddText(pos + ImVec2(50, size.y - 40), gui.text.to_im_color(), shortName);
            draw->AddText(pos + ImVec2(50, size.y - 25), gui.text_disabled.to_im_color(), "KingMod");

                                                                                
                                 
              
                                                                             
                                                                               
              
                        
                                                                          
                                                                    
                                                                                
            struct MenuHubTarget {
                const char* label;
                int tab;
                int sub;
                int titleMode;                                                 
            };
            struct MenuHubPage {
                const char* icon;
                const char* label;
                const MenuHubTarget* targets;
                int count;
            };

                                                                              
            static const MenuHubTarget hubOffline[] = {
                { ICON_FA_GAMEPAD " Freeplay",     9, 2, 0 },
                { ICON_FA_GLOBE " Local World",   12, 0, 0 },
                { ICON_FA_MAGIC " Effects",       12, 1, 0 },
                { ICON_FA_FILM " TAS",            14, 0, 0 },
            };

                                                   
            static const MenuHubTarget hubOnline[] = {
                { ICON_FA_COGS " Match Tools",             7, 0, 0 },
                { ICON_FA_STREAM " PsyNet",                3, 0, 0 },
                { ICON_FA_USER_PLUS " Invites",            4, 0, 0 },
                { ICON_FA_STAR " Favorites",               4, 1, 0 },
                { ICON_FA_SHIELD_ALT " Match Shield",     22, 0, 0 },
            };

                                                                            
                                                                             
            static const MenuHubTarget hubWorkshop[] = {
                { ICON_FA_MAP " Workshop + Launcher", 9, 3, 0 },
            };

                                                          
            static const MenuHubTarget hubServer[] = {
                { ICON_FA_SERVER " Host / Join",       9, 4, 0 },
                { ICON_FA_SLIDERS_H " Host Controls", 17, 0, 0 },
                { ICON_FA_USERS_COG " Admin",         17, 1, 0 },
                { ICON_FA_LINK " King Sync",          19, 0, 0 },
            };

                                                                           
            static const MenuHubTarget hubGarage[] = {
                { ICON_FA_BOX_OPEN " Item Spawner", 1, 0, 0 },
                { ICON_FA_EXCHANGE_ALT " Trade-Up", 1, 1, 0 },
                { ICON_FA_TSHIRT " Equipped",       1, 2, 0 },
                { ICON_FA_PAINT_BRUSH " Paint",     2, 0, 0 },
                { ICON_FA_CAR " Custom Car",        2, 2, 0 },
                { ICON_FA_CAR " Body",             10, 0, 0 },
                { ICON_FA_COG " Wheels",           10, 1, 0 },
                { ICON_FA_ID_CARD " Plates",       10, 2, 0 },
            };

                                                
            static const MenuHubTarget hubTitles[] = {
                { ICON_FA_CROWN " Titles",          7, 1, 0 },
                { ICON_FA_USER_EDIT " Custom Title",7, 1, 1 },
            };

                                                     
            static const MenuHubTarget hubVisuals[] = {
                { ICON_FA_ROUTE " Prediction",        6, 0, 0 },
                { ICON_FA_MAP_MARKED_ALT " Minimap",  6, 1, 0 },
                { ICON_FA_FUTBOL " Ball",             6, 2, 0 },
                { ICON_FA_DESKTOP " HUD",             2, 1, 0 },
                { ICON_FA_EYE " Overlays",            7, 2, 0 },
                { ICON_FA_TACHOMETER_ALT " FPS UI",   8, 1, 0 },
            };

                                                                           
            static const MenuHubTarget hubTextures[] = {
                { ICON_FA_FUTBOL " Ball",             11, 0, 0 },
                { ICON_FA_USER_CIRCLE " Avatar",      11, 1, 0 },
                { ICON_FA_CAR " Decal",               11, 2, 0 },
                { ICON_FA_ID_CARD " Banner",          11, 3, 0 },
                { ICON_FA_TACHOMETER_ALT " Boost",    11, 4, 0 },
            };

            static const MenuHubTarget hubCamera[] = {
                { ICON_FA_VIDEO " Camera",      5, 0, 0 },
                { ICON_FA_CAMERA " Cinematic", 18, 0, 0 },
            };

            static const MenuHubTarget hubTraining[] = {
                { ICON_FA_BULLSEYE " Training Lab",       16, 0, 0 },
                { ICON_FA_TACHOMETER_ALT " Session HUD",   25, 0, 0 },
            };

            static const MenuHubTarget hubAccount[] = {
                { ICON_FA_TROPHY " Rank",              0, 0, 0 },
                { ICON_FA_USER_SECRET " Player",        9, 1, 0 },
                { ICON_FA_CROWN " Rocket Pass",        13, 0, 0 },
                { ICON_FA_NETWORK_WIRED " Status",     13, 1, 0 },
            };

            static const MenuHubTarget hubTools[] = {
                { ICON_FA_ID_BADGE " Info",      9, 0, 0 },
                { ICON_FA_SAVE " Presets",        9, 5, 0 },
                { ICON_FA_COGS " Automation",    24, 0, 0 },
                { ICON_FA_SLIDERS_H " Profiles", 21, 0, 0 },
            };

            static const MenuHubTarget hubSettings[] = {
                { ICON_FA_PALETTE " Customize", 8, 0, 0 },
                { ICON_FA_KEYBOARD " Hotkey",   8, 2, 0 },
                { ICON_FA_ID_CARD " KingMod",   8, 3, 0 },
            };

            static const MenuHubPage hubPages[] = {
                { ICON_FA_GAMEPAD,  "Offline",  hubOffline,  IM_ARRAYSIZE(hubOffline)  },
                { ICON_FA_GLOBE,    "Online",   hubOnline,   IM_ARRAYSIZE(hubOnline)   },
                { ICON_FA_MAP,      "Workshop", hubWorkshop, IM_ARRAYSIZE(hubWorkshop) },
                { ICON_FA_SERVER,   "Server",   hubServer,   IM_ARRAYSIZE(hubServer)   },
                { ICON_FA_BOX_OPEN, "Garage",   hubGarage,   IM_ARRAYSIZE(hubGarage)   },
                { ICON_FA_CROWN,    "Titles",   hubTitles,   IM_ARRAYSIZE(hubTitles)   },
                { ICON_FA_EYE,      "Visuals",  hubVisuals,  IM_ARRAYSIZE(hubVisuals)  },
                { ICON_FA_PALETTE,  "Textures", hubTextures, IM_ARRAYSIZE(hubTextures) },
                { ICON_FA_CAMERA,   "Camera",   hubCamera,   IM_ARRAYSIZE(hubCamera)   },
                { ICON_FA_BULLSEYE, "Training", hubTraining, IM_ARRAYSIZE(hubTraining) },
                { ICON_FA_ID_BADGE, "Account",  hubAccount,  IM_ARRAYSIZE(hubAccount)  },
                { ICON_FA_TOOLS,    "Tools",    hubTools,    IM_ARRAYSIZE(hubTools)    },
                { ICON_FA_COG,      "Settings", hubSettings, IM_ARRAYSIZE(hubSettings) },
            };

            static int s_menuHubPage = 0;
            static int s_menuHubTab = 0;
            static int s_titleViewMode = 0;
            static bool s_menuHubInitialized = false;

            auto HubTargetMatchesCurrent = [&](const MenuHubTarget& target) -> bool {
                if (target.tab < 0 || target.tab >= 26)
                    return false;
                return gui.m_tab == target.tab &&
                       gui.m_active_subtab[target.tab] == target.sub &&
                       (target.tab != 7 || target.sub != 1 ||
                        s_titleViewMode == target.titleMode);
            };

            auto ApplyHubTarget = [&](int pageIndex, int targetIndex) {
                pageIndex = std::clamp(pageIndex, 0, (int)IM_ARRAYSIZE(hubPages) - 1);
                targetIndex = std::clamp(targetIndex, 0, hubPages[pageIndex].count - 1);

                const MenuHubTarget& target = hubPages[pageIndex].targets[targetIndex];
                s_menuHubPage = pageIndex;
                s_menuHubTab = targetIndex;
                if (target.tab == 7 && target.sub == 1)
                    s_titleViewMode = target.titleMode;

                gui.m_tab = target.tab;
                gui.m_active_subtab[target.tab] = target.sub;
                gui.m_anim = 0.f;
                GameEventHookModule::LastSelectedTab = target.tab;
            };

                                                                                    
                                                                                   
                                                                                   
                                                
            if (!s_menuHubInitialized)
            {
                bool found = false;
                for (int p = 0; p < (int)IM_ARRAYSIZE(hubPages) && !found; ++p) {
                    for (int t = 0; t < hubPages[p].count; ++t) {
                        const auto& target = hubPages[p].targets[t];
                        if (gui.m_tab == target.tab &&
                            gui.m_active_subtab[target.tab] == target.sub) {
                            s_menuHubPage = p;
                            s_menuHubTab = t;
                            s_titleViewMode = target.titleMode;
                            found = true;
                            break;
                        }
                    }
                }
                s_menuHubInitialized = true;
            }
            else if (!HubTargetMatchesCurrent(
                         hubPages[s_menuHubPage].targets[s_menuHubTab]))
            {
                bool found = false;
                for (int p = 0; p < (int)IM_ARRAYSIZE(hubPages) && !found; ++p) {
                    for (int t = 0; t < hubPages[p].count; ++t) {
                        const auto& target = hubPages[p].targets[t];
                        if (gui.m_tab == target.tab &&
                            gui.m_active_subtab[target.tab] == target.sub) {
                            s_menuHubPage = p;
                            s_menuHubTab = t;
                            s_titleViewMode = target.titleMode;
                            found = true;
                            break;
                        }
                    }
                }
            }

            ImGui::SetCursorPos(ImVec2(10, 70));
            ImGui::BeginChild("##tabs", ImVec2(150, size.y - 120));

            gui.group_title("Pages");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, 3.0f));
            for (int p = 0; p < (int)IM_ARRAYSIZE(hubPages); ++p)
            {
                const bool active = s_menuHubPage == p;
                if (gui.tab(hubPages[p].icon, hubPages[p].label, active) && !active)
                    ApplyHubTarget(p, 0);
            }
            ImGui::PopStyleVar();

            ImGui::EndChild();

                                                                             
                                                                             
            ImGui::SetCursorPos(ImVec2(190, 20));
            if (ImGui::Button(ICON_FA_SAVE " Save", ImVec2(100, 25)))
            {
                GameEventHookModule::SaveConfig();
                KingFeatures::SaveSettings();
                CustomTextureStudioModule::SaveConfig();
                Notify::Toast("KingMod", "Settings saved.", Notify::Style::Success, 2.0f);
            }

                                                                              
                                                                                
                                                                               
            const MenuHubPage& activeHubPage = hubPages[s_menuHubPage];
            const float subtabW = (std::max)(360.0f, size.x - 390.0f);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(7.0f, 0.0f));
            ImGui::SetCursorPos(ImVec2(300, 17));
            ImGui::BeginChild("##subtabs", ImVec2(subtabW, 32), false, ImGuiWindowFlags_HorizontalScrollbar);

            ImGui::GetWindowDrawList()->AddRectFilled(
                ImGui::GetWindowPos(),
                ImGui::GetWindowPos() + ImGui::GetWindowSize(),
                gui.button.to_im_color(), 4);
            ImGui::GetWindowDrawList()->AddRect(
                ImGui::GetWindowPos(),
                ImGui::GetWindowPos() + ImGui::GetWindowSize(),
                gui.border.to_im_color(), 4);

            for (int i = 0; i < activeHubPage.count; ++i)
            {
                const bool selected = s_menuHubTab == i;
                if (gui.subtab(
                        activeHubPage.targets[i].label,
                        selected,
                        activeHubPage.count,
                        i == 0
                            ? ImDrawFlags_RoundCornersLeft
                            : i == activeHubPage.count - 1
                                ? ImDrawFlags_RoundCornersRight
                                : 0) &&
                    !selected)
                {
                    ApplyHubTarget(s_menuHubPage, i);
                }

                if (i != activeHubPage.count - 1)
                    ImGui::SameLine();
            }

            ImGui::EndChild();
            ImGui::PopStyleVar();

                                                                                 
                                                                     
            {
                const float sx = 300.0f + subtabW + 10.0f;
                RenderMenuSearchBar(sx, 20.0f, size.x - sx - 20.0f);
            }

                           
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, gui.m_anim);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));

            ImGui::SetCursorPos(ImVec2(185, 81 - (5 * gui.m_anim)));
            ImGui::BeginChild("##childs", ImVec2(size.x - 200, size.y - 96));

            bool settingsChanged = false;
            static int selectedItemIndex = -1;

            const float kV32InfoCol = 230.0f;
            auto V32Info = [&](const char* label, const std::string& value) {
                ImGui::AlignTextToFramePadding();
                ImGui::TextDisabled("%s", label);
                ImGui::SameLine(kV32InfoCol);
                ImGui::TextColored(gui.accent_color.to_vec4(), "%s", value.empty() ? "-" : value.c_str());
            };

            auto V32RunBool = [](const char* okText, const char* failText, std::function<bool()> fn) {
                Main.Execute([ok = std::string(okText), fail = std::string(failText), fn = std::move(fn)]() mutable {
                    bool success = false;
                    try { success = fn(); } catch (...) { success = false; }
                    Notify::Toast("KingMod", success ? ok : fail,
                        success ? Notify::Style::Success : Notify::Style::Error, 2.5f);
                });
            };

                                                                                
                                                                   
            if (RenderMenuSearchResults()) {
                                          
            }
                                   
            else if (gui.m_tab == 16) {
                static float s_v32TrainStatsH = 0.f;
                BeginFitSection(s_v32TrainStatsH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_BULLSEYE "  TRAINING LAB");
                    ImGui::Spacing();
                    const auto& st = KingFeatures::Stats;
                    V32Info("Car Speed", std::to_string((int)st.CurrentCarSpeedKph) + " km/h  | max " + std::to_string((int)st.MaxCarSpeedKph));
                    V32Info("Ball Speed", std::to_string((int)st.CurrentBallSpeedKph) + " km/h  | max " + std::to_string((int)st.MaxBallSpeedKph));
                    V32Info("Boost", std::to_string((int)st.BoostPercent) + "%");
                    V32Info("Touches", std::to_string(st.TouchCount));
                    V32Info("Dodges", std::to_string(st.DodgeCount));
                    V32Info("Air Time", std::to_string(st.AirTimeSeconds).substr(0, 5) + " s");
                    V32Info("Kickoff Touch", st.LastKickoffTouchMs > 0.f
                        ? std::to_string((int)st.LastKickoffTouchMs) + " ms  | best " + std::to_string((int)st.BestKickoffTouchMs) + " ms"
                        : std::string("waiting"));
                    V32Info("0 -> 220 km/h", st.LastKickoffTimeTo220Ms > 0.f
                        ? std::to_string((int)st.LastKickoffTimeTo220Ms) + " ms"
                        : std::string("waiting"));
                    if (ImGui::Button(ICON_FA_SAVE "  Export Session Stats", ImVec2(190, 28)))
                        V32RunBool("Session stats saved.", "Could not save session stats.", [] { return KingFeatures::SaveSessionStats(); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_UNDO "  Reset Stats", ImVec2(145, 28)))
                        Main.Execute([] { KingFeatures::ResetSessionStats(); });
                EndFitSection(s_v32TrainStatsH);

                static float s_v32CheckpointH = 0.f;
                BeginFitSection(s_v32CheckpointH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SAVE "  CHECKPOINT");
                    const auto checkpoint = KingFeatures::GetCheckpoint();
                    ImGui::TextDisabled("Current slot: %s", checkpoint.Valid ? "SAVED" : "EMPTY");
                    if (ImGui::Button(ICON_FA_SAVE "  Save", ImVec2(145, 31)))
                        V32RunBool("Checkpoint saved.", "No car/ball available.", [] { return KingFeatures::SaveCheckpoint(); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_UNDO "  Restore", ImVec2(145, 31)))
                        V32RunBool("Checkpoint restored.", "No checkpoint available.", [] { return KingFeatures::RestoreCheckpoint(); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_TRASH "  Clear", ImVec2(120, 31)))
                        Main.Execute([] { KingFeatures::ClearCheckpoint(); });
                    ImGui::Checkbox("Auto-save first checkpoint", &KingFeatures::Config.AutoCheckpoint);
                EndFitSection(s_v32CheckpointH);

                static float s_v32ShotsH = 0.f;
                BeginFitSection(s_v32ShotsH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_ROCKET "  SHOT LAB");
                    ImGui::SliderFloat("Launch Speed##v32", &KingFeatures::Config.TrainingBallLaunchSpeed, 400.f, 4000.f, "%.0f uu/s");
                    ImGui::SliderFloat("Target Height##v32", &KingFeatures::Config.TrainingBallLaunchHeight, 0.f, 2200.f, "%.0f");
                    const float shotSpeed = KingFeatures::Config.TrainingBallLaunchSpeed;
                    const float shotHeight = KingFeatures::Config.TrainingBallLaunchHeight;
                    if (ImGui::Button(ICON_FA_BULLSEYE "  Blue Goal", ImVec2(125, 30))) Main.Execute([shotSpeed, shotHeight] { KingFeatures::LaunchBallTowardGoal(0, shotSpeed, shotHeight); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_BULLSEYE "  Orange Goal", ImVec2(125, 30))) Main.Execute([shotSpeed, shotHeight] { KingFeatures::LaunchBallTowardGoal(1, shotSpeed, shotHeight); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_CAR "  At My Car", ImVec2(120, 30))) Main.Execute([shotSpeed, shotHeight] { KingFeatures::LaunchBallAtLocalCar(shotSpeed, shotHeight); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_RANDOM "  Random", ImVec2(105, 30))) Main.Execute([] { KingFeatures::RandomizeBall(); });
                    if (ImGui::Button(ICON_FA_CROSSHAIRS "  Center Ball", ImVec2(160, 30))) Main.Execute([] { KingFeatures::CenterBall(true); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_BOLT "  Full Boost", ImVec2(145, 30))) Main.Execute([] { KingFeatures::GiveLocalFullBoost(); });
                EndFitSection(s_v32ShotsH);

                static float s_v32PresetH = 0.f;
                BeginFitSection(s_v32PresetH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_MAGIC "  PRACTICE PRESETS");
                    if (ImGui::Button(ICON_FA_FORWARD "  Ground Pass", ImVec2(145, 30))) {
                        KingFeatures::Config.TrainingBallLaunchSpeed = 1200.f;
                        KingFeatures::Config.TrainingBallLaunchHeight = 120.f;
                        Main.Execute([] { KingFeatures::LaunchBallAtLocalCar(1200.f, 120.f); });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_ROCKET "  Fast Shot", ImVec2(145, 30))) {
                        KingFeatures::Config.TrainingBallLaunchSpeed = 3000.f;
                        KingFeatures::Config.TrainingBallLaunchHeight = 350.f;
                        Main.Execute([] { KingFeatures::LaunchBallTowardGoal(1, 3000.f, 350.f); });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_ARROW_UP "  Aerial Feed", ImVec2(145, 30))) {
                        KingFeatures::Config.TrainingBallLaunchSpeed = 1850.f;
                        KingFeatures::Config.TrainingBallLaunchHeight = 1450.f;
                        Main.Execute([] { KingFeatures::LaunchBallAtLocalCar(1850.f, 1450.f); });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_MAGIC "  Chaos Shot", ImVec2(145, 30))) Main.Execute([] { KingFeatures::RandomizeBall(); });
                EndFitSection(s_v32PresetH);

                static float s_v32AssistsH = 0.f;
                BeginFitSection(s_v32AssistsH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SLIDERS_H "  TRAINING ASSISTS");
                    ImGui::Checkbox("Unlimited Boost", &KingFeatures::Config.UnlimitedBoost);
                    ImGui::Checkbox("Unlimited Dodge / Flip Window", &KingFeatures::Config.UnlimitedDodge);
                    ImGui::Checkbox("Speedometer Overlay", &KingFeatures::Config.Speedometer);
                    ImGui::Checkbox("Ball Telemetry", &KingFeatures::Config.BallTelemetry);
                    ImGui::Checkbox("Boost / Air-Time Telemetry", &KingFeatures::Config.BoostTelemetry);
                    ImGui::Checkbox("Shot Speed History", &KingFeatures::Config.ShotHistory);
                    ImGui::Checkbox("Ball Prediction", &GameEventHookModule::BallPredictionEnabled);
                EndFitSection(s_v32AssistsH);
            }

                                                                 
            else if (gui.m_tab == 17) {
                const bool hostReady = KingFeatures::IsHostSandboxAvailable();
                if (gui.m_active_subtab[17] == 0) {
                    static float s_v32HostStateH = 0.f;
                    BeginFitSection(s_v32HostStateH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SERVER "  HOST CONTROL");
                        ImGui::TextWrapped("LAN/private listen-server controls. Host writes are disabled in public/ranked matches and paused during the join settle guard.");
                        ImGui::Spacing();
                        V32Info("State", hostReady ? "READY - LAN / PRIVATE HOST" : (HostSync::IsJoinGuardActive() ? "JOIN GUARD ACTIVE" : "NOT AVAILABLE"));
                        V32Info("Connected", std::to_string(HostSync::GetConnectedPlayerCount()) + " player(s)");
                        V32Info("Host Sync", std::string(HostSync::GetStatusText()));
                    EndFitSection(s_v32HostStateH);

                    static float s_v32ScoreH = 0.f;
                    BeginFitSection(s_v32ScoreH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_TROPHY "  SCORE / CLOCK / ROUND");
                        ImGui::InputInt("Blue Score##v32", &KingFeatures::Config.HostScoreBlue);
                        ImGui::InputInt("Orange Score##v32", &KingFeatures::Config.HostScoreOrange);
                        ImGui::InputInt("Seconds##v32", &KingFeatures::Config.HostSeconds);
                        ImGui::Checkbox("Overtime##v32", &KingFeatures::Config.HostOvertime);
                        if (ImGui::Button(ICON_FA_CHECK "  Apply", ImVec2(120, 30))) V32RunBool("Score/time applied.", "Host control unavailable.", [] { return KingFeatures::HostApplyScoreAndTime(false); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_REDO "  Apply + Restart", ImVec2(150, 30))) V32RunBool("Score/time applied.", "Host control unavailable.", [] { return KingFeatures::HostApplyScoreAndTime(true); });
                        ImGui::SameLine();
                        if (ImGui::Button(KingFeatures::Config.HostPaused ? ICON_FA_PLAY "  Resume" : ICON_FA_PAUSE "  Pause", ImVec2(100, 30))) {
                            const bool pause = !KingFeatures::Config.HostPaused;
                            Main.Execute([pause] { KingFeatures::HostPause(pause); });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_CLOCK "  Overtime", ImVec2(105, 30))) V32RunBool("Overtime forced.", "Overtime unavailable.", [] { return KingFeatures::HostForceOvertime(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_REDO "  New Round", ImVec2(110, 30))) V32RunBool("New round started.", "Round control unavailable.", [] { return KingFeatures::HostStartNewRound(); });
                    EndFitSection(s_v32ScoreH);

                    static float s_v32PhysicsH = 0.f;
                    BeginFitSection(s_v32PhysicsH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_FUTBOL "  WORLD / BALL SANDBOX");
                        ImGui::SliderFloat("Game Speed##v32host", &KingFeatures::Config.HostGameSpeed, 0.1f, 2.5f, "%.2fx");
                        ImGui::SliderFloat("Ball Scale##v32host", &KingFeatures::Config.BallScale, 0.25f, 4.0f, "%.2fx");
                        ImGui::SliderFloat("Ball Gravity##v32host", &KingFeatures::Config.BallGravityScale, 0.0f, 5.0f, "%.2fx");
                        ImGui::SliderFloat("Ball Max Speed##v32host", &KingFeatures::Config.BallMaxSpeedScale, 0.25f, 5.0f, "%.2fx");
                        ImGui::SliderFloat("Ball Bounce##v32host", &KingFeatures::Config.BallBounceScale, 0.0f, 5.0f, "%.2fx");
                        ImGui::Checkbox("Ball Pinch Strength##v32host", &KingFeatures::Config.BallPinchStrengthEnabled);
                        ImGui::SetNextItemWidth(280.0f);
                        ImGui::SliderFloat("Pinch Strength##v32host", &KingFeatures::Config.BallPinchStrength, 0.25f, 5.0f, "%.2fx");
                        ImGui::TextDisabled("Authoritative only: Freeplay/offline or the LAN listen-server host. 1.00x is stock.");
                        if (ImGui::Button(ICON_FA_CHECK "  Apply Pinch Strength", ImVec2(165, 28)))
                            V32RunBool("Pinch strength applied.", "Pinch strength unavailable.", [] { return KingFeatures::ApplyBallPinchStrength(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TACHOMETER_ALT "  Apply Game Speed", ImVec2(160, 30))) {
                            const float scale = KingFeatures::Config.HostGameSpeed;
                            V32RunBool("Game speed applied.", "Game speed unavailable.", [scale] { return KingFeatures::HostSetGameSpeed(scale); });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_FUTBOL "  Apply Ball Physics", ImVec2(165, 30))) V32RunBool("Ball physics applied.", "Ball physics unavailable.", [] { return KingFeatures::HostApplyBallPhysics(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_UNDO "  Reset Ball", ImVec2(115, 30))) V32RunBool("Ball reset.", "Ball reset unavailable.", [] { return KingFeatures::HostResetBall(); });
                        ImGui::SameLine();
                        ImGui::Checkbox("Goals Enabled##v32", &KingFeatures::Config.HostGoalsEnabled);
                        ImGui::SameLine();
                        if (ImGui::Button("Apply Goals##v32", ImVec2(120, 26))) {
                            const bool enabled = KingFeatures::Config.HostGoalsEnabled;
                            V32RunBool("Goal state applied.", "Goal control unavailable.", [enabled] { return KingFeatures::HostSetGoalsEnabled(enabled); });
                        }
                        ImGui::SliderInt("Max Team Size##v32", &KingFeatures::Config.HostTeamSize, 1, 8);
                        if (ImGui::Button(ICON_FA_USERS "  Apply Team Size", ImVec2(150, 28))) {
                            const int teamSize = KingFeatures::Config.HostTeamSize;
                            V32RunBool("Team size applied.", "Team size unavailable.", [teamSize] { return KingFeatures::HostSetTeamSize(teamSize); });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_UNDO "  Reset Game", ImVec2(150, 28))) V32RunBool("Game reset.", "Reset unavailable.", [] { return KingFeatures::HostResetGame(); });
                        ImGui::Separator();
                        ImGui::TextDisabled("Physics presets");
                        if (ImGui::Button(ICON_FA_CHECK "  Classic", ImVec2(110, 28))) {
                            KingFeatures::Config.HostGameSpeed = 1.0f; KingFeatures::Config.BallScale = 1.0f;
                            KingFeatures::Config.BallGravityScale = 1.0f; KingFeatures::Config.BallMaxSpeedScale = 1.0f; KingFeatures::Config.BallBounceScale = 1.0f;
                            Main.Execute([] { KingFeatures::HostSetGameSpeed(1.0f); KingFeatures::HostApplyBallPhysics(); });
                        }
                        ImGui::SameLine(); if (ImGui::Button(ICON_FA_MOON "  Moon Ball", ImVec2(110, 28))) {
                            KingFeatures::Config.BallScale = 1.0f; KingFeatures::Config.BallGravityScale = 0.35f; KingFeatures::Config.BallMaxSpeedScale = 1.15f; KingFeatures::Config.BallBounceScale = 1.15f;
                            Main.Execute([] { KingFeatures::HostApplyBallPhysics(); });
                        }
                        ImGui::SameLine(); if (ImGui::Button(ICON_FA_BULLSEYE "  Pinball", ImVec2(110, 28))) {
                            KingFeatures::Config.BallScale = 0.75f; KingFeatures::Config.BallGravityScale = 0.8f; KingFeatures::Config.BallMaxSpeedScale = 2.5f; KingFeatures::Config.BallBounceScale = 2.0f;
                            Main.Execute([] { KingFeatures::HostApplyBallPhysics(); });
                        }
                        ImGui::SameLine(); if (ImGui::Button(ICON_FA_EXPAND "  Giant Ball", ImVec2(110, 28))) {
                            KingFeatures::Config.BallScale = 2.0f; KingFeatures::Config.BallGravityScale = 1.0f; KingFeatures::Config.BallMaxSpeedScale = 1.0f; KingFeatures::Config.BallBounceScale = 0.9f;
                            Main.Execute([] { KingFeatures::HostApplyBallPhysics(); });
                        }
                    EndFitSection(s_v32PhysicsH);

                    static float s_v32BotsH = 0.f;
                    BeginFitSection(s_v32BotsH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_ROBOT "  BOT MANAGER");
                        static char botName[48] = "KingBot";
                        static int botTeam = 0;
                        static int botSkill = 4;
                        ImGui::InputText("Bot Name##v32", botName, sizeof(botName));
                        ImGui::Combo("Team##v32bot", &botTeam, "Blue\0Orange\0Auto\0");
                        ImGui::SliderInt("Skill##v32bot", &botSkill, 0, 4);
                        if (ImGui::Button(ICON_FA_PLUS "  Spawn Bot", ImVec2(145, 30))) {
                            const std::string name(botName);
                            const int team = botTeam == 2 ? -1 : botTeam;
                            const int skill = botSkill;
                            Main.Execute([name, team, skill] {
                                const bool ok = HostSync::SpawnBot(name, team, skill);
                                Notify::Toast("KingMod", ok ? "Bot spawned." : "Could not spawn bot.", ok ? Notify::Style::Success : Notify::Style::Error, 2.f);
                            });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TRASH "  Remove All", ImVec2(145, 30))) {
                            Main.Execute([] {
                                const int count = HostSync::RemoveAllBots();
                                Notify::Toast("KingMod", "Removed " + std::to_string(count) + " bot(s).", Notify::Style::Info, 2.f);
                            });
                        }
                        ImGui::SameLine();
                        ImGui::TextDisabled("Active: %d", HostSync::GetActiveBotCount());
                    EndFitSection(s_v32BotsH);
                }
                else {
                    static float s_v32PlayersH = 0.f;
                    BeginFitSection(s_v32PlayersH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_USERS_COG "  PLAYER MANAGER");
                        ImGui::TextDisabled("Actions are LAN/private host-only and paused while a new player is joining.");
                        ImGui::SliderFloat("Car Scale##v32players", &KingFeatures::Config.HostCarScale, 0.25f, 3.0f, "%.2fx");
                        const auto players = KingFeatures::GetPlayerSnapshots();
                        if (players.empty()) {
                            ImGui::TextDisabled("No active player snapshots.");
                        }
                        const int count = (std::min)(static_cast<int>(players.size()), 24);
                        for (int i = 0; i < count; ++i) {
                            const auto snap = players[i];
                            const std::string name = snap.Name;
                            ImGui::PushID(42000 + i);
                            ImGui::Separator();
                            ImGui::Text("%s%s", name.empty() ? "Player" : name.c_str(), snap.Bot ? " [BOT]" : "");
                            ImGui::SameLine();
                            ImGui::TextDisabled(snap.Spectator ? "SPEC" : snap.TeamIndex == 0 ? "BLUE" : snap.TeamIndex == 1 ? "ORANGE" : "NONE");
                            if (ImGui::SmallButton("Blue")) Main.Execute([name] { KingFeatures::HostMovePlayerByName(name, 0); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Orange")) Main.Execute([name] { KingFeatures::HostMovePlayerByName(name, 1); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Spectate")) Main.Execute([name] { KingFeatures::HostSpectatePlayerByName(name); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Respawn")) Main.Execute([name] { KingFeatures::HostRespawnPlayerByName(name); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Freeze")) Main.Execute([name] { KingFeatures::HostFreezePlayerByName(name, true); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Unfreeze")) Main.Execute([name] { KingFeatures::HostFreezePlayerByName(name, false); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Scale")) {
                                const float scale = KingFeatures::Config.HostCarScale;
                                Main.Execute([name, scale] { KingFeatures::HostSetCarScaleByName(name, scale); });
                            }
                            ImGui::SameLine(); if (ImGui::SmallButton("Follow")) Main.Execute([name] { KingFeatures::FollowPlayerByName(name); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Unfollow")) Main.Execute([] { KingFeatures::UnfollowPlayer(); });
                            ImGui::SameLine(); if (ImGui::SmallButton("Kick")) Main.Execute([name] { KingFeatures::HostKickPlayerByName(name); });
                            ImGui::PopID();
                        }
                    EndFitSection(s_v32PlayersH);
                }
            }

                                               
            else if (gui.m_tab == 18) {
                static float s_v32PhotoH = 0.f;
                BeginFitSection(s_v32PhotoH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_CAMERA "  CINEMATIC / PHOTO MODE");
                    const bool photo = KingFeatures::IsPhotoMode();
                    if (ImGui::Button(photo ? ICON_FA_PLAY "  Exit Photo Mode" : ICON_FA_CAMERA "  Enter Photo Mode", ImVec2(-1, 36)))
                        Main.Execute([photo] { KingFeatures::SetPhotoMode(!photo); });
                    ImGui::Checkbox("Hide Rocket League HUD in Photo Mode", &KingFeatures::Config.HideGameHudInPhotoMode);
                    ImGui::Checkbox("Cinematic Bars", &KingFeatures::Config.CinematicBars);
                    ImGui::SliderFloat("Bar Size##v32cine", &KingFeatures::Config.CinematicBarSize, 0.02f, 0.25f, "%.2f");
                    if (ImGui::Button(ICON_FA_DESKTOP "  Toggle Game HUD", ImVec2(170, 30))) Main.Execute([] { KingFeatures::ToggleGameHud(); });
                EndFitSection(s_v32PhotoH);

                static float s_v32TimeH = 0.f;
                BeginFitSection(s_v32TimeH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_CLOCK "  TIME CONTROL");
                    ImGui::Checkbox("Slow Motion", &KingFeatures::Config.SlowMotion);
                    ImGui::SliderFloat("Slow Scale##v32", &KingFeatures::Config.SlowMotionScale, 0.05f, 1.0f, "%.2fx");
                    if (ImGui::Button(ICON_FA_TACHOMETER_ALT "  Normal Speed", ImVec2(145, 30))) Main.Execute([] { KingFeatures::SetWorldTimeScale(1.0f); });
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_CLOCK "  Apply Slow", ImVec2(145, 30))) {
                        const float scale = KingFeatures::Config.SlowMotionScale;
                        Main.Execute([scale] { KingFeatures::SetWorldTimeScale(scale); });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("0.25x", ImVec2(90, 30))) Main.Execute([] { KingFeatures::SetWorldTimeScale(0.25f); });
                    ImGui::SameLine();
                    if (ImGui::Button("0.50x", ImVec2(90, 30))) Main.Execute([] { KingFeatures::SetWorldTimeScale(0.50f); });
                EndFitSection(s_v32TimeH);

                static float s_v32CameraPathH = 0.f;
                BeginFitSection(s_v32CameraPathH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_ROUTE "  FREECAM / CAMERA PATH");
                    const auto keys = KingFeatures::GetCameraKeyframes();
                    V32Info("Keyframes", std::to_string(keys.size()));
                    V32Info("Playback", KingFeatures::IsCameraPathPlaying() ? "PLAYING" : "idle");
                    if (ImGui::Button(ICON_FA_VIDEO "  Toggle Freecam", ImVec2(160, 30))) Main.Execute([] { KingFeatures::ToggleFreeCam(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_PLUS "  Add Keyframe", ImVec2(160, 30))) Main.Execute([] { KingFeatures::CaptureCameraKeyframe(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_TRASH "  Clear", ImVec2(110, 30))) Main.Execute([] { KingFeatures::ClearCameraPath(); });
                    static float pathSeconds = 10.f;
                    ImGui::SliderFloat("Path Duration##v32", &pathSeconds, 1.f, 60.f, "%.1fs");
                    if (ImGui::Button(ICON_FA_PLAY "  Play Path", ImVec2(145, 30))) {
                        const float seconds = pathSeconds;
                        Main.Execute([seconds] { KingFeatures::StartCameraPathPlayback(seconds); });
                    }
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_STOP "  Stop", ImVec2(105, 30))) Main.Execute([] { KingFeatures::StopCameraPathPlayback(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_SAVE "  Save Path", ImVec2(130, 30)))
                        V32RunBool("Camera path saved.", "No camera path to save.", [] { return KingFeatures::SaveCameraPathToDisk(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Load Path", ImVec2(130, 30)))
                        V32RunBool("Camera path loaded.", "No saved camera path found.", [] { return KingFeatures::LoadCameraPathFromDisk(); });
                EndFitSection(s_v32CameraPathH);

                static float s_v32CameraTargetH = 0.f;
                BeginFitSection(s_v32CameraTargetH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_EYE "  FOLLOW PLAYER");
                    const auto players = KingFeatures::GetPlayerSnapshots();
                    if (players.empty()) ImGui::TextDisabled("Enter a match to list camera targets.");
                    for (int i = 0; i < (std::min)((int)players.size(), 16); ++i) {
                        const std::string name = players[i].Name;
                        ImGui::PushID(43000 + i);
                        if (ImGui::Button((std::string(ICON_FA_EYE "  ") + (name.empty() ? "Player" : name)).c_str(), ImVec2(-1, 28)))
                            Main.Execute([name] { KingFeatures::FollowPlayerByName(name); });
                        ImGui::PopID();
                    }
                EndFitSection(s_v32CameraTargetH);
            }

                                                           
            else if (gui.m_tab == 19) {
                static float s_v32SyncH = 0.f;
                BeginFitSection(s_v32SyncH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_NETWORK_WIRED "  KING SYNC");
                    bool syncEnabled = KingSync::IsEnabled();
                    if (ImGui::Checkbox("Enable LAN peer sync", &syncEnabled)) KingSync::SetEnabled(syncEnabled);
                    ImGui::Checkbox("Broadcast Presence", &KingSync::Config.BroadcastPresence);
                    ImGui::InputInt("UDP Port##v32sync", &KingSync::Config.Port);
                    ImGui::InputText("Direct Peer IP (Radmin/VPN optional)", KingSync::Config.DirectPeer, sizeof(KingSync::Config.DirectPeer));
                    ImGui::InputText("Custom Tag", KingSync::Config.CustomTag, sizeof(KingSync::Config.CustomTag));
                    ImGui::ColorEdit4("Peer Accent", KingSync::Config.Accent, ImGuiColorEditFlags_NoInputs);
                    V32Info("Status", KingSync::GetStatus());
                    ImGui::TextWrapped("Sync sends fixed KingMod presence/status metadata only. It does not execute commands received from another peer.");
                EndFitSection(s_v32SyncH);

                static float s_v32PeersH = 0.f;
                BeginFitSection(s_v32PeersH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_USERS "  DISCOVERED PEERS");
                    const auto peers = KingSync::GetPeers();
                    if (peers.empty()) ImGui::TextDisabled("No KingMod peers discovered yet.");
                    for (int i = 0; i < (std::min)((int)peers.size(), 32); ++i) {
                        const auto peer = peers[i];
                        ImGui::PushID(44000 + i);
                        ImGui::ColorButton("##peer", peer.Accent, ImGuiColorEditFlags_NoTooltip, ImVec2(13, 13));
                        ImGui::SameLine(); ImGui::Text("%s", peer.PlayerName.c_str());
                        ImGui::SameLine(); ImGui::TextDisabled("[%s] %s", peer.CustomTag.c_str(), peer.Address.c_str());
                        if (peer.IsHost) { ImGui::SameLine(); ImGui::TextColored(ImVec4(.3f,.9f,.4f,1.f), "HOST"); }
                        if (peer.ShieldEnabled) { ImGui::SameLine(); ImGui::TextDisabled("SHIELD"); }
                        if (peer.PhotoMode) { ImGui::SameLine(); ImGui::TextDisabled("PHOTO"); }
                        ImGui::PopID();
                    }
                EndFitSection(s_v32PeersH);
            }

                                                  
            else if (gui.m_tab == 21) {
                static float s_v32ProfilesH = 0.f;
                BeginFitSection(s_v32ProfilesH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_LAYER_GROUP "  FEATURE PROFILES");
                    ImGui::TextWrapped("Profiles change related KingMod options together. They do not navigate to another page.");
                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_SHIELD_ALT "  Competitive", ImVec2(-1, 36))) KingFeatures::ApplyProfile(KingFeatures::Profile::Competitive);
                    if (ImGui::Button(ICON_FA_BULLSEYE "  Training", ImVec2(-1, 36))) KingFeatures::ApplyProfile(KingFeatures::Profile::Training);
                    if (ImGui::Button(ICON_FA_SERVER "  LAN Host", ImVec2(-1, 36))) KingFeatures::ApplyProfile(KingFeatures::Profile::LANHost);
                    if (ImGui::Button(ICON_FA_CAMERA "  Cinematic", ImVec2(-1, 36))) KingFeatures::ApplyProfile(KingFeatures::Profile::Cinematic);
                    if (ImGui::Button(ICON_FA_BUG "  Debug", ImVec2(-1, 36))) KingFeatures::ApplyProfile(KingFeatures::Profile::Debug);
                EndFitSection(s_v32ProfilesH);

                static float s_v32ProfileDetailH = 0.f;
                BeginFitSection(s_v32ProfileDetailH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SLIDERS_H "  PROFILE COMPONENTS");
                    ImGui::Checkbox("Speedometer", &KingFeatures::Config.Speedometer);
                    ImGui::Checkbox("Ball Telemetry", &KingFeatures::Config.BallTelemetry);
                    ImGui::Checkbox("Boost Telemetry", &KingFeatures::Config.BoostTelemetry);
                    ImGui::Checkbox("Shot History", &KingFeatures::Config.ShotHistory);
                    ImGui::Checkbox("Session Panel", &KingFeatures::Config.SessionPanel);
                    ImGui::Checkbox("Debug Panel", &KingFeatures::Config.DebugPanel);
                    ImGui::Checkbox("Cinematic Bars", &KingFeatures::Config.CinematicBars);
                    ImGui::Checkbox("Unlimited Boost", &KingFeatures::Config.UnlimitedBoost);
                    ImGui::Checkbox("Unlimited Dodge", &KingFeatures::Config.UnlimitedDodge);
                EndFitSection(s_v32ProfileDetailH);
            }

                                                  
            else if (gui.m_tab == 22) {
                static float s_v32ShieldH = 0.f;
                BeginFitSection(s_v32ShieldH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SHIELD_ALT "  MATCHMAKING SHIELD");
                    bool shieldEnabled = MatchmakingShield::IsEnabled();
                    if (ImGui::Checkbox("Enable Matchmaking Shield", &shieldEnabled)) MatchmakingShield::SetEnabled(shieldEnabled);
                    V32Info("State", MatchmakingShield::IsWaitingForJoin() ? "MATCH HELD" : shieldEnabled ? "ARMED" : "OFF");
                    V32Info("Held For", std::to_string(MatchmakingShield::GetPendingSeconds()).substr(0, 4) + " s");
                    static bool autoAccept = MatchmakingShield::IsAutoAcceptEnabled();
                    static float autoDelay = MatchmakingShield::GetAutoAcceptDelay();
                    static float holdTimeout = MatchmakingShield::GetHoldTimeout();
                    if (ImGui::Checkbox("Auto-accept held match", &autoAccept)) MatchmakingShield::SetAutoAccept(autoAccept, autoDelay);
                    if (ImGui::SliderFloat("Auto Accept Delay##v32shield", &autoDelay, 0.25f, 15.f, "%.1fs")) MatchmakingShield::SetAutoAccept(autoAccept, autoDelay);
                    if (ImGui::SliderFloat("Hold Timeout##v32shield", &holdTimeout, 5.f, 120.f, "%.0fs")) MatchmakingShield::SetHoldTimeout(holdTimeout);
                    ImGui::TextDisabled("Manual accept key: F8 by default.");
                    if (MatchmakingShield::IsWaitingForJoin()) {
                        if (ImGui::Button(ICON_FA_SIGN_IN_ALT "  Accept Held Match", ImVec2(210, 34))) Main.Execute([] { MatchmakingShield::AcceptPendingJoin(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TIMES "  Cancel", ImVec2(130, 34))) Main.Execute([] { MatchmakingShield::CancelPendingJoin(); });
                    }
                EndFitSection(s_v32ShieldH);
            }

                                                   
            else if (gui.m_tab == 24) {
                static float s_v32AutomationH = 0.f;
                BeginFitSection(s_v32AutomationH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_MAGIC "  AUTOMATION");
                    bool automationChanged = false;
                    automationChanged |= ImGui::Checkbox(ICON_FA_FILM "  Skip Goal Replays", &GameEventHookModule::SkipReplays);
                    automationChanged |= ImGui::Checkbox(ICON_FA_LIST "  Auto Queue After Match", &GameEventHookModule::AutoQueueEnabled);
                    if (GameEventHookModule::AutoQueueEnabled)
                        automationChanged |= ImGui::SliderInt("Queue Delay##v32auto", &GameEventHookModule::AutoQueueDelaySeconds, 0, 30, "%d sec");
                    automationChanged |= ImGui::Checkbox(ICON_FA_SIGN_OUT_ALT "  Auto Leave After Match", &GameEventHookModule::AutoLeaveEnabled);
                    if (GameEventHookModule::AutoLeaveEnabled)
                        automationChanged |= ImGui::SliderInt("Leave Delay##v32auto", &GameEventHookModule::AutoLeaveDelaySeconds, 0, 30, "%d sec");
                    if (automationChanged) GameEventHookModule::SaveConfig();
                    ImGui::Separator();
                    ImGui::Checkbox("Auto-save Training Checkpoint", &KingFeatures::Config.AutoCheckpoint);
                    ImGui::Checkbox("Slow Motion While Enabled", &KingFeatures::Config.SlowMotion);
                    ImGui::Checkbox("Unlimited Boost", &KingFeatures::Config.UnlimitedBoost);
                    ImGui::Checkbox("Unlimited Dodge", &KingFeatures::Config.UnlimitedDodge);
                EndFitSection(s_v32AutomationH);

                static float s_v32QuickH = 0.f;
                BeginFitSection(s_v32QuickH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_BOLT "  QUICK ACTIONS");
                    if (ImGui::Button(ICON_FA_BULLSEYE "  Center Ball", ImVec2(135, 30))) Main.Execute([] { KingFeatures::CenterBall(true); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_BOLT "  Full Boost", ImVec2(125, 30))) Main.Execute([] { KingFeatures::GiveLocalFullBoost(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_SAVE "  Save Checkpoint", ImVec2(150, 30))) Main.Execute([] { KingFeatures::SaveCheckpoint(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_UNDO "  Restore Checkpoint", ImVec2(160, 30))) Main.Execute([] { KingFeatures::RestoreCheckpoint(); });
                    if (ImGui::Button(ICON_FA_SYNC "  Refresh Host State", ImVec2(160, 30))) Main.Execute([] { HostSync::SyncAllNow(); });
                    if (MatchmakingShield::IsWaitingForJoin()) {
                        ImGui::SameLine(); if (ImGui::Button(ICON_FA_CHECK "  Accept Held Match", ImVec2(160, 30))) Main.Execute([] { MatchmakingShield::AcceptPendingJoin(); });
                    }
                EndFitSection(s_v32QuickH);
            }

                                                     
            else if (gui.m_tab == 25) {
                static float s_v32SessionH = 0.f;
                BeginFitSection(s_v32SessionH);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_CHART_LINE "  SESSION HUD / ANALYTICS");
                    const auto& st = KingFeatures::Stats;
                    V32Info("Session", std::to_string((int)st.SessionSeconds) + " sec");
                    V32Info("Car", std::to_string((int)st.CurrentCarSpeedKph) + " km/h | max " + std::to_string((int)st.MaxCarSpeedKph));
                    V32Info("Ball", std::to_string((int)st.CurrentBallSpeedKph) + " km/h | max " + std::to_string((int)st.MaxBallSpeedKph));
                    V32Info("Boost", std::to_string((int)st.BoostPercent) + "%");
                    V32Info("Touches", std::to_string(st.TouchCount));
                    V32Info("Dodges", std::to_string(st.DodgeCount));
                    V32Info("Air Time", std::to_string(st.AirTimeSeconds).substr(0,5) + " sec");
                    ImGui::Separator();
                    ImGui::Checkbox("Speedometer", &KingFeatures::Config.Speedometer);
                    ImGui::Checkbox("Ball Telemetry", &KingFeatures::Config.BallTelemetry);
                    ImGui::Checkbox("Boost Telemetry", &KingFeatures::Config.BoostTelemetry);
                    ImGui::Checkbox("Shot History", &KingFeatures::Config.ShotHistory);
                    ImGui::Checkbox("Full Session Panel", &KingFeatures::Config.SessionPanel);
                    if (ImGui::Button(ICON_FA_SAVE "  Export Stats", ImVec2(155, 30))) V32RunBool("Session stats saved.", "Could not save stats.", [] { return KingFeatures::SaveSessionStats(); });
                    ImGui::SameLine(); if (ImGui::Button(ICON_FA_UNDO "  Reset Session", ImVec2(155, 30))) Main.Execute([] { KingFeatures::ResetSessionStats(); });
                EndFitSection(s_v32SessionH);
            }

                                  
            else if (gui.m_tab == 0) {
                gui.group_box("Rank Changer", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                RefreshRankPlaylistsForGui(false);

                static const char* ranklistbox_items[8] = {
                    "Bronze", "Silver", "Gold", "Platinum",
                    "Diamond", "Champion", "Grand Champion", "Supersonic Legend"
                };
                static int selected_rankitem = 0;
                static int reward_rankitem = 0;
                static int rankDivision = 1;
                static ImGuiTextFilter rankfilter;
                static ImGuiTextFilter playlistfilter;

                auto applyRankSelection = [&](int rankItem, int division) {
                    RankChanger.seasonrewards = rankItem + 1;
                    RankChanger.customrank = GetBaseTierForRankSelection(rankItem);
                    RankChanger.customrank += std::clamp(division, 1, 3) - 1;
                };

                rankDivision = std::clamp(rankDivision, 1, 3);
                RankChanger.customrankplaylist = std::clamp(RankChanger.customrankplaylist, 1, 4);
                RankChanger.seasonalwins = std::clamp(RankChanger.seasonalwins, 1, 10);

                const float columnWidth = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) * 0.5f;
                const float topRowHeight = 254.0f;

                ImGui::BeginChild("RankSelectionPanel", ImVec2(columnWidth, topRowHeight), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_TROPHY "  RANK SELECTION");
                ImGui::Separator();
                ImGui::TextDisabled("Selected: %s", ranklistbox_items[selected_rankitem]);
                rankfilter.Draw("Search ranks");
                if (ImGui::BeginListBox("##RankList", ImVec2(-1, -1))) {
                    for (int n = 0; n < IM_ARRAYSIZE(ranklistbox_items); ++n) {
                        if (!rankfilter.PassFilter(ranklistbox_items[n]))
                            continue;
                        const bool isSelected = n == selected_rankitem;
                        if (ImGui::Selectable(ranklistbox_items[n], isSelected))
                            selected_rankitem = n;
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("RankSettingsPanel", ImVec2(0, topRowHeight), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_SLIDERS_H "  RANK SETTINGS");
                ImGui::Separator();
                ImGui::InputInt("MMR", &RankChanger.custommmr);
                ImGui::SliderInt("Playlist Division", &RankChanger.customrankplaylist, 1, 4);
                ImGui::SliderInt("Rank Division", &rankDivision, 1, 3);
                ImGui::InputInt("Matches Played", &RankChanger.matchesPlayed);
                ImGui::InputInt("Win Streak", &RankChanger.winStreak);
                ImGui::InputInt("Placements", &RankChanger.seasonalwins);
                ImGui::Spacing();
                const float actionWidth = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) * 0.5f;
                if (ImGui::Button(ICON_FA_TROPHY "  Apply Rank", ImVec2(actionWidth, 0))) {
                    applyRankSelection(selected_rankitem, rankDivision);
                    Main.Execute([]() { RankChanger.ChangeRank(); });
                    Main.Execute([]() { Main.SpawnNotification("Rank", "Rank has been changed", 10); });
                }
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_TROPHY "  Reset Ranks", ImVec2(-1, 0))) {
                    Main.Execute([]() { RankChanger.ResetRank(); });
                    Main.Execute([]() { Main.SpawnNotification("Rank", "Rank has been reset", 10); });
                }
                if (ImGui::Button(ICON_FA_LIST "  Apply To All Playlists", ImVec2(-1, 0))) {
                    applyRankSelection(selected_rankitem, rankDivision);
                    Main.Execute([]() { RankChanger.ChangeRankAllPlaylists(); });
                    Main.Execute([]() { Main.SpawnNotification("Rank", "Applied to all playlists", 10); });
                }
                ImGui::EndChild();

                ImGui::Spacing();

                ImGui::BeginChild("RankPlaylistsPanel", ImVec2(columnWidth, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_LIST "  PLAYLIST");
                ImGui::Separator();
                ImGui::TextDisabled("Selected: %s", RankChanger.selectedplaylisttoedit.empty() ? "None" : RankChanger.selectedplaylisttoedit.c_str());
                if (ImGui::Button(ICON_FA_LIST "  Refresh Playlists", ImVec2(150, 0)))
                    RefreshRankPlaylistsForGui(true);
                ImGui::SameLine();
                ImGui::TextDisabled("%d found", static_cast<int>(RankChanger.PlaylistsForRankEditing.size()));
                playlistfilter.Draw("Search playlists");
                if (ImGui::BeginListBox("##PlaylistList", ImVec2(-1, -1))) {
                    for (int n = 0; n < static_cast<int>(RankChanger.PlaylistsForRankEditing.size()); ++n) {
                        const std::string& playlistName = RankChanger.PlaylistsForRankEditing[n];
                        if (playlistName.empty() || playlistName.find("null") != std::string::npos || !playlistfilter.PassFilter(playlistName.c_str()))
                            continue;
                        const bool isSelected = RankChanger.selectedplaylisttoedit == playlistName;
                        if (ImGui::Selectable(playlistName.c_str(), isSelected))
                            RankChanger.selectedplaylisttoedit = playlistName;
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("RankRewardsPanel", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_GIFT "  REWARDS & OVERLAY");
                ImGui::Separator();
                ImGui::Checkbox(ICON_FA_TROPHY "  Show Player MMR Overlay", &GameEventHookModule::ShowPlayerMMR);
                ImGui::TextDisabled("Reward rank");
                if (ImGui::BeginListBox("##RewardRank", ImVec2(-1, 108))) {
                    for (int n = 0; n < IM_ARRAYSIZE(ranklistbox_items); ++n) {
                        const bool isSelected = n == reward_rankitem;
                        if (ImGui::Selectable(ranklistbox_items[n], isSelected))
                            reward_rankitem = n;
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndListBox();
                }
                ImGui::InputInt("Reward Wins", &RankChanger.rewardWins);
                if (ImGui::Button(ICON_FA_TROPHY "  Apply Rewards", ImVec2(-1, 0))) {
                    RankChanger.seasonrewards = reward_rankitem + 1;
                    Main.Execute([]() { RankChanger.ApplyRewards(); });
                    Main.Execute([]() { Main.SpawnNotification("Rank", "Rewards applied", 10); });
                }
                ImGui::EndChild();

                gui.end_group_box();
            }
                                  
            else if (gui.m_tab == 1) {
                gui.group_box("Item Spawner", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                                                                                         
                static int itemId = 0;
                static int spawnQuantity = 1;



                {
                    ImGui::BeginChild("ItemsSection", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

                                      
                    if (gui.m_active_subtab[gui.m_tab] == 0) {
                                    
                    ImGui::SetWindowFontScale(1.1f);
                    ImVec4 itemBrowserColor = g_RedThemeColor;
                    ImGui::TextColored(itemBrowserColor, "ITEM SPAWNER");
                    ImGui::SetWindowFontScale(1.0f);

                    ImGui::Separator();
                    ImGui::Spacing();

                                   
                    ImGui::InputText("Search Items##ItemSearch", Items.itemSearch, IM_ARRAYSIZE(Items.itemSearch));

                    ImGui::Spacing();

                                                   
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Items List:");


                    if (ImGui::BeginListBox("##ItemsList", ImVec2(-1, 230))) {
                        Items.EnsureItemsLoaded();

                        std::string searchQuery = std::string(Items.itemSearch);
                        std::transform(searchQuery.begin(), searchQuery.end(), searchQuery.begin(), ::tolower);

                        for (const auto& item : Items.allItems) {
                            std::string itemNameLower = item.displayName;
                            std::transform(itemNameLower.begin(), itemNameLower.end(), itemNameLower.begin(), ::tolower);

                            bool shouldShow = searchQuery.empty() ||
                                (itemNameLower.find(searchQuery) != std::string::npos) ||
                                (item.category.find(searchQuery) != std::string::npos) ||
                                (std::to_string(item.id).find(searchQuery) != std::string::npos);

                            if (shouldShow) {
                                std::string itemLabel = "[" + std::to_string(item.id) + "] " + item.displayName + " (" + item.category + ")";
                                bool isSelected = (selectedItemIndex == item.id);
                                if (ImGui::Selectable(itemLabel.c_str(), isSelected)) {
                                    itemId = item.id;
                                    selectedItemIndex = item.id;
                                }
                            }
                        }
                        ImGui::EndListBox();
                    }

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                                      
                    ImGui::SetWindowFontScale(1.1f);
                    ImVec4 itemAttrColor = g_RedThemeColor;
                    ImGui::TextColored(itemAttrColor, "ITEM ATTRIBUTES");
                    ImGui::SetWindowFontScale(1.0f);

                    ImGui::Separator();
                    ImGui::Spacing();

                                       
                    static const char* items2[] = { "None", "Uncommon", "Rare", "Very Rare", "Import",
                                                  "Exotic", "Black Market", "Premium", "Limited", "Legacy" };
                    static int item_current = 0;

                    ImGui::Combo("Quality##Quality", &item_current, items2, IM_ARRAYSIZE(items2));
                    Items.Quality = (uint8_t)item_current;

                    static const char* Painted[] = { "None", "Crimson", "Lime", "Forest Green", "Pink",
                                                   "Cobalt", "Burnt Sienna", "Saffron", "Titanium White", "Grey",
                                                   "Orange", "Purple", "Sky Blue", "Black", "Gold",
                                                   "Rose Gold", "White Gold", "Onyx" };
                    static int Paint_current = 0;

                    ImGui::Combo("Paint##Paint", &Paint_current, Painted, IM_ARRAYSIZE(Painted));
                    Items.Paint = (uint8_t)Paint_current;

                    static const char* Certif[] = { "None", "Aviator", "Playmaker", "Show-off", "Acrobat", "Tactician",
                                                  "Sweeper", "Guardian", "Scorer", "Juggler", "Sniper", "Paragon",
                                                  "Goalkeeper", "Striker", "Turtle", "Victor" };
                    static int Certif_current = 0;

                    ImGui::Combo("Certification##Certif", &Certif_current, Certif, IM_ARRAYSIZE(Certif));
                    Items.Certif = (uint8_t)Certif_current;

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                                    
                    ImGui::SetWindowFontScale(1.1f);
                    ImVec4 spawnControlColor = g_RedThemeColor;
                    ImGui::TextColored(spawnControlColor, "SPAWN CONTROLS");
                    ImGui::SetWindowFontScale(1.0f);

                    ImGui::Separator();
                    ImGui::Spacing();

                    ImGui::InputInt("Quantity##ItemSpawnQuantity", &spawnQuantity);
                    if (spawnQuantity < 1) spawnQuantity = 1;
                    if (spawnQuantity > 250) spawnQuantity = 250;
                    ImGui::Spacing();

                    bool hasAttributes = (Items.Quality > 0) || (Items.Paint > 0 && Items.Paint < 18) || (Items.Certif < 15);
                    std::string buttonText = hasAttributes ? "Spawn Item with Attributes" : "Spawn Item";

                    if (ImGui::Button(buttonText.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        const int quantityToSpawn = spawnQuantity;
                        Main.Execute([=]() {
                            for (int spawnIndex = 0; spawnIndex < quantityToSpawn; ++spawnIndex) {
                                if (hasAttributes) {
                                    Items.CreateAndSpawnProduct(itemId, Items.Quality, Items.Paint, Items.Certif, seriesId);
                                }
                                else {
                                    Items.SpawnProduct(itemId, seriesId, tradeHold, true, std::string(spawnMessage), showAnimation);
                                }
                            }
                            });
                    }

                    ImGui::Spacing();

                                             
                    if (ImGui::Button(ICON_FA_PLUS "  Spawn All Items", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        Main.Execute([]() {
                            try {
                                Items.EnsureItemsLoaded();

                                int spawnedCount = 0;
                                for (const auto& item : Items.allItems) {
                                    try {
                                        Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                        spawnedCount++;
                                    }
                                    catch (...) {
                                        continue;
                                    }
                                }
                                Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " items", 5);
                            }
                            catch (...) {
                                                        
                            }
                            });
                    }

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();


                    if (SectionHeader(ICON_FA_BOXES "  SPAWN BY CATEGORY")) {
                        ImGui::Spacing();

                                           
                        if (ImGui::Button(ICON_FA_PLUS "  Spawn All Cars", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Body") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " bodies", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();


                        if (ImGui::Button(ICON_FA_PLUS "  Spawn All Banners", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Player Banner") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " Banners", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();
                                           
                        if (ImGui::Button(ICON_FA_FIRE "  Spawn All Boosts", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Rocket Boost") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " boosts", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();

                                                    
                        if (ImGui::Button(ICON_FA_BOMB "  Spawn All Goal Explosions", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Goal Explosion") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " goal explosions", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();

                                           
                        if (ImGui::Button(ICON_FA_PLUS "  Spawn All Trails", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Trail") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " trails", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();

                                           
                        if (ImGui::Button(ICON_FA_DHARMACHAKRA "  Spawn All Wheels", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Wheels") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " wheels", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();
                        if (ImGui::Button(ICON_FA_PLUS "  Spawn All Decals", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Decal") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " Decals", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();

                                             
                        if (ImGui::Button(ICON_FA_PLUS "  Spawn All Antennas", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([]() {
                                try {
                                    Items.EnsureItemsLoaded();
                                    int spawnedCount = 0;
                                    for (const auto& item : Items.allItems) {
                                        if (item.category == "Antenna") {
                                            try {
                                                Items.SpawnProduct(item.id, 0, 0, false, "", false);
                                                spawnedCount++;
                                            }
                                            catch (...) { continue; }
                                        }
                                    }
                                    Main.SpawnNotification("KingMod", "Spawned " + std::to_string(spawnedCount) + " antennas", 5);
                                }
                                catch (...) {}
                                });
                        }

                        ImGui::Spacing();
                    }

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                    if (SectionHeader(ICON_FA_GEM "  QUALITY SETS")) {
                        for (int quality = 0; quality <= 9; ++quality) {
                            const std::string qualityLabel = GetQualityLabel(quality);
                            const std::string buttonLabel = "Spawn All " + qualityLabel + " Items";
                            const std::string notificationLabel = qualityLabel + " items";
                            if (ImGui::Button(buttonLabel.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                                SpawnItemBatch(CollectItemIdsByQuality(quality), notificationLabel);
                            }
                            ImGui::Spacing();
                        }
                    }

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                    if (SectionHeader(ICON_FA_PLUS "  EXTRA")) {
                        const auto extraGroups = CollectExtraItemGroups();
                        for (const auto& group : extraGroups) {
                            const std::string label = "Spawn All " + FormatItemCategoryLabel(group.first);
                            const std::string notificationLabel = FormatItemCategoryLabel(group.first);
                            if (ImGui::Button(label.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                                SpawnItemBatch(group.second, notificationLabel);
                            }
                            ImGui::Spacing();
                        }
                    }

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();
                    }

                                       
                    if (gui.m_active_subtab[gui.m_tab] == 1) {
                    if (SectionHeader(ICON_FA_EXCHANGE_ALT "  TRADE-UP SIMULATOR")) {
                        static int tradeUpManualAddQuantity = 1;
                        static std::string tradeUpStatus = "Spawn or add local items here, then select 5 of one quality.";

                        ImGui::Text("Local Trade-Up Inventory: %d", static_cast<int>(g_LocalTradeUpEntries.size()));
                        ImGui::Checkbox(ICON_FA_TROPHY "  Spawn Reward Item", &g_LocalTradeUpSpawnRewardItem);

                        ImGui::Text("Add Selected Item Count:");
                        ImGui::InputInt("##TradeUpManualAddQuantity", &tradeUpManualAddQuantity);
                        if (tradeUpManualAddQuantity < 1) tradeUpManualAddQuantity = 1;
                        if (tradeUpManualAddQuantity > 50) tradeUpManualAddQuantity = 50;

                        if (ImGui::Button(ICON_FA_EXCHANGE_ALT "  Add Selected Item To Simulator", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            AddLocalTradeUpItems(itemId, tradeUpManualAddQuantity, "Manual Add");
                            const GameItem* selectedItem = FindGameItemById(itemId);
                            if (selectedItem && selectedItem->quality >= 1 && selectedItem->quality <= 6) {
                                tradeUpStatus = "Added " + std::to_string(tradeUpManualAddQuantity) + "x " + selectedItem->displayName;
                            }
                            else {
                                tradeUpStatus = "That item does not support the local trade-up simulator.";
                            }
                        }

                        ImGui::Spacing();

                        const int selectedTradeUpQuality = GetSelectedTradeUpQuality();
                        const int selectedTradeUpCount = GetSelectedTradeUpCount();
                        if (selectedTradeUpQuality > 0) {
                            ImGui::Text("Selected: %d / 5 %s items", selectedTradeUpCount, GetQualityLabel(selectedTradeUpQuality).c_str());
                        }
                        else {
                            ImGui::Text("Selected: %d / 5", selectedTradeUpCount);
                        }
                        ImGui::TextColored(ImVec4(0.82f, 0.82f, 0.85f, 1.0f), "%s", tradeUpStatus.c_str());

                        if (ImGui::Button(ICON_FA_TRASH "  Clear Selection", ImVec2((ImGui::GetContentRegionAvail().x - 6.0f) * 0.5f, 0))) {
                            ClearLocalTradeUpSelection();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_EXCHANGE_ALT "  Clear Simulator", ImVec2(-1, 0))) {
                            g_LocalTradeUpEntries.clear();
                            tradeUpStatus = "Local trade-up inventory cleared.";
                        }

                        if (ImGui::Button(ICON_FA_EXCHANGE_ALT "  Simulate Trade-Up", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            std::string resultMessage;
                            if (TrySimulateLocalTradeUp(resultMessage)) {
                                tradeUpStatus = resultMessage;
                                Main.SpawnNotification("KingMod", resultMessage, 4);
                            }
                            else {
                                tradeUpStatus = resultMessage;
                            }
                        }

                        ImGui::Spacing();
                        ImGui::BeginChild("TradeUpInventoryList", ImVec2(0, 170), true);
                        if (g_LocalTradeUpEntries.empty()) {
                            ImGui::TextDisabled("No local trade-up items yet.");
                        }
                        else {
                            const int activeQuality = GetSelectedTradeUpQuality();
                            for (auto& entry : g_LocalTradeUpEntries) {
                                const bool qualityLocked = activeQuality > 0 && !entry.Selected && entry.Quality != activeQuality;
                                const bool eligibleQuality = IsTradeUpQualitySupported(entry.Quality);
                                if (qualityLocked || !eligibleQuality) {
                                    ImGui::BeginDisabled();
                                }

                                bool selected = entry.Selected;
                                const std::string checkboxId = "##TradeUpEntry" + std::to_string(entry.EntryId);
                                if (ImGui::Checkbox(checkboxId.c_str(), &selected)) {
                                    entry.Selected = selected;
                                }

                                ImGui::SameLine();
                                ImGui::Text("[%s] %s (%s)", GetQualityLabel(entry.Quality).c_str(), entry.DisplayName.c_str(), entry.Category.c_str());

                                if (qualityLocked || !eligibleQuality) {
                                    ImGui::EndDisabled();
                                }
                            }
                        }
                        ImGui::EndChild();
                    }

                                     
                    ImGui::Spacing();
                    ImGui::Separator();
                    if (SectionHeader(ICON_FA_COINS "  CREDIT SPAWNER"))
                    {
                        ImGui::Indent(15.0f);

                        static int creditAmount = 1000;

                        ImGui::TextColored(g_RedThemeColor, ICON_FA_COINS "  Credit Amount:");
                        ImGui::InputInt("##CreditAmount", &creditAmount);
                        if (creditAmount < 1) creditAmount = 1;
                        if (creditAmount > 10000) creditAmount = 10000;

                        ImGui::Spacing();

                        if (ImGui::Button(ICON_FA_COINS "  Spawn Credits", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([=]() {
                                Items.SpawnNormalCredits(creditAmount, "Spawned Credits", true);
                            });
                        }

                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::Spacing();

                        ImGui::TextColored(g_RedThemeColor, ICON_FA_STAR "  Special Credit Types:");

                        if (ImGui::Button(ICON_FA_COINS "  Spawn Special Credits (ID 13)", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([=]() {
                                Items.SpawnSpecialCredits(creditAmount, "Spawned Special Credits", true);
                            });
                        }

                        ImGui::Spacing();

                        if (ImGui::Button(ICON_FA_COINS "  Spawn Esport Jeton (ID 8)", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([=]() {
                                Items.SpawnEsportJeton(creditAmount, "Spawned Esport Jeton", true);
                            });
                        }

                        ImGui::Spacing();

                        if (ImGui::Button(ICON_FA_COINS "  Spawn Togrogs (ID 32)", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                            Main.Execute([=]() {
                                Items.SpawnTogrogs(creditAmount, "Spawned Togrogs", true);
                            });
                        }

                        ImGui::Unindent();
                    }
                    }

                                                                             
                                                                             
                    if (gui.m_active_subtab[gui.m_tab] == 2) {
                        Items.EnsureItemsLoaded();

                        ImGui::TextColored(g_RedThemeColor, ICON_FA_TSHIRT "  EQUIPPED ITEMS");
                        ImGui::Separator();
                        ImGui::Spacing();

                                                                                  
                                                                                   
                                                                              
                        static bool equipOverridesEnabled = false;
                        ImGui::Checkbox(ICON_FA_POWER_OFF "  Enable Equip Overrides", &equipOverridesEnabled);
                        ImGui::Spacing();

                                                                                             
                                                                                              
                                                                                             
                                                                                            
                        if (equipOverridesEnabled) {
                            if (GameEventHookModule::IsInGame)
                                ImGui::TextDisabled("Live visual-only mode: handling/physics stay unchanged.");

                        static std::array<int, 12> equippedIds{};
                        static bool equippedIdsInitialized = false;
                        static char equippedSearch[12][128] = {};
                        static char presetName[48] = "Default";
                        static int selectedPresetIndex = -1;
                        auto lowerText = [](std::string value) {
                            std::transform(value.begin(), value.end(), value.begin(),
                                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                            return value;
                        };

                        struct EquippedSlotDefinition {
                            const char* label;
                            const char* emptyText;
                        };
                        static const EquippedSlotDefinition equippedSlotDefinitions[12] = {
                            { "Car", "Select a car" },
                            { "Decal", "Select a decal" },
                            { "Wheels", "Select wheels" },
                            { "Boost", "Select boost" },
                            { "Topper", "Select a topper" },
                            { "Antenna", "Select an antenna" },
                            { "Trail", "Select a trail" },
                            { "Primary Finish", "Select a primary finish" },
                            { "Accent Finish", "Select an accent finish" },
                            { "Engine Audio", "Select engine audio" },
                            { "Goal Explosion", "Select a goal explosion" },
                            { "Player Anthem", "Select a player anthem" }
                        };

                        auto matchesSlot = [&](const GameItem& item, int selectorIndex) {
                            const std::string category = lowerText(item.category);
                            switch (selectorIndex) {
                            case 0: return category == "body";
                            case 1: return category == "decal" || category == "skin";
                            case 2: return category == "wheels" || category == "wheel";
                            case 3: return category == "rocket boost" || category == "boost";
                            case 4: return category == "hat" || category == "topper";
                            case 5: return category == "antenna";
                            case 6: return category == "trail" || category == "supersonic trail" || category == "supersonictrail";
                            case 7: return category == "paint finish" || category == "paintfinish";
                            case 8: return category == "paint finish 2" || category == "paintfinish2" || category == "custom finish" || category == "customfinish";
                            case 9: return category == "engine audio" || category == "engineaudio";
                            case 10: return category == "goal explosion" || category == "goalexplosion";
                            case 11: return category == "player anthem" || category == "playeranthem" || category == "music stingers" || category == "musicstingers" || category == "music";
                            default: return false;
                            }
                        };

                        auto getLoadoutSlotIndex = [&](int selectorIndex) {
                            for (const GameItem& item : Items.allItems) {
                                if (item.slotIndex >= 0 && matchesSlot(item, selectorIndex))
                                    return item.slotIndex;
                            }
                            return -1;
                        };

                        if (!equippedIdsInitialized) {
                            equippedIds.fill(-2);
                            equippedIdsInitialized = true;
                        }
                        for (int selectorIndex = 0; selectorIndex < static_cast<int>(equippedIds.size()); ++selectorIndex) {
                            const int loadoutSlot = getLoadoutSlotIndex(selectorIndex);
                            if (equippedIds[selectorIndex] == -2 && loadoutSlot >= 0)
                                equippedIds[selectorIndex] = Items.GetEquippedProductId(loadoutSlot);
                        }

                        auto currentPreset = [&]() {
                            EquippedLoadoutPreset preset{};
                            for (int selectorIndex = 0; selectorIndex < static_cast<int>(preset.size()); ++selectorIndex) {
                                preset[selectorIndex].slotIndex = getLoadoutSlotIndex(selectorIndex);
                                preset[selectorIndex].productId = equippedIds[selectorIndex];
                                preset[selectorIndex].paintId = Items.GetEquippedPaintId(preset[selectorIndex].slotIndex);
                            }
                            return preset;
                        };

                        ImGui::BeginChild("EquippedPresetBox", ImVec2(0.0f, 188.0f), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SAVE "  LOADOUT PRESET");
                        ImGui::SetNextItemWidth(-1.0f);
                        ImGui::InputText("Preset Name##EquippedPresetName", presetName, IM_ARRAYSIZE(presetName));
                        const std::vector<std::string> savedPresets = Items.ListLoadoutPresets();
                        const char* selectedPreset = selectedPresetIndex >= 0 && selectedPresetIndex < static_cast<int>(savedPresets.size())
                            ? savedPresets[selectedPresetIndex].c_str() : "Choose a saved preset";
                        ImGui::SetNextItemWidth(-1.0f);
                        if (ImGui::BeginCombo("Saved Presets##EquippedPresetList", selectedPreset)) {
                            for (int i = 0; i < static_cast<int>(savedPresets.size()); ++i) {
                                const bool selected = i == selectedPresetIndex;
                                if (ImGui::Selectable(savedPresets[i].c_str(), selected)) {
                                    selectedPresetIndex = i;
                                    strncpy_s(presetName, savedPresets[i].c_str(), _TRUNCATE);
                                }
                                if (selected) ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        if (ImGui::Button(ICON_FA_UNDO "  Save Preset##EquippedPresetSave", ImVec2((ImGui::GetContentRegionAvail().x - 6.0f) * 0.5f, 0.0f))) {
                            Items.SaveLoadoutPreset(presetName, currentPreset());
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Load + Apply##EquippedPresetLoad", ImVec2(-1.0f, 0.0f))) {
                            EquippedLoadoutPreset loaded{};
                            if (Items.LoadLoadoutPreset(presetName, loaded)) {
                                equippedIds.fill(-1);
                                for (int selectorIndex = 0; selectorIndex < static_cast<int>(equippedIds.size()); ++selectorIndex) {
                                    const int loadoutSlot = getLoadoutSlotIndex(selectorIndex);
                                    for (const EquippedLoadoutItem& entry : loaded) {
                                        if (entry.slotIndex == loadoutSlot && entry.productId >= -1) {
                                            equippedIds[selectorIndex] = entry.productId;
                                            break;
                                        }
                                    }
                                }
                                const std::string loadedPresetName = presetName;
                                Main.Execute([loaded, loadedPresetName]() {
                                    bool complete = true;
                                    for (const EquippedLoadoutItem& entry : loaded) {
                                        if (entry.slotIndex >= 0 && entry.productId > 0) {
                                            if (!Items.EquipProductToSlotPainted(entry.productId, entry.slotIndex, entry.paintId))
                                                complete = false;
                                        }
                                    }
                                    Main.SpawnItemShopToast("LOADOUT PRESET",
                                        complete ? loadedPresetName + " loaded!" : "Preset loaded; loadout is not ready",
                                        complete ? 4 : 5);
                                });
                            }
                            else {
                                Main.Execute([]() {
                                    Main.SpawnItemShopToast("LOADOUT PRESET", "Could not load this preset", 5);
                                });
                            }
                        }
                        if (ImGui::Button(ICON_FA_UNDO "  Delete Preset##EquippedPresetDelete", ImVec2(-1.0f, 0.0f))) {
                            const std::string presetToDelete = presetName;
                            if (Items.DeleteLoadoutPreset(presetToDelete)) {
                                selectedPresetIndex = -1;
                                strncpy_s(presetName, "Default", _TRUNCATE);
                                Main.Execute([presetToDelete]() {
                                    Main.SpawnItemShopToast("LOADOUT PRESET", "Deleted " + presetToDelete, 3);
                                });
                            }
                            else {
                                Main.Execute([]() {
                                    Main.SpawnItemShopToast("LOADOUT PRESET", "Could not delete this preset", 5);
                                });
                            }
                        }
                        ImGui::EndChild();
                        ImGui::Spacing();

                        auto selectedName = [&](int selectedId, const char* fallback) {
                            for (const GameItem& item : Items.allItems) {
                                if (item.id == selectedId)
                                    return item.displayName;
                            }
                            return std::string(fallback);
                        };

                        static const char* loadoutPaintNames[] = {
                            "None", "Crimson", "Lime", "Forest Green", "Pink", "Cobalt",
                            "Burnt Sienna", "Saffron", "Titanium White", "Grey", "Orange",
                            "Purple", "Sky Blue", "Black", "Gold", "Rose Gold", "White Gold", "Onyx"
                        };
                        static const int loadoutPaintIds[] = {
                            0, 1, 2, 7, 9, 5, 6, 13, 12, 11, 10, 8, 4, 3, 14, 15, 16, 17
                        };

                        auto paintMenuIndexFromGameId = [&](int gamePaintId) {
                            for (int i = 0; i < IM_ARRAYSIZE(loadoutPaintIds); ++i)
                                if (loadoutPaintIds[i] == gamePaintId) return i;
                            return 0;
                        };

                        auto selectedItem = [&](int selectorIndex) -> const GameItem* {
                            const int selectedId = equippedIds[selectorIndex];
                            for (const GameItem& item : Items.allItems)
                                if (item.id == selectedId && matchesSlot(item, selectorIndex))
                                    return &item;
                            return nullptr;
                        };

                        auto drawItemCombo = [&](int selectorIndex, int loadoutSlot) {
                            const EquippedSlotDefinition& definition = equippedSlotDefinitions[selectorIndex];
                            const std::string comboId = "##EquippedSlot" + std::to_string(selectorIndex);
                            const std::string preview = selectedName(equippedIds[selectorIndex], definition.emptyText);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::BeginCombo(comboId.c_str(), preview.c_str())) {
                                ImGui::SetNextItemWidth(-1.0f);
                                const std::string searchId = "##EquippedSearch" + std::to_string(selectorIndex);
                                ImGui::InputText(searchId.c_str(), equippedSearch[selectorIndex], IM_ARRAYSIZE(equippedSearch[selectorIndex]));
                                const std::string filter = lowerText(equippedSearch[selectorIndex]);
                                ImGui::Separator();
                                for (const GameItem& item : Items.allItems) {
                                    if (item.slotIndex != loadoutSlot || !matchesSlot(item, selectorIndex))
                                        continue;
                                    const std::string searchable = lowerText(item.displayName + " " + item.category + " " + std::to_string(item.id));
                                    if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                        continue;
                                    const bool selected = item.id == equippedIds[selectorIndex];
                                    const std::string optionId = item.displayName + "##EquipProduct" + std::to_string(selectorIndex) + "_" + std::to_string(item.id);
                                    if (ImGui::Selectable(optionId.c_str(), selected)) {
                                        equippedIds[selectorIndex] = item.id;
                                        const int productId = item.id;
                                        const int currentPaint = item.paintable ? Items.GetEquippedPaintId(loadoutSlot) : 0;
                                        Items.SaveLoadoutPreset(presetName, currentPreset());
                                        Main.Execute([loadoutSlot, productId, currentPaint, name = item.displayName]() {
                                            const bool equipped = Items.EquipProductToSlotPainted(productId, loadoutSlot, currentPaint);
                                            Main.SpawnNotification("Loadout",
                                                equipped ? "Equipped " + name : "Could not equip " + name,
                                                equipped ? 3 : 5);
                                        });
                                    }
                                    if (selected) ImGui::SetItemDefaultFocus();
                                }
                                ImGui::EndCombo();
                            }
                        };

                        if (ImGui::BeginTable("EquippedSelectors", 3,
                            ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg |
                            ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH |
                            ImGuiTableFlags_PadOuterX)) {
                            const float tableWidth = ImGui::GetContentRegionAvail().x;
                            const float typeWidth = (std::max)(112.0f, (std::min)(145.0f, tableWidth * 0.19f));
                            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, typeWidth);
                            ImGui::TableSetupColumn("Item", ImGuiTableColumnFlags_WidthStretch, 0.58f);
                            ImGui::TableSetupColumn("Paint", ImGuiTableColumnFlags_WidthStretch, 0.42f);
                            ImGui::TableHeadersRow();

                            for (int selectorIndex = 0; selectorIndex < static_cast<int>(equippedIds.size()); ++selectorIndex) {
                                const int loadoutSlot = getLoadoutSlotIndex(selectorIndex);
                                ImGui::TableNextRow(ImGuiTableRowFlags_None, ImGui::GetFrameHeightWithSpacing() + 2.0f);
                                ImGui::TableSetColumnIndex(0);
                                ImGui::AlignTextToFramePadding();
                                ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x);
                                ImGui::TextUnformatted(equippedSlotDefinitions[selectorIndex].label);
                                ImGui::PopTextWrapPos();

                                ImGui::TableSetColumnIndex(1);
                                if (loadoutSlot < 0) {
                                    ImGui::TextDisabled("Not available");
                                } else {
                                    drawItemCombo(selectorIndex, loadoutSlot);
                                }

                                ImGui::TableSetColumnIndex(2);
                                const GameItem* item = selectedItem(selectorIndex);
                                const bool paintable = loadoutSlot >= 0 && item && item->paintable;
                                if (!paintable) {
                                    ImGui::BeginDisabled();
                                    int dummy = 0;
                                    ImGui::SetNextItemWidth(-1.0f);
                                    ImGui::Combo(("##PaintDisabled" + std::to_string(selectorIndex)).c_str(), &dummy,
                                        "Not paintable\0\0");
                                    ImGui::EndDisabled();
                                } else {
                                    int paintMenu = paintMenuIndexFromGameId(Items.GetEquippedPaintId(loadoutSlot));
                                    ImGui::SetNextItemWidth(-1.0f);
                                    if (ImGui::Combo(("##EquipPaint" + std::to_string(selectorIndex)).c_str(), &paintMenu,
                                        loadoutPaintNames, IM_ARRAYSIZE(loadoutPaintNames))) {
                                        const int productId = equippedIds[selectorIndex];
                                        const int gamePaintId = loadoutPaintIds[paintMenu];
                                        Main.Execute([loadoutSlot, productId, gamePaintId]() {
                                            Items.EquipProductToSlotPainted(productId, loadoutSlot, gamePaintId);
                                        });
                                    }
                                }
                            }
                            ImGui::EndTable();
                        }

                        ImGui::Spacing();
                        }                                    
                    }

                    ImGui::EndChild();
                }

                gui.end_group_box();
            }
                                  
            else if (gui.m_tab == 2) {
                gui.group_box("Paint / Cert", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                                
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                ImGui::Separator();
                ImGui::TextColored(g_RedThemeColor, ICON_FA_CAR "  BLACK CAR");
                ImGui::Separator();
                if (ImGui::Button(ICON_FA_CHECK "  Set Black Car", ImVec2(-1, 0))) {
                    Events.setblackcar = true;
                }
                if (ImGui::Button(ICON_FA_TRASH "  Remove Black Car", ImVec2(-1, 0))) {
                    Events.offblackcar = true;
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(g_RedThemeColor, ICON_FA_PAINT_BRUSH "  CUSTOM PAINT (Trim Only)");
                ImGui::Separator();

                if (ImGui::Checkbox(ICON_FA_PAINT_BRUSH "  Enable Custom Paint Trim", &Items.custompainttrim)) {
                    Main.Execute([]() {
                        GameEventHookModule::UpdateBodyColor();
                    });
                }

                if (Items.custompainttrim) {
                    if (ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow Trim", &Items.custompainttrimrgb)) {
                        Main.Execute([]() {
                            GameEventHookModule::UpdateBodyColor();
                        });
                    }

                    ImGui::Text("Trim Color:");
                                                                                 
                                                                
                    if (!Items.custompainttrimrgb) {
                        ImGui::ColorEdit3("##TrimColor", Items.customtrimcolors, ImGuiColorEditFlags_NoInputs);
                    }
                }

                                            
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(g_RedThemeColor, ICON_FA_FIRE "  ALPHA BOOST COLOR");

                if (ImGui::Checkbox(ICON_FA_FIRE "  Enable Alpha Boost Color", &Events.alphaBoostColorEnabled)) {
                    Main.Execute([]() {
                        Events.ApplyAlphaBoostColor();
                    });
                }

                if (Events.alphaBoostColorEnabled) {
                    if (ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow Boost Color", &Events.alphaBoostColorRainbow)) {
                        Main.Execute([]() {
                            Events.ApplyAlphaBoostColor();
                        });
                    }

                    ImGui::Text("Boost Color:");
                    if (!Events.alphaBoostColorRainbow &&
                        ImGui::ColorEdit4("##AlphaBoostColor", Events.alphaBoostColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                        Main.Execute([]() {
                            Events.ApplyAlphaBoostColor();
                        });
                    }
                }

                              
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(g_RedThemeColor, ICON_FA_DHARMACHAKRA "  WHEEL COLOR");

                if (ImGui::Checkbox(ICON_FA_DHARMACHAKRA "  Enable Wheel Color", &Events.wheelColorEnabled)) {
                    Main.Execute([]() {
                        Events.ApplyWheelColor();
                    });
                }

                if (Events.wheelColorEnabled) {
                    if (ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow Wheel Color", &Events.wheelColorRainbow)) {
                        Main.Execute([]() {
                            Events.ApplyWheelColor();
                        });
                    }

                    ImGui::Text("Wheel Color:");
                    if (!Events.wheelColorRainbow &&
                        ImGui::ColorEdit4("##WheelColor", Events.wheelColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                        Main.Execute([]() {
                            Events.ApplyWheelColor();
                        });
                    }
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(g_RedThemeColor, ICON_FA_LIGHTBULB "  UNDERGLOW");

                if (ImGui::Checkbox(ICON_FA_LIGHTBULB "  Enable Underglow", &Items.customunderglow)) {
                                                                                           
                    Items.hasresetunderglow = false;
                }

                if (Items.customunderglow) {
                    ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow Underglow", &Items.customunderglowrgb);

                    if (!Items.customunderglowrgb) {
                        ImGui::Text("Underglow Color:");
                        ImGui::ColorEdit3("##UnderglowColor", Items.customunderglowcolors, ImGuiColorEditFlags_NoInputs);
                    }
                }

                ImGui::Spacing();
                ImGui::Separator();
                }

                              
                if (gui.m_active_subtab[gui.m_tab] == 1) {
                if (SectionHeader(ICON_FA_TV "  HUD Colors"))
                {
                    ImGui::Indent(15.0f);

                    if (ImGui::Checkbox(ICON_FA_DESKTOP "  Enable HUD Colors", &Events.hudColorChangerEnabled)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    ImGui::Spacing();

                    if (ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow HUD Colors", &Events.hudColorRainbow)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }

                    if (ImGui::Checkbox(ICON_FA_DESKTOP "  Blue Team HUD", &Events.hudColorBlueTeam)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    if (Events.hudColorBlueTeam) {
                        if (ImGui::ColorEdit4("##HudBlue", Events.hudColorBlue, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                            settingsChanged = true;
                            Events.SaveHUDStadiumColors();
                        }
                    }

                    if (ImGui::Checkbox(ICON_FA_DESKTOP "  Orange Team HUD", &Events.hudColorOrangeTeam)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    if (Events.hudColorOrangeTeam) {
                        if (ImGui::ColorEdit4("##HudOrange", Events.hudColorOrange, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                            settingsChanged = true;
                            Events.SaveHUDStadiumColors();
                        }
                    }

                    ImGui::Unindent();
                }

                if (SectionHeader(ICON_FA_FUTBOL "  Stadium Colors"))
                {
                    ImGui::Indent(15.0f);

                    if (ImGui::Checkbox(ICON_FA_BUILDING "  Enable Stadium Colors", &Events.stadiumColorChangerEnabled)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    ImGui::Spacing();

                    if (ImGui::Checkbox(ICON_FA_RAINBOW "  Rainbow Stadium Colors", &Events.stadiumColorRainbow)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }

                    if (ImGui::Checkbox(ICON_FA_BUILDING "  Blue Team Stadium", &Events.stadiumColorBlueTeam)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    if (Events.stadiumColorBlueTeam) {
                        if (ImGui::ColorEdit4("##StadiumBlue", Events.stadiumColorBlue, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                            settingsChanged = true;
                            Events.SaveHUDStadiumColors();
                        }
                    }

                    if (ImGui::Checkbox(ICON_FA_BUILDING "  Orange Team Stadium", &Events.stadiumColorOrangeTeam)) {
                        settingsChanged = true;
                        Events.SaveHUDStadiumColors();
                    }
                    if (Events.stadiumColorOrangeTeam) {
                        if (ImGui::ColorEdit4("##StadiumOrange", Events.stadiumColorOrange, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                            settingsChanged = true;
                            Events.SaveHUDStadiumColors();
                        }
                    }

                    ImGui::Unindent();
                }

                ImGui::Spacing();
                ImGui::Separator();
                if (SectionHeader(ICON_FA_WINDOW_MAXIMIZE "  CUSTOM MODALS"))
                {
                    ImGui::Indent(12.0f);
                    const char* modalTypes[] = { "Fun", "Ban", "Warning" };
                    ImGui::Combo("Modal Type", &g_LocalModalEditor.ModalType, modalTypes, IM_ARRAYSIZE(modalTypes));
                    ImGui::ColorEdit4("Modal Color", (float*)&g_LocalModalEditor.Color);
                    ImGui::InputText("Modal Title", &g_LocalModalEditor.Title);
                    ImGui::InputTextMultiline("Modal Body", &g_LocalModalEditor.Body, ImVec2(-1, 100));

                    if (g_LocalModalEditor.ModalType == 1)
                    {
                        ImGui::Separator();
                        ImGui::TextDisabled("Ban citations");
                        for (size_t i = 0; i < g_LocalModalEditor.Citations.size(); ++i)
                        {
                            ImGui::PushID(static_cast<int>(i));
                            ImGui::InputText("Citation", &g_LocalModalEditor.Citations[i]);
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_TRASH "  Remove"))
                            {
                                g_LocalModalEditor.Citations.erase(g_LocalModalEditor.Citations.begin() + static_cast<long long>(i));
                                --i;
                            }
                            ImGui::PopID();
                        }
                        ImGui::InputText("New Citation", &g_LocalModalEditor.AddCitation);
                        if (ImGui::Button(ICON_FA_COMMENT_DOTS "  Add Citation") && !g_LocalModalEditor.AddCitation.empty())
                        {
                            g_LocalModalEditor.Citations.push_back(g_LocalModalEditor.AddCitation);
                            g_LocalModalEditor.AddCitation.clear();
                        }
                    }

                    ImGui::Separator();
                    ImGui::TextDisabled("Modal buttons");
                    for (size_t i = 0; i < g_LocalModalEditor.Buttons.size(); ++i)
                    {
                        ImGui::PushID(static_cast<int>(i + 100));
                        ImGui::InputText("Button Label", &g_LocalModalEditor.Buttons[i]);
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TRASH "  Remove") && g_LocalModalEditor.Buttons.size() > 1)
                        {
                            g_LocalModalEditor.Buttons.erase(g_LocalModalEditor.Buttons.begin() + static_cast<long long>(i));
                            --i;
                        }
                        ImGui::PopID();
                    }
                    ImGui::InputText("New Button", &g_LocalModalEditor.AddButton);
                    if (ImGui::Button(ICON_FA_PLUS "  Add Button") && !g_LocalModalEditor.AddButton.empty())
                    {
                        g_LocalModalEditor.Buttons.push_back(g_LocalModalEditor.AddButton);
                        g_LocalModalEditor.AddButton.clear();
                    }

                    ImGui::Separator();
                    if (ImGui::Button(ICON_FA_COMMENT_DOTS "  Show Modal", ImVec2(-1, 0)))
                    {
                        Fun::QueueModal(g_LocalModalEditor.ModalType, g_LocalModalEditor.Title, g_LocalModalEditor.Body,
                            static_cast<uint8_t>(g_LocalModalEditor.Color.x * 255.0f),
                            static_cast<uint8_t>(g_LocalModalEditor.Color.y * 255.0f),
                            static_cast<uint8_t>(g_LocalModalEditor.Color.z * 255.0f),
                            static_cast<uint8_t>(g_LocalModalEditor.Color.w * 255.0f),
                            g_LocalModalEditor.Citations, g_LocalModalEditor.Buttons);
                    }
                    ImGui::Unindent(12.0f);
                }
                }

                                                                                   
                                                                                            
                if (gui.m_active_subtab[gui.m_tab] == 2)
                {
                    CustomCar::CustomCarConfig& carConfig = CustomCar::GetConfig();

                    if (SectionHeader(ICON_FA_CAR "  CUSTOM CAR"))
                    {
                        bool configChanged = false;
                        configChanged |= ImGui::Checkbox("Enable Custom Car", &carConfig.enabled);
                        configChanged |= ImGui::Checkbox("Auto Refresh Model", &carConfig.autoRefresh);
                        if (configChanged)
                            CustomCar::SaveConfiguration();

                        if (ImGui::Button(ICON_FA_SYNC "  Refresh Car Model", ImVec2(220.0f, 32.0f)))
                            Main.Execute([] { CustomCar::RefreshCarModel(); });
                    }

                    if (SectionHeader(ICON_FA_CAR_SIDE "  CUSTOM BODIES"))
                    {
                        auto& bodyCustomizations = CustomCar::GetBodyCustomizations();
                        int totalBodies = 0;
                        for (const auto& [productId, customization] : bodyCustomizations)
                            totalBodies += static_cast<int>(customization.bodies.size());

                        if (bodyCustomizations.empty())
                        {
                            ImGui::TextDisabled("No custom bodies found.");
                            ImGui::Spacing();
                            if (ImGui::Button(ICON_FA_SYNC "  Reload JSON Files"))
                            {
                                CustomCar::LoadCustomBodies();
                                CustomCar::LoadConfiguration();
                            }
                        }
                        else
                        {
                            ImGui::TextDisabled("%d custom body option%s", totalBodies, totalBodies == 1 ? "" : "s");
                            ImGui::Spacing();

                            if (ImGui::BeginListBox("##custom_car_body_list", ImVec2(-1.0f, 260.0f)))
                            {
                                int entryId = 0;
                                for (auto& [productId, customization] : bodyCustomizations)
                                {
                                    for (size_t bodyIndex = 0; bodyIndex < customization.bodies.size(); ++bodyIndex)
                                    {
                                        ImGui::PushID(entryId++);
                                        CustomCar::CustomBodyData& body = customization.bodies[bodyIndex];
                                        const bool selected = customization.selectedBodyIdx && *customization.selectedBodyIdx == bodyIndex;

                                        std::string carName = "Car " + std::to_string(productId);
                                        auto productIt = CustomCar::s_allBodyProducts.find(productId);
                                        if (productIt != CustomCar::s_allBodyProducts.end() && !productIt->second.name.empty())
                                            carName = productIt->second.name;

                                        const std::string label = body.name + "  -  " + carName + " (ID " + std::to_string(productId) + ")";
                                        if (ImGui::Selectable(label.c_str(), selected))
                                        {
                                            customization.selectedBodyIdx = bodyIndex;
                                            CustomCar::SaveConfiguration();
                                            if (carConfig.autoRefresh)
                                                Main.Execute([] { CustomCar::RefreshCarModel(); });
                                        }
                                        if (selected) ImGui::SetItemDefaultFocus();
                                        ImGui::PopID();
                                    }
                                }
                                ImGui::EndListBox();
                            }

                            ImGui::Spacing();
                            if (ImGui::Button(ICON_FA_SYNC "  Reload Custom Bodies"))
                            {
                                CustomCar::LoadCustomBodies();
                                CustomCar::LoadConfiguration();
                            }
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_CAR "  Refresh Model"))
                                Main.Execute([] { CustomCar::RefreshCarModel(); });
                        }
                    }

                    if (SectionHeader(ICON_FA_TOOLS "  CUSTOM CAR TOOLS"))
                    {
                        ImGui::TextDisabled("Cached assets: %zu", CustomCar::GetCachedAssetCount());
                        ImGui::Spacing();

                        if (ImGui::Button(ICON_FA_TRASH "  Clear Cached Assets"))
                            CustomCar::ClearCachedAssets();
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open CustomCars Folder"))
                            OpenFolderInExplorer(CustomCar::GetCustomCarsFolder());

                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open CookedPCConsole Folder"))
                            OpenFolderInExplorer(CustomCar::GetCookedPCConsoleFolder());
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_FILE_CODE "  Create Example JSON"))
                        {
                            const bool created = CustomCar::CreateExampleJson();
                            Main.SpawnNotification("KingMod", created ? "Example custom-car JSON is ready" : "Could not create example JSON", 3);
                        }
                    }
                }

                gui.end_group_box();
            }

                            
            else if (gui.m_tab == 3) {
                gui.group_box("PsyNet", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                static int selectedPsyNetLogIndex = -1;
                static char psyNetFilter[128] = "";

                if (selectedPsyNetLogIndex >= static_cast<int>(PsyNetLogMessages.size())) {
                    selectedPsyNetLogIndex = PsyNetLogMessages.empty() ? -1 : static_cast<int>(PsyNetLogMessages.size()) - 1;
                }

                                                                             
                                                                             
                                                                               
                ImGui::PushStyleColor(ImGuiCol_ChildBg, gui.group_box_bg.to_vec4());
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.30f, 0.49f, 1.0f, 0.12f));
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImGui::GetStyleColorVec4(ImGuiCol_FrameBgActive));
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.031f, 0.035f, 0.058f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.050f, 0.054f, 0.078f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.070f, 0.074f, 0.098f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_Header, ImGui::GetStyleColorVec4(ImGuiCol_Header));
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImGui::GetStyleColorVec4(ImGuiCol_HeaderHovered));
                ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive));

                ImGui::TextColored(g_RedThemeColor, ICON_FA_NETWORK_WIRED "  PSYNET");
                ImGui::Separator();

                if (ImGui::Checkbox(ICON_FA_STREAM "  Enable PsyNet Logging", &EnablePsyNetLogging)) {
                    GameEventHookModule::SaveConfig();
                }
                
                static bool dumpEnabled = false;
                if (ImGui::Checkbox(ICON_FA_FILE_EXPORT "  Dump PsyNet to File", &dumpEnabled)) {
                    if (dumpEnabled)
                        PsyNetDumper::Enable();
                    else
                        PsyNetDumper::Disable();
                }

                if (ImGui::Checkbox(ICON_FA_POWER_OFF "  Enable Drop / Crate Edit", &EnableDropUnlockBypass)) {
                    GameEventHookModule::SaveConfig();
                }

                const float contentWidth = ImGui::GetContentRegionAvail().x;
                float rightPaneWidth = contentWidth * 0.40f;
                if (rightPaneWidth < 300.0f) rightPaneWidth = 300.0f;
                float leftPaneWidth = contentWidth - rightPaneWidth - 10.0f;
                if (leftPaneWidth < 260.0f) leftPaneWidth = 260.0f;

                const float totalHeight = ImGui::GetContentRegionAvail().y;
                float inspectHeight = totalHeight * 0.70f;
                if (inspectHeight < 320.0f) inspectHeight = 320.0f;

                ImGui::BeginChild("PsyNetTrafficViewer", ImVec2(leftPaneWidth, 0), true);
                ImGui::TextColored(ImVec4(0.88f, 0.88f, 0.90f, 1.0f), "Traffic Feed");
                ImGui::Separator();
                ImGui::Text("Entries: %d", static_cast<int>(PsyNetLogMessages.size()));
                ImGui::Text("Pending: %d", PsyNetPendingRequestCount);
                ImGui::Text("Drop Cache: %s", PsyNetHasCachedDropTable ? "Ready" : "Empty");
                ImGui::TextWrapped("State: %s", PsyNetStatusSummary.c_str());

                if (ImGui::Button(ICON_FA_STREAM "  Clear Feed", ImVec2(120, 0))) {
                    PsyNetLogMessages.clear();
                    PsyNetLogHeaders.clear();
                    PsyNetLogBodies.clear();
                    PsyNetStatusSummary = "Logs cleared";
                    selectedPsyNetLogIndex = -1;
                }

                ImGui::SameLine();
                ImGui::SetNextItemWidth(-1);
                ImGui::InputTextWithHint("Search##PsyNetFilter", "Filter traffic...", psyNetFilter, IM_ARRAYSIZE(psyNetFilter));

                ImGui::Spacing();
                ImGui::BeginChild("PsyNetTrafficList", ImVec2(0, 0), true);
                const std::string filterLower = ToLowerCopy(std::string(psyNetFilter));
                for (int i = 0; i < static_cast<int>(PsyNetLogMessages.size()); ++i) {
                    const std::string& summary = PsyNetLogMessages[i];
                    if (!filterLower.empty() && ToLowerCopy(summary).find(filterLower) == std::string::npos) {
                        continue;
                    }

                    const ImVec4 entryColor = GetPsyNetEntryColor(summary);
                    ImGui::PushStyleColor(ImGuiCol_Text, entryColor);
                    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(entryColor.x, entryColor.y, entryColor.z, 0.10f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(entryColor.x, entryColor.y, entryColor.z, 0.22f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(entryColor.x, entryColor.y, entryColor.z, 0.32f));
                    const std::string selectableLabel = summary + "##PsyNetLog" + std::to_string(i);
                    if (ImGui::Selectable(selectableLabel.c_str(), selectedPsyNetLogIndex == i)) {
                        selectedPsyNetLogIndex = i;
                    }
                    ImGui::PopStyleColor(4);
                }
                ImGui::EndChild();
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginGroup();
                ImGui::BeginChild("PsyNetInspectViewer", ImVec2(0, inspectHeight), true);
                ImGui::TextColored(ImVec4(0.88f, 0.88f, 0.90f, 1.0f), "Inspect Panel");
                ImGui::Separator();

                if (selectedPsyNetLogIndex >= 0 && selectedPsyNetLogIndex < static_cast<int>(PsyNetLogMessages.size())) {
                    const std::string& summary = PsyNetLogMessages[selectedPsyNetLogIndex];
                    const std::string& headers = selectedPsyNetLogIndex < static_cast<int>(PsyNetLogHeaders.size())
                        ? PsyNetLogHeaders[selectedPsyNetLogIndex]
                        : std::string("No headers");
                    const std::string& body = selectedPsyNetLogIndex < static_cast<int>(PsyNetLogBodies.size())
                        ? PsyNetLogBodies[selectedPsyNetLogIndex]
                        : std::string("No body");
                    const ImVec4 entryColor = GetPsyNetEntryColor(summary);
                    const std::string formattedBody = GetFormattedJsonPreview(body);

                    ImGui::TextColored(entryColor, "%s", summary.c_str());
                    ImGui::Spacing();

                    if (ImGui::Button(ICON_FA_COPY "  Copy Headers", ImVec2(120, 0))) {
                        ImGui::SetClipboardText(headers.c_str());
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_COPY "  Copy Body", ImVec2(120, 0))) {
                        ImGui::SetClipboardText(formattedBody.c_str());
                    }

                    ImGui::Spacing();

                    if (SectionHeader(ICON_FA_HEADING "  HEADERS")) {
                        ImGui::BeginChild("PsyNetHeaders", ImVec2(0, 82), true, ImGuiWindowFlags_HorizontalScrollbar);
                        ImGui::TextUnformatted(headers.c_str());
                        ImGui::EndChild();
                    }

                    if (SectionHeader(ICON_FA_ALIGN_LEFT "  BODY")) {
                        ImGui::BeginChild("PsyNetBody", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
                        ImGui::TextUnformatted(formattedBody.c_str());
                        ImGui::EndChild();
                    }
                }
                else {
                    ImGui::Dummy(ImVec2(0.0f, 0.0f));
                }

                ImGui::PopStyleColor(11);
                gui.end_group_box();
            }
                           
            else if (gui.m_tab == 4) {
                gui.group_box("Party", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                                  
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                    ImGui::Spacing();
                    int friendsPendingCount = 0;
                    int partyInvitesCount = 0;
                    try { if (auto friends = Instances.GetInstanceOf<UGFxData_Friends_TA>()) friendsPendingCount = (int)friends->Pending.size(); } catch (...) {}
                    try { if (auto partyInvites = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>()) partyInvitesCount = (int)partyInvites->Invites.size(); } catch (...) {}
                    std::string btnFriends = "Remove All Friend Requests (" + std::to_string(friendsPendingCount) + ")";
                    std::string btnParty = "Remove All Party Invites (" + std::to_string(partyInvitesCount) + ")";
                    if (ImGui::Button(btnFriends.c_str(), ImVec2(-1, 25))) {
                        Main.Execute([]() {
                            int declined = 0;
                            try {
                                UGFxData_Friends_TA* friends = Instances.GetInstanceOf<UGFxData_Friends_TA>();
                                if (friends) {
                                    for (auto inv : friends->Pending) {
                                        try { friends->DeclineEpicFriendInvite(inv.PersonaId); declined++; } catch (...) {}
                                    }
                                }
                                UOnlinePlayerFriends_X* onlineFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
                                if (onlineFriends && friends) {
                                    for (auto inv : friends->Pending) {
                                        try { onlineFriends->DeclineEpicFriendInvite(inv.PersonaId); } catch (...) {}
                                    }
                                }
                            } catch (...) {}
                            Main.SpawnNotification("KingMod", std::string("Declined ") + std::to_string(declined) + " friend requests", 3);
                        });
                    }
                    ImGui::Spacing();
                    if (ImGui::Button(btnParty.c_str(), ImVec2(-1, 25))) {
                        Main.Execute([]() {
                            int declined = 0;
                            try {
                                UGFxData_PartyInvite_TA* partyInvites = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>();
                                if (partyInvites) {
                                    int count = (int)partyInvites->Invites.size();
                                    for (int i = 0; i < count; ++i) { try { partyInvites->SetUserInvitedResponse(i, false); declined++; } catch (...) {} }
                                }
                            } catch (...) {}
                            Main.SpawnNotification("KingMod", std::string("Declined ") + std::to_string(declined) + " party invites", 3);
                        });
                    }
                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_USER_PLUS "  Remove All Club Invites", ImVec2(-1, 25))) {
                        Main.Execute([]() {
                            try {
                                UGFxData_Clubs_TA* clubs = Instances.GetInstanceOf<UGFxData_Clubs_TA>();
                                if (clubs) {
                                    clubs->RejectAllClubInvites();
                                    Main.SpawnNotification("KingMod", "Cleared all club invites", 3);
                                } else {
                                    Main.SpawnNotification("KingMod", "Clubs data not available", 3);
                                }
                            } catch (...) {
                                Main.SpawnNotification("KingMod", "Failed to clear club invites", 3);
                            }
                        });
                    }
                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_TRASH "  Decline Everything Now", ImVec2(-1, 25))) {
                        Main.Execute([]() {
                            int declinedFriends = 0, declinedParty = 0;
                            try {
                                if (auto friends = Instances.GetInstanceOf<UGFxData_Friends_TA>()) {
                                    for (auto inv : friends->Pending) { try { friends->DeclineEpicFriendInvite(inv.PersonaId); declinedFriends++; } catch (...) {} }
                                }
                            } catch (...) {}
                            try {
                                if (auto partyInvites = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>()) {
                                    int count = (int)partyInvites->Invites.size();
                                    for (int i = 0; i < count; ++i) { try { partyInvites->SetUserInvitedResponse(i, false); declinedParty++; } catch (...) {} }
                                }
                            } catch (...) {}
                            try {
                                if (auto clubs = Instances.GetInstanceOf<UGFxData_Clubs_TA>()) { clubs->RejectAllClubInvites(); }
                            } catch (...) {}
                            Main.SpawnNotification("KingMod", "Declined all friend/party/club invites", 3);
                        });
                    }
                    ImGui::Spacing();
                    ImGui::Spacing();
                    static int platformIndex = 0;                   
                    const char* platforms[] = { "Epic", "Steam" };
                    ImGui::Combo("Platform", &platformIndex, platforms, IM_ARRAYSIZE(platforms));
                    static std::string idInput;
                    static std::string favTitleInput;
                    ImGui::InputText("Account ID", &idInput);
                    ImGui::InputText("Favorite Title (optional)", &favTitleInput);
                    if (ImGui::Button(ICON_FA_PLUS "  Add To Favorites", ImVec2(-1, 22))) {
                        int plat = platformIndex;
                        std::string idStr = idInput;
                        std::string titleStr = favTitleInput;
                        bool exists = false;
                        for (auto& p : GameEventHookModule::FavoritePartyIds) { if (p.platform == plat && p.id == idStr) { exists = true; break; } }
                        if (!exists && !idStr.empty()) {
                            GameEventHookModule::FavoritePartyIds.push_back({plat, idStr, titleStr});
                            GameEventHookModule::SaveConfig();
                            Main.SpawnNotification("KingMod", "Added to favorites", 2);
                        }
                    }
                    if (ImGui::Button(ICON_FA_USER_PLUS "  Invite By ID", ImVec2(-1, 25))) {
                        int platform = platformIndex;
                        std::string idStr = idInput;
                        Main.Execute([platform, idStr]() {
                            try {
                                UGFxData_PartyInvite_TA* party = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>();
                                if (!party) { Main.SpawnNotification("KingMod", "Party system not available", 3); return; }
                                FUniqueNetId toInvite{};
                                toInvite.SplitscreenID = 0;
                                if (platform == 0) {
                                    toInvite.Platform = EOnlinePlatform::OnlinePlatform_Epic;
                                    std::wstring wid(idStr.begin(), idStr.end());
                                    toInvite.EpicAccountId = FString(wid.c_str());
                                    party->InviteToParty(toInvite);
                                    Main.SpawnNotification("KingMod", "Invite sent (Epic)", 3);
                                } else {
                                    uint64_t uid = 0;
                                    try { uid = std::stoull(idStr); } catch (...) { uid = 0; }
                                    FUniqueNetId steamId{};
                                    steamId.Platform = EOnlinePlatform::OnlinePlatform_Steam;
                                    steamId.Uid = uid;
                                    steamId.SplitscreenID = 0;
                                    bool invited = false;
                                    try {
                                        UPersonas_TA* personas = Instances.GetInstanceOf<UPersonas_TA>();
                                        UOnlinePlayerFriends_X* onlineFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
                                        if (personas && onlineFriends) {
                                            FUniqueNetId linkedEpic = personas->GetLinkedEpicId(steamId, onlineFriends);
                                            std::string linked = linkedEpic.EpicAccountId.ToString();
                                            if (!linked.empty()) {
                                                FUniqueNetId epicTarget{};
                                                epicTarget.Platform = EOnlinePlatform::OnlinePlatform_Epic;
                                                epicTarget.SplitscreenID = 0;
                                                epicTarget.EpicAccountId = linkedEpic.EpicAccountId;
                                                party->InviteToParty(epicTarget);
                                                Main.SpawnNotification("KingMod", "Invite sent (resolved to Epic)", 3);
                                                invited = true;
                                            }
                                        }
                                    } catch (...) {}
                                    if (!invited) {
                                        toInvite = steamId;
                                        party->InviteToParty(toInvite);
                                        Main.SpawnNotification("KingMod", "Invite sent (Steam) — if crossplay blocked, provide Epic ID", 4);
                                    }
                                     try {
                                         auto& rec = GameEventHookModule::RecentPartyIds;
                                         rec.insert(rec.begin(), {1, idStr});
                                         for (size_t i = 1; i < rec.size(); ) { if (rec[i] == rec[0]) rec.erase(rec.begin() + i); else ++i; }
                                         if (rec.size() > 10) rec.resize(10);
                                         GameEventHookModule::SaveConfig();
                                     } catch (...) {}
                                }
                            } catch (...) { Main.SpawnNotification("KingMod", "Failed to send invite", 3); }
                        });
                    }
                    if (ImGui::Button(ICON_FA_USER_PLUS "  Request Join By ID", ImVec2(-1, 25))) {
                        int platform = platformIndex;
                        std::string idStr = idInput;
                        Main.Execute([platform, idStr]() {
                            try {
                                UGFxData_PartyJoinRequest_TA* joinReq = Instances.GetInstanceOf<UGFxData_PartyJoinRequest_TA>();
                                if (!joinReq) { Main.SpawnNotification("KingMod", "Join request system not available", 3); return; }
                                FUniqueNetId target{};
                                target.SplitscreenID = 0;
                                if (platform == 0) {
                                    target.Platform = EOnlinePlatform::OnlinePlatform_Epic;
                                    std::wstring wid(idStr.begin(), idStr.end());
                                    target.EpicAccountId = FString(wid.c_str());
                                    joinReq->SendJoinRequest(target);
                                    Main.SpawnNotification("KingMod", "Join request sent (Epic)", 3);
                                } else {
                                    uint64_t uid = 0;
                                    try { uid = std::stoull(idStr); } catch (...) { uid = 0; }
                                    FUniqueNetId steamId{};
                                    steamId.Platform = EOnlinePlatform::OnlinePlatform_Steam;
                                    steamId.Uid = uid;
                                    steamId.SplitscreenID = 0;
                                    bool sent = false;
                                    try {
                                        UPersonas_TA* personas = Instances.GetInstanceOf<UPersonas_TA>();
                                        UOnlinePlayerFriends_X* onlineFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
                                        if (personas && onlineFriends) {
                                            FUniqueNetId linkedEpic = personas->GetLinkedEpicId(steamId, onlineFriends);
                                            std::string linked = linkedEpic.EpicAccountId.ToString();
                                            if (!linked.empty()) {
                                                FUniqueNetId epicTarget{};
                                                epicTarget.Platform = EOnlinePlatform::OnlinePlatform_Epic;
                                                epicTarget.SplitscreenID = 0;
                                                epicTarget.EpicAccountId = linkedEpic.EpicAccountId;
                                                joinReq->SendJoinRequest(epicTarget);
                                                Main.SpawnNotification("KingMod", "Join request sent (resolved to Epic)", 3);
                                                sent = true;
                                            }
                                        }
                                    } catch (...) {}
                                    if (!sent) {
                                        joinReq->SendJoinRequest(steamId);
                                        Main.SpawnNotification("KingMod", "Join request sent (Steam) — if blocked, resolve Epic ID", 4);
                                    }
                                }
                                try {
                                    auto& rec = GameEventHookModule::RecentPartyIds;
                                    rec.insert(rec.begin(), {platform, idStr});
                                    for (size_t i = 1; i < rec.size(); ) { if (rec[i] == rec[0]) rec.erase(rec.begin() + i); else ++i; }
                                    if (rec.size() > 10) rec.resize(10);
                                    GameEventHookModule::SaveConfig();
                                } catch (...) {}
                            } catch (...) { Main.SpawnNotification("KingMod", "Failed to send join request", 3); }
                        });
                    }
                    ImGui::Spacing();
                }
                    ImGui::Separator();
                                    
                if (gui.m_active_subtab[gui.m_tab] == 1) {
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_STAR "  FAVORITES");
                    static int editingFav = -1;
                    static std::string editTitle, editId;
                    static int editPlatform = 0;
                    ImGui::BeginChild("##Favs", ImVec2(0, 140), true);
                    for (int i = 0; i < (int)GameEventHookModule::FavoritePartyIds.size(); ++i) {
                        int plat = GameEventHookModule::FavoritePartyIds[i].platform;
                        std::string id = GameEventHookModule::FavoritePartyIds[i].id;
                        std::string title = GameEventHookModule::FavoritePartyIds[i].title;
                        std::string label = (title.empty() ? std::string("[No title] ") : ("[" + title + "] ")) + std::string(plat == 0 ? "Epic: " : "Steam: ") + id;
                        ImGui::Text("%s", label.c_str());
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Invite##") + std::to_string(i)).c_str())) {
                            int p = plat; std::string v = id;
                            Main.Execute([p, v]() {
                                try {
                                    UGFxData_PartyInvite_TA* party = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>();
                                    if (!party) { Main.SpawnNotification("KingMod", "Party system not available", 3); return; }
                                    if (p == 0) {
                                        FUniqueNetId x{}; x.Platform = EOnlinePlatform::OnlinePlatform_Epic; x.SplitscreenID = 0; std::wstring w(v.begin(), v.end()); x.EpicAccountId = FString(w.c_str());
                                        party->InviteToParty(x); Main.SpawnNotification("KingMod", "Invite sent (Epic)", 3);
                                    } else {
                                        uint64_t uid = 0; try { uid = std::stoull(v); } catch (...) { uid = 0; }
                                        FUniqueNetId s{}; s.Platform = EOnlinePlatform::OnlinePlatform_Steam; s.Uid = uid; s.SplitscreenID = 0;
                                        bool invited = false;
                                        try {
                                            UPersonas_TA* personas = Instances.GetInstanceOf<UPersonas_TA>();
                                            UOnlinePlayerFriends_X* onlineFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
                                            if (personas && onlineFriends) {
                                                FUniqueNetId linkedEpic = personas->GetLinkedEpicId(s, onlineFriends);
                                                std::string linked = linkedEpic.EpicAccountId.ToString();
                                                if (!linked.empty()) {
                                                    FUniqueNetId e{}; e.Platform = EOnlinePlatform::OnlinePlatform_Epic; e.SplitscreenID = 0; e.EpicAccountId = linkedEpic.EpicAccountId;
                                                    party->InviteToParty(e); Main.SpawnNotification("KingMod", "Invite sent (resolved to Epic)", 3); invited = true;
                                                }
                                            }
                                        } catch (...) {}
                                        if (!invited) { party->InviteToParty(s); Main.SpawnNotification("KingMod", "Invite sent (Steam)", 3); }
                                    }
                                } catch (...) { Main.SpawnNotification("KingMod", "Failed to send invite", 3); }
                            });
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Request##") + std::to_string(i)).c_str())) {
                            int p = plat; std::string v = id;
                            Main.Execute([p, v]() {
                                try {
                                    UGFxData_PartyJoinRequest_TA* joinReq = Instances.GetInstanceOf<UGFxData_PartyJoinRequest_TA>();
                                    if (!joinReq) { Main.SpawnNotification("KingMod", "Join request system not available", 3); return; }
                                    if (p == 0) {
                                        FUniqueNetId x{}; x.Platform = EOnlinePlatform::OnlinePlatform_Epic; x.SplitscreenID = 0; std::wstring w(v.begin(), v.end()); x.EpicAccountId = FString(w.c_str());
                                        joinReq->SendJoinRequest(x); Main.SpawnNotification("KingMod", "Join request sent (Epic)", 3);
                                    } else {
                                        uint64_t uid = 0; try { uid = std::stoull(v); } catch (...) { uid = 0; }
                                        FUniqueNetId s{}; s.Platform = EOnlinePlatform::OnlinePlatform_Steam; s.Uid = uid; s.SplitscreenID = 0;
                                        bool sent = false;
                                        try {
                                            UPersonas_TA* personas = Instances.GetInstanceOf<UPersonas_TA>();
                                            UOnlinePlayerFriends_X* onlineFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
                                            if (personas && onlineFriends) {
                                                FUniqueNetId linkedEpic = personas->GetLinkedEpicId(s, onlineFriends);
                                                std::string linked = linkedEpic.EpicAccountId.ToString();
                                                if (!linked.empty()) {
                                                    FUniqueNetId e{}; e.Platform = EOnlinePlatform::OnlinePlatform_Epic; e.SplitscreenID = 0; e.EpicAccountId = linkedEpic.EpicAccountId;
                                                    joinReq->SendJoinRequest(e); Main.SpawnNotification("KingMod", "Join request sent (resolved to Epic)", 3); sent = true;
                                                }
                                            }
                                        } catch (...) {}
                                        if (!sent) { joinReq->SendJoinRequest(s); Main.SpawnNotification("KingMod", "Join request sent (Steam)", 3); }
                                    }
                                } catch (...) { Main.SpawnNotification("KingMod", "Failed to send join request", 3); }
                            });
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Edit##") + std::to_string(i)).c_str())) {
                            editingFav = i;
                            editPlatform = plat;
                            editId = id;
                            editTitle = title;
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Up##") + std::to_string(i)).c_str())) {
                            if (i > 0) {
                                auto tmp = GameEventHookModule::FavoritePartyIds[i-1];
                                GameEventHookModule::FavoritePartyIds[i-1] = GameEventHookModule::FavoritePartyIds[i];
                                GameEventHookModule::FavoritePartyIds[i] = tmp;
                                GameEventHookModule::SaveConfig();
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Down##") + std::to_string(i)).c_str())) {
                            if (i + 1 < (int)GameEventHookModule::FavoritePartyIds.size()) {
                                auto tmp = GameEventHookModule::FavoritePartyIds[i+1];
                                GameEventHookModule::FavoritePartyIds[i+1] = GameEventHookModule::FavoritePartyIds[i];
                                GameEventHookModule::FavoritePartyIds[i] = tmp;
                                GameEventHookModule::SaveConfig();
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("Remove##") + std::to_string(i)).c_str())) {
                            GameEventHookModule::FavoritePartyIds.erase(GameEventHookModule::FavoritePartyIds.begin() + i);
                            GameEventHookModule::SaveConfig();
                            break;
                        }
                        if (editingFav == i) {
                            ImGui::Separator();
                            const char* ptxt[] = {"Epic", "Steam"};
                            ImGui::Combo("Platform##edit", &editPlatform, ptxt, IM_ARRAYSIZE(ptxt));
                            ImGui::InputText("ID##edit", &editId);
                            ImGui::InputText("Title##edit", &editTitle);
                            if (ImGui::SmallButton("Save##fav")) {
                                if (!editId.empty()) {
                                    GameEventHookModule::FavoritePartyIds[i].platform = editPlatform;
                                    GameEventHookModule::FavoritePartyIds[i].id = editId;
                                    GameEventHookModule::FavoritePartyIds[i].title = editTitle;
                                    GameEventHookModule::SaveConfig();
                                    Main.SpawnNotification("KingMod", "Favorite updated", 2);
                                }
                                editingFav = -1;
                            }
                            ImGui::SameLine();
                            if (ImGui::SmallButton("Cancel##fav")) {
                                editingFav = -1;
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_CLOCK "  RECENT");
                    ImGui::BeginChild("##Recent", ImVec2(0, 120), true);
                    for (int i = 0; i < (int)GameEventHookModule::RecentPartyIds.size(); ++i) {
                        int plat = GameEventHookModule::RecentPartyIds[i].first;
                        std::string id = GameEventHookModule::RecentPartyIds[i].second;
                        std::string label = std::string(plat == 0 ? "Epic: " : "Steam: ") + id;
                        ImGui::Text("%s", label.c_str());
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("InviteR##") + std::to_string(i)).c_str())) {
                            int p = plat; std::string v = id;
                            Main.Execute([p, v]() {
                                try {
                                    UGFxData_PartyInvite_TA* party = Instances.GetInstanceOf<UGFxData_PartyInvite_TA>();
                                    if (!party) { Main.SpawnNotification("KingMod", "Party system not available", 3); return; }
                                    if (p == 0) {
                                        FUniqueNetId x{}; x.Platform = EOnlinePlatform::OnlinePlatform_Epic; x.SplitscreenID = 0; std::wstring w(v.begin(), v.end()); x.EpicAccountId = FString(w.c_str());
                                        party->InviteToParty(x); Main.SpawnNotification("KingMod", "Invite sent (Epic)", 3);
                                    } else {
                                        uint64_t uid = 0; try { uid = std::stoull(v); } catch (...) { uid = 0; }
                                        FUniqueNetId s{}; s.Platform = EOnlinePlatform::OnlinePlatform_Steam; s.Uid = uid; s.SplitscreenID = 0;
                                        party->InviteToParty(s); Main.SpawnNotification("KingMod", "Invite sent (Steam)", 3);
                                    }
                                } catch (...) { Main.SpawnNotification("KingMod", "Failed to send invite", 3); }
                            });
                        }
                        ImGui::SameLine();
                        if (ImGui::SmallButton((std::string("RequestR##") + std::to_string(i)).c_str())) {
                            int p = plat; std::string v = id;
                            Main.Execute([p, v]() {
                                try {
                                    UGFxData_PartyJoinRequest_TA* joinReq = Instances.GetInstanceOf<UGFxData_PartyJoinRequest_TA>();
                                    if (!joinReq) { Main.SpawnNotification("KingMod", "Join request system not available", 3); return; }
                                    if (p == 0) {
                                        FUniqueNetId x{}; x.Platform = EOnlinePlatform::OnlinePlatform_Epic; x.SplitscreenID = 0; std::wstring w(v.begin(), v.end()); x.EpicAccountId = FString(w.c_str());
                                        joinReq->SendJoinRequest(x); Main.SpawnNotification("KingMod", "Join request sent (Epic)", 3);
                                    } else {
                                        uint64_t uid = 0; try { uid = std::stoull(v); } catch (...) { uid = 0; }
                                        FUniqueNetId s{}; s.Platform = EOnlinePlatform::OnlinePlatform_Steam; s.Uid = uid; s.SplitscreenID = 0;
                                        joinReq->SendJoinRequest(s); Main.SpawnNotification("KingMod", "Join request sent (Steam)", 3);
                                    }
                                } catch (...) { Main.SpawnNotification("KingMod", "Failed to send join request", 3); }
                            });
                        }
                    }
                    ImGui::EndChild();
                    if (ImGui::Button(ICON_FA_USERS "  Leave Current Party", ImVec2(-1, 25))) {
                        Main.Execute([]() {
                            try {
                                UGFxData_Party_TA* party = Instances.GetInstanceOf<UGFxData_Party_TA>();
                                if (party) {
                                    party->LeaveParty();
                                    try { party->OnConfirmLeaveParty(nullptr); } catch (...) {}
                                    Main.SpawnNotification("KingMod", "Left current party", 3);
                                } else {
                                    Main.SpawnNotification("KingMod", "Party system not available", 3);
                                }
                            } catch (...) {
                                Main.SpawnNotification("KingMod", "Failed to leave party", 3);
                            }
                        });
                    }
                }

gui.end_group_box();
            }

                            
            else if (gui.m_tab == 5) {
                gui.group_box("Camera", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                    if (ImGui::Checkbox(ICON_FA_VIDEO "  Enable Camera Override", &Events.enableCameraSettings))
                    {
                        GameEventHookModule::SaveConfig();
                    }
                    ImGui::Spacing();

                    Events.RefreshCameraPresets();

                    static int selectedPresetIndex = -1;
                    if (ImGui::BeginCombo("Camera Preset##CameraPreset", selectedPresetIndex >= 0 && selectedPresetIndex < (int)Events.cameraPresets.size() ? Events.cameraPresets[selectedPresetIndex].c_str() : "Select Preset"))
                    {
                        for (int i = 0; i < (int)Events.cameraPresets.size(); i++)
                        {
                            bool isSelected = (selectedPresetIndex == i);
                            if (ImGui::Selectable(Events.cameraPresets[i].c_str(), isSelected))
                            {
                                selectedPresetIndex = i;
                                strncpy_s(Events.presetName, Events.cameraPresets[i].c_str(), sizeof(Events.presetName) - 1);
                            }
                            if (isSelected) ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }

                    ImGui::SliderFloat("Distance", &Events.cameraDistance, 100.0f, 500.0f, "%.0f");
                    ImGui::SliderFloat("Height", &Events.cameraHeight, 0.0f, 300.0f, "%.0f");
                    ImGui::SliderFloat("Angle (Pitch)", &Events.cameraAngle, -30.0f, 10.0f, "%.1f");
                    ImGui::SliderFloat("Stiffness", &Events.cameraStiffness, 0.0f, 1.0f, "%.2f");

                    ImGui::Spacing();
                    ImGui::InputText("Preset Name", Events.presetName, sizeof(Events.presetName));

                    if (ImGui::Button(ICON_FA_UNDO "  Save Preset", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 25)))
                    {
                        if (strlen(Events.presetName) > 0)
                        {
                            Events.SaveCameraPreset(Events.presetName);
                            Main.SpawnNotification("KingMod", "Camera preset saved: " + std::string(Events.presetName), 2);
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_UNDO "  Load Preset", ImVec2(ImGui::GetContentRegionAvail().x, 25)))
                    {
                        if (selectedPresetIndex >= 0 && selectedPresetIndex < (int)Events.cameraPresets.size())
                        {
                            Events.LoadCameraPreset(Events.cameraPresets[selectedPresetIndex]);
                            Main.SpawnNotification("KingMod", "Camera preset loaded: " + Events.cameraPresets[selectedPresetIndex], 2);
                        }
                    }
                    if (ImGui::Button(ICON_FA_UNDO "  Delete Preset", ImVec2(ImGui::GetContentRegionAvail().x, 25)))
                    {
                        if (selectedPresetIndex >= 0 && selectedPresetIndex < (int)Events.cameraPresets.size())
                        {
                            std::string nameToDelete = Events.cameraPresets[selectedPresetIndex];
                            Events.DeleteCameraPreset(nameToDelete);
                            selectedPresetIndex = -1;
                            strncpy_s(Events.presetName, "default", sizeof(Events.presetName) - 1);
                            Main.SpawnNotification("KingMod", "Camera preset deleted: " + nameToDelete, 2);
                        }
                    }
                gui.end_group_box();
            }

                          
            else if (gui.m_tab == 6) {
                gui.group_box("Ball", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                auto AddToggle = [&](const char* label, bool& value) {
                    if (ImGui::Checkbox(label, &value)) {
                        GameEventHookModule::SaveConfig();
                    }
                };

                auto AddToggleWithColor = [&](const char* label, bool& value, ImVec4& color) {
                                                                                    
                                                                                    
                                                                                     
                                                                            
                    ImGui::ColorEdit4((std::string("##Color") + label).c_str(), (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::SameLine();
                    if (ImGui::Checkbox(label, &value)) {
                        GameEventHookModule::SaveConfig();
                    }
                };

                                     
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                auto& settings = BallPrediction::GetSettings();

                                                                   
                auto HelpMarker = [](const char* desc) {
                    ImGui::TextDisabled("(?)");
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 25.0f);
                        ImGui::TextUnformatted(desc);
                        ImGui::PopTextWrapPos();
                        ImGui::EndTooltip();
                    }
                };

                                                                                 
                auto ColorRow = [](const char* label, FLinearColor& col) -> bool {
                    float c[4] = { col.R, col.G, col.B, col.A };
                    if (ImGui::ColorEdit4(label, c, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
                        col.R = c[0]; col.G = c[1]; col.B = c[2]; col.A = c[3];
                        return true;
                    }
                    return false;
                };

                const ImGuiStyle& bpStyle = ImGui::GetStyle();
                const float availX = ImGui::GetContentRegionAvail().x;
                const float colW   = (availX - bpStyle.ItemSpacing.x) * 0.5f;

                                                                                   
                                                                              
                                                                              
                                                                                   
                                                                                   
                                                                                  
                const float bpToggleH = ImGui::GetTextLineHeightWithSpacing();
                const float bpFrameH  = ImGui::GetFrameHeightWithSpacing();
                const float bpTitleH  = ImGui::GetTextLineHeightWithSpacing();
                const float bpSepH    = bpStyle.ItemSpacing.y * 2.0f + 1.0f;
                auto bpCardH = [&](int toggles, int frames) {
                    return bpStyle.WindowPadding.y * 2.0f + bpTitleH + bpSepH
                         + bpToggleH * (float)toggles + bpFrameH * (float)frames;
                };
                                                                                     
                const float bpMainH  = bpCardH(2, settings.bRainbow ? 2 : 1);
                const float bpGoalH  = bpCardH(1, 1);
                const float bpCrossH = bpCardH(1, 1);
                const float topH     = bpMainH + bpGoalH + bpCrossH + bpStyle.ItemSpacing.y * 2.0f + 4.0f;

                                                              
                ImGui::BeginChild("BPPresetsPanel", ImVec2(colW, topH), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SAVE "  PRESETS MANAGER");
                    ImGui::Separator();

                    static int  s_selPreset = -1;
                    static char s_presetName[64] = "";
                    std::vector<std::string> presets = BallPrediction::ListPresets();
                    std::string favorite = BallPrediction::GetFavorite();
                    if (s_selPreset >= (int)presets.size()) s_selPreset = -1;

                    if (ImGui::BeginListBox("##bppresets", ImVec2(-1, topH - 118))) {
                        for (int i = 0; i < (int)presets.size(); ++i) {
                            const bool isSel = (s_selPreset == i);
                            std::string label = (presets[i] == favorite)
                                ? (std::string(ICON_FA_STAR "  ") + presets[i])
                                : (std::string("       ") + presets[i]);
                            if (ImGui::Selectable(label.c_str(), isSel)) {
                                s_selPreset = i;
                                strncpy_s(s_presetName, presets[i].c_str(), _TRUNCATE);
                            }
                            if (isSel && ImGui::IsMouseDoubleClicked(0)) {
                                if (BallPrediction::LoadPreset(presets[i])) {
                                    GameEventHookModule::SaveConfig();
                                    Main.SpawnNotification("KingMod", "Preset loaded", 2);
                                }
                            }
                        }
                        ImGui::EndListBox();
                    }

                    {
                        const float bw = (ImGui::GetContentRegionAvail().x - bpStyle.ItemSpacing.x * 2.0f) / 3.0f;
                        const bool hasSel = (s_selPreset >= 0 && s_selPreset < (int)presets.size());
                        if (ImGui::Button(ICON_FA_CHECK_CIRCLE " Load", ImVec2(bw, 0)) && hasSel) {
                            if (BallPrediction::LoadPreset(presets[s_selPreset])) {
                                GameEventHookModule::SaveConfig();
                                Main.SpawnNotification("KingMod", "Preset loaded", 2);
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TRASH " Delete", ImVec2(bw, 0)) && hasSel) {
                            if (BallPrediction::DeletePreset(presets[s_selPreset])) {
                                s_selPreset = -1;
                                Main.SpawnNotification("KingMod", "Preset deleted", 2);
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_STAR " Favorite", ImVec2(bw, 0)) && hasSel) {
                            BallPrediction::SetFavorite(presets[s_selPreset]);
                            Main.SpawnNotification("KingMod", "Favorite set", 2);
                        }

                        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 64.0f - bpStyle.ItemSpacing.x);
                        ImGui::InputText("##bppresetname", s_presetName, sizeof(s_presetName));
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SAVE "  Save", ImVec2(64.0f, 0)) && s_presetName[0] != '\0') {
                            if (BallPrediction::SavePreset(s_presetName)) {
                                Main.SpawnNotification("KingMod", "Preset saved", 2);
                            }
                        }
                    }
                ImGui::EndChild();

                                                                        
                ImGui::SameLine();
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
                ImGui::BeginChild("BPRightCol", ImVec2(0, topH), false);
                ImGui::PopStyleVar();

                                      
                    ImGui::BeginChild("BPMain", ImVec2(0, bpMainH), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_ROUTE "  BALL PREDICTION");
                        ImGui::Separator();
                                                                                    
                                                                                  
                        if (ImGui::Checkbox(ICON_FA_ROUTE "  Enable Prediction##bpmain", &GameEventHookModule::BallPredictionEnabled)) settingsChanged = true;
                        if (ColorRow("Prediction Color", settings.cLineColor)) {
                            BallPrediction::UpdateColorFromPicker();
                            settingsChanged = true;
                        }
                                                                                     
                                                                                    
                                                                                    
                                                                              
                        ImGui::TextUnformatted(ICON_FA_RAINBOW "  Rainbow Prediction Color");
                        ImGui::SameLine();
                        if (ImGui::Checkbox("##bprainbow", &settings.bRainbow)) settingsChanged = true;
                                                                                   
                                                                                  
                                                                            
                        if (settings.bRainbow) {
                            if (KingSliderFloat("Rainbow Speed", &settings.fRainbowSpeed, 0.0f, 100.0f, "%.0f")) settingsChanged = true;
                        }
                    ImGui::EndChild();

                                              
                    ImGui::BeginChild("BPGoal", ImVec2(0, bpGoalH), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_BULLSEYE "  BALL PREDICTION IN GOAL");
                        ImGui::Separator();
                                                                                       
                        if (ImGui::Checkbox(ICON_FA_POWER_OFF "  Enable##bpgoal", &settings.bPredictGoal)) settingsChanged = true;
                        if (ColorRow("In-Goal Color", settings.cGoalColor)) settingsChanged = true;
                    ImGui::EndChild();

                                        
                    ImGui::BeginChild("BPCross", ImVec2(0, bpCrossH), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_CROSSHAIRS "  CROSSHAIR IN GOAL");
                        ImGui::Separator();
                                                                                       
                        if (ImGui::Checkbox(ICON_FA_POWER_OFF "  Enable##bpcross", &settings.bGoalCrosshair)) settingsChanged = true;
                        if (ColorRow("Crosshair Color", settings.cGoalCrosshairColor)) settingsChanged = true;
                    ImGui::EndChild();

                ImGui::EndChild();              

                                                                             
                ImGui::Spacing();
                ImGui::BeginChild("BPSettings", ImVec2(0, settings.bPreHitEnabled ? 390.0f : 250.0f), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SLIDERS_H "  BALL PREDICTION SETTINGS");
                    ImGui::Separator();

                    const float halfW = (ImGui::GetContentRegionAvail().x - bpStyle.ItemSpacing.x) * 0.5f;

                                                                         
                    ImGui::BeginChild("BPSetCore", ImVec2(halfW, 0), false);
                        ImGui::TextUnformatted("Drawing Style");
                        ImGui::SetNextItemWidth(-1);
                        if (ImGui::Combo("##bpdrawstyle", &settings.iDrawStyle, "Classic\0Dash\0Trail\0")) settingsChanged = true;

                        ImGui::Spacing();
                        int tr  = settings.iTickrate < 15 ? 15 : (settings.iTickrate > 120 ? 120 : settings.iTickrate);
                        int pts = (int)(settings.fPredictionTime * (float)tr) + 1;
                        ImGui::Text("Prediction Length: %.2fs  (~%d pts)", settings.fPredictionTime, pts);
                        ImGui::SetNextItemWidth(-1);
                        if (ImGui::SliderFloat("##bplength", &settings.fPredictionTime, 0.25f, 15.0f, "%.2fs")) {
                            settings.fMaxReach = settings.fPredictionTime;
                            BallPrediction::ForceRefresh();
                            settingsChanged = true;
                        }


                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_CAR "  CAR TOUCH PREDICTION");
                        ImGui::TextDisabled("Uses live body hitbox, speed, rotation, angular velocity, throttle, steer and boost state.");
                        if (ImGui::Checkbox(ICON_FA_ROUTE "  Predict imminent car touch", &settings.bPreHitEnabled))
                            settingsChanged = true;
                        if (settings.bPreHitEnabled)
                        {
                                                                             
                                                                          
                            int preHitModeUi = 0;
                            if (settings.iPreHitCarMode == 3) preHitModeUi = 1;
                            else if (settings.iPreHitCarMode == 1) preHitModeUi = 2;
                            else if (settings.iPreHitCarMode == 2) preHitModeUi = 3;

                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::Combo("##prehitcars", &preHitModeUi,
                                "All Cars\0Earliest Hit\0My Car Only\0Selected Car\0"))
                            {
                                static constexpr int kUiToPreHitMode[4] = { 0, 3, 1, 2 };
                                settings.iPreHitCarMode = kUiToPreHitMode[std::clamp(preHitModeUi, 0, 3)];
                                settingsChanged = true;
                            }

                            if (settings.iPreHitCarMode == 2)
                            {
                                int carSlot = settings.iPreHitSelectedCarIndex + 1;
                                ImGui::SetNextItemWidth(-1.0f);
                                if (ImGui::SliderInt("##prehitcarslot", &carSlot, 1, 24, "Selected car: %d"))
                                {
                                    settings.iPreHitSelectedCarIndex = carSlot - 1;
                                    settingsChanged = true;
                                }
                            }

                            ImGui::Text("Detection Distance: %.0f uu", settings.fPreHitMaxCarDistance);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::SliderFloat("##prehitdistance", &settings.fPreHitMaxCarDistance,
                                250.0f, 5000.0f, "%.0f uu")) settingsChanged = true;

                            ImGui::Text("Look Ahead: %.2fs", settings.fPreHitLookAhead);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::SliderFloat("##prehitlookahead", &settings.fPreHitLookAhead,
                                0.15f, 2.0f, "%.2fs")) settingsChanged = true;

                            ImGui::Text("Hitbox Tolerance: %.0f uu", settings.fPreHitHitboxPadding);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::SliderFloat("##prehithitboxpadding", &settings.fPreHitHitboxPadding,
                                0.0f, 80.0f, "%.0f uu")) settingsChanged = true;

                            const auto& impactNow = BallPrediction::GetPreHitPredictions();
                            if (!impactNow.empty())
                            {
                                const auto& impact = impactNow.front();
                                ImGui::TextColored(gui.accent_color.to_vec4(),
                                    "First touch: Car %d in %.2fs | car %.0f km/h | closing %.0f uu/s",
                                    impact.CarIndex + 1, impact.TimeToHit,
                                    impact.CarSpeed * 0.036f, impact.ClosingSpeed);
                                if (settings.iPreHitCarMode == 0 && impactNow.size() > 1)
                                    ImGui::TextDisabled("All Cars: %d reachable touches; main line follows the earliest.",
                                        (int)impactNow.size());
                                ImGui::TextDisabled(
                                    "Physics: %s%s | throttle %.2f | steer %.2f | hitbox %.0fx%.0fx%.0f",
                                    impact.OnGround ? "ground" : "air", impact.Boosting ? " + boost" : "",
                                    impact.Throttle, impact.Steer,
                                    impact.CarHitboxExtent.X * 2.0f, impact.CarHitboxExtent.Y * 2.0f, impact.CarHitboxExtent.Z * 2.0f);
                            }
                            else
                            {
                                ImGui::TextDisabled("No reachable car touch inside the selected range yet.");
                            }
                        }
                    ImGui::EndChild();

                    ImGui::SameLine();

                                                                             
                    ImGui::BeginChild("BPSetExtra", ImVec2(0, 0), false);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted("Tickrate"); ImGui::SameLine(); HelpMarker(
                            "Samples per second used to build the prediction line. "
                            "Higher = smoother and more accurate, at a small performance cost. "
                            "Capped at 120 (the physics tick rate).");
                        ImGui::SetNextItemWidth(-1);
                        if (ImGui::SliderInt("##bptickrate", &settings.iTickrate, 30, 120)) {
                            BallPrediction::ForceRefresh();
                            settingsChanged = true;
                        }

                        ImGui::TextUnformatted("Thickness");
                        ImGui::SetNextItemWidth(-1);
                        if (ImGui::SliderFloat("##bpthickness", &settings.fThickness, 0.5f, 10.0f, "%.1f")) settingsChanged = true;

                        ImGui::TextUnformatted("Opacity");
                        ImGui::SetNextItemWidth(-1);
                        if (ImGui::SliderFloat("##bpopacity", &settings.fOpacity, 0.0f, 1.0f, "%.2f")) settingsChanged = true;

                                                                                   
                                                                                  
                                                                                   
                        if (ImGui::Checkbox(ICON_FA_TACHOMETER_ALT "  Speed Color", &settings.bUseSpeedColor)) settingsChanged = true;
                        if (ImGui::Checkbox(ICON_FA_ROUTE "  Smoothing", &settings.bExtraSmoothing)) settingsChanged = true;
                    ImGui::EndChild();
                ImGui::EndChild();              

                                                                                                           
                ImGui::Spacing();
                if (ImGui::Checkbox(ICON_FA_EYE "  Show Line", &settings.bShowLine)) settingsChanged = true;
                if (ImGui::Checkbox(ICON_FA_DOT_CIRCLE "  Landing Marker", &settings.bShowLanding)) settingsChanged = true;
                if (ImGui::Checkbox(ICON_FA_DOT_CIRCLE "  Bounce Markers", &settings.bShowBounces)) settingsChanged = true;
                if (ImGui::Checkbox(ICON_FA_DOT_CIRCLE "  Time-to-Goal", &settings.bShowGoalTimer)) settingsChanged = true;
                ImGui::Spacing();
                if (ImGui::Button(ICON_FA_SYNC " Refresh")) {
                    BallPrediction::ForceRefresh();
                    Main.SpawnNotification("KingMod", "Ball prediction refreshed", 2);
                }
                }

                                  
                if (gui.m_active_subtab[gui.m_tab] == 1) {
                static float s_minimapH = 0.f;
                BeginFitSection(s_minimapH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_MAP "  MINIMAP");
                ImGui::Separator();
                
                AddToggle(ICON_FA_MAP "  Enable Minimap", GameEventHookModule::MinimapEnabled);
                if (GameEventHookModule::MinimapEnabled) {
                    ImGui::Indent(10);
                    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
                    if (ImGui::SliderFloat("Size", &GameEventHookModule::MinimapSize, 50.0f, 500.0f, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Alpha", &GameEventHookModule::MinimapAlpha, 0.0f, 1.0f, "%.2f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Left / Right##Mini", &GameEventHookModule::MinimapPos.x, 0.0f, displaySize.x, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##Mini", &GameEventHookModule::MinimapPos.y, 0.0f, displaySize.y, "%.0f")) settingsChanged = true;
                    
                                                                                     
                                                                                    
                                                                                      
                                                                                
                    if (ImGui::Checkbox(ICON_FA_FUTBOL "  Show Ball", &GameEventHookModule::MinimapShowBall)) settingsChanged = true;
                    if (ImGui::Checkbox(ICON_FA_EYE "  Show Players", &GameEventHookModule::MinimapShowPlayers)) settingsChanged = true;
                    if (ImGui::Checkbox(ICON_FA_USERS "  Team Colors", &GameEventHookModule::MinimapTeamColors)) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                EndFitSection(s_minimapH);
                }

                                                                                 
                                                                              
                                            
                if (gui.m_active_subtab[gui.m_tab] == 2) {
                static float s_ballVisH = 0.f, s_ballSpdH = 0.f;

                BeginFitSection(s_ballVisH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_FUTBOL "  BALL VISUALS");
                ImGui::Separator();
                ImGui::Spacing();

                if (ImGui::Checkbox(ICON_FA_CIRCLE_NOTCH "  3D Ball Sphere", &GameEventHookModule::Ball3DSphereEnabled)) settingsChanged = true;
                if (GameEventHookModule::Ball3DSphereEnabled) {
                    ImGui::Indent(10);
                    if (ImGui::ColorEdit4("Sphere Color", (float*)&GameEventHookModule::Ball3DSphereColor,
                                          ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) settingsChanged = true;
                    ImGui::Unindent(10);
                }

                EndFitSection(s_ballVisH);

                BeginFitSection(s_ballSpdH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_TACHOMETER_ALT "  BALL SPEED");
                ImGui::Separator();
                ImGui::Spacing();

                if (ImGui::Checkbox(ICON_FA_TACHOMETER_ALT "  Show Ball Speed", &GameEventHookModule::BallSpeedDisplayEnabled)) settingsChanged = true;
                if (GameEventHookModule::BallSpeedDisplayEnabled) {
                    ImGui::Indent(10);
                    ImVec2 dispSize = ImGui::GetIO().DisplaySize;
                    if (ImGui::Combo("Unit", &GameEventHookModule::BallSpeedUnit, "km/h\0mph\0uu/s\0")) settingsChanged = true;
                    if (ImGui::SliderFloat("Text Size##Spd", &GameEventHookModule::BallSpeedDisplaySize, 0.5f, 4.0f, "%.2f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Left / Right##Spd", &GameEventHookModule::BallSpeedDisplayX, 0.0f, dispSize.x, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##Spd", &GameEventHookModule::BallSpeedDisplayY, 0.0f, dispSize.y, "%.0f")) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                EndFitSection(s_ballSpdH);
                }


                if (settingsChanged) {
                    GameEventHookModule::SaveConfig();
                }


                gui.end_group_box();
            }

                          
                                                                                   
                                                                            
                                                                               
                                                                              
                                                                 
            else if (gui.m_tab == 7 || gui.m_tab == 10 || gui.m_tab == 11 ||
                     gui.m_tab == 12 || gui.m_tab == 13) {
                const char* pageTitle =
                    gui.m_tab == 10 ? "Car" :
                    gui.m_tab == 11 ? "Textures" :
                    gui.m_tab == 12 ? "World" :
                    gui.m_tab == 13 ? "Account" : "Game";
                gui.group_box(pageTitle, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                const int pgTab = gui.m_tab;
                const int pgSub = gui.m_active_subtab[gui.m_tab];
                const bool pgFeatures = (pgTab == 7  && pgSub == 0);
                const bool pgTitles   = (pgTab == 7  && pgSub == 1);
                const bool pgOverlays = (pgTab == 7  && pgSub == 2);
                const bool pgCarBody  = (pgTab == 10 && pgSub == 0);
                const bool pgWheels   = (pgTab == 10 && pgSub == 1);
                const bool pgPlates   = (pgTab == 10 && pgSub == 2);
                const bool pgTexBall   = (pgTab == 11 && pgSub == 0);
                const bool pgTexAvi    = (pgTab == 11 && pgSub == 1);
                const bool pgTexDecal  = (pgTab == 11 && pgSub == 2);
                const bool pgTexBanner = (pgTab == 11 && pgSub == 3);
                const bool pgTexBoost  = (pgTab == 11 && pgSub == 4);
                const bool pgTraining = (pgTab == 12 && pgSub == 0);
                const bool pgEffects  = (pgTab == 12 && pgSub == 1);
                const bool pgRocket   = (pgTab == 13 && pgSub == 0);
                const bool pgNetwork  = (pgTab == 13 && pgSub == 1);
                const bool pgAnyMoved = pgCarBody || pgWheels || pgPlates ||
                                        pgTexBall || pgTexAvi || pgTexDecal || pgTexBanner || pgTexBoost ||
                                        pgTraining || pgEffects || pgRocket || pgNetwork;

                auto AddToggle = [&](const char* label, bool& value) {
                    if (ImGui::Checkbox(label, &value)) {
                        GameEventHookModule::SaveConfig();
                    }
                };

                auto AddToggleWithColor = [&](const char* label, bool& value, ImVec4& color) {
                                                                                    
                                                                                    
                                                                                     
                                                                            
                    ImGui::ColorEdit4((std::string("##Color") + label).c_str(), (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::SameLine();
                    if (ImGui::Checkbox(label, &value)) {
                        GameEventHookModule::SaveConfig();
                    }
                };

                                   
                if (pgFeatures) {
                                    
                ImGui::SetWindowFontScale(1.3f);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_DATABASE "  DATA MANAGEMENT");
                ImGui::SetWindowFontScale(1.0f);
                ImGui::Spacing();
                
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Reset all inventory and player data:");
                if (ImGui::Button(ICON_FA_SYNC "  Sync Player Data", ImVec2(-1, 40))) {
                    Main.Execute([]() {
                        try {
                            USaveData_TA* saveData = Instances.GetSaveData();
                            if (saveData) {
                                                                                    
                                saveData->ForceResyncOnlineProducts();
                                saveData->ForceFetchOnlineProducts();

                         
                                Main.SpawnNotification("KingMod", "Player data synced from server", 5);
                            }
                            else {
                                Console.Error("[Data] SaveData not available");
                            }
                        }
                        catch (...) {
                            Console.Error("[Data] Exception during data sync");
                        }
                        });
                }
                
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                                                  
                ImGui::SetWindowFontScale(1.2f);
                ImVec4 headerColor = g_RedThemeColor;
                ImGui::TextColored(headerColor, "FEATURES");
                ImGui::SetWindowFontScale(1.0f);
                
                ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 0.9f), "Welcome to KingMod");
                ImGui::Spacing();
                ImGui::Separator();

                ImGui::SetWindowFontScale(1.1f);
                ImVec4 gameHeaderColor = g_RedThemeColor;
                ImGui::TextColored(gameHeaderColor, "GAME FEATURES");
                ImGui::SetWindowFontScale(1.0f);
                const bool localServerFeatures = Events.CanUseLocalServerFeatures();
                ImGui::TextColored(localServerFeatures ? ImVec4(0.35f, 0.88f, 0.58f, 1.0f) : ImVec4(1.0f, 0.48f, 0.42f, 1.0f),
                    localServerFeatures ? "Local server physics available" : "Server physics disabled in Casual and Ranked");
                ImGui::TextDisabled("Gravity, game speed and unlimited flips: World > Local Server / Extra > Freeplay");
                bool changed = false;
                changed |= ImGui::Checkbox(ICON_FA_FILM "  Skip Replays", &GameEventHookModule::SkipReplays);
                changed |= ImGui::Checkbox(ICON_FA_LIST "  Auto Queue", &GameEventHookModule::AutoQueueEnabled);
                
                if (GameEventHookModule::AutoQueueEnabled) {
                    ImGui::Indent(20);
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Queue Delay (seconds):");
                    changed |= ImGui::SliderInt("##QueueDelay", &GameEventHookModule::AutoQueueDelaySeconds, 0, 30);
                    ImGui::Unindent(20);
                }
                changed |= ImGui::Checkbox(ICON_FA_SIGN_OUT_ALT "  Auto Leave Match", &GameEventHookModule::AutoLeaveEnabled);

                if (GameEventHookModule::AutoLeaveEnabled) {
                    ImGui::Indent(20);
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Leave Delay (seconds):");
                    changed |= ImGui::SliderInt("##LeaveDelay", &GameEventHookModule::AutoLeaveDelaySeconds, 0, 30);
                    ImGui::Unindent(20);
                }
  
                if (changed) {
                    GameEventHookModule::SaveConfig();
                }

                ImGui::Spacing();
                ImGui::Separator();

                ImGui::SetWindowFontScale(1.1f);
                ImVec4 actionHeaderColor = g_RedThemeColor;
                ImGui::TextColored(actionHeaderColor, "GAME ACTIONS");
                ImGui::SetWindowFontScale(1.0f);
                
                if (ImGui::Button(ICON_FA_SYNC "  Reload Main Menu", ImVec2(-1, 25))) {
                    Main.Execute([]() {
                        Events.ReloadMainMenu();
                    });
                }
                
                if (ImGui::Button(ICON_FA_SYNC "  Reload Car Body Model", ImVec2(-1, 25))) {
                    Main.Execute([]() {
                        CustomCar::RefreshCarModel();
                    });
                }
                
                if (ImGui::Button(ICON_FA_SIGN_OUT_ALT "  Forfeit Match", ImVec2(-1, 25))) {
                    Main.Execute([]() {
                        Main.Forfeit();
                    });
                }

                ImGui::Spacing();
                ImGui::Separator();

                ImGui::SetWindowFontScale(1.1f);
                ImVec4 splitHeaderColor = g_RedThemeColor;
                ImGui::TextColored(splitHeaderColor, "SPLITSCREEN MANAGEMENT");
                ImGui::SetWindowFontScale(1.0f);
                if (ImGui::Button(ICON_FA_PLUS "  Add Splitscreen Player", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                    Main.Execute([]() {
                        Main.AddSplitscreenPlayer();
                    });
                }

                }

                                                                                   
                                                    
                if (pgOverlays) {
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                static float s_playerVisH = 0.f;
                BeginFitSection(s_playerVisH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_USER "  PLAYER VISUALS");
                ImGui::Separator();
                ImGui::Spacing();
                
                AddToggleWithColor(ICON_FA_PROJECT_DIAGRAM "  Draw Tracers", GameEventHookModule::TracersEnabled, GameEventHookModule::TracersColor);
                if (GameEventHookModule::TracersEnabled) {
                    ImGui::Indent(10);
                    if (ImGui::Checkbox(ICON_FA_USERS "  Use Team Colors", &GameEventHookModule::UseTeamColorsForTracers)) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                
                AddToggleWithColor(ICON_FA_VECTOR_SQUARE "  Draw Car Hitboxes", GameEventHookModule::Hitboxes, GameEventHookModule::HitboxColor);
                
                AddToggleWithColor(ICON_FA_RULER "  Player Distance", GameEventHookModule::PlayerDistanceTextEnabled, GameEventHookModule::PlayerDistanceTextColor);
                
                AddToggleWithColor(ICON_FA_FIRE "  Opponent Boost", GameEventHookModule::OpponentBoostEnabled, GameEventHookModule::OpponentBoostColor);
                if (GameEventHookModule::OpponentBoostEnabled) {
                    ImGui::Indent(10);
                    if (ImGui::SliderFloat("Scale", &GameEventHookModule::OpponentBoostScale, 0.5f, 3.0f, "%.1fx")) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                
                AddToggle(ICON_FA_PROJECT_DIAGRAM "  Velocity Arrows", GameEventHookModule::VelocityArrowsEnabled);
                if (GameEventHookModule::VelocityArrowsEnabled) {
                    ImGui::Indent(10);
                    ImGui::ColorEdit4("Ball Arrow Color", (float*)&GameEventHookModule::VelocityArrowBallColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::ColorEdit4("Car Arrow Color", (float*)&GameEventHookModule::VelocityArrowCarColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::Unindent(10);
                }
                EndFitSection(s_playerVisH);
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                static float s_genVisH = 0.f;
                BeginFitSection(s_genVisH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_LAYER_GROUP "  GENERAL & OVERLAYS");
                ImGui::Separator();
                ImGui::Spacing();
                
                                    
                
                                 
                if (ImGui::Checkbox(ICON_FA_SYNC "  Flip Indicator", &GameEventHookModule::FlipIndicatorEnabled)) {
                    settingsChanged = true;
                    GameEventHookModule::SaveConfig();
                }
                if (GameEventHookModule::FlipIndicatorEnabled) {
                    ImGui::Indent(10);
                    if (ImGui::SliderFloat("Size", &GameEventHookModule::FlipIndicatorSize, 0.5f, 5.0f, "%.1f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Left / Right##FlipX", &GameEventHookModule::FlipIndicatorPos.x, 0.0f, 1.0f, "%.2f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##FlipY", &GameEventHookModule::FlipIndicatorPos.y, 0.0f, 1.0f, "%.2f")) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                
                                   
                AddToggle(ICON_FA_FIRE "  BoostPad Timers", GameEventHookModule::BoostPadTimers);
                if (GameEventHookModule::BoostPadTimers) {
                    ImGui::Indent(10);
                    if (ImGui::SliderFloat("Marker Size", &GameEventHookModule::BoostPadMarkerScale, 0.5f, 3.0f, "%.2fx")) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                
                             
                AddToggle(ICON_FA_FUTBOL "  Ball Speed", GameEventHookModule::BallSpeedDisplayEnabled);
                if (GameEventHookModule::BallSpeedDisplayEnabled) {
                    ImGui::Indent(10);
                    if (ImGui::SliderFloat("Size##Speed", &GameEventHookModule::BallSpeedDisplaySize, 0.5f, 3.0f, "%.2fx")) settingsChanged = true;
                    if (ImGui::SliderFloat("Left / Right##Speed", &GameEventHookModule::BallSpeedDisplayX, 0.0f, 1.0f, "%.2f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##Speed", &GameEventHookModule::BallSpeedDisplayY, 0.0f, 1.0f, "%.2f")) settingsChanged = true;
                    ImGui::Unindent(10);
                }
                
                                     
                AddToggle(ICON_FA_GAMEPAD "  Controller", GameEventHookModule::ControllerOverlay);
                if (GameEventHookModule::ControllerOverlay) {
                    ImGui::Indent(10);
                    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
                    if (ImGui::SliderFloat("Left / Right##Cont", &GameEventHookModule::ControllerOverlayPos.x, 0.0f, displaySize.x, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##Cont", &GameEventHookModule::ControllerOverlayPos.y, 0.0f, displaySize.y, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Alpha##Cont", &GameEventHookModule::ControllerOverlayAlpha, 0.0f, 0.8f, "%.2f")) settingsChanged = true;
                    ImGui::Unindent(10);
                }

                                   
                AddToggle(ICON_FA_KEYBOARD "  Keyboard Overlay", GameEventHookModule::KeyboardOverlay);
                if (GameEventHookModule::KeyboardOverlay) {
                    ImGui::Indent(10);
                    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
                    if (ImGui::SliderFloat("Left / Right##Key", &GameEventHookModule::KeyboardOverlayPos.x, 0.0f, displaySize.x, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Up / Down##Key", &GameEventHookModule::KeyboardOverlayPos.y, 0.0f, displaySize.y, "%.0f")) settingsChanged = true;
                    if (ImGui::SliderFloat("Alpha##Key", &GameEventHookModule::KeyboardOverlayAlpha, 0.0f, 0.8f, "%.2f")) settingsChanged = true;
                    ImGui::Unindent(10);
                }

                EndFitSection(s_genVisH);
                }

                                 
                if (pgTitles) {
                    if (s_titleViewMode == 0) {

                ImGui::BeginChild("TitlesBrowserPanel", ImVec2(0, 210), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

                ImGui::SetWindowFontScale(1.1f);
                ImVec4 titleBrowserColor = g_RedThemeColor;
                ImGui::TextColored(titleBrowserColor, "TITLES BROWSER");
                ImGui::SetWindowFontScale(1.0f);

                                                 
                static ImGuiTextFilter titlefilter; titlefilter.Draw("Search Titles");
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Titles:");
                if (ImGui::BeginListBox("##TitlesList", ImVec2(-1, 120)))
                {
                    for (int n = 0; n < Titles.TitlesForImGui.size(); n++)
                    {
                        const bool IsSelected = (Titles.selectedTitleForSpawn.titleid == Titles.TitlesForImGui[n].titleid);
                        if (Titles.TitlesForImGui[n].titletext != "" && Titles.TitlesForImGui[n].titletext != "null") {
                            if (titlefilter.PassFilter(Titles.TitlesForImGui[n].titletext.c_str()))
                            {
                                ImGui::PushID(n);

                                                                                                   

                                                                      
                                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(
                                    Titles.TitlesForImGui[n].titlecolor.R,
                                    Titles.TitlesForImGui[n].titlecolor.G,
                                    Titles.TitlesForImGui[n].titlecolor.B,
                                    255                                       
                                ));

                                if (ImGui::Selectable(Titles.TitlesForImGui[n].titletext.c_str(), IsSelected, ImGuiSelectableFlags_SelectOnClick))
                                {
                                    Titles.selectedTitleForSpawn = Titles.TitlesForImGui[n];
                                }

                                                             
                                if (IsSelected) {
                                    ImGui::SetItemDefaultFocus();
                                }

                                ImGui::PopStyleColor();
                                ImGui::PopID();
                            }
                        }
                    }
                    ImGui::EndListBox();
                }
                ImGui::EndChild();

                ImGui::Spacing();

                ImGui::BeginChild("TitleSpawnerPanel", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

                                        
                ImGui::SetWindowFontScale(1.1f);
                ImVec4 titleSpawnerColor = g_RedThemeColor;
                ImGui::TextColored(titleSpawnerColor, "TITLE SPAWNER");
                ImGui::SetWindowFontScale(1.0f);

                const bool hasSelectedTitle = !Titles.selectedTitleForSpawn.titleid.empty();
                ImGui::TextDisabled("Selected title: %s", hasSelectedTitle ? Titles.selectedTitleForSpawn.titletext.c_str() : "Choose a title above");

                                            
                static char titleSpawnMessage[256] = "";
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Spawn Message:");
                ImGui::InputText("##TitleSpawnMessage", titleSpawnMessage, IM_ARRAYSIZE(titleSpawnMessage));

                                           
                static bool showTitleAnimation = true;
                ImGui::Checkbox(ICON_FA_CROWN "  Show Title Animation", &showTitleAnimation);

                ImGui::Spacing();

                                     
                if (!hasSelectedTitle) ImGui::BeginDisabled();
                if (ImGui::Button(ICON_FA_CROWN "  Spawn Selected Title", ImVec2(-1, 0))) {
                    Main.Execute([=]() {
                        try {
                                                  
                            USaveData_TA* saveData = Instances.GetSaveData();
                            if (!saveData) {
                                Console.Error("[Titles] SaveData not available");
                                return;
                            }

                                                                   
                            FOnlineProductData productData;
                            productData.ProductID = 3036;                    
                            productData.SeriesID = 0;
                            productData.InstanceID = Items.GeneratePIID(3036);
                            productData.TradeHold = 0;
                            productData.AddedTimestamp = Items.GetTimestampLong();

                                                        
                            TArray<FOnlineProductAttribute> attributes;
                            attributes.push_back({ L"TitleId", Format::ToFString(Titles.selectedTitleForSpawn.titleid) });
                            productData.Attributes = attributes;

                                                               
                            UOnlineProduct_TA* product = saveData->GiveOnlineProductData(productData, FString(L""), 0.0f, false);
                            if (product) {
                                Main.SpawnNotification("KingMod", "Spawned: " + Titles.selectedTitleForSpawn.titleid, 3);
                            }
                            else {
                                Console.Error("[Titles] Failed to spawn title: " + Titles.selectedTitleForSpawn.titleid);
                            }
                        }
                        catch (...) {
                            Console.Error("[Titles] Exception spawning title");
                        }
                        });
                }
                if (!hasSelectedTitle) ImGui::EndDisabled();

                ImGui::Spacing();
                
                if (ImGui::Button(ICON_FA_CROWN "  Reload All Titles", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                    Main.Execute([]() {
                        Titles.TitlesForImGui.clear();
                        Titles.LoadAllTitle();
                        Main.SpawnNotification("KingMod", "Reloaded all titles", 3);
                    });
                }

                ImGui::Spacing();

                                                                                
                static int titleSpawnIndex = 0;
                static bool isSpawningAllTitles = false;
                static float spawnTimer = 0.0f;
                static int totalSpawned = 0;
                static const float SPAWN_DELAY = 0.01f;                             

                if (!isSpawningAllTitles) {
                    if (ImGui::Button(ICON_FA_CROWN "  SPAWN ALL TITLES (Async)", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        titleSpawnIndex = 0;
                        totalSpawned = 0;
                        isSpawningAllTitles = true;
                        spawnTimer = 0.0f;
                        Main.SpawnNotification("KingMod", "Starting title spawn process...", 2);
                    }
                }
                else {
                                    
                    int totalTitles = 0;
                    for (const auto& title : Titles.TitlesForImGui) {
                        if (!title.titletext.empty() && title.titletext != "null") {
                            totalTitles++;
                        }
                    }

                    float progress = totalTitles > 0 ? (float)totalSpawned / (float)totalTitles : 0.0f;

                    ImGui::ProgressBar(progress, ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, 0),
                        ("Spawning: " + std::to_string(totalSpawned) + "/" + std::to_string(totalTitles)).c_str());

                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_STOP "  Stop", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        isSpawningAllTitles = false;
                        titleSpawnIndex = 0;
                        std::string stopMsg = "Stopped at " + std::to_string(totalSpawned) + " titles";
                        Main.SpawnNotification("KingMod", stopMsg, 3);
                    }

                                                      
                    spawnTimer += ImGui::GetIO().DeltaTime;
                    if (spawnTimer >= SPAWN_DELAY) {
                        spawnTimer = 0.0f;

                                                         
                        bool foundTitle = false;
                        while (titleSpawnIndex < Titles.TitlesForImGui.size() && !foundTitle) {
                            if (!Titles.TitlesForImGui[titleSpawnIndex].titletext.empty() &&
                                Titles.TitlesForImGui[titleSpawnIndex].titletext != "null") {

                                                                  
                                Main.Execute([=]() {
                                    try {
                                        USaveData_TA* saveData = Instances.GetSaveData();
                                        if (saveData) {
                                                                            
                                            FOnlineProductData productData;
                                            productData.ProductID = 3036;                    
                                            productData.SeriesID = 0;
                                            productData.InstanceID = Items.GeneratePIID(3036);
                                            productData.TradeHold = 0;
                                            productData.AddedTimestamp = Items.GetTimestampLong();

                                                                        
                                            TArray<FOnlineProductAttribute> attributes;
                                            attributes.push_back({ L"TitleId", Format::ToFString(Titles.TitlesForImGui[titleSpawnIndex].titleid) });
                                            productData.Attributes = attributes;

                                                              
                                            UOnlineProduct_TA* product = saveData->GiveOnlineProductData(productData, FString(L""), 0.0f, false);
                                            if (product) {
                                                totalSpawned++;
                                            }
                                        }
                                    }
                                    catch (...) {
                                                            
                                    }
                                    });

                                foundTitle = true;
                            }
                            titleSpawnIndex++;
                        }

                                              
                        if (titleSpawnIndex >= Titles.TitlesForImGui.size()) {
                            isSpawningAllTitles = false;
                            titleSpawnIndex = 0;
                            std::string completeMsg = "Completed! Spawned " + std::to_string(totalSpawned) + " titles";
                            Main.SpawnNotification("KingMod", completeMsg, 5);
                        }
                    }
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                
                ImGui::EndChild();
                
                    }
                    else {
                        ImGui::BeginChild(
                            "CustomTitleOnlyPanel",
                            ImVec2(0, 0),
                            true,
                            ImGuiWindowFlags_AlwaysUseWindowPadding);

                        ImGui::SetWindowFontScale(1.12f);
                        ImGui::TextColored(
                            g_RedThemeColor,
                            ICON_FA_CROWN "  CUSTOM TITLE");
                        ImGui::SetWindowFontScale(1.0f);
                        ImGui::TextDisabled(
                            "Edit the custom title directly here. Normal title inventory tools are in the Titles tab.");
                        ImGui::Separator();
                        ImGui::Spacing();

                        if (ImGui::Checkbox("Enable Custom Title", &Events.setcustomtitle))
                        GameEventHookModule::SaveConfig();
                    ImGui::TextDisabled("LAN/hosted sessions sync title text and colors to other KingMod clients.");
                    ImGui::Spacing();
                                       
                    ImGui::Text("Title Text:");
                    static char titleBuffer[128] = "";

                                                                
                    if (Events.titletext != std::string(titleBuffer)) {
                        strncpy_s(titleBuffer, Events.titletext.c_str(), sizeof(titleBuffer) - 1);
                    }

                    if (ImGui::InputText("##CustomTitleText", titleBuffer, sizeof(titleBuffer))) {
                        Events.titletext = std::string(titleBuffer);
                        Events.setcustomtitle = !Events.titletext.empty();
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit()) GameEventHookModule::SaveConfig();

                    ImGui::Spacing();

                                         
                    ImGui::Text("Title Color:");
                    float titleColorFloat[3] = {
                        ((Events.titlecolor >> 16) & 0xFF) / 255.0f,
                        ((Events.titlecolor >> 8) & 0xFF) / 255.0f,
                        (Events.titlecolor & 0xFF) / 255.0f
                    };

                    if (ImGui::ColorEdit3("##TitleColor", titleColorFloat, ImGuiColorEditFlags_NoInputs)) {
                        Events.titlecolor = ((int)(titleColorFloat[0] * 255) << 16) |
                            ((int)(titleColorFloat[1] * 255) << 8) |
                            (int)(titleColorFloat[2] * 255);
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit()) GameEventHookModule::SaveConfig();

                    ImGui::Spacing();

                                        
                    ImGui::Text("Glow Color:");
                    float glowColorFloat[3] = {
                        ((Events.titleglowcolor >> 16) & 0xFF) / 255.0f,
                        ((Events.titleglowcolor >> 8) & 0xFF) / 255.0f,
                        (Events.titleglowcolor & 0xFF) / 255.0f
                    };

                    if (ImGui::ColorEdit3("##GlowColor", glowColorFloat, ImGuiColorEditFlags_NoInputs)) {
                        Events.titleglowcolor = ((int)(glowColorFloat[0] * 255) << 16) |
                            ((int)(glowColorFloat[1] * 255) << 8) |
                            (int)(glowColorFloat[2] * 255);
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit()) GameEventHookModule::SaveConfig();

                    ImGui::Spacing();

                                   
                    if (ImGui::Button(ICON_FA_CROWN "  Reset Title", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        Events.titletext = "";
                        Events.titlecolor = 0xFFFFFF;
                        Events.titleglowcolor = 0x000000;
                        Events.setcustomtitle = false;
                        memset(titleBuffer, 0, sizeof(titleBuffer));
                        GameEventHookModule::SaveConfig();
                        Main.SpawnNotification("KingMod", "Title reset to defaults!", 3);

                    }

                    ImGui::Spacing();

                                                                                     
                    if (ImGui::Button(ICON_FA_CROWN "  Spawn Custom Title", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        const std::string titleToSpawn = titleBuffer;
                        Events.titletext = titleToSpawn;
                        Events.setcustomtitle = !titleToSpawn.empty();
                        GameEventHookModule::SaveConfig();
                        Main.Execute([titleToSpawn]() {
                            CustomTitleWheel::SpawnCustomTitle(titleToSpawn.c_str());
                        });
                    }

                        ImGui::EndChild();
                    }
                }

                                                                                  
                                                                                   
                if (pgAnyMoved) {
                                                                                  
                                                                                   
                                                                      
                if (pgCarBody)
                {
                    if (ImGui::Button(ICON_FA_CROWN "  Premium Garage"))
                        Events.premium_garage_active = true;
                    ImGui::Spacing();
                }

                if (pgCarBody && SectionHeader(ICON_FA_ARROWS_ALT "  CAR POSITION(Lobby)"))
                {
                    ImGui::Indent(15.0f);
                    
                    bool posChanged = false;
                    posChanged |= ImGui::DragFloat("X Position", &Events.carPositionX, 10.0f);
                    posChanged |= ImGui::DragFloat("Y Position", &Events.carPositionY, 10.0f);
                    posChanged |= ImGui::DragFloat("Z Position", &Events.carPositionZ, 10.0f);
                    
                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_SYNC "  Rotation");
                    posChanged |= ImGui::DragFloat("Pitch (Up/Down)", &Events.carRotationPitch, 1.0f, -180.0f, 180.0f, "%.1f deg");
                    posChanged |= ImGui::DragFloat("Yaw (Left/Right)", &Events.carRotationYaw, 1.0f, -180.0f, 180.0f, "%.1f deg");
                    
                    if (posChanged) {
                        Main.Execute([]() {
                            UOnline_X* online_x = Instances.GetInstanceOf<UOnline_X>();
                            bool inMenu = (online_x && online_x->IsInMainMenu());
                            if (!inMenu) return;

                            FVector loc = { Events.carPositionX, Events.carPositionY, Events.carPositionZ };
                            FRotator rot;
                            rot.Pitch = static_cast<int>(Events.carRotationPitch * 182.044f);
                            rot.Yaw = static_cast<int>(Events.carRotationYaw * 182.044f);
                            rot.Roll = 0;

                            UGFxData_Garage_TA* garageGFX = Instances.GetInstanceOf<UGFxData_Garage_TA>();
                            if (garageGFX && garageGFX->CarPreviewSet) {
                                UCarPreviewSet_TA* previewSet = garageGFX->CarPreviewSet;
                                ACarPreviewActor_TA* previewactor = previewSet->GetPlayerCarPreviewActor(Instances.IULocalPlayer());
                                if (!previewactor && previewSet->CarPreviewActors.size() > 0) {
                                    previewactor = previewSet->CarPreviewActors[0];
                                }
                                if (previewactor) {
                                    previewactor->SetLocation(loc);
                                    previewactor->SetRotation(rot);
                                }
                            }
                        });
                    }
                    
                    ImGui::Unindent();
                }

                if (pgCarBody && SectionHeader(ICON_FA_EXPAND "  CAR SCALE"))
                {
                    ImGui::Indent(15.0f);

                    if (ImGui::SliderFloat("Scale", &Events.carScale, 0.1f, 5.0f)) {
                        Main.Execute([]() {
                            APlayerController* pc = Instances.IAPlayerController();
                            if (pc && pc->Pawn) {
                                pc->Pawn->DrawScale = Events.carScale;
                                                                         
                                APRI_TA* pri = static_cast<APRI_TA*>(pc->PlayerReplicationInfo);
                                if (pri) {
                                    std::string currentTitle = pri->Title.ToString();
                                                                     
                                    size_t scalePos = currentTitle.find("KINGMOD_SCALE:");
                                    if (scalePos != std::string::npos) {
                                        size_t scaleEnd = currentTitle.find(";", scalePos);
                                        if (scaleEnd != std::string::npos) {
                                            currentTitle.erase(scalePos, scaleEnd - scalePos + 1);
                                        } else {
                                            currentTitle.erase(scalePos);
                                        }
                                    }
                                                             
                                    if (Events.carScale != 1.0f) {
                                        currentTitle += "KINGMOD_SCALE:" + std::to_string(Events.carScale) + ";";
                                    }
                                    std::wstring wideCurrentTitle(currentTitle.begin(), currentTitle.end());
                                    pri->Title = FName(wideCurrentTitle.c_str());
                                }
                            }
                        });
                    }
                    if (ImGui::Button(ICON_FA_UNDO "  Reset Scale")) {
                        Events.carScale = 1.0f;
                        Main.Execute([]() {
                            APlayerController* pc = Instances.IAPlayerController();
                            if (pc && pc->Pawn) {
                                pc->Pawn->DrawScale = 1.0f;
                                                                   
                                APRI_TA* pri = static_cast<APRI_TA*>(pc->PlayerReplicationInfo);
                                if (pri) {
                                    std::string currentTitle = pri->Title.ToString();
                                    size_t scalePos = currentTitle.find("KINGMOD_SCALE:");
                                    if (scalePos != std::string::npos) {
                                        size_t scaleEnd = currentTitle.find(";", scalePos);
                                        if (scaleEnd != std::string::npos) {
                                            currentTitle.erase(scalePos, scaleEnd - scalePos + 1);
                                        } else {
                                            currentTitle.erase(scalePos);
                                        }
                                        std::wstring wideCurrentTitle(currentTitle.begin(), currentTitle.end());
                                        pri->Title = FName(wideCurrentTitle.c_str());
                                    }
                                }
                            }
                        });
                    }

                    ImGui::Unindent();
                }
                if (pgEffects && SectionHeader(ICON_FA_MAGIC "  EFFECTS"))
                {
                    ImGui::Indent(15.0f);

                    if (ImGui::Checkbox(ICON_FA_BOMB "  Remove Demo Smoke", &GameEventHookModule::RemoveDemoSmoke))
                        GameEventHookModule::SaveConfig();

                    if (ImGui::Checkbox(ICON_FA_BOMB "  Remove Goal Explosion", &GameEventHookModule::RemoveGoalExplosion))
                        GameEventHookModule::SaveConfig();

                    ImGui::Unindent();
                }
                if (pgWheels && SectionHeader(ICON_FA_COG "  WHEEL CUSTOMIZATION")) {
                    ImGui::Indent(8.0f);
                    ImGui::Spacing();

                    ImGui::TextColored(g_RedThemeColor, ICON_FA_EXPAND "  Size");
                    ImGui::Separator();
                    KingSliderFloat("Width", &Events.wheelWidth, 0.1f, 3.0f, "%.2f");
                    KingSliderFloat("Height", &Events.wheelHeight, 0.1f, 3.0f, "%.2f");
                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_DHARMACHAKRA "  Set Wheel Size")) {
                        Events.wheelSizeState = 1;
                        GameEventHookModule::SaveConfig();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_DHARMACHAKRA "  Reset Wheels")) {
                        Events.wheelSizeState = 3;
                        GameEventHookModule::SaveConfig();
                    }

                    ImGui::Spacing();
                    ImGui::Spacing();

                    ImGui::TextColored(g_RedThemeColor, ICON_FA_ARROWS_ALT "  Translation & Camber");
                    ImGui::Separator();

                                                                              
                                                                               
                                                                                
                                                                               
                    ImGui::Text("Apply To:");
                    ImGui::SameLine();
                    ImGui::RadioButton("All", &Events.wheelTarget, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Front", &Events.wheelTarget, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Rear", &Events.wheelTarget, 2);

                                                                                
                                                                                 
                    const bool editAll = (Events.wheelTarget == 0);
                    const int editSide = (Events.wheelTarget == 2) ? 1 : 0;

                    float editY = Events.wheelOffsetY[editSide];
                    float editZ = Events.wheelOffsetZ[editSide];
                    float editRoll = Events.wheelRoll[editSide];

                                                                                 
                                                                              
                    bool offsetChanged = false;
                    offsetChanged |= KingSliderFloat("Left / Right", &editY, -50.0f, 50.0f, "%.1f");
                    offsetChanged |= KingSliderFloat("Up / Down", &editZ, -30.0f, 30.0f, "%.1f");
                    offsetChanged |= KingSliderFloat("Roll (Camber)", &editRoll, -45.0f, 45.0f, "%.1f");
                    if (offsetChanged) {
                                                                            
                        if (editAll) {
                            Events.wheelOffsetY[0] = Events.wheelOffsetY[1] = editY;
                            Events.wheelOffsetZ[0] = Events.wheelOffsetZ[1] = editZ;
                            Events.wheelRoll[0]    = Events.wheelRoll[1]    = editRoll;
                        } else {
                            Events.wheelOffsetY[editSide] = editY;
                            Events.wheelOffsetZ[editSide] = editZ;
                            Events.wheelRoll[editSide]    = editRoll;
                        }
                        Events.wheelOffsetActive = true;
                    }
                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_UNDO "  Reset Offsets")) {
                                                                                 
                                                                      
                        if (editAll || Events.wheelTarget == 1) {
                            Events.wheelOffsetY[0] = Events.wheelOffsetZ[0] = Events.wheelRoll[0] = 0.0f;
                        }
                        if (editAll || Events.wheelTarget == 2) {
                            Events.wheelOffsetY[1] = Events.wheelOffsetZ[1] = Events.wheelRoll[1] = 0.0f;
                        }
                        Events.wheelOffsetState = 3;
                        GameEventHookModule::SaveConfig();
                    }

                                                                       
                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_FOLDER "  Configs");
                    ImGui::Separator();
                    ImGui::SetNextItemWidth(160.0f);
                    ImGui::InputText("##wheelCfgName", Events.wheelConfigName, sizeof(Events.wheelConfigName));
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_SAVE "  Save##wheelCfg")) {
                        if (Events.wheelConfigName[0])
                            Events.SaveWheelConfig(Events.wheelConfigName);
                    }

                    static std::vector<std::string> s_wheelCfgs;
                    static int s_wheelCfgSel = -1;
                    if (ImGui::Button(ICON_FA_SYNC "  Refresh##wheelCfg")) {
                        s_wheelCfgs = Events.ListWheelConfigs();
                        s_wheelCfgSel = -1;
                    }
                    if (s_wheelCfgs.empty())
                        s_wheelCfgs = Events.ListWheelConfigs();

                    ImGui::SetNextItemWidth(160.0f);
                    const char* preview = (s_wheelCfgSel >= 0 && s_wheelCfgSel < (int)s_wheelCfgs.size())
                        ? s_wheelCfgs[s_wheelCfgSel].c_str() : "Select config";
                    if (ImGui::BeginCombo("##wheelCfgList", preview)) {
                        for (int i = 0; i < (int)s_wheelCfgs.size(); ++i) {
                            bool sel = (s_wheelCfgSel == i);
                            if (ImGui::Selectable(s_wheelCfgs[i].c_str(), sel))
                                s_wheelCfgSel = i;
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Load##wheelCfg")) {
                        if (s_wheelCfgSel >= 0 && s_wheelCfgSel < (int)s_wheelCfgs.size()) {
                            Events.LoadWheelConfig(s_wheelCfgs[s_wheelCfgSel]);
                            Events.wheelOffsetActive = true;
                        }
                    }

                    ImGui::Spacing();
                    ImGui::Unindent(8.0f);
                }

                static SimpleImGuiFileBrowser fileBrowser;
                static int textureTarget = 0;                                                                                            

                if (pgPlates && SectionHeader(ICON_FA_ID_CARD "  LICENSE PLATES")) {
                    ImGui::Indent(8.0f);
                    ImGui::Spacing();

                                                                               
                                                                                
                    bool plateSettingsChanged = false;

                    auto plateControls = [&](const char* title, bool front) {
                        ImGui::PushID(front ? "plateFront" : "plateRear");
                        ImGui::TextColored(g_RedThemeColor, "%s", title);
                        ImGui::Separator();

                        bool* enabled       = front ? &Items.plateFrontEnabled : &Items.plateRearEnabled;
                        char* pathBuf       = front ? Items.plateFrontImagePath : Items.plateRearImagePath;
                        float* bg           = front ? Items.plateFrontBgColor   : Items.plateRearBgColor;
                        float* off          = front ? Items.plateFrontOffset    : Items.plateRearOffset;
                        float* roll         = front ? &Items.plateFrontRoll     : &Items.plateRearRoll;
                        float* pitch        = front ? &Items.plateFrontPitch    : &Items.plateRearPitch;
                        float* yaw          = front ? &Items.plateFrontYaw      : &Items.plateRearYaw;
                        float* width        = front ? &Items.plateFrontWidth    : &Items.plateRearWidth;
                        float* height       = front ? &Items.plateFrontHeight   : &Items.plateRearHeight;
                        bool*  dirty        = front ? &Items.plateFrontDirty     : &Items.plateRearDirty;

                        if (ImGui::Checkbox(ICON_FA_POWER_OFF "  Enable", enabled)) { *dirty = true; plateSettingsChanged = true; }

                        ImGui::Text("Image: %s", pathBuf[0] ? pathBuf : "(none)");
                        if (ImGui::Button(ICON_FA_IMAGE "  Select Image (.png)")) {
                            textureTarget = front ? 3 : 4;
                            fileBrowser.ClearAllowedExtensions();
                            fileBrowser.SetTitle(front ? "Select Front Plate Image" : "Select Rear Plate Image");
                            fileBrowser.Open();
                        }

                        if (ImGui::ColorEdit4("Background", bg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar))
                            { *dirty = true; plateSettingsChanged = true; }

                        plateSettingsChanged |= KingSliderFloat("Width",  width,  0.01f, 1.0f, "%.3f");
                        plateSettingsChanged |= KingSliderFloat("Height", height, 0.01f, 1.0f, "%.3f");
                                                                                   
                        plateSettingsChanged |= KingSliderFloat("Forward / Back", &off[0], -100.0f, 100.0f, "%.1f");
                        plateSettingsChanged |= KingSliderFloat("Left / Right",   &off[1], -100.0f, 100.0f, "%.1f");
                        plateSettingsChanged |= KingSliderFloat("Up / Down",      &off[2], -100.0f, 100.0f, "%.1f");
                                                                    
                        plateSettingsChanged |= KingSliderFloat("Tilt Forward / Back", pitch, -180.0f, 180.0f, "%.0f");
                        plateSettingsChanged |= KingSliderFloat("Turn Left / Right",   yaw,   -180.0f, 180.0f, "%.0f");
                        plateSettingsChanged |= KingSliderFloat("Roll (Lean)",         roll,  -180.0f, 180.0f, "%.0f");

                        ImGui::PopID();
                        ImGui::Spacing();
                    };

                    plateControls("Front Plate", true);
                    plateControls("Rear Plate", false);

                                                                                 
                                                                                
                                                                            
                    if (plateSettingsChanged && ImGui::IsItemDeactivatedAfterEdit()) {
                        GameEventHookModule::SaveConfig();
                    }

                    ImGui::Unindent(8.0f);
                }
                                                                                  
                                                                                 
                                                                                  
                                                                                                
                if (pgTexBall || pgTexAvi || pgTexDecal || pgTexBanner || pgTexBoost)
                {
                    ImGui::Indent(15.0f);

                    if (pgTexBall)
                    {
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_FUTBOL "  Ball Textures");
                        ImGui::Spacing();

                        if (ImGui::Checkbox("Enable Ball Texture", &BallTexturesModule::IsEnabled))
                        {
                            GameEventHookModule::SaveConfig();
                            if (BallTexturesModule::IsEnabled)
                                Main.Execute([] { BallTexturesModule::ApplySelectedSkinToAllBalls(); });
                            else
                                BallTexturesModule::RestoreDefaultTextures();
                        }

                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open Folder##balltex"))
                            OpenFolderInExplorer(BallTexturesModule::BallTexturesFolder);
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SYNC "  Refresh##balltex"))
                            Main.Execute([] { BallTexturesModule::SearchForBallSkins(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_PLUS "  Add from PC##balltex"))
                        {
                            textureTarget = 0;
                            fileBrowser.ClearAllowedExtensions();
                            fileBrowser.SetTitle("Select Ball Texture");
                            fileBrowser.Open();
                        }

                        ImGui::Spacing();
                        ImGui::TextDisabled("Ball texture");
                        const char* ballPreviewName = BallTexturesModule::SelectedSkinName.empty()
                            ? "Select texture..." : BallTexturesModule::SelectedSkinName.c_str();
                        if (ImGui::BeginCombo("##ball_texture_selector", ballPreviewName))
                        {
                            for (const auto& [key, skin] : BallTexturesModule::SavedTextureData)
                            {
                                const bool selected = key == BallTexturesModule::SelectedSkinName;
                                if (ImGui::Selectable(key.c_str(), selected))
                                {
                                    BallTexturesModule::SelectedSkinName = key;
                                    BallTexturesModule::IsEnabled = true;
                                    GameEventHookModule::SaveConfig();
                                    Main.Execute([] { BallTexturesModule::ApplySelectedSkinToAllBalls(); });
                                }

                                fs::path hoverPreviewPath;
                                auto diffuseIt = skin.paramTextures.find("Diffuse");
                                if (diffuseIt != skin.paramTextures.end())
                                    hoverPreviewPath = diffuseIt->second.imgPath;
                                else if (!skin.paramTextures.empty())
                                    hoverPreviewPath = skin.paramTextures.begin()->second.imgPath;
                                DrawLocalTextureHoverPreview(hoverPreviewPath);
                                if (selected) ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        if (BallTexturesModule::SavedTextureData.empty())
                            ImGui::TextDisabled("No ball textures found.");
                    }

                    if (pgTexAvi)
                    {
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_USER_CIRCLE "  Avatar Textures");
                        ImGui::Spacing();

                        if (ImGui::Checkbox("Enable Avatar Texture", &CustomAvatarModule::IsEnabled))
                        {
                            GameEventHookModule::SaveConfig();
                            if (CustomAvatarModule::IsEnabled &&
                                CustomAvatarModule::SelectedFileIndex >= 0 &&
                                CustomAvatarModule::SelectedFileIndex < static_cast<int>(CustomAvatarModule::AvailableFiles.size()))
                            {
                                const fs::path selectedPath = CustomAvatarModule::AvailableFiles[CustomAvatarModule::SelectedFileIndex];
                                Main.Execute([selectedPath] { CustomAvatarModule::ApplyTextureFromPath(selectedPath); });
                            }
                        }

                        ImGui::TextDisabled("This page replaces only your normal local avatar. Platform icons are controlled from Extras > Player.");

                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open Folder##avatartex"))
                            OpenFolderInExplorer(CustomAvatarModule::AvatarsFolder);
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SYNC "  Refresh##avatartex"))
                            CustomAvatarModule::ScanAvatarFiles();
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_PLUS "  Add from PC##avatartex"))
                        {
                            textureTarget = 1;
                            fileBrowser.ClearAllowedExtensions();
                            fileBrowser.SetTitle("Select Avatar Texture");
                            fileBrowser.Open();
                        }

                        ImGui::Spacing();
                        ImGui::TextDisabled("Avatar texture");
                        std::string avatarPreviewName = "Select texture...";
                        if (CustomAvatarModule::SelectedFileIndex >= 0 &&
                            CustomAvatarModule::SelectedFileIndex < static_cast<int>(CustomAvatarModule::AvailableFiles.size()))
                            avatarPreviewName = CustomAvatarModule::AvailableFiles[CustomAvatarModule::SelectedFileIndex].filename().string();
                        if (ImGui::BeginCombo("##avatar_texture_selector", avatarPreviewName.c_str()))
                        {
                            for (int i = 0; i < static_cast<int>(CustomAvatarModule::AvailableFiles.size()); ++i)
                            {
                                const bool selected = i == CustomAvatarModule::SelectedFileIndex;
                                const std::string name = CustomAvatarModule::AvailableFiles[i].filename().string();
                                if (ImGui::Selectable(name.c_str(), selected))
                                {
                                    CustomAvatarModule::SelectedFileIndex = i;
                                    CustomAvatarModule::IsEnabled = true;
                                    const fs::path selectedPath = CustomAvatarModule::AvailableFiles[i];
                                    GameEventHookModule::SaveConfig();
                                    Main.Execute([selectedPath] { CustomAvatarModule::ApplyTextureFromPath(selectedPath); });
                                }
                                DrawLocalTextureHoverPreview(CustomAvatarModule::AvailableFiles[i]);
                                if (selected) ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        if (CustomAvatarModule::AvailableFiles.empty())
                            ImGui::TextDisabled("No avatar images found.");
                    }

                                                                                         
                                                                     
                    static std::array<float, CustomTextureStudioModule::FeatureCount> s_safeTextureHeights{};

                    auto RenderSafeTextureFeature = [&](size_t featureIndex)
                    {
                        if (featureIndex >= CustomTextureStudioModule::FeatureCount)
                            return;

                        const auto& defs = CustomTextureStudioModule::Definitions();
                        const auto& def = defs[featureIndex];
                        const TextureStudioFeatureState state = CustomTextureStudioModule::StateForFeature(featureIndex);

                        ImGui::PushID(static_cast<int>(featureIndex));
                        BeginFitSection(s_safeTextureHeights[featureIndex]);

                        ImGui::TextColored(g_RedThemeColor, "%s", def.label);
                        if (def.description && *def.description)
                            ImGui::TextDisabled("%s", def.description);

                        bool enabled = state.enabled;
                        if (ImGui::Checkbox("Enable##safe_texture_feature", &enabled))
                        {
                            Main.Execute([featureIndex, enabled] {
                                CustomTextureStudioModule::SetEnabled(featureIndex, enabled);
                            });
                        }

                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open Folder##safe_texture_feature"))
                            OpenFolderInExplorer(CustomTextureStudioModule::FolderForFeature(featureIndex));
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SYNC "  Refresh##safe_texture_feature"))
                        {
                            Main.Execute([featureIndex] {
                                CustomTextureStudioModule::ScanFilesForFeature(featureIndex);
                                CustomTextureStudioModule::ApplyFeature(featureIndex);
                            });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_PLUS "  Add from PC##safe_texture_feature"))
                        {
                            textureTarget = 1000 + static_cast<int>(featureIndex);
                            fileBrowser.ClearAllowedExtensions();
                            fileBrowser.SetTitle(std::string("Select ") + def.label + " Image");
                            fileBrowser.Open();
                        }

                        const std::vector<fs::path> files = CustomTextureStudioModule::FilesForFeature(featureIndex);
                        const std::string preview = state.selectedFileName.empty() ? "Select image..." : state.selectedFileName;
                        ImGui::TextDisabled("Image");
                        if (ImGui::BeginCombo("##safe_texture_image", preview.c_str()))
                        {
                            for (int fileIndex = 0; fileIndex < static_cast<int>(files.size()); ++fileIndex)
                            {
                                const bool selected = fileIndex == state.selectedFileIndex;
                                const std::string name = files[fileIndex].filename().string();
                                if (ImGui::Selectable(name.c_str(), selected))
                                {
                                    Main.Execute([featureIndex, fileIndex] {
                                        CustomTextureStudioModule::SelectImage(featureIndex, fileIndex);
                                    });
                                }
                                DrawLocalTextureHoverPreview(files[fileIndex]);
                                if (selected) ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }

                        if (files.empty())
                            ImGui::TextDisabled("No images found. Use Add from PC or Open Folder.");
                        else
                            ImGui::TextDisabled("Hover a filename to preview. Selecting it applies automatically.");

                        const int activeCount = CustomTextureStudioModule::MatchCount(featureIndex);
                        if (enabled && activeCount == 0)
                            ImGui::TextDisabled("Waiting for the supported game/UI object to become available.");

                        EndFitSection(s_safeTextureHeights[featureIndex]);
                        ImGui::Spacing();
                        ImGui::PopID();
                    };

                    if (pgTexDecal)
                    {
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_CAR "  Custom Decal");
                        ImGui::TextDisabled("Local custom car decal image.");
                        ImGui::Spacing();
                        RenderSafeTextureFeature(0);
                    }

                    if (pgTexBanner)
                    {
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_ID_CARD "  Custom Banner");
                        ImGui::TextDisabled("Client-side player banner image.");
                        ImGui::Spacing();
                        RenderSafeTextureFeature(1);
                    }

                    if (pgTexBoost)
                    {
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_TACHOMETER_ALT "  Boost Meter Textures");
                        ImGui::Spacing();

                        if (ImGui::Checkbox("Enable Boost Meter Texture", &CustomBoostMeterModule::IsEnabled))
                        {
                            GameEventHookModule::SaveConfig();
                            if (CustomBoostMeterModule::IsEnabled)
                                Main.Execute([] { CustomBoostMeterModule::ApplySelectedSkin(); });
                            else
                                Main.Execute([] { CustomBoostMeterModule::RestoreMeter(); });
                        }

                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open Folder##boosttex"))
                            OpenFolderInExplorer(CustomBoostMeterModule::MeterFolder);
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SYNC "  Refresh##boosttex"))
                            Main.Execute([] { CustomBoostMeterModule::SearchForSkins(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SEARCH "  Dump Names##boosttex"))
                            CustomBoostMeterModule::DumpTextureNames();

                        ImGui::Spacing();
                        ImGui::TextDisabled("Boost meter skin");
                        const char* boostPreviewName = CustomBoostMeterModule::SelectedSkinName.empty()
                            ? "Select texture..." : CustomBoostMeterModule::SelectedSkinName.c_str();
                        if (ImGui::BeginCombo("##boost_texture_selector", boostPreviewName))
                        {
                            for (const auto& [key, skin] : CustomBoostMeterModule::SavedSkins)
                            {
                                const bool selected = key == CustomBoostMeterModule::SelectedSkinName;
                                if (ImGui::Selectable(key.c_str(), selected))
                                {
                                    CustomBoostMeterModule::SelectedSkinName = key;
                                    CustomBoostMeterModule::IsEnabled = true;
                                    GameEventHookModule::SaveConfig();
                                    Main.Execute([] { CustomBoostMeterModule::ApplySelectedSkin(); });
                                }
                                fs::path hoverPreviewPath;
                                if (!skin.layers.empty())
                                {
                                    auto bgIt = std::find_if(skin.layers.begin(), skin.layers.end(),
                                        [](const BoostMeterLayer& layer) { return layer.layerName == "Background"; });
                                    hoverPreviewPath = (bgIt != skin.layers.end()) ? bgIt->imgFile : skin.layers.front().imgFile;
                                }
                                DrawLocalTextureHoverPreview(hoverPreviewPath);
                                if (selected) ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                        if (CustomBoostMeterModule::SavedSkins.empty())
                            ImGui::TextDisabled("No boost-meter skins found. Put a skin JSON + images in the folder.");
                    }

                    ImGui::Unindent();
                }

                fileBrowser.Display();
                if (fileBrowser.HasSelected()) {
                    fs::path sel = fileBrowser.GetSelected();
                    try {
                        if (textureTarget == 0) {
                                                                  
                            fs::path dest = BallTexturesModule::BallTexturesFolder / sel.filename();
                            if (!fs::exists(dest)) {
                                fs::copy_file(sel, dest);
                            }
                            
                                                                            
                            fs::path jsonDest = dest;
                            jsonDest.replace_extension(".json");
                            if (!fs::exists(jsonDest)) {
                                std::ofstream jsonFile(jsonDest);
                                if (jsonFile.is_open()) {
                                    jsonFile << "{\n"
                                             << "  \"" << sel.stem().string() << "\": {\n"
                                             << "    \"Params\": {\n"
                                             << "      \"Diffuse\": \"" << sel.filename().string() << "\"\n"
                                             << "    }\n"
                                             << "  }\n"
                                             << "}\n";
                                    jsonFile.close();
                                }
                            }
                            
                            Main.Execute([sel]() { 
                                const std::string autoSkinKey = "Auto: " + sel.stem().string();
                                BallTexturesModule::IsEnabled = true;
                                BallTexturesModule::SearchForBallSkins(); 
                                BallTexturesModule::SelectedSkinName.clear();
                                if (BallTexturesModule::SavedTextureData.find(autoSkinKey) != BallTexturesModule::SavedTextureData.end()) {
                                    BallTexturesModule::SelectedSkinName = autoSkinKey;
                                } else {
                                    for (const auto& [key, skin] : BallTexturesModule::SavedTextureData) {
                                        if (skin.name == sel.stem().string()) {
                                            BallTexturesModule::SelectedSkinName = key;
                                            break;
                                        }
                                    }
                                }
                                GameEventHookModule::SaveConfig();
                                BallTexturesModule::ApplySelectedSkinToAllBalls();
                            });
                            Main.SpawnNotification("KingMod", "Added Ball Texture and generated JSON", 3);
                        } else if (textureTarget == 1) {
                                                     
                            fs::path dest = CustomAvatarModule::AvatarsFolder / sel.filename();
                            if (!fs::exists(dest)) {
                                fs::copy_file(sel, dest);
                            }
                            
                                                                     
                            Main.Execute([dest, sel]() { 
                                CustomAvatarModule::IsEnabled = true;
                                CustomAvatarModule::ScanAvatarFiles();
                                                                     
                                for (int i = 0; i < static_cast<int>(CustomAvatarModule::AvailableFiles.size()); ++i) {
                                    if (CustomAvatarModule::AvailableFiles[i].filename() == sel.filename()) {
                                        CustomAvatarModule::SelectedFileIndex = i;
                                        GameEventHookModule::SaveConfig();
                                        break;
                                    }
                                }
                                CustomAvatarModule::ApplyTextureFromPath(dest); 
                            });
                            Main.SpawnNotification("KingMod", "Added and Applied Avatar Texture", 3);
                        } else if (textureTarget >= 1000) {
                            const size_t featureIndex = static_cast<size_t>(textureTarget - 1000);
                            const fs::path featureFolder = CustomTextureStudioModule::FolderForFeature(featureIndex);
                            std::error_code ec;
                            fs::create_directories(featureFolder, ec);
                            fs::path dest = featureFolder / sel.filename();
                            if (!fs::equivalent(sel, dest, ec)) {
                                fs::copy_file(sel, dest, fs::copy_options::overwrite_existing, ec);
                            }
                            Main.Execute([featureIndex, dest]() {
                                CustomTextureStudioModule::ScanFilesForFeature(featureIndex);
                                const auto files = CustomTextureStudioModule::FilesForFeature(featureIndex);
                                for (int i = 0; i < static_cast<int>(files.size()); ++i) {
                                    if (files[i].filename() == dest.filename()) {
                                        CustomTextureStudioModule::SelectImage(featureIndex, i);
                                        return;
                                    }
                                }
                                CustomTextureStudioModule::ApplyFeature(featureIndex);
                            });
                            Main.SpawnNotification("KingMod", "Added and applied texture", 3);
                        } else if (textureTarget == 3 || textureTarget == 4) {
                                                                                    
                                                                                        
                            const bool front = (textureTarget == 3);
                            char* pathBuf = front ? Items.plateFrontImagePath : Items.plateRearImagePath;
                            strncpy_s(pathBuf, sizeof(Items.plateFrontImagePath), sel.string().c_str(), _TRUNCATE);
                            if (front) { Items.plateFrontEnabled = true; Items.plateFrontDirty = true; }
                            else       { Items.plateRearEnabled  = true; Items.plateRearDirty  = true; }
                            Main.SpawnNotification("KingMod", "Set license plate image", 3);
                        }

                    } catch (...) {
                        Main.SpawnNotification("KingMod", "Failed to add texture", 3);
                    }
                    fileBrowser.ClearSelected();
                }
                if (pgTraining && SectionHeader(ICON_FA_GLOBE "  LOCAL SERVER SETTINGS"))
                {
                    ImGui::Indent(15.0f);
                    const bool canApplyWorld = Events.CanUseLocalServerFeatures();
                    ImGui::TextColored(canApplyWorld ? ImVec4(0.35f, 0.88f, 0.58f, 1.0f) : ImVec4(1.0f, 0.48f, 0.42f, 1.0f),
                        canApplyWorld ? "Active in this session" : "Available only in Freeplay, Training, Workshop, offline, or a LAN server you host");
                    ImGui::Spacing();
                    auto applySpeed = [](float value) {
                        Main.Execute([value]() {
                            if (!Events.CanUseLocalServerFeatures()) return;
                            APlayerController* pc = Instances.IAPlayerController();
                            if (pc && pc->WorldInfo) pc->WorldInfo->TimeDilation = value;
                        });
                    };
                    auto applyGravity = [](float value) {
                        Main.Execute([value]() {
                            if (!Events.CanUseLocalServerFeatures()) return;
                            APlayerController* pc = Instances.IAPlayerController();
                            if (pc && pc->WorldInfo) pc->WorldInfo->WorldGravityZ = value;
                        });
                    };
                    if (!canApplyWorld) ImGui::BeginDisabled();
                    if (ImGui::SliderFloat("Game Speed (Time Dilation)", &Events.timeDilation, 0.1f, 5.0f)) {
                        applySpeed(Events.timeDilation);
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit()) GameEventHookModule::SaveConfig();
                    if (ImGui::Button(ICON_FA_TACHOMETER_ALT "  Reset Speed")) {
                        Events.timeDilation = 1.0f;
                        applySpeed(1.0f);
                        GameEventHookModule::SaveConfig();
                    }

                    ImGui::Spacing();
                    ImGui::Text("Speed Presets:");
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Slow (0.5x)")) { Events.timeDilation = 0.5f; applySpeed(0.5f); GameEventHookModule::SaveConfig(); }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Normal (1.0x)")) { Events.timeDilation = 1.0f; applySpeed(1.0f); GameEventHookModule::SaveConfig(); }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Fast (1.5x)")) { Events.timeDilation = 1.5f; applySpeed(1.5f); GameEventHookModule::SaveConfig(); }
                    ImGui::Spacing();

                    if (ImGui::DragFloat("World Gravity Z", &Events.worldGravityZ, 10.0f, -5000.0f, 5000.0f)) {
                        applyGravity(Events.worldGravityZ);
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit()) GameEventHookModule::SaveConfig();
                    if (ImGui::Button(ICON_FA_WEIGHT_HANGING "  Reset Gravity")) {
                        Events.worldGravityZ = -650.0f;
                        applyGravity(-650.0f);
                        GameEventHookModule::SaveConfig();
                    }
                    ImGui::Text("Gravity Presets:");
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Moon (-200)")) { Events.worldGravityZ = -200.0f; applyGravity(-200.0f); GameEventHookModule::SaveConfig(); }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Normal (-650)")) { Events.worldGravityZ = -650.0f; applyGravity(-650.0f); GameEventHookModule::SaveConfig(); }
                    ImGui::SameLine();
                    if (ImGui::Button(ICON_FA_DOT_CIRCLE "  Heavy (-2000)")) { Events.worldGravityZ = -2000.0f; applyGravity(-2000.0f); GameEventHookModule::SaveConfig(); }

                    ImGui::Spacing();
                    if (!canApplyWorld) ImGui::EndDisabled();
                    ImGui::Unindent();
                }

                                                                           
                if (pgNetwork) {
                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_COMMENT "  ONLINE STATUS");
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Checkbox(ICON_FA_COMMENT "  Enable Custom Online Status", &Events.setOnlineStatus);
                    if (Events.setOnlineStatus)
                    {
                        ImGui::Indent();
                        ImGui::InputText("##CustomStatus", &Events.customStatus);
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_COMMENT "  Set Status")) {
                            Events.forceStatusUpdate = true;
                        }
                        ImGui::Unindent();
                    }

                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_NETWORK_WIRED "  NETWORK");
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Checkbox(ICON_FA_WIFI "  Enable Ping Spoofer", &Events.enablePingSpoof);
                    if (Events.enablePingSpoof)
                    {
                        ImGui::Indent();
                        ImGui::TextDisabled("Local PRI display. Rocket League stores ping in 1/255-second buckets (~3.92 ms each).");
                        ImGui::Text("Target Ping:");
                        ImGui::SameLine();
                        if (ImGui::InputInt("##CustomPing", &Events.customPingValue))
                        {
                            if (Events.customPingValue < 0) Events.customPingValue = 0;
                            if (Events.customPingValue > 999) Events.customPingValue = 999;
                        }
                        if (ImGui::Button("0 ms##PingPreset")) Events.customPingValue = 0;
                        ImGui::SameLine();
                        if (ImGui::Button("4 ms##PingPreset")) Events.customPingValue = 4;
                        ImGui::SameLine();
                        if (ImGui::Button("8 ms##PingPreset")) Events.customPingValue = 8;
                        ImGui::SameLine();
                        if (ImGui::Button("12 ms##PingPreset")) Events.customPingValue = 12;
                        const int pingBytePreview = Events.customPingValue <= 0 ? 0 :
                            (std::max)(1, (std::min)(255, static_cast<int>(std::lround((255.0 * Events.customPingValue) / 1000.0))));
                        const int effectivePing = pingBytePreview == 0 ? 0 :
                            static_cast<int>(std::ceil((1000.0 * pingBytePreview) / 255.0));
                        ImGui::TextDisabled("Effective quantized display: ~%d ms (Ping byte %d)", effectivePing, pingBytePreview);
                        ImGui::Unindent();
                    }
                }

                if (pgRocket)
                {
                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_ROCKET "  ROCKET PASS");
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Indent(15.0f);
                    
                    ImGui::Text("Tier Level:");
                    ImGui::InputInt("##RocketPassTier", &Events.rocketPassTier);
                    if (Events.rocketPassTier < 1) Events.rocketPassTier = 1;
                    if (Events.rocketPassTier > 9999999) Events.rocketPassTier = 9999999;

                    ImGui::Text("XP Multiplier:");
                    ImGui::SliderFloat("##RocketPassXPMult", &Events.rocketPassXPMultiplier, 0.1f, 10.0f, "%.1fx");

                    ImGui::Checkbox(ICON_FA_CROWN "  Premium Pass", &Events.rocketPassPremium);

                    ImGui::Spacing();
                    if (ImGui::Button(ICON_FA_CHECK "  Apply Settings", ImVec2(-1, 30))) {
                        Main.Execute([]() {
                            Events.ApplyRocketPassSettings(Events.rocketPassTier, Events.rocketPassXPMultiplier, Events.rocketPassPremium);
                        });
                        Main.SpawnNotification("KingMod", "Rocket Pass applied!", 3);
                    }
                    
                    ImGui::Unindent();

                    ImGui::Spacing();
                    ImGui::TextColored(g_RedThemeColor, ICON_FA_ID_CARD "  ACCOUNT");
                    ImGui::Separator();
                }
                }


                if (settingsChanged) {
                    GameEventHookModule::SaveConfig();
                }


                gui.end_group_box();
            }

                              
            else if (gui.m_tab == 8) {
                gui.group_box("Settings", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                                                                          
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                    static float s_presetsCardH = 0.f, s_colorsCardH = 0.f, s_othersCardH = 0.f;
                    static char  s_uiName[64] = "";
                    static int   s_uiSel = -1;
                    bool themeChanged = false;

                                                                    
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 6));
                    const float kCtrlCol = 210.0f;                          

                                                                                     
                                                                                  
                    auto ToggleRow = [&](const char* label, bool& v) -> bool {
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(label);
                        ImGui::SameLine(kCtrlCol);
                        std::string id = std::string("##t_") + label;
                        return ImGui::Checkbox(id.c_str(), &v);
                    };
                    auto ColorRow = [&](const char* label, ImVec4& col) -> bool {
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(label);
                        ImGui::SameLine(kCtrlCol);
                        std::string id = std::string("##c_") + label;
                        return ImGui::ColorEdit4(id.c_str(), (float*)&col,
                            ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    };

                                                                        
                    BeginFitSection(s_presetsCardH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SWATCHBOOK "  PRESETS MANAGER");
                        ImGui::Spacing();

                        std::vector<std::string> uiPresets = UITheme::ListPresets();
                        std::string uiFav = UITheme::GetFavorite();
                        if (s_uiSel >= (int)uiPresets.size()) s_uiSel = -1;

                        if (ImGui::BeginListBox("##uipresets", ImVec2(-1, 120))) {
                            for (int i = 0; i < (int)uiPresets.size(); ++i) {
                                bool sel = (s_uiSel == i);
                                std::string lbl = (uiPresets[i] == uiFav)
                                    ? (std::string(ICON_FA_STAR "  ") + uiPresets[i])
                                    : (std::string("       ") + uiPresets[i]);
                                if (ImGui::Selectable(lbl.c_str(), sel)) {
                                    s_uiSel = i;
                                    strncpy_s(s_uiName, uiPresets[i].c_str(), _TRUNCATE);
                                }
                                if (sel && ImGui::IsMouseDoubleClicked(0) && UITheme::LoadPreset(uiPresets[i])) {
                                    GameEventHookModule::SaveConfig();
                                    Main.SpawnNotification("KingMod", "Theme loaded", 2);
                                }
                            }
                            ImGui::EndListBox();
                        }

                        ImGui::Spacing();
                        const bool uiHasSel = (s_uiSel >= 0 && s_uiSel < (int)uiPresets.size());
                        const float uiBtnW = (ImGui::GetContentRegionAvail().x - 20.0f) / 3.0f;
                        if (ImGui::Button(ICON_FA_CHECK_CIRCLE "  Load", ImVec2(uiBtnW, 32)) && uiHasSel && UITheme::LoadPreset(uiPresets[s_uiSel])) {
                            GameEventHookModule::SaveConfig();
                            Main.SpawnNotification("KingMod", "Theme loaded", 2);
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TRASH "  Delete", ImVec2(uiBtnW, 32)) && uiHasSel && UITheme::DeletePreset(uiPresets[s_uiSel])) {
                            s_uiSel = -1;
                            Main.SpawnNotification("KingMod", "Theme deleted", 2);
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_STAR "  Set Favorite", ImVec2(uiBtnW, 32)) && uiHasSel) {
                            UITheme::SetFavorite(uiPresets[s_uiSel]);
                            Main.SpawnNotification("KingMod", "Favorite set", 2);
                        }

                        ImGui::Spacing();
                        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 110.0f);
                        ImGui::InputText("##uipresetname", s_uiName, sizeof(s_uiName));
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_SAVE "  Save", ImVec2(100, 0)) && s_uiName[0] != '\0' && UITheme::SavePreset(s_uiName)) {
                            GameEventHookModule::SaveConfig();
                            Main.SpawnNotification("KingMod", "Theme saved", 2);
                        }
                    EndFitSection(s_presetsCardH);

                    ImGui::Spacing();

                                                                  
                    BeginFitSection(s_colorsCardH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_PALETTE "  UI COLORS");
                        ImGui::Spacing();

                        if (ColorRow(ICON_FA_FILL_DRIP "  Accent Color", GameEventHookModule::UIAccentColor)) themeChanged = true;
                        if (ToggleRow(ICON_FA_RAINBOW "  Rainbow Accent", GameEventHookModule::UIAccentRainbow)) themeChanged = true;
                        if (GameEventHookModule::UIAccentRainbow &&
                            KingSliderFloat("Accent Speed", &GameEventHookModule::UIAccentRainbowSpeed, 0.0f, 100.0f, "%.0f")) themeChanged = true;

                        ImGui::Spacing();
                        if (ColorRow(ICON_FA_TINT "  Background Color", GameEventHookModule::UIBackgroundColor)) themeChanged = true;
                        if (ToggleRow(ICON_FA_RAINBOW "  Rainbow Background", GameEventHookModule::UIBackgroundRainbow)) themeChanged = true;
                        if (GameEventHookModule::UIBackgroundRainbow &&
                            KingSliderFloat("Background Speed", &GameEventHookModule::UIBackgroundRainbowSpeed, 0.0f, 100.0f, "%.0f")) themeChanged = true;

                        ImGui::Spacing();
                        if (ToggleRow(ICON_FA_MAGIC "  Enable Blur Effect", GameEventHookModule::UIBlurEnabled)) themeChanged = true;
                    EndFitSection(s_colorsCardH);

                    ImGui::Spacing();

                                                               
                    BeginFitSection(s_othersCardH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_COGS "  OTHERS");
                        ImGui::Spacing();

                                       
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_KEYBOARD "  Menu Keybind");
                        ImGui::SameLine(kCtrlCol);
                        ImGui::SetNextItemWidth(-1.0f);
                        const int otherKey = RenderBindSelector("##omenukey",
                            GameEventHookModule::MenuToggleKey.c_str());
                        if (otherKey >= 0) {
                            GameEventHookModule::MenuToggleKey = kBindKeys[otherKey];
                            themeChanged = true;
                        }

                        ImGui::Spacing();
                                              
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_FOLDER_OPEN "  KingMod Folder");
                        ImGui::SameLine(kCtrlCol);
                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Open Folder", ImVec2(-1, 0)))
                            OpenFolderInExplorer(GetKingModResourcesDirectoryPath());
                    EndFitSection(s_othersCardH);

                    ImGui::PopStyleVar(2);

                    if (themeChanged) GameEventHookModule::SaveConfig();
                }

                                                                        
                if (gui.m_active_subtab[gui.m_tab] == 1) {
                    static float s_overlayCardH = 0.f;
                    BeginFitSection(s_overlayCardH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_DESKTOP "  OVERLAY");
                        ImGui::Spacing();
                        ImGui::Checkbox(ICON_FA_TACHOMETER_ALT "  Show FPS Counter", &GUIComponent::showFPSCounter);
                    EndFitSection(s_overlayCardH);
                }

                              
                if (gui.m_active_subtab[gui.m_tab] == 2) {
                static float s_keyCardH = 0.f;
                BeginFitSection(s_keyCardH);
                ImGui::TextColored(g_RedThemeColor, ICON_FA_KEYBOARD "  MENU TOGGLE KEY");
                ImGui::Spacing();

                ImGui::SetNextItemWidth(-1.0f);
                const int selectedKey = RenderBindSelector("##MenuToggleKey",
                    GameEventHookModule::MenuToggleKey.c_str());
                if (selectedKey >= 0) {
                    GameEventHookModule::MenuToggleKey = kBindKeys[selectedKey];
                    GameEventHookModule::SaveConfig();
                }
                EndFitSection(s_keyCardH);
                }

                                  
                if (gui.m_active_subtab[gui.m_tab] == 3) {
                static float s_licCardH = 0.f;
                BeginFitSection(s_licCardH);
            
                ImGui::TextColored(g_RedThemeColor, ICON_FA_ID_CARD "  KINGMOD");
                ImGui::Spacing();

                ImGui::TextColored(g_RedThemeColor, ICON_FA_POWER_OFF "  DLL");
                ImGui::Spacing();
                if (ImGui::Button(ICON_FA_SIGN_OUT_ALT "  Unload DLL", ImVec2(-1, 32)))
                {
                    GUIComponent::RequestUnload();
                }
                EndFitSection(s_licCardH);
                }

                gui.end_group_box();
            }

                                                                           
                                                                          
                                               
            else if (gui.m_tab == 9) {
                gui.group_box("Extras", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 6));
                const float kExCol = 230.0f;                           

                auto ExToggle = [&](const char* label, bool& v) -> bool {
                    ImGui::AlignTextToFramePadding();
                    ImGui::TextUnformatted(label);
                    ImGui::SameLine(kExCol);
                    std::string id = std::string("##ex_t_") + label;
                    return ImGui::Checkbox(id.c_str(), &v);
                };
                auto ExInfo = [&](const char* label, const std::string& value) {
                    ImGui::AlignTextToFramePadding();
                    ImGui::TextDisabled("%s", label);
                    ImGui::SameLine(kExCol);
                    ImGui::TextColored(gui.accent_color.to_vec4(), "%s",
                                       value.empty() ? "-" : value.c_str());
                };

                struct ArenaOption { const char* package; const char* name; };
                static const ArenaOption arenas[] = {
                    { "ARC_Darc_P", "Starbase ARC (Aftermath)" }, { "ARC_P", "ARCtagon" },
                    { "CHN_Stadium_Day_P", "Forbidden Temple (Day)" }, { "CHN_Stadium_P", "Forbidden Temple" },
                    { "EuroStadium_Night_P", "Mannfield (Night)" }, { "EuroStadium_P", "Mannfield" },
                    { "EuroStadium_Rainy_P", "Mannfield (Stormy)" }, { "Farm_Night_P", "Farmstead (Night)" },
                    { "Haunted_TrainStation_P", "Urban Central (Haunted)" }, { "HoopsStadium_P", "Dunk House" },
                    { "Labs_Basin_P", "Basin" }, { "Labs_CirclePillars_P", "Pillars" },
                    { "Labs_Corridor_P", "Corridor" }, { "Labs_Cosmic_P", "Cosmic (Old)" },
                    { "Labs_Cosmic_V4_P", "Cosmic (New)" }, { "Labs_DoubleGoal_P", "Double Goal (Old)" },
                    { "Labs_DoubleGoal_V2_P", "Double Goal (New)" }, { "Labs_Galleon_Mast_P", "Galleon Retro" },
                    { "Labs_Galleon_P", "Galleon" }, { "Labs_Holyfield_P", "Loophole" },
                    { "Labs_Octagon_02_P", "Octagon (New)" }, { "Labs_Octagon_P", "Octagon (Old)" },
                    { "Labs_PillarGlass_P", "Hourglass" }, { "Labs_PillarHeat_P", "Barricade" },
                    { "Labs_PillarWings_P", "Colossus" }, { "Labs_Underpass_P", "Underpass" },
                    { "Labs_Utopia_P", "Utopia Retro" }, { "NeoTokyo_P", "Tokyo Underpass" },
                    { "NeoTokyo_Standard_P", "Neo Tokyo" }, { "NeoTokyo_Toon_p", "Neo Tokyo (Comic)" },
                    { "Park_Night_P", "Beckwith Park (Midnight)" }, { "Park_P", "Beckwith Park" },
                    { "Park_Rainy_P", "Beckwith Park (Stormy)" }, { "Park_Snowy_P", "Beckwith Park (Snowy)" },
                    { "ShatterShot_P", "Core 707" }, { "Stadium_Foggy_P", "DFH Stadium (Stormy)" },
                    { "Stadium_P", "DFH Stadium" }, { "Stadium_Race_Day_p", "DFH Stadium (Circuit)" },
                    { "Stadium_Winter_P", "DFH Stadium (Snowy)" }, { "TrainStation_Dawn_P", "Urban Central (Dawn)" },
                    { "TrainStation_Night_P", "Urban Central (Night)" }, { "TrainStation_P", "Urban Central" },
                    { "Underwater_P", "AquaDome" }, { "UtopiaStadium_Dusk_P", "Utopia Coliseum (Dusk)" },
                    { "UtopiaStadium_P", "Utopia Coliseum" }, { "UtopiaStadium_Snow_P", "Utopia Coliseum (Snowy)" },
                    { "Wasteland_Night_P", "Badlands (Night)" }, { "Wasteland_P", "Badlands" },
                    { "arc_standard_p", "Starbase ARC" }, { "bb_p", "Champions Field (NFL)" },
                    { "beach_P", "Salty Shores" }, { "beach_night_p", "Salty Shores (Night)" },
                    { "cs_day_p", "Champions Field (Day)" }, { "cs_hw_p", "Rivals Arena" },
                    { "cs_p", "Champions Field" }, { "eurostadium_snownight_p", "Mannfield (Snowy)" },
                    { "farm_p", "Farmstead" }, { "music_p", "Neon Fields" },
                    { "outlaw_p", "Deadeye Canyon" }, { "park_bman_p", "Beckwith Park (Batman)" },
                    { "stadium_day_p", "DFH Stadium (Day)" }, { "throwbackhockey_p", "Throwback Stadium (Snowy)" },
                    { "throwbackstadium_P", "Throwback Stadium" }, { "wasteland_Night_S_P", "Wasteland (Night)" },
                    { "wasteland_s_p", "Wasteland" }
                };
                static const char* const gameModes[] = {
                    "Soccar", "Hoops", "Snow Day", "Rumble", "Dropshot", "Heatseeker", "Gridiron"
                };
                struct MatchOption { const char* name; const char* values; };
                static const MatchOption matchOptions[] = {
                    { "Match Length", "5 Minutes\0" "10 Minutes\0" "20 Minutes\0" "Unlimited\0" },
                    { "Max Score", "Default\0" "1 Goal\0" "3 Goals\0" "5 Goals\0" "7 Goals\0" "Unlimited\0" },
                    { "Overtime", "Unlimited\0" "+5 Max, First Score\0" "+5 Max, Random Team\0" },
                    { "Max Time", "Default\0" "11 Minutes\0" },
                    { "Series Length", "Unlimited\0" "3 Games\0" "5 Games\0" "7 Games\0" },
                    { "Game Speed", "Default\0" "Slo-mo\0" "Time Warp\0" },
                    { "Ball Max Speed", "Default\0" "Slow\0" "Fast\0" "Super Fast\0" },
                    { "Ball Type", "Default\0" "Cube\0" "Puck\0" "Basketball\0" "Beach Ball\0" "Anniversary\0" "Haunted\0" },
                    { "Ball Gravity", "Default\0" "Low\0" "High\0" "Super High\0" },
                    { "Ball Physics", "Default\0" "Light\0" "Heavy\0" "Super Light\0" "Curveball\0" "Beach Curve\0" },
                    { "Ball Size", "Default\0" "Small\0" "Medium\0" "Large\0" "Gigantic\0" },
                    { "Bounciness", "Default\0" "Low\0" "High\0" "Super High\0" },
                    { "Ball Count", "One\0" },
                    { "Boost Amount", "Default\0" "No Boost\0" "Unlimited\0" "Recharge Slow\0" "Recharge Fast\0" },
                    { "Rumble", "None\0" "Default\0" "Slow\0" "Civilized\0" "Destruction Derby\0" "Spring Loaded\0" "Spikes Only\0" "Rugby\0" "Haunted Beam\0" "Tactical\0" },
                    { "Boost Strength", "1x\0" "1.5x\0" "2x\0" "10x\0" },
                    { "World Gravity", "Default\0" "Low\0" "High\0" "Super High\0" "Reverse\0" },
                    { "Demolitions", "Default\0" "Disabled\0" "Friendly Fire\0" "On Contact\0" "On Contact FF\0" },
                    { "Respawn", "3 Seconds\0" "2 Seconds\0" "1 Second\0" "No Goal Reset\0" },
                    { "Bot Loadouts", "Default\0" "Random\0" },
                    { "Audio", "Default\0" "Haunted\0" },
                    { "Game Event", "Default\0" "Haunted\0" "Rugby\0" }
                };
                static_assert(IM_ARRAYSIZE(matchOptions) == CustomMatchModule::HostMutatorCount);

                                                                     
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                    static float s_infoH = 0.f, s_shieldH = 0.f, s_folderH = 0.f;

                    BeginFitSection(s_infoH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_ID_BADGE "  DASHBOARD");
                        ImGui::Spacing();

                        ImGui::AlignTextToFramePadding();
                        ImGui::TextDisabled("Injection Status");
                        ImGui::SameLine(kExCol);
                        ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.40f, 1.0f), ICON_FA_CHECK "  Injected");

                        ExInfo("Username", menu_avatar::Name());
                        ExInfo("Platform", GameEventHookModule::GetLocalPlatformName());
                        ExInfo("Operating System", GameEventHookModule::GetOperatingSystemName());
                        ExInfo("Mod Version", GameEventHookModule::ModuleVersion);

                        {
                            ExInfo("Access", "KingMod");
                            ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.40f, 1.0f), ICON_FA_CHECK "  Active");
                        }
                    EndFitSection(s_infoH);

                    BeginFitSection(s_shieldH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SHIELD_ALT "  MATCH SHIELD");
                        ImGui::Spacing();

                        {
                            bool shieldEnabled = MatchmakingShield::IsEnabled();
                            if (ExToggle(ICON_FA_SHIELD_ALT "  Hold Match Before Joining", shieldEnabled)) {
                                if (!shieldEnabled && MatchmakingShield::IsWaitingForJoin())
                                    Main.Execute([]() { MatchmakingShield::AcceptPendingJoin(); });
                                MatchmakingShield::SetEnabled(shieldEnabled);
                                GameEventHookModule::SaveConfig();
                            }
                        }

                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_KEYBOARD "  Join Key");
                        ImGui::SameLine(kExCol);
                        ImGui::SetNextItemWidth(240.0f);
                        {
                            const int shieldKey = RenderBindSelector("##ex_shieldkey",
                                GameEventHookModule::MatchmakingShieldKeyName);
                            if (shieldKey >= 0) {
                                strncpy_s(GameEventHookModule::MatchmakingShieldKeyName,
                                    sizeof(GameEventHookModule::MatchmakingShieldKeyName),
                                    kBindKeys[shieldKey], _TRUNCATE);
                                MatchmakingShield::SetJoinKey(GameEventHookModule::KeyNameToVk(kBindKeys[shieldKey]));
                                GameEventHookModule::SaveConfig();
                            }
                        }
                        ImGui::SameLine();
                        ImGui::TextDisabled("(?)");
                        if (ImGui::IsItemHovered())
                            ImGui::SetTooltip("Single letters/digits (A, 5), function keys (F5), or names\n"
                                              "like Space, Enter, Insert, Delete, Home, End, PageUp.");

                        ImGui::Spacing();
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextDisabled("Current");
                        ImGui::SameLine(kExCol);
                        if (MatchmakingShield::IsWaitingForJoin())
                            ImGui::TextColored(ImVec4(1.0f, 0.75f, 0.20f, 1.0f), ICON_FA_CLOCK "  Holding a match");
                        else
                            ImGui::TextDisabled("Idle");

                        ImGui::Spacing();
                        {
                            const bool held = MatchmakingShield::IsWaitingForJoin();
                            const float shieldHalf = (ImGui::GetContentRegionAvail().x - 10.0f) * 0.5f;
                            if (!held) ImGui::BeginDisabled();
                            if (ImGui::Button(ICON_FA_SIGN_IN_ALT "  Join Held Match Now", ImVec2(shieldHalf, 32)))
                                Main.Execute([]() { MatchmakingShield::AcceptPendingJoin(); });
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_TIMES_CIRCLE "  Decline Held Match", ImVec2(-1, 32)))
                                Main.Execute([]() { MatchmakingShield::CancelPendingJoin(); });
                            if (!held) ImGui::EndDisabled();
                        }

                    EndFitSection(s_shieldH);

                    BeginFitSection(s_folderH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_FOLDER_OPEN "  FILES");
                        ImGui::Spacing();
                        const float halfW = (ImGui::GetContentRegionAvail().x - 10.0f) * 0.5f;
                        if (ImGui::Button(ICON_FA_FOLDER_OPEN "  KingMod Folder", ImVec2(halfW, 32)))
                            GameEventHookModule::OpenKingModFolder();
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_MAP "  Workshop Folder", ImVec2(-1, 32)))
                            GameEventHookModule::OpenWorkshopFolder();
                    EndFitSection(s_folderH);
                }

                                                                       
                else if (gui.m_active_subtab[gui.m_tab] == 1) {
                    static float s_nameH = 0.f, s_visH = 0.f, s_ballH = 0.f;

                    BeginFitSection(s_nameH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_USER_EDIT "  LOCAL NAME");
                        ImGui::Spacing();
                        ImGui::TextDisabled("Local only - the server and other players still see your real username.");
                        ImGui::TextDisabled("Use Apply via Steam to change the name everyone sees.");
                        if (ExToggle(ICON_FA_EYE_SLASH "  Blank Local Name (local only)", GameEventHookModule::UsernameInvisible))
                            GameEventHookModule::SaveConfig();

                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_USER "  Local Username");
                        ImGui::SameLine(kExCol);
                        ImGui::SetNextItemWidth(-1.0f);
                        ImGui::InputText("##ex_localusername", GameEventHookModule::UsernameChangeText,
                                         sizeof(GameEventHookModule::UsernameChangeText));

                        ImGui::Spacing();
                        if (ImGui::Button(ICON_FA_CHECK "  Apply Local Name", ImVec2(170.0f, 28.0f))) {
                            if (!GameEventHookModule::UsernameInvisible)
                                GameEventHookModule::UsernameChangerEnabled = true;
                            Main.Execute([]() { GameEventHookModule::ApplyUsernameChange(); });
                            GameEventHookModule::SaveConfig();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_UNDO "  Restore", ImVec2(130.0f, 28.0f))) {
                            GameEventHookModule::UsernameChangerEnabled = false;
                            GameEventHookModule::UsernameInvisible = false;
                            Main.Execute([]() { GameEventHookModule::ApplyUsernameChange(); });
                            GameEventHookModule::SaveConfig();
                        }
                        ImGui::SameLine();
                        ImGui::TextDisabled("One local update");

                                                                           
                                                                           
                                                                            
                        ImGui::Spacing();
                        if (ImGui::Button(ICON_FA_GLOBE "  Apply via Steam (name everyone sees)", ImVec2(-1.0f, 28.0f))) {
                            Main.Execute([]() { GameEventHookModule::ApplySteamUsername(); });
                        }

                                                                                       
                                                                              
                        ImGui::Spacing();
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextDisabled("Result");
                        ImGui::SameLine(kExCol);
                        ImGui::PushTextWrapPos(0.0f);
                        if (!GameEventHookModule::UsernameChangeStatus.empty())
                            ImGui::TextColored(gui.accent_color.to_vec4(), "%s",
                                               GameEventHookModule::UsernameChangeStatus.c_str());
                        else if (GameEventHookModule::UsernameChangerEnabled ||
                                 GameEventHookModule::UsernameInvisible)
                            ImGui::TextDisabled("Ready - press Apply Local Name");
                        else
                            ImGui::TextDisabled("Off -- your real name is shown");
                        ImGui::PopTextWrapPos();
                    EndFitSection(s_nameH);

                    BeginFitSection(s_visH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_EYE "  VISIBILITY");
                        ImGui::Spacing();
                        if (ExToggle(ICON_FA_STOPWATCH "  Enemy Flip Timer / Reset Indicator", GameEventHookModule::EnemyResetIndicatorEnabled))
                            GameEventHookModule::SaveConfig();
                        if (ExToggle(ICON_FA_IMAGE "  Platform Avatar Icons", GameEventHookModule::ShowPlatformOnScoreboard))
                        {
                            const bool enabled = GameEventHookModule::ShowPlatformOnScoreboard;
                            GameEventHookModule::SaveConfig();
                            Main.Execute([enabled]() {
                                if (enabled) CustomAvatarModule::ApplyPlatformIcons();
                                else CustomAvatarModule::RestorePlatformIcons();
                            });
                        }
                        ImGui::TextDisabled("Uses steam.png / epic.png / psn.png / xbox.png / switch.png / psynet.png from the Avatar folder. No platform text is added to names.");
                        if (ExToggle(ICON_FA_TACHOMETER_ALT "  Show MMR On Scoreboard", GameEventHookModule::ShowPlayerMMR))
                            GameEventHookModule::SaveConfig();
                        if (ExToggle(ICON_FA_PLAY "  POV Camera In Replays", GameEventHookModule::PovInReplay))
                            GameEventHookModule::SaveConfig();
                    EndFitSection(s_visH);

                }

                                                                         
                else if (gui.m_active_subtab[gui.m_tab] == 2) {
                    static float s_fpH = 0.f;

                    BeginFitSection(s_fpH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_GAMEPAD "  FREEPLAY");
                        ImGui::Spacing();
                        const bool canUseLocalFeatures = Events.CanUseLocalServerFeatures();
                        ImGui::TextColored(canUseLocalFeatures ? ImVec4(0.35f, 0.88f, 0.58f, 1.0f) : ImVec4(1.0f, 0.48f, 0.42f, 1.0f),
                            canUseLocalFeatures ? "Local/host features are active" : "Unlimited flips work only in Freeplay, Training, Workshop, offline, or a hosted LAN server");
                        if (!canUseLocalFeatures) ImGui::BeginDisabled();
                        if (ExToggle(ICON_FA_ROCKET "  Unlimited Flips / Jumps", GameEventHookModule::UnlimitedJumpsEnabled))
                            GameEventHookModule::SaveConfig();
                        ImGui::Spacing();
                        ImGui::Checkbox("Ball Pinch Strength##offline", &KingFeatures::Config.BallPinchStrengthEnabled);
                        if (KingFeatures::Config.BallPinchStrengthEnabled) {
                            ImGui::Indent(10.0f);
                            ImGui::SetNextItemWidth(230.0f);
                            ImGui::SliderFloat("Pinch Strength##offline", &KingFeatures::Config.BallPinchStrength, 0.25f, 5.0f, "%.2fx");
                            ImGui::TextDisabled("1.00x = stock. Uses Rocket League's replicated car-bounce scale.");
                            ImGui::Unindent(10.0f);
                        }
                        if (!canUseLocalFeatures) ImGui::EndDisabled();

                        if (ExToggle(ICON_FA_COMMENT "  Scored Message", GameEventHookModule::ScoredMessageEnabled)) {
                            GameEventHookModule::ScoredMessageStatus =
                                GameEventHookModule::ScoredMessageEnabled
                                    ? "Armed - waiting for a goal event"
                                    : "Disabled";
                            GameEventHookModule::SaveConfig();
                        }

                        if (GameEventHookModule::ScoredMessageEnabled) {
                            ImGui::Indent(10.0f);

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextDisabled("Speed Unit");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(150.0f);
                            if (ImGui::Combo("##ex_goalspeedunit", &GameEventHookModule::BallSpeedUnit,
                                             "km/h\0mph\0uu/s\0"))
                                GameEventHookModule::SaveConfig();

                            if (ImGui::Button(ICON_FA_COMMENT "  Test Local Message", ImVec2(190.0f, 28.0f)))
                                GameEventHookModule::SendLocalChatMessage("Goal message test");
                            ImGui::Unindent(10.0f);
                        }

                        ImGui::Spacing();
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextDisabled("Status");
                        ImGui::SameLine(kExCol);
                        if (!GameEventHookModule::ScoredMessageStatus.empty())
                            ImGui::TextColored(gui.accent_color.to_vec4(), "%s",
                                               GameEventHookModule::ScoredMessageStatus.c_str());
                        else if (GameEventHookModule::ScoredMessageEnabled)
                            ImGui::TextDisabled("Armed - waiting for a goal event");
                        else
                            ImGui::TextDisabled("Disabled");
                    EndFitSection(s_fpH);

                }

                                                                         
                else if (gui.m_active_subtab[gui.m_tab] == 3) {
                    static int   s_wsPage        = 0;
                    static float s_wsTopH        = 0.f;
                    static float s_wsDlH         = 0.f;
                    static float s_wsInstH       = 0.f;
                    static float s_wsSessionH    = 0.f;
                    static bool  s_wsFirstOpen   = false;
                    static bool  s_wsInstScanned = false;
                    static bool  s_wsSessionScanned = false;

                    if (!s_wsFirstOpen) {
                        s_wsFirstOpen = true;
                        GameEventHookModule::RefreshWorkshopBrowse(1);
                    }

                    BeginFitSection(s_wsTopH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_MAP "  WORKSHOP");
                        ImGui::Spacing();
                        const float wsPageW = (ImGui::GetContentRegionAvail().x - 16.0f) / 3.0f;
                        for (int p = 0; p < 3; ++p) {
                            const bool wsSel = (s_wsPage == p);
                            if (wsSel) {
                                ImGui::PushStyleColor(ImGuiCol_Button,        gui.accent_color.to_vec4());
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, gui.accent_color.to_vec4());
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  gui.accent_color.to_vec4());
                            }
                            const char* wsPageLabel = p == 0 ? ICON_FA_DOWNLOAD "  Download"
                                : (p == 1 ? ICON_FA_FOLDER_OPEN "  Installed"
                                          : ICON_FA_GAMEPAD "  Freeplay Launcher");
                            if (ImGui::Button(wsPageLabel, ImVec2(p < 2 ? wsPageW : -1, 34))) {
                                s_wsPage = p;
                                if (p == 1) {
                                    s_wsInstScanned = true;
                                    GameEventHookModule::RefreshWorkshopInstalled();
                                }
                                else if (p == 2 && !s_wsSessionScanned) {
                                    s_wsSessionScanned = true;
                                    GameEventHookModule::RefreshWorkshopMapList();
                                }
                            }
                            if (wsSel) ImGui::PopStyleColor(3);
                            if (p < 2) ImGui::SameLine();
                        }
                    EndFitSection(s_wsTopH);

                    if (s_wsPage == 0) {
                        BeginFitSection(s_wsDlH);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_DATABASE "  Source");
                            ImGui::SameLine(kExCol);
                            ImGui::TextDisabled("Community Maps");
                            if (GameEventHookModule::WorkshopBpMaxId > 0) {
                                ImGui::SameLine();
                                ImGui::TextDisabled(ICON_FA_ID_BADGE "  1 - %d",
                                                    GameEventHookModule::WorkshopBpMaxId);
                            }

                            ImGui::Spacing();
                            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 300.0f);
                            const bool searchEnter = ImGui::InputTextWithHint(
                                "##ex_wssearch", ICON_FA_SEARCH "  Name, author or map id...",
                                GameEventHookModule::WorkshopBrowseSearch,
                                sizeof(GameEventHookModule::WorkshopBrowseSearch),
                                ImGuiInputTextFlags_EnterReturnsTrue);
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(150.0f);
                            if (ImGui::Combo("##ex_wssort", &GameEventHookModule::WorkshopBrowseSort,
                                             "Featured\0Newest\0Top Rated\0"))
                                GameEventHookModule::RefreshWorkshopBrowse(1);
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_SEARCH "  Search", ImVec2(-1, 0)) || searchEnter)
                                GameEventHookModule::RefreshWorkshopBrowse(1);

                            ImGui::Spacing();
                            if (ImGui::Button(ICON_FA_ANGLE_LEFT "  Prev", ImVec2(100, 28)))
                                GameEventHookModule::RefreshWorkshopBrowse(GameEventHookModule::WorkshopBrowsePage - 1);
                            ImGui::SameLine();
                            ImGui::AlignTextToFramePadding();
                            ImGui::Text("Page %d", GameEventHookModule::WorkshopBrowsePage);
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_ANGLE_RIGHT "  Next", ImVec2(100, 28)))
                                GameEventHookModule::RefreshWorkshopBrowse(GameEventHookModule::WorkshopBrowsePage + 1);
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_SYNC "  Refresh", ImVec2(110, 28)))
                                GameEventHookModule::RefreshWorkshopBrowse(GameEventHookModule::WorkshopBrowsePage);
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Folder", ImVec2(-1, 28)))
                                GameEventHookModule::OpenWorkshopFolder();

                            if (GameEventHookModule::WorkshopBrowseLoading) {
                                ImGui::Spacing();
                                ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_SYNC "  Loading...");
                            }
                            if (!GameEventHookModule::WorkshopBrowseError.empty()) {
                                ImGui::Spacing();
                                ImGui::PushTextWrapPos(0.0f);
                                ImGui::TextColored(ImVec4(0.90f, 0.35f, 0.35f, 1.0f), ICON_FA_TIMES "  %s",
                                                   GameEventHookModule::WorkshopBrowseError.c_str());
                                ImGui::PopTextWrapPos();
                            }
                        EndFitSection(s_wsDlH);

                        ImGui::BeginChild("##ex_wslist", ImVec2(0, ImGui::GetContentRegionAvail().y - 10.0f),
                                          false, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        {
                            auto& items = GameEventHookModule::WorkshopBrowse;
                            const float cardW = 250.0f;
                            const float availW = ImGui::GetContentRegionAvail().x;
                            int perRow = (int)(availW / (cardW + 10.0f));
                            if (perRow < 1) perRow = 1;

                            for (int i = 0; i < (int)items.size(); ++i) {
                                auto& it = items[i];

                                ImGui::PushID(i);
                                ImGui::BeginGroup();
                                {
                                    const ImVec2 origin = ImGui::GetCursorScreenPos();
                                    ImDrawList* dl = ImGui::GetWindowDrawList();

                                    const ImVec2 imgSize(cardW, cardW * 0.5625f);
                                    if (it.previewTexture) {
                                        ImGui::Image((ImTextureID)it.previewTexture, imgSize);
                                    } else {
                                        dl->AddRectFilled(origin, ImVec2(origin.x + imgSize.x, origin.y + imgSize.y),
                                                          gui.button.to_im_color(), 4.0f);
                                        dl->AddRect(origin, ImVec2(origin.x + imgSize.x, origin.y + imgSize.y),
                                                    gui.border.to_im_color(), 4.0f);
                                        const char* ph = ICON_FA_IMAGE;
                                        const ImVec2 ts = ImGui::CalcTextSize(ph);
                                        dl->AddText(ImVec2(origin.x + (imgSize.x - ts.x) * 0.5f,
                                                           origin.y + (imgSize.y - ts.y) * 0.5f),
                                                    gui.text_disabled.to_im_color(), ph);
                                        ImGui::Dummy(imgSize);
                                    }

                                    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + cardW);
                                    ImGui::TextColored(gui.accent_color.to_vec4(), "%s", it.title.c_str());
                                    ImGui::PopTextWrapPos();

                                    if (!it.author.empty()) {
                                        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + cardW);
                                        ImGui::TextDisabled(ICON_FA_USER "  %s", it.author.c_str());
                                        ImGui::PopTextWrapPos();
                                    }
                                    if (it.fileSize > 0)
                                        ImGui::TextDisabled(ICON_FA_HDD "  %.1f MB   " ICON_FA_STAR "  %d",
                                                            (double)it.fileSize / (1024.0 * 1024.0), it.subscriptions);
                                    else if (it.source == 1)
                                        ImGui::TextDisabled(ICON_FA_DOWNLOAD "  %d   " ICON_FA_ID_BADGE "  #%s",
                                                            it.subscriptions, it.id.c_str());
                                    else
                                        ImGui::TextDisabled(ICON_FA_STAR "  %d subscribers", it.subscriptions);

                                    if (it.progress >= 0 && it.progress <= 100) {
                                        ImGui::ProgressBar(it.progress / 100.0f, ImVec2(cardW, 18.0f));
                                    } else if (it.progress == -3) {
                                        ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_CLOCK "  %s",
                                                           it.status.empty() ? "Waiting..." : it.status.c_str());
                                    } else if (it.progress == -2) {
                                        ImGui::TextColored(ImVec4(0.90f, 0.35f, 0.35f, 1.0f), ICON_FA_TIMES "  %s",
                                                           it.status.empty() ? "Failed" : it.status.c_str());
                                    } else if (it.installed) {
                                        const char* installedText =
                                            (it.source == 1 && !it.status.empty())
                                                ? it.status.c_str()
                                                : "Installed";
                                        ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.40f, 1.0f),
                                                           ICON_FA_CHECK "  %s", installedText);
                                    } else {
                                        ImGui::Dummy(ImVec2(cardW, 18.0f));
                                    }

                                    const bool webOnly = it.fileUrl.empty() && !it.pageUrl.empty();
                                    const float btnW = webOnly ? (cardW - 16.0f) / 3.0f
                                                               : (cardW - 8.0f) * 0.5f;
                                    const bool busy = (it.progress == -3 ||
                                                       (it.progress >= 0 && it.progress <= 100));
                                    if (busy) ImGui::BeginDisabled();
                                    const char* downloadLabel = it.installed
                                        ? (it.source == 1 ? ICON_FA_CHECK "  Downloaded"
                                                          : ICON_FA_CHECK "  Installed")
                                        : ICON_FA_DOWNLOAD "  Download";
                                    if (ImGui::Button(downloadLabel, ImVec2(btnW, 28.0f)))
                                        GameEventHookModule::DownloadWorkshopItem(i);
                                    if (busy) ImGui::EndDisabled();
                                    if (webOnly) {
                                        ImGui::SameLine();
                                        if (ImGui::Button(ICON_FA_GLOBE "  Page", ImVec2(btnW, 28.0f)))
                                            GameEventHookModule::OpenWorkshopItemPage(i);
                                    }
                                    ImGui::SameLine();
                                    if (ImGui::Button(ICON_FA_PLAY "  Play", ImVec2(btnW, 28.0f))) {
                                        if (!GameEventHookModule::LoadWorkshopItem(i)) {
                                            const char* reason = it.status.empty()
                                                ? "Download the map first"
                                                : it.status.c_str();
                                            Main.SpawnNotification("KingMod", reason, 4);
                                        }
                                    }
                                }
                                ImGui::EndGroup();
                                ImGui::PopID();

                                if ((i % perRow) != perRow - 1 && i != (int)items.size() - 1)
                                    ImGui::SameLine();
                            }

                            if (items.empty() && !GameEventHookModule::WorkshopBrowseLoading)
                                ImGui::TextDisabled("Nothing to show.");
                        }
                        ImGui::EndChild();
                    }
                    else if (s_wsPage == 1) {
                        if (!s_wsInstScanned) {
                            s_wsInstScanned = true;
                            GameEventHookModule::RefreshWorkshopInstalled();
                        }

                        BeginFitSection(s_wsInstH);
                            const float wsThird = (ImGui::GetContentRegionAvail().x - 20.0f) / 3.0f;
                            if (ImGui::Button(ICON_FA_SYNC "  Rescan", ImVec2(wsThird, 30)))
                                GameEventHookModule::RefreshWorkshopInstalled();
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_FOLDER_OPEN "  Workshop Folder", ImVec2(wsThird, 30)))
                                GameEventHookModule::OpenWorkshopFolder();
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_CUBE "  Maps Folder", ImVec2(-1, 30)))
                                GameEventHookModule::OpenCustomMapsFolder();

                            ImGui::Spacing();
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_LIST "  Loader");
                            ImGui::SameLine(kExCol);
                            ImGui::TextDisabled("Rocket League Workshop (automatic)");

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_CUBE "  Selected");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::InputText("##ex_wsmappath", GameEventHookModule::WorkshopMapPath,
                                                 sizeof(GameEventHookModule::WorkshopMapPath)))
                                GameEventHookModule::SaveConfig();

                            if (!GameEventHookModule::WorkshopInstalledStatus.empty()) {
                                ImGui::Spacing();
                                ImGui::PushTextWrapPos(0.0f);
                                ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_INFO_CIRCLE "  %s",
                                                   GameEventHookModule::WorkshopInstalledStatus.c_str());
                                ImGui::PopTextWrapPos();
                            }
                            if (!GameEventHookModule::WorkshopLoadStatus.empty()) {
                                ImGui::PushTextWrapPos(0.0f);
                                ImGui::TextColored(ImVec4(0.58f, 0.78f, 1.0f, 1.0f), ICON_FA_PLAY "  %s",
                                                   GameEventHookModule::WorkshopLoadStatus.c_str());
                                ImGui::PopTextWrapPos();
                            }
                        EndFitSection(s_wsInstH);

                        ImGui::BeginChild("##ex_wsinstalled", ImVec2(0, ImGui::GetContentRegionAvail().y - 10.0f),
                                          false, ImGuiWindowFlags_AlwaysUseWindowPadding);
                        {
                            auto& list = GameEventHookModule::WorkshopInstalled;
                            for (int i = 0; i < (int)list.size(); ++i) {
                                const auto& e = list[i];
                                ImGui::PushID(1000 + i);

                                const bool isSelected =
                                    (!e.mapFile.empty() && e.mapFile == GameEventHookModule::WorkshopMapPath);
                                if (isSelected)
                                    ImGui::PushStyleColor(ImGuiCol_ChildBg, gui.accent_color.to_vec4(0.16f));
                                ImGui::BeginChild(ImGui::GetID("row"), ImVec2(0, 86.0f), true,
                                                  ImGuiWindowFlags_AlwaysUseWindowPadding);
                                {
                                    const char* kindIcon = (e.kind == 0) ? ICON_FA_CUBE : ICON_FA_FILE_ARCHIVE;
                                    ImGui::TextColored(gui.accent_color.to_vec4(), "%s  %s", kindIcon, e.name.c_str());

                                    if (!e.innerMap.empty())
                                        ImGui::TextDisabled(ICON_FA_BOX_OPEN "  %s", e.innerMap.c_str());
                                    else if (e.kind != 0)
                                        ImGui::TextDisabled(ICON_FA_BOX_OPEN "  ?");
                                    else
                                        ImGui::TextDisabled(" ");

                                    ImGui::TextDisabled(ICON_FA_HDD "  %.1f MB      %s",
                                                        (double)e.size / (1024.0 * 1024.0), e.status.c_str());

                                    ImGui::SameLine();
                                    const float rowBtnW = 104.0f;
                                    float rightX = ImGui::GetContentRegionMax().x - rowBtnW;
                                    const bool canExtract = (e.kind != 0);
                                    if (canExtract) rightX -= rowBtnW + 6.0f;
                                    rightX -= rowBtnW + 6.0f;
                                    if (rightX < ImGui::GetCursorPosX() + 8.0f)
                                        rightX = ImGui::GetCursorPosX() + 8.0f;
                                    ImGui::SetCursorPosX(rightX);

                                    if (canExtract) {
                                        if (ImGui::Button(ICON_FA_BOX_OPEN "  Extract", ImVec2(rowBtnW, 26.0f)))
                                            GameEventHookModule::ExtractWorkshopInstalled(i);
                                        ImGui::SameLine();
                                    }

                                    const bool canLoad = !e.mapFile.empty();
                                    if (!canLoad) ImGui::BeginDisabled();
                                    if (ImGui::Button(ICON_FA_PLAY "  Load", ImVec2(rowBtnW, 26.0f))) {
                                        strncpy_s(GameEventHookModule::WorkshopMapPath,
                                                  sizeof(GameEventHookModule::WorkshopMapPath),
                                                  e.mapFile.c_str(), _TRUNCATE);
                                        GameEventHookModule::SaveConfig();
                                        GameEventHookModule::LoadWorkshopMap(
                                            false, 0, 8, std::string(), std::string(),
                                            std::string(), std::string(), true);
                                    }
                                    if (!canLoad) ImGui::EndDisabled();

                                    ImGui::SameLine();
                                    if (ImGui::Button(ICON_FA_TRASH "  Delete", ImVec2(rowBtnW, 26.0f))) {
                                        GameEventHookModule::DeleteWorkshopInstalled(i);
                                        ImGui::EndChild();
                                        if (isSelected) ImGui::PopStyleColor();
                                        ImGui::PopID();
                                        break;
                                    }
                                }
                                ImGui::EndChild();
                                if (isSelected) ImGui::PopStyleColor();
                                ImGui::PopID();
                            }

                            if (list.empty())
                                ImGui::TextDisabled("No maps or archives in the workshop folder.");
                        }
                        ImGui::EndChild();
                    }
                    else {
                        static const char* const sessionModes[] = {
                            "Freeplay",
                            "Exhibition Match"
                        };
                        struct ArenaOption { const char* package; const char* name; };
                        static const ArenaOption arenas[] = {
                            { "ARC_Darc_P", "Starbase ARC (Aftermath)" },
                            { "ARC_P", "ARCtagon" },
                            { "CHN_Stadium_Day_P", "Forbidden Temple (Day)" },
                            { "CHN_Stadium_P", "Forbidden Temple" },
                            { "EuroStadium_Night_P", "Mannfield (Night)" },
                            { "EuroStadium_P", "Mannfield" },
                            { "EuroStadium_Rainy_P", "Mannfield (Stormy)" },
                            { "Farm_Night_P", "Farmstead (Night)" },
                            { "Haunted_TrainStation_P", "Urban Central (Haunted)" },
                            { "HoopsStadium_P", "Dunk House" },
                            { "Labs_Basin_P", "Basin" },
                            { "Labs_CirclePillars_P", "Pillars" },
                            { "Labs_Corridor_P", "Corridor" },
                            { "Labs_Cosmic_P", "Cosmic (Old)" },
                            { "Labs_Cosmic_V4_P", "Cosmic (New)" },
                            { "Labs_DoubleGoal_P", "Double Goal (Old)" },
                            { "Labs_DoubleGoal_V2_P", "Double Goal (New)" },
                            { "Labs_Galleon_Mast_P", "Galleon Retro" },
                            { "Labs_Galleon_P", "Galleon" },
                            { "Labs_Holyfield_P", "Loophole" },
                            { "Labs_Octagon_02_P", "Octagon (New)" },
                            { "Labs_Octagon_P", "Octagon (Old)" },
                            { "Labs_PillarGlass_P", "Hourglass" },
                            { "Labs_PillarHeat_P", "Barricade" },
                            { "Labs_PillarWings_P", "Colossus" },
                            { "Labs_Underpass_P", "Underpass" },
                            { "Labs_Utopia_P", "Utopia Retro" },
                            { "NeoTokyo_P", "Tokyo Underpass" },
                            { "NeoTokyo_Standard_P", "Neo Tokyo" },
                            { "NeoTokyo_Toon_p", "Neo Tokyo (Comic)" },
                            { "Park_Night_P", "Beckwith Park (Midnight)" },
                            { "Park_P", "Beckwith Park" },
                            { "Park_Rainy_P", "Beckwith Park (Stormy)" },
                            { "Park_Snowy_P", "Beckwith Park (Snowy)" },
                            { "ShatterShot_P", "Core 707" },
                            { "Stadium_Foggy_P", "DFH Stadium (Stormy)" },
                            { "Stadium_P", "DFH Stadium" },
                            { "Stadium_Race_Day_p", "DFH Stadium (Circuit)" },
                            { "Stadium_Winter_P", "DFH Stadium (Snowy)" },
                            { "TrainStation_Dawn_P", "Urban Central (Dawn)" },
                            { "TrainStation_Night_P", "Urban Central (Night)" },
                            { "TrainStation_P", "Urban Central" },
                            { "Underwater_P", "AquaDome" },
                            { "UtopiaStadium_Dusk_P", "Utopia Coliseum (Dusk)" },
                            { "UtopiaStadium_P", "Utopia Coliseum" },
                            { "UtopiaStadium_Snow_P", "Utopia Coliseum (Snowy)" },
                            { "Wasteland_Night_P", "Badlands (Night)" },
                            { "Wasteland_P", "Badlands" },
                            { "arc_standard_p", "Starbase ARC" },
                            { "bb_p", "Champions Field (NFL)" },
                            { "beach_P", "Salty Shores" },
                            { "beach_night_p", "Salty Shores (Night)" },
                            { "cs_day_p", "Champions Field (Day)" },
                            { "cs_hw_p", "Rivals Arena" },
                            { "cs_p", "Champions Field" },
                            { "eurostadium_snownight_p", "Mannfield (Snowy)" },
                            { "farm_p", "Farmstead" },
                            { "music_p", "Neon Fields" },
                            { "outlaw_p", "Deadeye Canyon" },
                            { "park_bman_p", "Beckwith Park (Batman)" },
                            { "stadium_day_p", "DFH Stadium (Day)" },
                            { "throwbackhockey_p", "Throwback Stadium (Snowy)" },
                            { "throwbackstadium_P", "Throwback Stadium" },
                            { "wasteland_Night_S_P", "Wasteland (Night)" },
                            { "wasteland_s_p", "Wasteland" }
                        };
                        static const char* const gameModes[] = {
                            "Soccar", "Hoops", "Snow Day", "Rumble",
                            "Dropshot", "Heatseeker", "Gridiron"
                        };
                        struct MatchOption { const char* name; const char* values; };
                        static const MatchOption matchOptions[] = {
                            { "Match Length", "5 Minutes\0" "10 Minutes\0" "20 Minutes\0" "Unlimited\0" },
                            { "Max Score", "Default\0" "1 Goal\0" "3 Goals\0" "5 Goals\0" "7 Goals\0" "Unlimited\0" },
                            { "Overtime", "Unlimited\0" "+5 Max, First Score\0" "+5 Max, Random Team\0" },
                            { "Max Time", "Default\0" "11 Minutes\0" },
                            { "Series Length", "Unlimited\0" "3 Games\0" "5 Games\0" "7 Games\0" },
                            { "Game Speed", "Default\0" "Slo-mo\0" "Time Warp\0" },
                            { "Ball Max Speed", "Default\0" "Slow\0" "Fast\0" "Super Fast\0" },
                            { "Ball Type", "Default\0" "Cube\0" "Puck\0" "Basketball\0" "Beach Ball\0" "Anniversary\0" "Haunted\0" },
                            { "Ball Gravity", "Default\0" "Low\0" "High\0" "Super High\0" },
                            { "Ball Physics", "Default\0" "Light\0" "Heavy\0" "Super Light\0" "Curveball\0" "Beach Curve\0" },
                            { "Ball Size", "Default\0" "Small\0" "Medium\0" "Large\0" "Gigantic\0" },
                            { "Bounciness", "Default\0" "Low\0" "High\0" "Super High\0" },
                            { "Ball Count", "One\0" },
                            { "Boost Amount", "Default\0" "No Boost\0" "Unlimited\0" "Recharge Slow\0" "Recharge Fast\0" },
                            { "Rumble", "None\0" "Default\0" "Slow\0" "Civilized\0" "Destruction Derby\0" "Spring Loaded\0" "Spikes Only\0" "Rugby\0" "Haunted Beam\0" "Tactical\0" },
                            { "Boost Strength", "1x\0" "1.5x\0" "2x\0" "10x\0" },
                            { "World Gravity", "Default\0" "Low\0" "High\0" "Super High\0" "Reverse\0" },
                            { "Demolitions", "Default\0" "Disabled\0" "Friendly Fire\0" "On Contact\0" "On Contact FF\0" },
                            { "Respawn", "3 Seconds\0" "2 Seconds\0" "1 Second\0" "No Goal Reset\0" },
                            { "Bot Loadouts", "Default\0" "Random\0" },
                            { "Audio", "Default\0" "Haunted\0" },
                            { "Game Event", "Default\0" "Haunted\0" "Rugby\0" }
                        };
                        static_assert(sizeof(matchOptions) / sizeof(matchOptions[0]) ==
                                      CustomMatchModule::HostMutatorCount);
                        static char s_wsWorkshopFilter[64] = "";
                        static char s_wsArenaFilter[64] = "";

                        if (CustomMatchModule::LanHostIP.empty())
                            CustomMatchModule::LanHostIP = CustomMatchModule::GetDetectedLocalIP();

                        BeginFitSection(s_wsSessionH);
                            ImGui::TextColored(g_RedThemeColor, ICON_FA_GAMEPAD "  FREEPLAY / LOCAL LAUNCHER");
                            ImGui::Spacing();

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_GAMEPAD "  Session Type");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::Combo("##ws_session_type",
                                    &CustomMatchModule::WorkshopLocalMode,
                                    sessionModes, IM_ARRAYSIZE(sessionModes)))
                                CustomMatchModule::SaveConfig();

                            ImGui::Spacing();
                            ImGui::Separator();
                            ImGui::Spacing();

                            const int sessionMode = CustomMatchModule::WorkshopLocalMode;
                            if (sessionMode != 2) {
                                ImGui::TextDisabled("Choose an installed Workshop map and launch it locally.");

                                ImGui::AlignTextToFramePadding();
                                ImGui::TextUnformatted(ICON_FA_MAP "  Map");
                                ImGui::SameLine(kExCol);
                                ImGui::SetNextItemWidth(-1.0f);

                                if (true) {
                                    if (!s_wsSessionScanned) {
                                        s_wsSessionScanned = true;
                                        GameEventHookModule::RefreshWorkshopMapList();
                                    }

                                    std::string selectedName = "Select an installed map";
                                    if (GameEventHookModule::WorkshopMapPath[0] != '\0') {
                                        selectedName = std::filesystem::path(
                                            GameEventHookModule::WorkshopMapPath).stem().string();
                                    }
                                    if (ImGui::BeginCombo("##ws_session_map", selectedName.c_str())) {
                                        ImGui::SetNextItemWidth(-1.0f);
                                        ImGui::InputTextWithHint("##ws_workshop_filter", ICON_FA_SEARCH "  Search maps...",
                                                                 s_wsWorkshopFilter, sizeof(s_wsWorkshopFilter));
                                        std::string filter = s_wsWorkshopFilter;
                                        std::transform(filter.begin(), filter.end(), filter.begin(),
                                            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                        for (const std::string& mapPath : GameEventHookModule::WorkshopMapList) {
                                            const std::string label = std::filesystem::path(mapPath).stem().string();
                                            std::string searchable = label;
                                            std::transform(searchable.begin(), searchable.end(), searchable.begin(),
                                                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                            if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                                continue;
                                            ImGui::PushID(mapPath.c_str());
                                            const bool selected = mapPath == GameEventHookModule::WorkshopMapPath;
                                            if (ImGui::Selectable(label.c_str(), selected)) {
                                                strncpy_s(GameEventHookModule::WorkshopMapPath,
                                                          sizeof(GameEventHookModule::WorkshopMapPath),
                                                          mapPath.c_str(), _TRUNCATE);
                                                GameEventHookModule::SaveConfig();
                                            }
                                            if (selected) ImGui::SetItemDefaultFocus();
                                            ImGui::PopID();
                                        }
                                        if (GameEventHookModule::WorkshopMapList.empty())
                                            ImGui::TextDisabled("No installed .upk or .udk maps");
                                        ImGui::EndCombo();
                                    }
                                }
                                else {
                                    constexpr int arenaCount = static_cast<int>(sizeof(arenas) / sizeof(arenas[0]));
                                    CustomMatchModule::WorkshopArenaIndex = std::clamp(
                                        CustomMatchModule::WorkshopArenaIndex, 0, arenaCount - 1);
                                    const char* preview = arenas[CustomMatchModule::WorkshopArenaIndex].name;
                                    if (ImGui::BeginCombo("##ws_standard_map", preview)) {
                                        ImGui::SetNextItemWidth(-1.0f);
                                        ImGui::InputTextWithHint("##ws_arena_filter", ICON_FA_SEARCH "  Search arenas...",
                                                                 s_wsArenaFilter, sizeof(s_wsArenaFilter));
                                        std::string filter = s_wsArenaFilter;
                                        std::transform(filter.begin(), filter.end(), filter.begin(),
                                            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                        for (int arenaIndex = 0; arenaIndex < arenaCount; ++arenaIndex) {
                                            std::string searchable = arenas[arenaIndex].name;
                                            std::transform(searchable.begin(), searchable.end(), searchable.begin(),
                                                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                            if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                                continue;
                                            const bool selected = CustomMatchModule::WorkshopArenaIndex == arenaIndex;
                                            if (ImGui::Selectable(arenas[arenaIndex].name, selected)) {
                                                CustomMatchModule::WorkshopArenaIndex = arenaIndex;
                                                CustomMatchModule::SaveConfig();
                                            }
                                            if (selected) ImGui::SetItemDefaultFocus();
                                        }
                                        ImGui::EndCombo();
                                    }
                                }

                                if (sessionMode == 1) {
                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_GAMEPAD "  Mode");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    if (ImGui::Combo("##ws_game_mode",
                                                     &CustomMatchModule::WorkshopGameModeIndex,
                                                     gameModes, 7))
                                        CustomMatchModule::SaveConfig();

                                    int playersIndex = std::clamp(CustomMatchModule::MaxPlayers / 2 - 1, 0, 3);
                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_USERS "  Players");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    if (ImGui::Combo("##ws_players", &playersIndex, "2\0" "4\0" "6\0" "8\0")) {
                                        CustomMatchModule::MaxPlayers = (playersIndex + 1) * 2;
                                        CustomMatchModule::SaveConfig();
                                    }

                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_ROBOT "  Bots");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    if (ImGui::Combo("##ws_bot_difficulty", &CustomMatchModule::BotDifficulty,
                                            "None\0" "Beginner\0" "Rookie\0" "Pro\0" "All-Star\0" "Unfair\0"))
                                        CustomMatchModule::SaveConfig();

                                    ImGui::Spacing();
                                    ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_SLIDERS_H "  ADVANCED MATCH SETTINGS");
                                    ImGui::Spacing();
                                    if (ImGui::BeginTable("##ws_advanced_match_settings", 3,
                                            ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_PadOuterX)) {
                                                                                                         
                                                                                                             
                                                                                              
                                        if (CustomMatchModule::HostMutatorCount > 12)
                                            CustomMatchModule::HostMutatorSelections[12] = 0;

                                        for (size_t optionIndex = 0;
                                             optionIndex < static_cast<size_t>(CustomMatchModule::HostMutatorCount);
                                             ++optionIndex) {
                                            if (optionIndex == 12)
                                                continue;
                                            ImGui::TableNextColumn();
                                            ImGui::PushID(static_cast<int>(optionIndex));
                                            ImGui::TextDisabled("%s", matchOptions[optionIndex].name);
                                            ImGui::SetNextItemWidth(-1.0f);
                                            if (ImGui::Combo("##value",
                                                    &CustomMatchModule::HostMutatorSelections[optionIndex],
                                                    matchOptions[optionIndex].values))
                                                CustomMatchModule::SaveConfig();
                                            ImGui::PopID();
                                        }
                                        ImGui::EndTable();
                                    }

                                    ImGui::Spacing();

                                    if (false) {
                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_WIFI "  Share IP");
                                    ImGui::SameLine(kExCol);
                                    const float refreshW = 104.0f;
                                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - refreshW - 8.0f);
                                    ImGui::InputTextWithHint("##ws_host_ip", "Radmin / LAN IPv4",
                                                             &CustomMatchModule::LanHostIP);
                                    if (ImGui::IsItemDeactivatedAfterEdit())
                                        CustomMatchModule::SaveConfig();
                                    ImGui::SameLine();
                                    if (ImGui::Button(ICON_FA_SYNC "  Detect", ImVec2(-1.0f, 0.0f))) {
                                        CustomMatchModule::LanHostIP = CustomMatchModule::GetDetectedLocalIP();
                                        CustomMatchModule::SaveConfig();
                                    }

                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_NETWORK_WIRED "  UDP Port");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    CustomMatchModule::LanHostPort = "7777";
                                    ImGui::InputText("##ws_host_port", &CustomMatchModule::LanHostPort,
                                                     ImGuiInputTextFlags_ReadOnly);

                                    if (ImGui::Button(ICON_FA_COPY "  Copy Join Address", ImVec2(-1.0f, 28.0f))) {
                                        const std::string address = CustomMatchModule::LanHostIP + ":7777";
                                        ImGui::SetClipboardText(address.c_str());
                                        Main.SpawnNotification("KingMod", "Copied " + address, 2);
                                    }

                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_LOCK "  Password");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    ImGui::InputTextWithHint("##ws_host_password", "Optional: letters and numbers",
                                                             &CustomMatchModule::HostPassword);
                                    if (ImGui::IsItemDeactivatedAfterEdit())
                                        CustomMatchModule::SaveConfig();
                                    }
                                }

                                ImGui::Spacing();
                                const char* launchLabel = sessionMode == 1
                                    ? ICON_FA_FUTBOL "  Launch Exhibition Match##ws_launch_exhibition"
                                    : ICON_FA_PLAY "  Launch Freeplay##ws_launch_freeplay";
                                if (ImGui::Button(launchLabel, ImVec2(-1.0f, 36.0f))) {
                                    CustomMatchModule::SaveConfig();
                                    if (true) {
                                        GameEventHookModule::LoadWorkshopMap(
                                            false,
                                            CustomMatchModule::WorkshopGameModeIndex,
                                            CustomMatchModule::MaxPlayers,
                                            std::string(),
                                            CustomMatchModule::BuildGameTagsString(sessionMode == 0),
                                            std::string(), std::string(), sessionMode == 0);
                                    }
                                    else {
                                        GameEventHookModule::LaunchStandardMap(
                                            arenas[CustomMatchModule::WorkshopArenaIndex].package,
                                            sessionMode == 1,
                                            CustomMatchModule::WorkshopGameModeIndex,
                                            CustomMatchModule::MaxPlayers,
                                            CustomMatchModule::HostPassword,
                                            CustomMatchModule::BuildGameTagsString(false));
                                    }
                                }
                            }
                            else {
                                if (ImGui::Checkbox("##ws_join_use_workshop", &CustomMatchModule::WorkshopUseMap))
                                    CustomMatchModule::SaveConfig();
                                ImGui::SameLine();
                                ImGui::TextUnformatted("Preload the host's Workshop map");

                                if (CustomMatchModule::WorkshopUseMap) {
                                    if (!s_wsSessionScanned) {
                                        s_wsSessionScanned = true;
                                        GameEventHookModule::RefreshWorkshopMapList();
                                    }

                                    ImGui::AlignTextToFramePadding();
                                    ImGui::TextUnformatted(ICON_FA_MAP "  Map");
                                    ImGui::SameLine(kExCol);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    std::string selectedName = "Select the same map as the host";
                                    if (GameEventHookModule::WorkshopMapPath[0] != '\0')
                                        selectedName = std::filesystem::path(
                                            GameEventHookModule::WorkshopMapPath).stem().string();
                                    if (ImGui::BeginCombo("##ws_join_workshop_map", selectedName.c_str())) {
                                        ImGui::SetNextItemWidth(-1.0f);
                                        ImGui::InputTextWithHint("##ws_join_workshop_filter",
                                            ICON_FA_SEARCH "  Search maps...",
                                            s_wsWorkshopFilter, sizeof(s_wsWorkshopFilter));
                                        std::string filter = s_wsWorkshopFilter;
                                        std::transform(filter.begin(), filter.end(), filter.begin(),
                                            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                        for (const std::string& mapPath : GameEventHookModule::WorkshopMapList) {
                                            const std::string label = std::filesystem::path(mapPath).stem().string();
                                            std::string searchable = label;
                                            std::transform(searchable.begin(), searchable.end(), searchable.begin(),
                                                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                            if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                                continue;
                                            ImGui::PushID(mapPath.c_str());
                                            const bool selected = mapPath == GameEventHookModule::WorkshopMapPath;
                                            if (ImGui::Selectable(label.c_str(), selected)) {
                                                strncpy_s(GameEventHookModule::WorkshopMapPath,
                                                          sizeof(GameEventHookModule::WorkshopMapPath),
                                                          mapPath.c_str(), _TRUNCATE);
                                                GameEventHookModule::SaveConfig();
                                            }
                                            if (selected) ImGui::SetItemDefaultFocus();
                                            ImGui::PopID();
                                        }
                                        if (GameEventHookModule::WorkshopMapList.empty())
                                            ImGui::TextDisabled("No installed .upk or .udk maps");
                                        ImGui::EndCombo();
                                    }
                                }

                                ImGui::AlignTextToFramePadding();
                                ImGui::TextUnformatted(ICON_FA_WIFI "  Host / Domain");
                                ImGui::SameLine(kExCol);
                                ImGui::SetNextItemWidth(-1.0f);
                                ImGui::InputTextWithHint("##ws_join_ip", "26.10.20.30 or play.example.com",
                                                         &CustomMatchModule::LanJoinIP);
                                if (ImGui::IsItemDeactivatedAfterEdit())
                                    CustomMatchModule::SaveConfig();

                                ImGui::AlignTextToFramePadding();
                                ImGui::TextUnformatted(ICON_FA_NETWORK_WIRED "  Port");
                                ImGui::SameLine(kExCol);
                                ImGui::SetNextItemWidth(-1.0f);
                                ImGui::InputTextWithHint("##ws_join_port", "7777",
                                                         &CustomMatchModule::LanJoinPort,
                                                         ImGuiInputTextFlags_CharsDecimal);
                                if (ImGui::IsItemDeactivatedAfterEdit())
                                    CustomMatchModule::SaveConfig();

                                ImGui::AlignTextToFramePadding();
                                ImGui::TextUnformatted(ICON_FA_LOCK "  Password");
                                ImGui::SameLine(kExCol);
                                ImGui::SetNextItemWidth(-1.0f);
                                ImGui::InputTextWithHint("##ws_join_password", "Optional",
                                                         &CustomMatchModule::JoinPassword);
                                if (ImGui::IsItemDeactivatedAfterEdit())
                                    CustomMatchModule::SaveConfig();

                                ImGui::Spacing();
                                if (ImGui::Button(ICON_FA_LINK "  Join Match", ImVec2(-1.0f, 36.0f))) {
                                    CustomMatchModule::SaveConfig();
                                    if (CustomMatchModule::WorkshopUseMap) {
                                        GameEventHookModule::LoadWorkshopMap(
                                            false, 0, 8, CustomMatchModule::JoinPassword,
                                            std::string(),
                                            CustomMatchModule::LanJoinIP,
                                            CustomMatchModule::LanJoinPort);
                                    }
                                    else {
                                        if (!CustomMatchModule::JoinLanMatchByIP(
                                                CustomMatchModule::LanJoinIP,
                                                CustomMatchModule::LanJoinPort,
                                                CustomMatchModule::JoinPassword)) {
                                            Main.SpawnNotification("KingMod",
                                                "Enter a valid host/domain, port and password", 4);
                                        }
                                    }
                                }
                            }

                            ImGui::Spacing();
                            ImGui::PushTextWrapPos(0.0f);
                            if (CustomMatchModule::WorkshopLocalMode == 1) {
                                ImGui::TextDisabled(ICON_FA_INFO_CIRCLE
                                    "  Exhibition Match uses your mode, bots and advanced settings. It is not joinable by other players.");
                            }
                            else {
                                ImGui::TextDisabled(ICON_FA_INFO_CIRCLE
                                    "  Freeplay starts the Workshop map with local training controls.");
                            }
                            ImGui::PopTextWrapPos();

                            if (!GameEventHookModule::WorkshopLoadStatus.empty()) {
                                ImGui::Spacing();
                                ImGui::TextColored(gui.accent_color.to_vec4(), "%s",
                                                   GameEventHookModule::WorkshopLoadStatus.c_str());
                            }
                        EndFitSection(s_wsSessionH);
                    }
                }

                else if (gui.m_active_subtab[gui.m_tab] == 4) {
                    static float s_serverH = 0.0f;
                    static bool s_serverScanned = false;
                    static char s_serverWorkshopFilter[64] = "";
                    static char s_serverArenaFilter[64] = "";
                    static int  s_botMgmtSkill = 4;

                    if (!s_serverScanned) {
                        s_serverScanned = true;
                        GameEventHookModule::RefreshWorkshopMapList();
                        if (GameEventHookModule::WorkshopMapPath[0] == '\0' &&
                            !GameEventHookModule::WorkshopMapList.empty()) {
                            strncpy_s(GameEventHookModule::WorkshopMapPath,
                                sizeof(GameEventHookModule::WorkshopMapPath),
                                GameEventHookModule::WorkshopMapList.front().c_str(), _TRUNCATE);
                            GameEventHookModule::SaveConfig();
                        }
                    }
                    if (CustomMatchModule::LanHostIP.empty())
                        CustomMatchModule::LanHostIP = CustomMatchModule::GetDetectedLocalIP();

                    BeginFitSection(s_serverH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SERVER "  SERVER");
                        ImGui::Spacing();

                        static const char* const serverModes[] = {
                            ICON_FA_SERVER "  Host LAN Match##server_mode_host",
                            ICON_FA_LINK "  Join LAN Match##server_mode_join"
                        };
                        const float serverModeW = (ImGui::GetContentRegionAvail().x - 8.0f) * 0.5f;
                        for (int mode = 0; mode < 2; ++mode) {
                            const bool selected = CustomMatchModule::ServerSessionMode == mode;
                            if (selected) {
                                ImGui::PushStyleColor(ImGuiCol_Button, gui.accent_color.to_vec4());
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, gui.accent_color.to_vec4());
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive, gui.accent_color.to_vec4());
                            }
                            if (ImGui::Button(serverModes[mode], ImVec2(mode == 0 ? serverModeW : -1.0f, 32.0f))) {
                                CustomMatchModule::ServerSessionMode = mode;
                                CustomMatchModule::SaveConfig();
                            }
                            if (selected) ImGui::PopStyleColor(3);
                            if (mode == 0) ImGui::SameLine();
                        }

                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::Spacing();

                        if (ImGui::Checkbox("##server_use_workshop", &CustomMatchModule::WorkshopUseMap))
                            CustomMatchModule::SaveConfig();
                        ImGui::SameLine();
                        ImGui::TextUnformatted(CustomMatchModule::ServerSessionMode == 0
                            ? "Host a Workshop map" : "Preload the host's Workshop map");

                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_MAP "  Map");
                        ImGui::SameLine(kExCol);
                        ImGui::SetNextItemWidth(-1.0f);
                        if (CustomMatchModule::WorkshopUseMap) {
                            std::string selectedName = CustomMatchModule::ServerSessionMode == 0
                                ? "Select an installed map" : "Select the same map as the host";
                            if (GameEventHookModule::WorkshopMapPath[0] != '\0')
                                selectedName = std::filesystem::path(GameEventHookModule::WorkshopMapPath).stem().string();
                            if (ImGui::BeginCombo("##server_workshop_map", selectedName.c_str())) {
                                ImGui::SetNextItemWidth(-1.0f);
                                ImGui::InputTextWithHint("##server_workshop_filter", ICON_FA_SEARCH "  Search maps...",
                                    s_serverWorkshopFilter, sizeof(s_serverWorkshopFilter));
                                std::string filter = s_serverWorkshopFilter;
                                std::transform(filter.begin(), filter.end(), filter.begin(),
                                    [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                for (const std::string& mapPath : GameEventHookModule::WorkshopMapList) {
                                    const std::string label = std::filesystem::path(mapPath).stem().string();
                                    std::string searchable = label;
                                    std::transform(searchable.begin(), searchable.end(), searchable.begin(),
                                        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                    if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                        continue;
                                    ImGui::PushID(mapPath.c_str());
                                    const bool selected = mapPath == GameEventHookModule::WorkshopMapPath;
                                    if (ImGui::Selectable(label.c_str(), selected)) {
                                        strncpy_s(GameEventHookModule::WorkshopMapPath,
                                            sizeof(GameEventHookModule::WorkshopMapPath), mapPath.c_str(), _TRUNCATE);
                                        GameEventHookModule::SaveConfig();
                                    }
                                    if (selected) ImGui::SetItemDefaultFocus();
                                    ImGui::PopID();
                                }
                                if (GameEventHookModule::WorkshopMapList.empty())
                                    ImGui::TextDisabled("No installed .upk or .udk maps");
                                ImGui::EndCombo();
                            }
                        }
                        else {
                            constexpr int arenaCount = static_cast<int>(IM_ARRAYSIZE(arenas));
                            CustomMatchModule::WorkshopArenaIndex = std::clamp(
                                CustomMatchModule::WorkshopArenaIndex, 0, arenaCount - 1);
                            if (ImGui::BeginCombo("##server_arena",
                                    arenas[CustomMatchModule::WorkshopArenaIndex].name)) {
                                ImGui::SetNextItemWidth(-1.0f);
                                ImGui::InputTextWithHint("##server_arena_filter", ICON_FA_SEARCH "  Search arenas...",
                                    s_serverArenaFilter, sizeof(s_serverArenaFilter));
                                std::string filter = s_serverArenaFilter;
                                std::transform(filter.begin(), filter.end(), filter.begin(),
                                    [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                for (int arenaIndex = 0; arenaIndex < arenaCount; ++arenaIndex) {
                                    std::string searchable = arenas[arenaIndex].name;
                                    std::transform(searchable.begin(), searchable.end(), searchable.begin(),
                                        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                    if (!filter.empty() && searchable.find(filter) == std::string::npos)
                                        continue;
                                    const bool selected = CustomMatchModule::WorkshopArenaIndex == arenaIndex;
                                    if (ImGui::Selectable(arenas[arenaIndex].name, selected)) {
                                        CustomMatchModule::WorkshopArenaIndex = arenaIndex;
                                        CustomMatchModule::SaveConfig();
                                    }
                                    if (selected) ImGui::SetItemDefaultFocus();
                                }
                                ImGui::EndCombo();
                            }
                        }

                        if (CustomMatchModule::ServerSessionMode == 0) {
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_GAMEPAD "  Mode");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::Combo("##server_game_mode", &CustomMatchModule::WorkshopGameModeIndex,
                                    gameModes, IM_ARRAYSIZE(gameModes)))
                                CustomMatchModule::SaveConfig();

                            int playersIndex = std::clamp(CustomMatchModule::MaxPlayers / 2 - 1, 0, 3);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_USERS "  Players");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::Combo("##server_players", &playersIndex, "2\0" "4\0" "6\0" "8\0")) {
                                CustomMatchModule::MaxPlayers = (playersIndex + 1) * 2;
                                CustomMatchModule::SaveConfig();
                            }

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_ROBOT "  Bots");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            if (ImGui::Combo("##server_bots", &CustomMatchModule::BotDifficulty,
                                    "None\0" "Beginner\0" "Rookie\0" "Pro\0" "All-Star\0" "Unfair\0"))
                                CustomMatchModule::SaveConfig();

                            ImGui::Spacing();
                            ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_SLIDERS_H "  ADVANCED MATCH SETTINGS");
                            ImGui::Spacing();
                            if (ImGui::BeginTable("##server_advanced", 3,
                                    ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_PadOuterX)) {
                                for (size_t optionIndex = 0;
                                     optionIndex < static_cast<size_t>(CustomMatchModule::HostMutatorCount);
                                     ++optionIndex) {
                                    ImGui::TableNextColumn();
                                    ImGui::PushID(static_cast<int>(optionIndex));
                                    ImGui::TextDisabled("%s", matchOptions[optionIndex].name);
                                    ImGui::SetNextItemWidth(-1.0f);
                                    if (ImGui::Combo("##server_value",
                                            &CustomMatchModule::HostMutatorSelections[optionIndex],
                                            matchOptions[optionIndex].values))
                                        CustomMatchModule::SaveConfig();
                                    ImGui::PopID();
                                }
                                ImGui::EndTable();
                            }

                            ImGui::Spacing();
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_WIFI "  Share IP");
                            ImGui::SameLine(kExCol);
                            const float detectW = 104.0f;
                            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - detectW - 8.0f);
                            ImGui::InputTextWithHint("##server_host_ip", "Radmin / LAN IPv4",
                                &CustomMatchModule::LanHostIP);
                            if (ImGui::IsItemDeactivatedAfterEdit()) CustomMatchModule::SaveConfig();
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_SYNC "  Detect", ImVec2(-1.0f, 0.0f))) {
                                CustomMatchModule::LanHostIP = CustomMatchModule::GetDetectedLocalIP();
                                CustomMatchModule::SaveConfig();
                            }

                            CustomMatchModule::LanHostPort = "7777";
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_NETWORK_WIRED "  UDP Port");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::InputText("##server_host_port", &CustomMatchModule::LanHostPort,
                                ImGuiInputTextFlags_ReadOnly);

                            if (ImGui::Button(ICON_FA_COPY "  Copy Join Address", ImVec2(-1.0f, 28.0f))) {
                                const std::string address = CustomMatchModule::LanHostIP + ":7777";
                                ImGui::SetClipboardText(address.c_str());
                                Main.SpawnNotification("KingMod", "Copied " + address, 2);
                            }

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_LOCK "  Password");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::InputTextWithHint("##server_host_password", "Optional: letters and numbers",
                                &CustomMatchModule::HostPassword);
                            if (ImGui::IsItemDeactivatedAfterEdit()) CustomMatchModule::SaveConfig();

                            ImGui::Spacing();
                            if (ImGui::Button(ICON_FA_SERVER "  Host LAN Match##server_host_action", ImVec2(-1.0f, 36.0f))) {
                                CustomMatchModule::SaveConfig();
                                const std::string tags = CustomMatchModule::BuildGameTagsString(false);
                                if (CustomMatchModule::WorkshopUseMap)
                                    GameEventHookModule::LoadWorkshopMap(true,
                                        CustomMatchModule::WorkshopGameModeIndex,
                                        CustomMatchModule::MaxPlayers,
                                        CustomMatchModule::HostPassword, tags,
                                        std::string(), std::string(), false);
                                else
                                    GameEventHookModule::LaunchStandardMap(
                                        arenas[CustomMatchModule::WorkshopArenaIndex].package, true,
                                        CustomMatchModule::WorkshopGameModeIndex,
                                        CustomMatchModule::MaxPlayers,
                                        CustomMatchModule::HostPassword, tags, false);
                            }

                            ImGui::TextDisabled(ICON_FA_INFO_CIRCLE
                                "  Share the VPN IPv4 above, or forward UDP 7777. Workshop guests need the same map files.");
                        }
                        else {
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_WIFI "  Host / Domain");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::InputTextWithHint("##server_join_host", "26.10.20.30 or play.example.com",
                                &CustomMatchModule::LanJoinIP);
                            if (ImGui::IsItemDeactivatedAfterEdit()) CustomMatchModule::SaveConfig();

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_NETWORK_WIRED "  Port");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::InputTextWithHint("##server_join_port", "7777", &CustomMatchModule::LanJoinPort,
                                ImGuiInputTextFlags_CharsDecimal);
                            if (ImGui::IsItemDeactivatedAfterEdit()) CustomMatchModule::SaveConfig();

                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted(ICON_FA_LOCK "  Password");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::InputTextWithHint("##server_join_password", "Optional",
                                &CustomMatchModule::JoinPassword);
                            if (ImGui::IsItemDeactivatedAfterEdit()) CustomMatchModule::SaveConfig();

                            ImGui::Spacing();
                            if (ImGui::Button(ICON_FA_SATELLITE_DISH "  Request Server Status##server_status_request",
                                    ImVec2(-1.0f, 30.0f))) {
                                CustomMatchModule::SaveConfig();
                                if (!CustomMatchModule::RequestLanServerStatus(
                                        CustomMatchModule::LanJoinIP,
                                        CustomMatchModule::LanJoinPort,
                                        CustomMatchModule::JoinPassword))
                                    Main.SpawnNotification("KingMod Server Test",
                                        "Enter a valid address and port, or wait for the current test", 4);
                            }

                            if (ImGui::Button(ICON_FA_LINK "  Join LAN Match##server_join_action", ImVec2(-1.0f, 36.0f))) {
                                CustomMatchModule::SaveConfig();
                                if (CustomMatchModule::WorkshopUseMap)
                                    GameEventHookModule::LoadWorkshopMap(false, 0, 8,
                                        CustomMatchModule::JoinPassword, std::string(),
                                        CustomMatchModule::LanJoinIP,
                                        CustomMatchModule::LanJoinPort, false);
                                else if (!CustomMatchModule::JoinLanMatchByIP(
                                        CustomMatchModule::LanJoinIP,
                                        CustomMatchModule::LanJoinPort,
                                        CustomMatchModule::JoinPassword))
                                    Main.SpawnNotification("KingMod",
                                        "Enter a valid host/domain, port and password", 4);
                            }

                            ImGui::TextDisabled(ICON_FA_INFO_CIRCLE
                                "  Enter localhost, LAN/VPN/public IP, IPv6, or a DNS name. Leave Password empty if the host has none.");
                            ImGui::TextDisabled("   Public joins require UDP 7777; the status request uses TCP 7777.");
                        }

                                                                              
                        if (Events.CanUseLocalServerFeatures() && GameEventHookModule::IsInGame) {
                            ImGui::Spacing();
                            ImGui::Separator();
                            ImGui::Spacing();
                            ImGui::TextColored(gui.accent_color.to_vec4(), ICON_FA_ROBOT "  BOT MANAGEMENT");
                            ImGui::Spacing();

                                                            
                            static char botNameInput[64] = "Bot";
                            static int s_botMgmtTeam = 0;                                          
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted("Name");
                            ImGui::SameLine(kExCol);
                            const float spawnBtnW = 72.0f;
                            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - spawnBtnW - 8.0f);
                            ImGui::InputText("##bot_mgmt_name", botNameInput, sizeof(botNameInput));
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_PLUS "  Spawn", ImVec2(spawnBtnW, 0.0f))) {
                                std::string bname = botNameInput;
                                if (bname.empty()) bname = "Bot";
                                                                        
                                                                         
                                const int engineTeam = (s_botMgmtTeam == 1) ? 0
                                                     : (s_botMgmtTeam == 2) ? 1 : 255;
                                const int skill = s_botMgmtSkill;
                                                                                      
                                MainComponent::Execute([bname, engineTeam, skill] {
                                    HostSync::SpawnBot(bname, engineTeam, skill);
                                });
                                strncpy_s(botNameInput, sizeof(botNameInput), "Bot", _TRUNCATE);
                            }

                                               
                            ImGui::AlignTextToFramePadding();
                            ImGui::TextUnformatted("Team");
                            ImGui::SameLine(kExCol);
                            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.45f);
                            ImGui::Combo("##bot_mgmt_team", &s_botMgmtTeam, "Auto\0Orange\0Blue\0");
                            ImGui::SameLine();
                            ImGui::TextUnformatted("Skill");
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(-1.0f);
                            ImGui::Combo("##bot_mgmt_skill", &s_botMgmtSkill,
                                "Intro\0Easy\0Medium\0Hard\0Unfair\0");

                                                                   
                            const int botCount = HostSync::GetActiveBotCount();
                            ImGui::TextDisabled("Active bots: %d", botCount);

                                             
                            if (botCount > 0) {
                                ImGui::Spacing();
                                if (ImGui::Button(ICON_FA_TRASH "  Remove All Bots", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 0.0f))) {
                                                                   
                                    MainComponent::Execute([] {
                                        int removed = HostSync::RemoveAllBots();
                                        Main.SpawnNotification("KingMod", "Removed " + std::to_string(removed) + " bot(s)", 2);
                                    });
                                }
                                ImGui::SameLine();
                                static char removeBotName[64] = "";
                                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                                ImGui::InputTextWithHint("##bot_remove_name", "Remove by name...", removeBotName, sizeof(removeBotName));
                                if (ImGui::IsItemDeactivatedAfterEdit() && removeBotName[0] != '\0') {
                                    std::string rname = removeBotName;
                                                                   
                                    MainComponent::Execute([rname] {
                                        HostSync::RemoveBotByName(rname);
                                    });
                                    removeBotName[0] = '\0';
                                }
                            }

                                                           
                            MainComponent::Execute([=] {
                                HostSync::SetBotSkillLevel(s_botMgmtSkill);
                            });

                            ImGui::Spacing();
                        }

                        if (!GameEventHookModule::WorkshopLoadStatus.empty()) {
                            ImGui::Spacing();
                            ImGui::TextColored(gui.accent_color.to_vec4(), "%s",
                                GameEventHookModule::WorkshopLoadStatus.c_str());
                        }
                    EndFitSection(s_serverH);
                }

                                                                        
                else if (gui.m_active_subtab[gui.m_tab] == 5) {
                    static float s_presH = 0.f;
                    static int   s_pageIdx = 0;
                    static int   s_presSel = -1;
                    static char  s_presName[64] = "";

                    BeginFitSection(s_presH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_SAVE "  PRESETS MANAGER");
                        ImGui::Spacing();

                        std::vector<std::string> pages = ModPresets::PageNames();
                        if (s_pageIdx >= (int)pages.size()) s_pageIdx = 0;

                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(ICON_FA_LAYER_GROUP "  Page");
                        ImGui::SameLine(kExCol);
                        ImGui::SetNextItemWidth(240.0f);
                        const bool allPageSelected = !pages.empty() && pages[s_pageIdx] == "ALL";
                        if (allPageSelected) ImGui::PushStyleColor(ImGuiCol_Text, g_RedThemeColor);
                        const bool pageComboOpen = ImGui::BeginCombo("##ex_prespage", pages.empty() ? "" : pages[s_pageIdx].c_str());
                        if (allPageSelected) ImGui::PopStyleColor();
                        if (pageComboOpen) {
                            for (int i = 0; i < (int)pages.size(); ++i) {
                                const bool isAll = pages[i] == "ALL";
                                if (isAll) ImGui::PushStyleColor(ImGuiCol_Text, g_RedThemeColor);
                                if (ImGui::Selectable(pages[i].c_str(), s_pageIdx == i)) {
                                    s_pageIdx = i;
                                    s_presSel = -1;
                                    s_presName[0] = '\0';
                                }
                                if (isAll) ImGui::PopStyleColor();
                            }
                            ImGui::EndCombo();
                        }

                        if (!pages.empty()) {
                            const std::string page = pages[s_pageIdx];
                            std::vector<std::string> names = ModPresets::List(page);
                            const std::string fav = ModPresets::GetFavorite(page);
                            if (s_presSel >= (int)names.size()) s_presSel = -1;

                            ImGui::Spacing();
                            if (ImGui::BeginListBox("##ex_preslist", ImVec2(-1, 140))) {
                                for (int i = 0; i < (int)names.size(); ++i) {
                                    const bool sel = (s_presSel == i);
                                    std::string lbl = (names[i] == fav)
                                        ? (std::string(ICON_FA_STAR "  ") + names[i])
                                        : (std::string("       ") + names[i]);
                                    if (ImGui::Selectable(lbl.c_str(), sel)) {
                                        s_presSel = i;
                                        strncpy_s(s_presName, names[i].c_str(), _TRUNCATE);
                                    }
                                    if (sel && ImGui::IsMouseDoubleClicked(0) && ModPresets::Load(page, names[i])) {
                                        GameEventHookModule::SaveConfig();
                                        Main.SpawnNotification("KingMod", names[i] + " loaded!", 2);
                                    }
                                }
                                if (names.empty())
                                    ImGui::TextDisabled("No presets saved for this page yet.");
                                ImGui::EndListBox();
                            }

                            const float qW = (ImGui::GetContentRegionAvail().x - 30.0f) / 4.0f;
                            const bool haveSel = (s_presSel >= 0 && s_presSel < (int)names.size());

                            if (!haveSel) ImGui::BeginDisabled();
                            if (ImGui::Button(ICON_FA_CHECK "  Load", ImVec2(qW, 30))) {
                                if (ModPresets::Load(page, names[s_presSel])) {
                                    GameEventHookModule::SaveConfig();
                                    Main.SpawnNotification("KingMod", names[s_presSel] + " loaded!", 2);
                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_STAR "  Favorite", ImVec2(qW, 30))) {
                                ModPresets::SetFavorite(page, names[s_presSel] == fav ? std::string() : names[s_presSel]);
                            }
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_TRASH "  Delete", ImVec2(qW, 30))) {
                                if (ModPresets::Delete(page, names[s_presSel])) {
                                    s_presSel = -1;
                                    Main.SpawnNotification("KingMod", "Preset deleted", 2);
                                }
                            }
                            if (!haveSel) ImGui::EndDisabled();
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_SYNC "  Reload List", ImVec2(-1, 30)))
                                s_presSel = -1;

                            ImGui::Spacing();
                            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 130.0f);
                            ImGui::InputTextWithHint("##ex_presname", "Preset name...", s_presName, sizeof(s_presName));
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_SAVE "  Save", ImVec2(-1, 0))) {
                                if (s_presName[0] != '\0' && ModPresets::Save(page, s_presName))
                                    Main.SpawnNotification("KingMod", "Preset saved", 2);
                            }
                        }
                    EndFitSection(s_presH);
                }

                ImGui::PopStyleVar(2);
                gui.end_group_box();
            }

                                                                                
                                                                                   
                                                                                  
                                                                                 
            else if (gui.m_tab == 14) {
                gui.group_box("TAS", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 6));

                                                                             
                enum { kPendingNone = 0, kPendingDelete = 1, kPendingOverwrite = 2 };
                static bool s_confirmNewTAS = true, s_confirmDelete = true, s_confirmOverwrite = true;
                static char s_newName[64] = "";
                static int  s_fileSel = -1;
                static int  s_pending = kPendingNone;
                static std::string s_pendingPath, s_pendingName;
                static std::vector<std::string> s_files;
                static bool s_filesLoaded = false;

                if (!s_filesLoaded) {
                    s_files = KingTAS::GetSavedFiles();
                    s_filesLoaded = true;
                    if (s_fileSel >= (int)s_files.size()) s_fileSel = -1;
                }
                auto savedExists = [&](const std::string& name) -> bool {
                    for (const std::string& p : s_files)
                        if (std::filesystem::path(p).stem().string() == name) return true;
                    return false;
                };

                                                                                
                                                                                 
                                                                            
                                                             
                if (gui.m_active_subtab[14] < 0 || gui.m_active_subtab[14] > 3)
                    gui.m_active_subtab[14] = 0;
                {
                    static const char* kTasTabs[] = {
                        ICON_FA_GAMEPAD " Controls",
                        ICON_FA_COG " Settings",
                        ICON_FA_INFO_CIRCLE " Loaded TAS",
                        ICON_FA_FOLDER_OPEN " Files"
                    };

                                                                                 
                                                                                
                                                                                 
                                                                            
                    const float tasTabStripW = ImGui::GetContentRegionAvail().x;
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, 0.0f));
                    ImGui::BeginChild("##tas_subtabs", ImVec2(tasTabStripW, 32.0f), false,
                        ImGuiWindowFlags_HorizontalScrollbar);

                    ImGui::GetWindowDrawList()->AddRectFilled(
                        ImGui::GetWindowPos(),
                        ImGui::GetWindowPos() + ImGui::GetWindowSize(),
                        gui.button.to_im_color(), 4.0f);
                    ImGui::GetWindowDrawList()->AddRect(
                        ImGui::GetWindowPos(),
                        ImGui::GetWindowPos() + ImGui::GetWindowSize(),
                        gui.border.to_im_color(), 4.0f);

                    for (int tasTab = 0; tasTab < IM_ARRAYSIZE(kTasTabs); ++tasTab) {
                        const bool selected = gui.m_active_subtab[14] == tasTab;
                        if (gui.subtab(kTasTabs[tasTab], selected, IM_ARRAYSIZE(kTasTabs),
                                tasTab == 0 ? ImDrawFlags_RoundCornersLeft :
                                tasTab == IM_ARRAYSIZE(kTasTabs) - 1 ? ImDrawFlags_RoundCornersRight : 0) && !selected) {
                            gui.m_active_subtab[14] = tasTab;
                        }
                        if (tasTab != IM_ARRAYSIZE(kTasTabs) - 1) ImGui::SameLine();
                    }

                    ImGui::EndChild();
                    ImGui::PopStyleVar();
                    ImGui::Dummy(ImVec2(0.0f, 8.0f));
                }

                                                                                 
                if (gui.m_active_subtab[gui.m_tab] == 0) {
                    static float s_ctrlH = 0.f, s_speedH = 0.f;

                    BeginFitSection(s_ctrlH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_GAMEPAD "  TAS CONTROLS");
                        ImGui::SameLine();
                        ImGui::TextDisabled("(?)");
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::PushTextWrapPos(360.0f);
                            ImGui::TextUnformatted(
                                "Quick Guide: New TAS -> Start -> Record -> Stop -> Update -> Save. "
                                "To replay: Files -> Load -> Start. Selected recording inputs let "
                                "you branch/edit from the middle of a replay.");
                            ImGui::PopTextWrapPos();
                            ImGui::EndTooltip();
                        }
                        ImGui::Spacing();

                        const float bW = (ImGui::GetContentRegionAvail().x - 40.0f) / 5.0f;
                        if (ImGui::Button(ICON_FA_PLAY "  Start", ImVec2(bW, 32)))
                            Main.Execute([] { KingTAS::Start(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_STOP "  Stop", ImVec2(bW, 32)))
                            Main.Execute([] { KingTAS::Stop(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_REDO "  Update", ImVec2(bW, 32)))
                            Main.Execute([] { KingTAS::Update(); });
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_PLUS "  New TAS", ImVec2(bW, 32))) {
                            s_newName[0] = '\0';
                            ImGui::OpenPopup("New TAS");
                        }
                        ImGui::SameLine();
                        const bool canSaveTas = KingTAS::HasLoadedTAS();
                        if (!canSaveTas) ImGui::BeginDisabled();
                        if (ImGui::Button(ICON_FA_SAVE "  Save", ImVec2(-1, 32))) {
                            const KingTAS::TASInfo saveInfo = KingTAS::GetInfo();
                            if (s_confirmOverwrite && savedExists(saveInfo.Name)) {
                                s_pending = kPendingOverwrite;
                                s_pendingName = saveInfo.Name;
                                ImGui::OpenPopup("##tas_confirm");
                            } else {
                                Main.Execute([] { KingTAS::Save(); });
                                s_filesLoaded = false;
                            }
                        }
                        if (!canSaveTas) ImGui::EndDisabled();
                    EndFitSection(s_ctrlH);

                    ImGui::Dummy(ImVec2(0, 4));

                    BeginFitSection(s_speedH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_TACHOMETER_ALT "  SPEED");
                        ImGui::Spacing();
                        float replay = KingTAS::GetReplaySpeed();
                        if (KingSliderFloat("Replaying Speed", &replay, 0.01f, 4.0f, "%.3f"))
                            KingTAS::SetReplaySpeed(replay);
                        float record = KingTAS::GetRecordSpeed();
                        if (KingSliderFloat("Recording Speed", &record, 0.01f, 4.0f, "%.3f"))
                            KingTAS::SetRecordSpeed(record);
                    EndFitSection(s_speedH);

                    ImGui::Dummy(ImVec2(0, 4));

                    ImGui::AlignTextToFramePadding();
                    ImGui::TextDisabled("State:");
                    ImGui::SameLine();
                    ImGui::TextColored(gui.accent_color.to_vec4(), "%s", KingTAS::GetStateName());
                    ImGui::SameLine(0, 24);
                    ImGui::TextDisabled("Status:");
                    ImGui::SameLine();
                    ImGui::TextUnformatted(KingTAS::GetStatus().c_str());

                    ImGui::Dummy(ImVec2(0, 4));

                    static float s_tipH = 0.f;
                    BeginFitSection(s_tipH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_INFO_CIRCLE "  TAS TIP");
                        ImGui::Spacing();
                        ImGui::TextWrapped(
                            "Create a new TAS at the car/ball position you want, then press Start "
                            "to record. When finished, press Stop -> Update -> Save TAS. To replay "
                            "later, open Files -> Load -> Controls -> Start.");
                        ImGui::Spacing();
                        ImGui::TextWrapped(
                            "Replay Speed controls playback speed and Recording Speed controls "
                            "recording speed. In Settings, selected inputs such as Boost or Jump "
                            "will stop replaying and start recording from that point, letting you "
                            "edit or extend a TAS. Loaded TAS shows saved/pending frames, map, "
                            "sensitivities and hitbox requirements. For the best result, use the "
                            "same map, hitbox and sensitivity settings used when the TAS was "
                            "created.");
                    EndFitSection(s_tipH);
                }

                                                                                 
                else if (gui.m_active_subtab[gui.m_tab] == 1) {
                    static float s_genH = 0.f, s_intH = 0.f, s_popH = 0.f, s_advH = 0.f;

                    BeginFitSection(s_genH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_COG "  GENERAL");
                        ImGui::Spacing();
                        bool sror = KingTAS::GetStartReplayOnReset();
                        if (ImGui::Checkbox("Start Replay On Reset", &sror))
                            KingTAS::SetStartReplayOnReset(sror);
                    EndFitSection(s_genH);

                    ImGui::Dummy(ImVec2(0, 4));

                    BeginFitSection(s_intH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_GAMEPAD "  START RECORDING OPTIONS");
                        ImGui::Spacing();
                        ImGui::TextWrapped("Select which inputs will stop replaying and begin recording.");
                        ImGui::Spacing();
                        KingTAS::InterruptInputs ii = KingTAS::GetInterruptInputs();
                        bool iiChanged = false;
                        iiChanged |= ImGui::Checkbox("Throttle", &ii.Throttle);
                        ImGui::SameLine(180); iiChanged |= ImGui::Checkbox("Steer", &ii.Steer);
                        iiChanged |= ImGui::Checkbox("Air Roll", &ii.AirRoll);
                        ImGui::SameLine(180); iiChanged |= ImGui::Checkbox("Powerslide", &ii.Powerslide);
                        iiChanged |= ImGui::Checkbox("Jump", &ii.Jump);
                        ImGui::SameLine(180); iiChanged |= ImGui::Checkbox("Boost", &ii.Boost);
                        if (iiChanged) KingTAS::SetInterruptInputs(ii);
                    EndFitSection(s_intH);

                    ImGui::Dummy(ImVec2(0, 4));

                    if (ImGui::CollapsingHeader("Popup Settings")) {
                        BeginFitSection(s_popH);
                            ImGui::TextDisabled("Safety confirmations shown before destructive actions.");
                            ImGui::Spacing();
                            ImGui::Checkbox("Confirm New TAS", &s_confirmNewTAS);
                            ImGui::Checkbox("Confirm Delete TAS", &s_confirmDelete);
                            ImGui::Checkbox("Confirm Overwrite Save", &s_confirmOverwrite);
                        EndFitSection(s_popH);
                    }

                    ImGui::Dummy(ImVec2(0, 4));

                    BeginFitSection(s_advH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_EXCLAMATION_TRIANGLE "  ADVANCED");
                        ImGui::Spacing();
                        bool env = KingTAS::GetEnvironmentValidation();
                        if (ImGui::Checkbox("Validate Map / Sensitivities / Hitbox", &env))
                            KingTAS::SetEnvironmentValidation(env);
                        bool listen = KingTAS::GetAllowListenServer();
                        if (ImGui::Checkbox("Allow Listen Server / Host (on by default)", &listen))
                            KingTAS::SetAllowListenServer(listen);
                        ImGui::TextDisabled("   Lets TAS run while you host a LAN/listen match. Replay/Record");
                        ImGui::TextDisabled("   speed changes game speed for everyone connected while active.");
                    EndFitSection(s_advH);
                }

                                                                                 
                else if (gui.m_active_subtab[gui.m_tab] == 2) {
                    static float s_infoH = 0.f, s_actH = 0.f;
                    const bool loaded = KingTAS::HasLoadedTAS();
                    KingTAS::TASInfo info = KingTAS::GetInfo();

                    auto row = [&](const char* k, const std::string& v) {
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextDisabled("%s", k);
                        ImGui::SameLine(210);
                        ImGui::TextColored(gui.accent_color.to_vec4(), "%s", v.empty() ? "-" : v.c_str());
                    };

                    BeginFitSection(s_infoH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_INFO_CIRCLE "  LOADED TAS");
                        ImGui::Spacing();
                        if (!loaded) {
                            ImGui::TextDisabled("No TAS loaded.");
                        } else {
                            char buf[96];
                            row("TAS Name", info.Name);
                            row("Map", info.MapName);
                            row("State", KingTAS::GetStateName());
                            row("Saved Frames", std::to_string(info.SavedFrameCount));
                            row("Pending Frames", std::to_string(info.PendingFrameCount));
                            snprintf(buf, sizeof(buf), "%.3f", info.ReplaySpeed); row("Replay Speed", buf);
                            snprintf(buf, sizeof(buf), "%.3f", info.RecordSpeed); row("Record Speed", buf);

                            ImGui::Spacing();
                            SectionHeader("EXPECTED SETUP");
                            snprintf(buf, sizeof(buf), "%.4f", info.ExpectedSteeringSensitivity); row("Steering Sensitivity", buf);
                            snprintf(buf, sizeof(buf), "%.4f", info.ExpectedAirSensitivity);      row("Air Sensitivity", buf);
                            snprintf(buf, sizeof(buf), "%.4f", info.ExpectedDodgeThreshold);       row("Dodge Threshold", buf);
                            if (info.HasExpectedHitbox) {
                                snprintf(buf, sizeof(buf), "%.1f  %.1f  %.1f", info.ExpectedHitboxExtent.X, info.ExpectedHitboxExtent.Y, info.ExpectedHitboxExtent.Z);
                                row("Hitbox Extent (X/Y/Z)", buf);
                                snprintf(buf, sizeof(buf), "%.1f  %.1f  %.1f", info.ExpectedHitboxOffset.X, info.ExpectedHitboxOffset.Y, info.ExpectedHitboxOffset.Z);
                                row("Hitbox Offset (X/Y/Z)", buf);
                            } else {
                                row("Hitbox", std::string("not captured"));
                            }
                        }
                    EndFitSection(s_infoH);

                    if (loaded) {
                        ImGui::Dummy(ImVec2(0, 4));
                        BeginFitSection(s_actH);
                            if (KingTAS::HasPendingRecording()) {
                                ImGui::TextColored(g_RedThemeColor, ICON_FA_EXCLAMATION_TRIANGLE "  New recording is pending. Press Update before Save.");
                                ImGui::Spacing();
                            }
                            const float hW = (ImGui::GetContentRegionAvail().x - 10.0f) / 2.0f;
                            if (ImGui::Button(ICON_FA_SAVE "  Save TAS", ImVec2(hW, 32))) {
                                if (s_confirmOverwrite && savedExists(info.Name)) {
                                    s_pending = kPendingOverwrite;
                                    s_pendingName = info.Name;
                                    ImGui::OpenPopup("##tas_confirm");
                                } else {
                                    Main.Execute([] { KingTAS::Save(); });
                                    s_filesLoaded = false;
                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button(ICON_FA_FLAG_CHECKERED "  Stop + Update", ImVec2(-1, 32)))
                                Main.Execute([] { KingTAS::StopAndUpdate(); });
                        EndFitSection(s_actH);
                    }
                }

                                                                                 
                else if (gui.m_active_subtab[gui.m_tab] == 3) {
                    static float s_filesH = 0.f;

                    BeginFitSection(s_filesH);
                        ImGui::TextColored(g_RedThemeColor, ICON_FA_FOLDER_OPEN "  TAS FILES");
                        ImGui::SameLine();
                        if (ImGui::SmallButton(ICON_FA_SYNC " Refresh")) s_filesLoaded = false;
                        ImGui::TextDisabled("%s", KingTAS::GetSaveDirectory().c_str());
                        ImGui::Spacing();

                        if (s_files.empty()) {
                            ImGui::TextDisabled("No saved TAS files.");
                        } else if (ImGui::BeginListBox("##tas_files", ImVec2(-1, 200))) {
                            for (int i = 0; i < (int)s_files.size(); ++i) {
                                const bool sel = (s_fileSel == i);
                                std::string name = std::filesystem::path(s_files[i]).stem().string();
                                if (ImGui::Selectable((std::string(ICON_FA_FILM "  ") + name).c_str(), sel))
                                    s_fileSel = i;
                            }
                            ImGui::EndListBox();
                        }

                        const bool haveSel = (s_fileSel >= 0 && s_fileSel < (int)s_files.size());
                        const float hW = (ImGui::GetContentRegionAvail().x - 10.0f) / 2.0f;

                        if (!haveSel) ImGui::BeginDisabled();
                        if (ImGui::Button(ICON_FA_CHECK "  Load", ImVec2(hW, 32))) {
                            std::string path = s_files[s_fileSel];
                            Main.Execute([path] { KingTAS::Load(path); });
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TRASH "  Delete", ImVec2(-1, 32))) {
                            if (s_confirmDelete) {
                                s_pending = kPendingDelete;
                                s_pendingPath = s_files[s_fileSel];
                                s_pendingName = std::filesystem::path(s_files[s_fileSel]).stem().string();
                                ImGui::OpenPopup("##tas_confirm");
                            } else {
                                std::string path = s_files[s_fileSel];
                                Main.Execute([path] { KingTAS::DeleteFile(path); });
                                s_fileSel = -1;
                                s_filesLoaded = false;
                            }
                        }
                        if (!haveSel) ImGui::EndDisabled();
                    EndFitSection(s_filesH);
                }

                                                                                
                                                                                  
                                                                         
                {
                    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal("New TAS", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                        ImGui::TextUnformatted("TAS Name:");
                        ImGui::SetNextItemWidth(280.0f);
                        ImGui::InputText("##tas_newname", s_newName, sizeof(s_newName));
                        if (s_confirmNewTAS && KingTAS::HasLoadedTAS()) {
                            ImGui::Spacing();
                            ImGui::TextColored(g_RedThemeColor, ICON_FA_EXCLAMATION_TRIANGLE "  This replaces the currently loaded TAS.");
                        }
                        ImGui::Spacing();
                        const bool canCreate = (s_newName[0] != '\0');
                        if (!canCreate) ImGui::BeginDisabled();
                        if (ImGui::Button(ICON_FA_PLUS "  Create", ImVec2(130, 0))) {
                            std::string name = s_newName;
                            Main.Execute([name] { KingTAS::NewTAS(name); });
                            s_filesLoaded = false;
                            ImGui::CloseCurrentPopup();
                        }
                        if (!canCreate) ImGui::EndDisabled();
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TIMES "  Cancel", ImVec2(130, 0)))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                    }
                }
                {
                    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal("##tas_confirm", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                        if (s_pending == kPendingDelete)
                            ImGui::TextUnformatted("Delete this TAS file?");
                        else if (s_pending == kPendingOverwrite)
                            ImGui::TextUnformatted("Overwrite the existing save?");
                        if (!s_pendingName.empty())
                            ImGui::TextDisabled("%s", s_pendingName.c_str());
                        ImGui::Spacing();
                        if (ImGui::Button(ICON_FA_CHECK "  Confirm", ImVec2(130, 0))) {
                            if (s_pending == kPendingDelete) {
                                std::string path = s_pendingPath;
                                Main.Execute([path] { KingTAS::DeleteFile(path); });
                                s_fileSel = -1;
                            } else if (s_pending == kPendingOverwrite) {
                                Main.Execute([] { KingTAS::Save(); });
                            }
                            s_pending = kPendingNone;
                            s_filesLoaded = false;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(ICON_FA_TIMES "  Cancel", ImVec2(130, 0))) {
                            s_pending = kPendingNone;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndPopup();
                    }
                }

                ImGui::PopStyleVar(2);
                gui.end_group_box();
            }
            ImGui::Dummy(ImVec2(0.0f, 30.0f));

            ImGui::EndChild();
            ImGui::PopStyleVar(2);

            ImGui::End();
        }
        ImGui::PopStyleVar();                 
    }

    if (IsOpen) {
                                      
        ImVec2 mousePos = ImGui::GetMousePos();
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        float size = 12.0f;
        ImU32 color = IM_COL32(0, 182, 216, 255);                  
        
                       
        drawList->AddLine(ImVec2(mousePos.x - size, mousePos.y), ImVec2(mousePos.x + size, mousePos.y), IM_COL32(0, 0, 0, 255), 4.0f);
        drawList->AddLine(ImVec2(mousePos.x, mousePos.y - size), ImVec2(mousePos.x, mousePos.y + size), IM_COL32(0, 0, 0, 255), 4.0f);
        
                      
        drawList->AddLine(ImVec2(mousePos.x - size, mousePos.y), ImVec2(mousePos.x + size, mousePos.y), color, 2.0f);
        drawList->AddLine(ImVec2(mousePos.x, mousePos.y - size), ImVec2(mousePos.x, mousePos.y + size), color, 2.0f);
        
                              
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }

                                                                               
                                        
    Notify::Render();

                                         
    ImGui::EndFrame();
    ImGui::Render();
}

void SelectableColor(ImU32 color)
{
    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, color);
}

GUIComponent GUI;
