#pragma once

#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../ImGui/imgui.h"
#include <array>
#include <string>
#include <vector>

                                                            
                                                                                
                                                                               
namespace KingSync
{
    struct Peer
    {
        std::string PlayerName;
        std::string CustomTag;
        std::string Address;
        ImVec4 Accent = ImVec4(1, 1, 1, 1);
        bool IsHost = false;
        bool ShieldEnabled = false;
        bool PhotoMode = false;
        ULONGLONG LastSeen = 0;
    };

    struct Settings
    {
        bool Enabled = false;
        bool BroadcastPresence = true;
        int Port = 49230;
        char DirectPeer[64] = "";                                   
        char CustomTag[32] = "KingMod";
        float Accent[4] = { 0.95f, 0.16f, 0.18f, 1.0f };
    };

    extern Settings Config;

    void Initialize();
    void Shutdown();
    void Tick();
    void SetEnabled(bool enabled);
    bool IsEnabled();
    std::vector<Peer> GetPeers();
    int GetPeerCount();
    std::string GetStatus();
}
