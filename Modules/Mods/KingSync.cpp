#include "KingSync.hpp"

#include "GameEventHook.hpp"
#include "HostSync.hpp"
#include "MatchmakingShield.hpp"
#include "KingFeatures.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Console.hpp"
#include <Windows.h>
#include <winsock.h>
#include <algorithm>
#include <cstring>
#include <mutex>
#include <iterator>
#pragma comment(lib, "ws2_32.lib")

namespace KingSync
{
    Settings Config{};

    namespace
    {
#pragma pack(push, 1)
        struct Packet
        {
            uint32_t Magic = 0x304D4B58;          
            uint16_t Version = 33;
            uint16_t Size = 0;
            uint32_t Flags = 0;
            char PlayerName[32]{};
            char CustomTag[32]{};
            float Accent[4]{ 1,1,1,1 };
            uint64_t SentTick = 0;
        };
#pragma pack(pop)

        enum Flags : uint32_t
        {
            FlagHost = 1u << 0,
            FlagShield = 1u << 1,
            FlagPhoto = 1u << 3
        };

        SOCKET g_socket = INVALID_SOCKET;
        bool g_wsaReady = false;
        ULONGLONG g_lastBroadcast = 0;
        std::vector<Peer> g_peers;
        std::mutex g_peerMutex;
        std::string g_status = "Disabled";
        constexpr ULONGLONG kBroadcastMs = 1500;
        constexpr ULONGLONG kPeerTimeoutMs = 7000;

        std::string LocalPlayerName()
        {
            try
            {
                UEngine* engine = UEngine::GetEngine();
                if (!engine || !engine->IsA<UGameEngine>()) return "KingModUser";
                auto* ge = static_cast<UGameEngine*>(engine);
                if (ge->GamePlayers.empty() || !ge->GamePlayers[0] || !ge->GamePlayers[0]->Actor)
                    return "KingModUser";
                APlayerController* pc = ge->GamePlayers[0]->Actor;
                if (!pc->PlayerReplicationInfo) return "KingModUser";
                std::string n = pc->PlayerReplicationInfo->PlayerName.ToString();
                return n.empty() ? "KingModUser" : n;
            }
            catch (...) { return "KingModUser"; }
        }

        void CloseSocket()
        {
            if (g_socket != INVALID_SOCKET)
            {
                closesocket(g_socket);
                g_socket = INVALID_SOCKET;
            }
            if (g_wsaReady)
            {
                WSACleanup();
                g_wsaReady = false;
            }
        }

        bool EnsureSocket()
        {
            if (g_socket != INVALID_SOCKET) return true;

            WSADATA data{};
            if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
            {
                g_status = "WSAStartup failed";
                return false;
            }
            g_wsaReady = true;

            g_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (g_socket == INVALID_SOCKET)
            {
                g_status = "UDP socket failed";
                CloseSocket();
                return false;
            }

            BOOL broadcast = TRUE;
            setsockopt(g_socket, SOL_SOCKET, SO_BROADCAST,
                reinterpret_cast<const char*>(&broadcast), sizeof(broadcast));

            BOOL reuse = TRUE;
            setsockopt(g_socket, SOL_SOCKET, SO_REUSEADDR,
                reinterpret_cast<const char*>(&reuse), sizeof(reuse));

            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            addr.sin_port = htons(static_cast<u_short>((std::max)(1024, (std::min)(Config.Port, 65535))));
            if (bind(g_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR)
            {
                g_status = "UDP port is already in use";
                CloseSocket();
                return false;
            }

            u_long nonBlocking = 1;
            ioctlsocket(g_socket, FIONBIO, &nonBlocking);
            g_status = "LAN sync ready";
            return true;
        }

        void Broadcast()
        {
            if (!Config.BroadcastPresence || g_socket == INVALID_SOCKET) return;

            Packet p{};
            p.Size = static_cast<uint16_t>(sizeof(Packet));
            const std::string name = LocalPlayerName();
            strncpy_s(p.PlayerName, name.c_str(), _TRUNCATE);
            strncpy_s(p.CustomTag, Config.CustomTag, _TRUNCATE);
            for (int i = 0; i < 4; ++i) p.Accent[i] = Config.Accent[i];
            p.SentTick = GetTickCount64();
            if (Events.CanUseLocalServerFeatures()) p.Flags |= FlagHost;
            if (MatchmakingShield::IsEnabled()) p.Flags |= FlagShield;
            if (KingFeatures::IsPhotoMode()) p.Flags |= FlagPhoto;

            sockaddr_in dst{};
            dst.sin_family = AF_INET;
            dst.sin_port = htons(static_cast<u_short>((std::max)(1024, (std::min)(Config.Port, 65535))));
            dst.sin_addr.s_addr = INADDR_BROADCAST;
            sendto(g_socket, reinterpret_cast<const char*>(&p), sizeof(p), 0,
                reinterpret_cast<sockaddr*>(&dst), sizeof(dst));

                                                                                   
                                                                
            if (Config.DirectPeer[0] != '\0')
            {
                const unsigned long directAddress = inet_addr(Config.DirectPeer);
                if (directAddress != INADDR_NONE)
                {
                    sockaddr_in direct{};
                    direct.sin_family = AF_INET;
                    direct.sin_port = dst.sin_port;
                    direct.sin_addr.s_addr = directAddress;
                    sendto(g_socket, reinterpret_cast<const char*>(&p), sizeof(p), 0,
                        reinterpret_cast<sockaddr*>(&direct), sizeof(direct));
                }
            }
        }

        void UpsertPeer(const Packet& p, const sockaddr_in& sender)
        {
            if (p.Magic != 0x304D4B58 || p.Version != 33 || p.Size != sizeof(Packet))
                return;

            char nameBuf[33]{};
            char tagBuf[33]{};
            memcpy(nameBuf, p.PlayerName, 32);
            memcpy(tagBuf, p.CustomTag, 32);
            const std::string name(nameBuf);
            if (name.empty()) return;

            char* ip = inet_ntoa(sender.sin_addr);
            const std::string address = ip ? ip : "LAN";
            const ULONGLONG now = GetTickCount64();

            std::lock_guard<std::mutex> lock(g_peerMutex);
            auto it = std::find_if(g_peers.begin(), g_peers.end(),
                [&](const Peer& peer) { return peer.PlayerName == name && peer.Address == address; });
            if (it == g_peers.end())
            {
                g_peers.push_back(Peer{});
                it = std::prev(g_peers.end());
            }

            it->PlayerName = name;
            it->CustomTag = std::string(tagBuf);
            it->Address = address;
            it->Accent = ImVec4(p.Accent[0], p.Accent[1], p.Accent[2], p.Accent[3]);
            it->IsHost = (p.Flags & FlagHost) != 0;
            it->ShieldEnabled = (p.Flags & FlagShield) != 0;
            it->PhotoMode = (p.Flags & FlagPhoto) != 0;
            it->LastSeen = now;
        }

        void Receive()
        {
            if (g_socket == INVALID_SOCKET) return;
            for (int i = 0; i < 16; ++i)
            {
                Packet p{};
                sockaddr_in sender{};
                int senderLen = sizeof(sender);
                const int got = recvfrom(g_socket, reinterpret_cast<char*>(&p), sizeof(p), 0,
                    reinterpret_cast<sockaddr*>(&sender), &senderLen);
                if (got == SOCKET_ERROR || got <= 0) break;
                if (got == sizeof(Packet)) UpsertPeer(p, sender);
            }
        }

        void Prune()
        {
            const ULONGLONG now = GetTickCount64();
            std::lock_guard<std::mutex> lock(g_peerMutex);
            g_peers.erase(std::remove_if(g_peers.begin(), g_peers.end(),
                [&](const Peer& p) { return now > p.LastSeen && now - p.LastSeen > kPeerTimeoutMs; }),
                g_peers.end());
        }
    }

    void Initialize()
    {
        g_status = "Disabled";
    }

    void Shutdown()
    {
        CloseSocket();
        std::lock_guard<std::mutex> lock(g_peerMutex);
        g_peers.clear();
        g_status = "Disabled";
    }

    void SetEnabled(bool enabled)
    {
        if (Config.Enabled == enabled) return;
        Config.Enabled = enabled;
        if (!enabled)
        {
            CloseSocket();
            std::lock_guard<std::mutex> lock(g_peerMutex);
            g_peers.clear();
            g_status = "Disabled";
        }
        else
        {
            EnsureSocket();
        }
    }

    bool IsEnabled() { return Config.Enabled; }

    void Tick()
    {
        if (!Config.Enabled) return;
        if (!EnsureSocket()) return;

        const ULONGLONG now = GetTickCount64();
        if (g_lastBroadcast == 0 || now - g_lastBroadcast >= kBroadcastMs)
        {
            g_lastBroadcast = now;
            Broadcast();
        }
        Receive();
        Prune();
    }

    std::vector<Peer> GetPeers()
    {
        std::lock_guard<std::mutex> lock(g_peerMutex);
        return g_peers;
    }

    int GetPeerCount()
    {
        std::lock_guard<std::mutex> lock(g_peerMutex);
        return static_cast<int>(g_peers.size());
    }

    std::string GetStatus()
    {
        if (!Config.Enabled) return "Disabled";
        return g_status + " | peers " + std::to_string(GetPeerCount());
    }
}
