#include "menu_avatar.hpp"
#include "blur.hpp"                                                                    
#include "../Components/Includes.hpp"

#include <windows.h>
#include <d3d11.h>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>

                                                                            
                                                                               
                                                                             
                                                                              
                                                   
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#include "stb_image.h"
#include "../resource.h"

namespace menu_avatar
{
                                                                                      
                                                                                
                                                                              
    using SteamInternal_CreateInterface_fn = void* (__fastcall*)(const char*);
    using SteamAPI_InterfaceGetter_fn = void* (__cdecl*)();

    using SteamAPI_ISteamUser_GetSteamID_fn    = uint64_t (__fastcall*)(void*);
    using SteamAPI_ISteamFriends_GetPersonaName_fn = const char* (__fastcall*)(void*);
    using SteamAPI_ISteamFriends_GetLargeFriendAvatar_fn = int (__fastcall*)(void*, uint64_t);
    using SteamAPI_ISteamUtils_GetImageSize_fn = bool (__fastcall*)(void*, int, uint32_t*, uint32_t*);
    using SteamAPI_ISteamUtils_GetImageRGBA_fn = bool (__fastcall*)(void*, int, uint8_t*, int);

    static SteamInternal_CreateInterface_fn        g_CreateInterface = nullptr;
    static SteamAPI_ISteamUser_GetSteamID_fn       g_GetSteamID = nullptr;
    static SteamAPI_ISteamFriends_GetPersonaName_fn g_GetPersonaName = nullptr;
    static SteamAPI_ISteamFriends_GetLargeFriendAvatar_fn g_GetLargeFriendAvatar = nullptr;
    static SteamAPI_ISteamUtils_GetImageSize_fn     g_GetImageSize = nullptr;
    static SteamAPI_ISteamUtils_GetImageRGBA_fn     g_GetImageRGBA = nullptr;
    static void*                                   g_UserInterface = nullptr;
    static void*                                   g_FriendsInterface = nullptr;
    static void*                                   g_UtilsInterface = nullptr;
    static bool                                    g_steamReady = false;

    static void* ResolveSteamInterface(HMODULE steamDll, const char* const* versions, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
                                                                     
                                                                        
                                                                         
                                                                       
                                                                         
            const std::string version(versions[i]);
            const size_t digits = version.find_last_not_of("0123456789") + 1;
            if (digits == 0 || digits >= version.size())
                continue;
            const std::string exportName = "SteamAPI_" + version.substr(0, digits) + "_v" + version.substr(digits);
            if (auto getter = reinterpret_cast<SteamAPI_InterfaceGetter_fn>(GetProcAddress(steamDll, exportName.c_str())))
            {
                if (void* interfacePtr = getter())
                    return interfacePtr;
            }

            if (g_CreateInterface)
            {
                if (void* interfacePtr = g_CreateInterface(versions[i]))
                    return interfacePtr;
            }
        }
        return nullptr;
    }

    static void InitSteamFlat()
    {
                                                                             
                                                                         
                                                                            
        if (g_steamReady && g_UtilsInterface) return;

        HMODULE steamDll = GetModuleHandleA("steam_api64.dll");
        if (!steamDll) return;

        g_CreateInterface = (SteamInternal_CreateInterface_fn)GetProcAddress(steamDll, "SteamInternal_CreateInterface");
        g_GetSteamID      = (SteamAPI_ISteamUser_GetSteamID_fn)GetProcAddress(steamDll, "SteamAPI_ISteamUser_GetSteamID");
        g_GetPersonaName  = (SteamAPI_ISteamFriends_GetPersonaName_fn)GetProcAddress(steamDll, "SteamAPI_ISteamFriends_GetPersonaName");
        g_GetLargeFriendAvatar = (SteamAPI_ISteamFriends_GetLargeFriendAvatar_fn)GetProcAddress(
            steamDll, "SteamAPI_ISteamFriends_GetLargeFriendAvatar");
        g_GetImageSize = (SteamAPI_ISteamUtils_GetImageSize_fn)GetProcAddress(
            steamDll, "SteamAPI_ISteamUtils_GetImageSize");
        g_GetImageRGBA = (SteamAPI_ISteamUtils_GetImageRGBA_fn)GetProcAddress(
            steamDll, "SteamAPI_ISteamUtils_GetImageRGBA");

        if (!g_GetSteamID)
            return;

                                                                            
                                                                           
                                                         
                                                                         
                                                                           
        const char* userVersions[] = { "SteamUser023", "SteamUser024", "SteamUser022", "SteamUser021", "SteamUser020", "SteamUser019" };
        const char* friendsVersions[] = { "SteamFriends018", "SteamFriends017", "SteamFriends016", "SteamFriends015", "SteamFriends014" };
        const char* utilsVersions[] = { "SteamUtils010", "SteamUtils011", "SteamUtils009", "SteamUtils008" };
        g_UserInterface = ResolveSteamInterface(steamDll, userVersions, sizeof(userVersions) / sizeof(userVersions[0]));
        g_FriendsInterface = ResolveSteamInterface(steamDll, friendsVersions, sizeof(friendsVersions) / sizeof(friendsVersions[0]));
        g_UtilsInterface = ResolveSteamInterface(steamDll, utilsVersions, sizeof(utilsVersions) / sizeof(utilsVersions[0]));

                                                                              
                                                                                
                                                                            
        if (g_UserInterface && g_FriendsInterface)
            g_steamReady = true;
    }

    static uint64_t GetSteamIdFlat()
    {
        InitSteamFlat();
        if (!g_steamReady || !g_UserInterface) return 0;
        return g_GetSteamID(g_UserInterface);
    }

                                                                                
    static char     g_name[64]  = "Player";
    static int      g_platform  = 0;                                 
    static uint64_t g_steamId   = 0;
    static bool     g_haveName  = false;
                                                                            
                                                                                
                                                                            
    static int      g_nameMisses = 0;

    const char* Name()     { return g_name; }
    int         Platform() { return g_platform; }
    uint64_t    SteamId()  { return g_steamId; }

                                                                               
    static ID3D11ShaderResourceView* g_srv = nullptr;

    static ID3D11Device* GetDevice()
    {
        if (!blur::device) return nullptr;
        ID3D11Device* dev = nullptr;
        blur::device->GetDevice(&dev);
        return dev;
    }

    static ID3D11ShaderResourceView* BuildTexture(ID3D11Device* dev, const std::vector<uint8_t>& rgba, uint32_t w, uint32_t h)
    {
        if (!dev || w == 0 || h == 0 || rgba.size() < static_cast<size_t>(w) * h * 4)
            return nullptr;

        D3D11_TEXTURE2D_DESC td = {};
        td.Width = w;
        td.Height = h;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        td.SampleDesc.Count = 1;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = rgba.data();
        sd.SysMemPitch = w * 4;

        ID3D11Texture2D* tex = nullptr;
        if (FAILED(dev->CreateTexture2D(&td, &sd, &tex)))
            return nullptr;

        ID3D11ShaderResourceView* srv = nullptr;
        if (FAILED(dev->CreateShaderResourceView(tex, nullptr, &srv)))
        {
            tex->Release();
            return nullptr;
        }
        tex->Release();
        return srv;
    }

                                                                            
                                                                               
                                                             
    static void LoadEmbeddedAvatar()
    {
        if (g_srv) return;

        HMODULE module = GUIComponent::DllModule
            ? static_cast<HMODULE>(GUIComponent::DllModule)
            : GetModuleHandleA(nullptr);
        HRSRC resource = FindResourceA(module, MAKEINTRESOURCEA(IDR_KINGMOD_TOAST_ICON),
                                       reinterpret_cast<LPCSTR>(RT_RCDATA));
        if (!resource) return;

        HGLOBAL loaded = LoadResource(module, resource);
        const void* bytes = loaded ? LockResource(loaded) : nullptr;
        const DWORD size = SizeofResource(module, resource);
        if (!bytes || size == 0) return;

        int width = 0, height = 0, channels = 0;
        stbi_uc* pixels = stbi_load_from_memory(
            static_cast<const stbi_uc*>(bytes), static_cast<int>(size),
            &width, &height, &channels, 4);
        if (!pixels || width <= 0 || height <= 0)
        {
            if (pixels) stbi_image_free(pixels);
            return;
        }

        std::vector<uint8_t> rgba(
            pixels, pixels + static_cast<size_t>(width) * height * 4);
        stbi_image_free(pixels);

        if (ID3D11Device* dev = GetDevice())
        {
            g_srv = BuildTexture(dev, rgba, static_cast<uint32_t>(width),
                                 static_cast<uint32_t>(height));
            dev->Release();
        }
    }

                                                                                     
    ID3D11ShaderResourceView* CreateTextureFromMemory(const void* data, size_t size,
                                                      int* outWidth, int* outHeight)
    {
        if (!data || size == 0)
            return nullptr;

        int w = 0, h = 0, ch = 0;
        stbi_uc* pixels = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(data),
                                                static_cast<int>(size), &w, &h, &ch, 4);
        if (!pixels)
            return nullptr;

        std::vector<uint8_t> rgba(pixels, pixels + static_cast<size_t>(w) * h * 4);
        stbi_image_free(pixels);

        ID3D11ShaderResourceView* srv = nullptr;
        if (ID3D11Device* dev = GetDevice())
        {
            srv = BuildTexture(dev, rgba, static_cast<uint32_t>(w), static_cast<uint32_t>(h));
            dev->Release();
        }

        if (srv)
        {
            if (outWidth)  *outWidth = w;
            if (outHeight) *outHeight = h;
        }
        return srv;
    }

                                                                                        
                                                                          
    static void RefreshIdentity()
    {
        const uint64_t steamId = GetSteamIdFlat();
        g_platform = steamId != 0 ? 1 : 0;
        g_steamId  = steamId;
    }

                                                                             
                                                                                
                                                                                
    static bool IsReadable(const void* address, size_t byteCount)
    {
        if (!address || byteCount == 0)
            return false;
        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi))
            return false;
        const DWORD protection = mbi.Protect & 0xFF;
        if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_GUARD) != 0 || protection == PAGE_NOACCESS)
            return false;
        const auto begin = reinterpret_cast<uintptr_t>(address);
        const auto end = begin + byteCount;
        const auto regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        return end >= begin && end <= regionEnd;
    }

                             
                                                                            
                                                                                 
                                                                          
                                                                            
                                                                   
                                                                             
                                                                                
                                                                                 
                                                                             
                                           
    static void RefreshName()
    {
        std::string name;
        const auto isUsableName = [](const std::string& value)
        {
            if (value.empty()) return false;
            std::string folded = value;
            std::transform(folded.begin(), folded.end(), folded.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                                                                 
                                                                               
                                                                            
                                                                     
            return folded != "player" && folded != "unknown";
        };

                                                                              
                                                                                
                                                 
        try
        {
            for (UGFxData_LocalPlayer_TA* local :
                 Instances.GetAllInstancesOf<UGFxData_LocalPlayer_TA>())
            {
                if (!local || !local->bPrimaryPlayer) continue;
                const std::string uiName = local->PlayerName.ToString();
                if (isUsableName(uiName))
                {
                    name = uiName;
                    break;
                }
            }
        }
        catch (...) {}

                                                                                   
        if (name.empty())
        if (UEngine* engine = Instances.IUEngine())
        {
            if (IsReadable(engine, sizeof(UEngine)) && engine->GamePlayers.size() > 0)
            {
                ULocalPlayer* localPlayer = engine->GamePlayers[0];
                if (IsReadable(localPlayer, sizeof(ULocalPlayer)))
                {
                    if (IsReadable(localPlayer->Actor, sizeof(APlayerController)) &&
                        IsReadable(localPlayer->Actor->PlayerReplicationInfo, sizeof(APlayerReplicationInfo)))
                    {
                        std::string pri = localPlayer->Actor->PlayerReplicationInfo->PlayerName.ToString();
                        if (isUsableName(pri))
                            name = pri;
                    }

                                                                                     
                                                                             
                                           
                      
                                                                                     
                                                                                    
                                                                                    
                                                                              
                      
                                                                                      
                                                                                       
                                                                                      
                                                                                 
                                                        
                                                                           
                                                                  
                                                                                    
                                                                                     
                                                   
                    if (name.empty())
                    {
                        ULocalPlayer_X* lpx = static_cast<ULocalPlayer_X*>(localPlayer);

                        if (IsReadable(lpx->OnlinePlayer, sizeof(UOnlinePlayer_X)))
                        {
                            std::string online = lpx->OnlinePlayer->PlayerName.ToString();
                            if (isUsableName(online))
                                name = online;
                        }

                        if (name.empty())
                        {
                            std::string nick = lpx->eventGetNickname().ToString();

                                                                                    
                                                              
                            if (nick.empty())
                            {
                                FString eosName;
                                if (lpx->GetEosNameIfAvailable(eosName))
                                    nick = eosName.ToString();
                            }
                            if (isUsableName(nick))
                                name = nick;
                        }
                    }
                }
            }
        }

                                                                                
                                                                                
                                                                     
        if (name.empty())
        {
            APlayerController* controller = Instances.IAPlayerController();
            if (!IsReadable(controller, sizeof(APlayerController)))
            {
                if (ULocalPlayer* localPlayer = Instances.IULocalPlayer())
                    controller = localPlayer->Actor;
            }

            if (IsReadable(controller, sizeof(APlayerController)) &&
                IsReadable(controller->PlayerReplicationInfo, sizeof(APlayerReplicationInfo)))
            {
                std::string pri = controller->PlayerReplicationInfo->PlayerName.ToString();
                if (isUsableName(pri))
                    name = pri;
            }
        }

                                                                  
                                                                            
        if (name.empty())
        {
            if (ULocalPlayer* localPlayer = Instances.IULocalPlayer())
            {
                if (IsReadable(localPlayer, sizeof(ULocalPlayer)))
                {
                    ULocalPlayer_X* lpx = static_cast<ULocalPlayer_X*>(localPlayer);
                    if (IsReadable(lpx->OnlinePlayer, sizeof(UOnlinePlayer_X)))
                    {
                        const std::string online = lpx->OnlinePlayer->PlayerName.ToString();
                        if (isUsableName(online))
                            name = online;
                    }
                    if (name.empty())
                    {
                        const std::string nick = lpx->eventGetNickname().ToString();
                        if (isUsableName(nick))
                            name = nick;
                    }
                }
            }
        }

                                                                            
                                                                               
                                  
        if (name.empty())
        {
            InitSteamFlat();
            if (g_FriendsInterface && g_GetPersonaName)
            {
                if (const char* persona = g_GetPersonaName(g_FriendsInterface))
                {
                    const std::string steamName = persona;
                    if (isUsableName(steamName))
                        name = steamName;
                }
            }
        }

        if (!name.empty())
        {
            size_t n = name.size();
            if (n > sizeof(g_name) - 1) n = sizeof(g_name) - 1;
            memcpy(g_name, name.c_str(), n);
            g_name[n] = '\0';
            if (!g_haveName)
                Console.Write(std::string("[menu_avatar] Player name resolved: \"") + g_name + "\"");
            g_haveName = true;
            g_nameMisses = 0;
        }
        else
        {
                                                                                   
                                                                                  
                                                                                 
                                                                                 
                                                     
            ++g_nameMisses;
            if (g_nameMisses == 150)
                Console.Warning("[menu_avatar] Could not resolve the player name from any source "
                                "(PlayerReplicationInfo, OnlinePlayer_X::PlayerName, GetNickname, "
                                "EOS name, Steam persona) -- still showing \"Player\".");
        }
    }

    ID3D11ShaderResourceView* Texture()
    {
        return g_srv;
    }

    void Shutdown()
    {
        if (g_srv)
        {
            g_srv->Release();
            g_srv = nullptr;
        }
        g_steamId = 0;
        g_steamReady = false;
        g_UserInterface = nullptr;
        g_FriendsInterface = nullptr;
        g_UtilsInterface = nullptr;
        g_GetSteamID = nullptr;
        g_GetPersonaName = nullptr;
        g_GetLargeFriendAvatar = nullptr;
        g_GetImageSize = nullptr;
        g_GetImageRGBA = nullptr;
    }

    void Update()
    {
        static auto lastIdentity = std::chrono::steady_clock::time_point();
        static auto lastName     = std::chrono::steady_clock::time_point();
        auto now = std::chrono::steady_clock::now();

        if (now - lastIdentity > std::chrono::milliseconds(500))
        {
            lastIdentity = now;
            RefreshIdentity();
        }
                                                                               
                                                                                  
                                                                                 
                                                                                  
                                                                                   
                                                                                    
                                                                              
                                                             
        std::chrono::milliseconds nameInterval(100);
        if (g_haveName)             nameInterval = std::chrono::milliseconds(2000);
        else if (g_nameMisses > 150) nameInterval = std::chrono::milliseconds(1000);
        if (now - lastName > nameInterval)
        {
            lastName = now;
            RefreshName();
        }

        if (!g_srv)
            LoadEmbeddedAvatar();
    }
}
