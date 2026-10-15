#pragma once

#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <limits>
#include <string>

namespace WorkshopSteamDownloader
{
    namespace fs = std::filesystem;

    struct WorkshopStatus
    {
        bool available = false;
        bool subscribed = false;
        bool installed = false;
        bool needsUpdate = false;
        bool downloading = false;
        bool downloadPending = false;
        float progress = 0.0f;
        std::string installPath;
        std::string mapPath;
    };

    inline bool TryParseWorkshopId(const std::string& text, uint64_t& workshopId)
    {
        workshopId = 0;
        if (text.empty())
            return false;

        uint64_t value = 0;
        for (unsigned char ch : text)
        {
            if (!std::isdigit(ch))
                return false;

            const uint64_t digit = static_cast<uint64_t>(ch - '0');
            if (value > ((std::numeric_limits<uint64_t>::max)() - digit) / 10)
                return false;
            value = (value * 10) + digit;
        }

        if (value == 0)
            return false;

        workshopId = value;
        return true;
    }

    inline bool IsMapExtension(std::string extension)
    {
        std::transform(extension.begin(), extension.end(), extension.begin(),
            [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        return extension == ".udk" || extension == ".upk" || extension == ".umap";
    }

    inline bool GetWorkshopInstallPath(uint64_t workshopId, std::string& path)
    {
        path.clear();
        (void)workshopId;
        return false;
    }

    inline bool GetWorkshopInstallMapPath(uint64_t workshopId, std::string& mapPath)
    {
        mapPath.clear();
        (void)workshopId;
        return false;
    }

    inline float GetWorkshopDownloadProgress(uint64_t workshopId)
    {
        (void)workshopId;
        return 0.0f;
    }

    inline bool IsWorkshopMapInstalled(uint64_t workshopId)
    {
        (void)workshopId;
        return false;
    }

    inline bool DownloadWorkshopMap(uint64_t workshopId)
    {
        (void)workshopId;
        return false;
    }

    inline WorkshopStatus QueryWorkshopStatus(uint64_t workshopId)
    {
        (void)workshopId;
        return WorkshopStatus{};
    }
}
