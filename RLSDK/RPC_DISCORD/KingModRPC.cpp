#include "KingModRPC.hpp"
#include "../../PublicConfig.hpp"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR
#define LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR 0x00000100
#endif
#ifndef LOAD_LIBRARY_SEARCH_SYSTEM32
#define LOAD_LIBRARY_SEARCH_SYSTEM32 0x00000800
#endif

#include "../../resource.h"
#include "win64-dynamic/include/discord_rpc.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <functional>
#include <iterator>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace
{
    constexpr const char* kApplicationId = KINGMOD_DISCORD_APPLICATION_ID;
    constexpr const char* kLargeImageKey = "kingmod";
    constexpr const char* kSmallImageKey = "kmoctane";

#ifdef _WIN64
    constexpr int kDiscordRpcResourceId = IDR_DISCORD_RPC_X64;
    constexpr wchar_t kDiscordRpcArch[] = L"x64";
#else
    constexpr int kDiscordRpcResourceId = IDR_DISCORD_RPC_X86;
    constexpr wchar_t kDiscordRpcArch[] = L"x86";
#endif

    using DiscordInitializeFn = void (*)(const char*, DiscordEventHandlers*, int, const char*);
    using DiscordShutdownFn = void (*)();
    using DiscordRunCallbacksFn = void (*)();
    using DiscordUpdatePresenceFn = void (*)(const DiscordRichPresence*);
    using DiscordClearPresenceFn = void (*)();
    using DiscordUpdateHandlersFn = void (*)(DiscordEventHandlers*);

    struct DiscordApi
    {
        DiscordInitializeFn Initialize = nullptr;
        DiscordShutdownFn Shutdown = nullptr;
        DiscordRunCallbacksFn RunCallbacks = nullptr;
        DiscordUpdatePresenceFn UpdatePresence = nullptr;
        DiscordClearPresenceFn ClearPresence = nullptr;
        DiscordUpdateHandlersFn UpdateHandlers = nullptr;

        bool Complete() const
        {
            return Initialize && Shutdown && RunCallbacks &&
                UpdatePresence && ClearPresence;
        }

        void Reset()
        {
            *this = {};
        }
    };

    std::atomic<bool> g_Running{ false };
    std::atomic<bool> g_Initialized{ false };
    std::atomic<bool> g_Connected{ false };

    HMODULE g_DiscordModule = nullptr;
    DiscordApi g_Api{};
    std::thread g_CallbackWorker;

    std::mutex g_LifecycleMutex;
    std::mutex g_PresenceMutex;
    std::mutex g_CallbackMutex;
    std::mutex g_ErrorMutex;

    KingModRPC::Presence g_Presence{};
    KingModRPC::JoinCallback g_JoinCallback{};
    std::int64_t g_DefaultStartTimestamp = 0;
    std::wstring g_ExtractedDllPath;
    std::string g_LastError;

    void SetLastErrorMessage(std::string message)
    {
        std::lock_guard<std::mutex> lock(g_ErrorMutex);
        g_LastError = std::move(message);
    }

    std::string Win32ErrorText(DWORD error)
    {
        if (error == ERROR_SUCCESS)
            return "No Win32 error";

        LPSTR buffer = nullptr;
        const DWORD length = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&buffer),
            0,
            nullptr);

        std::string text;
        if (length && buffer)
        {
            text.assign(buffer, length);
            while (!text.empty() &&
                (text.back() == '\r' || text.back() == '\n' || text.back() == ' '))
            {
                text.pop_back();
            }
        }
        else
        {
            text = "Win32 error " + std::to_string(error);
        }

        if (buffer)
            LocalFree(buffer);

        return text;
    }

    HMODULE GetThisModule()
    {
        return reinterpret_cast<HMODULE>(&__ImageBase);
    }

    bool GetEmbeddedDiscordBytes(const void*& data, DWORD& size)
    {
        data = nullptr;
        size = 0;

        HMODULE self = GetThisModule();
        if (!self)
        {
            SetLastErrorMessage("Could not resolve KingMod module handle for Discord RPC resource");
            return false;
        }

        HRSRC resource = FindResourceW(
            self,
            MAKEINTRESOURCEW(kDiscordRpcResourceId),
            RT_RCDATA);
        if (!resource)
        {
            SetLastErrorMessage(
                "Embedded discord-rpc.dll resource was not found (" +
                Win32ErrorText(GetLastError()) + ")");
            return false;
        }

        size = SizeofResource(self, resource);
        if (size < 1024)
        {
            SetLastErrorMessage("Embedded discord-rpc.dll resource is empty or invalid");
            return false;
        }

        HGLOBAL loaded = LoadResource(self, resource);
        if (!loaded)
        {
            SetLastErrorMessage(
                "LoadResource failed for embedded discord-rpc.dll (" +
                Win32ErrorText(GetLastError()) + ")");
            return false;
        }

        data = LockResource(loaded);
        if (!data)
        {
            SetLastErrorMessage("LockResource failed for embedded discord-rpc.dll");
            return false;
        }

        const auto* bytes = static_cast<const std::uint8_t*>(data);
        if (size < 2 || bytes[0] != 'M' || bytes[1] != 'Z')
        {
            SetLastErrorMessage("Embedded Discord RPC resource is not a valid PE image");
            return false;
        }

        return true;
    }

    std::wstring BuildPrivateTempPath()
    {
        wchar_t temp[MAX_PATH + 1]{};
        DWORD length = GetTempPathW(MAX_PATH, temp);
        if (length == 0 || length > MAX_PATH)
            return {};

        std::filesystem::path base(temp);
        base /= L"KingMod";

        std::error_code ec;
        std::filesystem::create_directories(base, ec);
        if (ec)
            return {};

        std::wostringstream name;
        name << L"discord-rpc-" << kDiscordRpcArch
             << L"-" << GetCurrentProcessId()
             << L"-" << std::hex
             << reinterpret_cast<std::uintptr_t>(GetThisModule())
             << L".dll";

        return (base / name.str()).wstring();
    }

    bool WriteResourceDllToDisk(std::wstring& outPath)
    {
        const void* resourceData = nullptr;
        DWORD resourceSize = 0;
        if (!GetEmbeddedDiscordBytes(resourceData, resourceSize))
            return false;

        outPath = BuildPrivateTempPath();
        if (outPath.empty())
        {
            SetLastErrorMessage("Could not create KingMod temporary Discord RPC path");
            return false;
        }

        // Always replace our process-specific file. This prevents a stale DLL
        // from an older KingMod build being loaded after an update.
        HANDLE file = CreateFileW(
            outPath.c_str(),
            GENERIC_WRITE,
            0,
            nullptr,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_TEMPORARY,
            nullptr);

        if (file == INVALID_HANDLE_VALUE)
        {
            SetLastErrorMessage(
                "Could not materialize embedded discord-rpc.dll (" +
                Win32ErrorText(GetLastError()) + ")");
            return false;
        }

        const auto* bytes = static_cast<const std::uint8_t*>(resourceData);
        DWORD total = 0;
        bool ok = true;

        while (total < resourceSize)
        {
            DWORD written = 0;
            const DWORD remaining = resourceSize - total;
            if (!WriteFile(file, bytes + total, remaining, &written, nullptr) || written == 0)
            {
                ok = false;
                break;
            }
            total += written;
        }

        FlushFileBuffers(file);
        CloseHandle(file);

        if (!ok || total != resourceSize)
        {
            const DWORD error = GetLastError();
            DeleteFileW(outPath.c_str());
            SetLastErrorMessage(
                "Failed writing embedded discord-rpc.dll (" +
                Win32ErrorText(error) + ")");
            return false;
        }

        return true;
    }

    template <typename T>
    T ResolveExport(HMODULE module, const char* name)
    {
        return reinterpret_cast<T>(GetProcAddress(module, name));
    }

    bool LoadEmbeddedDiscordRpc()
    {
        if (g_DiscordModule && g_Api.Complete())
            return true;

        std::wstring path;
        if (!WriteResourceDllToDisk(path))
            return false;

        // Prefer a constrained dependency search path. The bundled discord-rpc
        // DLL only needs Windows system libraries, so searching the game folder
        // or current working directory is unnecessary.
        HMODULE module = LoadLibraryExW(
            path.c_str(),
            nullptr,
            LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR |
            LOAD_LIBRARY_SEARCH_SYSTEM32);

        if (!module && GetLastError() == ERROR_INVALID_PARAMETER)
        {
            // Compatibility fallback for systems without the modern search
            // flags. Rocket League currently targets modern Windows, but this
            // keeps the wrapper graceful on older installations.
            module = LoadLibraryW(path.c_str());
        }

        if (!module)
        {
            const DWORD error = GetLastError();
            DeleteFileW(path.c_str());
            SetLastErrorMessage(
                "LoadLibraryEx failed for embedded discord-rpc.dll (" +
                Win32ErrorText(error) + ")");
            return false;
        }

        DiscordApi api{};
        api.Initialize = ResolveExport<DiscordInitializeFn>(module, "Discord_Initialize");
        api.Shutdown = ResolveExport<DiscordShutdownFn>(module, "Discord_Shutdown");
        api.RunCallbacks = ResolveExport<DiscordRunCallbacksFn>(module, "Discord_RunCallbacks");
        api.UpdatePresence = ResolveExport<DiscordUpdatePresenceFn>(module, "Discord_UpdatePresence");
        api.ClearPresence = ResolveExport<DiscordClearPresenceFn>(module, "Discord_ClearPresence");
        api.UpdateHandlers = ResolveExport<DiscordUpdateHandlersFn>(module, "Discord_UpdateHandlers");

        if (!api.Complete())
        {
            FreeLibrary(module);
            DeleteFileW(path.c_str());
            SetLastErrorMessage("Embedded discord-rpc.dll is missing one or more required exports");
            return false;
        }

        g_DiscordModule = module;
        g_Api = api;
        g_ExtractedDllPath = std::move(path);
        return true;
    }

    void UnloadEmbeddedDiscordRpc()
    {
        g_Api.Reset();

        if (g_DiscordModule)
        {
            FreeLibrary(g_DiscordModule);
            g_DiscordModule = nullptr;
        }

        if (!g_ExtractedDllPath.empty())
        {
            DeleteFileW(g_ExtractedDllPath.c_str());
            g_ExtractedDllPath.clear();
        }
    }

    std::string Base64UrlEncode(const std::string& input)
    {
        static constexpr char table[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789-_";

        std::string out;
        out.reserve((input.size() * 4 + 2) / 3);

        std::uint32_t value = 0;
        int bits = -6;

        for (unsigned char c : input)
        {
            value = (value << 8) | static_cast<std::uint32_t>(c);
            bits += 8;

            while (bits >= 0)
            {
                out.push_back(table[(value >> bits) & 0x3F]);
                bits -= 6;
            }
        }

        if (bits > -6)
            out.push_back(table[((value << 8) >> (bits + 8)) & 0x3F]);

        return out;
    }

    bool Base64UrlDecode(const std::string& input, std::string& output)
    {
        static int reverseTable[256];
        static std::once_flag once;

        std::call_once(once, []()
        {
            std::fill(std::begin(reverseTable), std::end(reverseTable), -1);
            constexpr char alphabet[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789-_";

            for (int i = 0; alphabet[i] != '\0'; ++i)
                reverseTable[static_cast<unsigned char>(alphabet[i])] = i;
        });

        output.clear();
        std::uint32_t value = 0;
        int bits = -8;

        for (unsigned char c : input)
        {
            const int decoded = reverseTable[c];
            if (decoded < 0)
                return false;

            value = (value << 6) | static_cast<std::uint32_t>(decoded);
            bits += 6;

            if (bits >= 0)
            {
                output.push_back(static_cast<char>((value >> bits) & 0xFF));
                bits -= 8;
            }
        }

        return true;
    }

    std::uint64_t Fnv1a64(const std::string& value)
    {
        std::uint64_t hash = 14695981039346656037ull;
        for (unsigned char c : value)
        {
            hash ^= c;
            hash *= 1099511628211ull;
        }
        return hash;
    }

    void PushPresenceToDiscord()
    {
        if (!g_Initialized.load(std::memory_order_acquire) || !g_Api.UpdatePresence)
            return;

        KingModRPC::Presence presence;
        {
            std::lock_guard<std::mutex> lock(g_PresenceMutex);
            presence = g_Presence;
        }

        const std::int64_t start = presence.startTimestamp > 0
            ? presence.startTimestamp
            : g_DefaultStartTimestamp;

        const int currentPlayers = std::max(0, presence.currentPlayers);
        const int maxPlayers = std::max(currentPlayers, presence.maxPlayers);

        std::string partyId = presence.partyId;
        if (partyId.empty())
            partyId = std::string("kingmod-") + kApplicationId;

        DiscordRichPresence rpc{};
        rpc.details = presence.details.empty() ? nullptr : presence.details.c_str();
        rpc.state = presence.state.empty() ? nullptr : presence.state.c_str();
        rpc.startTimestamp = start;
        rpc.largeImageKey = kLargeImageKey;
        rpc.largeImageText = "KingMod";
        rpc.smallImageKey = kSmallImageKey;
        rpc.smallImageText = "KingMod Octane";
        rpc.instance = presence.instance ? 1 : 0;

        if (!presence.joinSecret.empty())
        {
            rpc.partyId = partyId.c_str();
            rpc.partySize = currentPlayers;
            rpc.partyMax = maxPlayers;
            rpc.joinSecret = presence.joinSecret.c_str();
        }

        g_Api.UpdatePresence(&rpc);
    }

    void OnDiscordReady(const DiscordUser*)
    {
        g_Connected.store(true, std::memory_order_release);
        PushPresenceToDiscord();
    }

    void OnDiscordDisconnected(int, const char*)
    {
        g_Connected.store(false, std::memory_order_release);
    }

    void OnDiscordError(int, const char*)
    {
        g_Connected.store(false, std::memory_order_release);
    }

    void OnDiscordJoinGame(const char* joinSecret)
    {
        if (!joinSecret || !*joinSecret)
            return;

        KingModRPC::JoinCallback callback;
        {
            std::lock_guard<std::mutex> lock(g_CallbackMutex);
            callback = g_JoinCallback;
        }

        if (callback)
            callback(joinSecret);
    }

    DiscordEventHandlers MakeHandlers()
    {
        DiscordEventHandlers handlers{};
        handlers.ready = &OnDiscordReady;
        handlers.disconnected = &OnDiscordDisconnected;
        handlers.errored = &OnDiscordError;
        handlers.joinGame = &OnDiscordJoinGame;
        return handlers;
    }

    void CallbackWorkerLoop()
    {
        // The bundled RPC DLL owns its IPC thread. This worker only pumps user
        // callbacks (READY/disconnect/join) at a modest cadence.
        while (g_Running.load(std::memory_order_acquire))
        {
            auto runCallbacks = g_Api.RunCallbacks;
            if (runCallbacks)
                runCallbacks();

            for (int i = 0; i < 10 && g_Running.load(std::memory_order_acquire); ++i)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

namespace KingModRPC
{
    bool Initialize()
    {
        std::lock_guard<std::mutex> lifecycleLock(g_LifecycleMutex);

        if (g_Initialized.load(std::memory_order_acquire))
            return true;

        if (!kApplicationId[0])
        {
            SetLastErrorMessage("Set KINGMOD_DISCORD_APPLICATION_ID to enable Discord RPC.");
            return false;
        }

        SetLastErrorMessage(std::string{});
        g_Connected.store(false, std::memory_order_release);
        g_DefaultStartTimestamp = static_cast<std::int64_t>(std::time(nullptr));

        {
            std::lock_guard<std::mutex> lock(g_PresenceMutex);
            g_Presence = Presence{};
            g_Presence.details = "Playing Rocket League";
            g_Presence.state = "KingMod";
        }

        if (!LoadEmbeddedDiscordRpc())
            return false;

        DiscordEventHandlers handlers = MakeHandlers();

        // autoRegister=0: KingMod runs inside Rocket League and only needs the
        // live Discord client join callback. We do not overwrite the user's OS
        // protocol/game registration just because the DLL was injected.
        g_Api.Initialize(kApplicationId, &handlers, 0, nullptr);
        g_Initialized.store(true, std::memory_order_release);
        g_Running.store(true, std::memory_order_release);

        try
        {
            g_CallbackWorker = std::thread(CallbackWorkerLoop);
        }
        catch (...)
        {
            g_Running.store(false, std::memory_order_release);
            g_Initialized.store(false, std::memory_order_release);
            g_Api.Shutdown();
            UnloadEmbeddedDiscordRpc();
            SetLastErrorMessage("Could not create the Discord RPC callback worker");
            return false;
        }

        // Queue the initial activity immediately. READY will push it again after
        // the Discord client finishes its handshake.
        PushPresenceToDiscord();
        return true;
    }

    void Shutdown()
    {
        std::unique_lock<std::mutex> lifecycleLock(g_LifecycleMutex);

        if (!g_Initialized.load(std::memory_order_acquire) && !g_DiscordModule)
            return;

        g_Running.store(false, std::memory_order_release);
        lifecycleLock.unlock();

        if (g_CallbackWorker.joinable())
            g_CallbackWorker.join();

        lifecycleLock.lock();

        if (g_Api.ClearPresence)
            g_Api.ClearPresence();

        if (g_Api.Shutdown)
            g_Api.Shutdown();

        g_Initialized.store(false, std::memory_order_release);
        g_Connected.store(false, std::memory_order_release);

        UnloadEmbeddedDiscordRpc();
    }

    bool IsConnected()
    {
        return g_Connected.load(std::memory_order_acquire);
    }

    std::string GetLastErrorMessage()
    {
        std::lock_guard<std::mutex> lock(g_ErrorMutex);
        return g_LastError;
    }

    void SetPresence(const Presence& presence)
    {
        {
            std::lock_guard<std::mutex> lock(g_PresenceMutex);
            g_Presence = presence;
        }

        // The official RPC library safely caches/sends activity even while its
        // transport is reconnecting, so do not discard an update merely because
        // READY has not fired yet.
        PushPresenceToDiscord();
    }

    void ClearPresence()
    {
        if (g_Initialized.load(std::memory_order_acquire) && g_Api.ClearPresence)
            g_Api.ClearPresence();
    }

    void SetJoinCallback(JoinCallback callback)
    {
        std::lock_guard<std::mutex> lock(g_CallbackMutex);
        g_JoinCallback = std::move(callback);
    }

    std::string BuildJoinSecret(const std::string& ipPort, const std::string& password)
    {
        const std::string secret =
            std::string("KM1.") + Base64UrlEncode(ipPort) + "." + Base64UrlEncode(password);

        // Discord RPC documents a 128-byte secret limit. Refuse an oversized
        // payload rather than silently publishing a truncated, unjoinable one.
        if (secret.size() > 127)
            return {};

        return secret;
    }

    bool ParseJoinSecret(
        const std::string& secret,
        std::string& outIpPort,
        std::string& outPassword)
    {
        outIpPort.clear();
        outPassword.clear();

        constexpr const char* prefix = "KM1.";
        if (secret.rfind(prefix, 0) != 0)
            return false;

        const std::size_t firstPart = std::strlen(prefix);
        const std::size_t dot = secret.find('.', firstPart);
        if (dot == std::string::npos)
            return false;

        if (!Base64UrlDecode(secret.substr(firstPart, dot - firstPart), outIpPort))
            return false;

        if (!Base64UrlDecode(secret.substr(dot + 1), outPassword))
            return false;

        return !outIpPort.empty();
    }

    void SetJoinableServer(
        const std::string& ipPort,
        const std::string& password,
        int currentPlayers,
        int maxPlayers,
        const std::string& details,
        const std::string& state)
    {
        Presence presence;
        presence.details = details;
        presence.state = state;
        presence.currentPlayers = std::max(1, currentPlayers);
        presence.maxPlayers = std::max(presence.currentPlayers, maxPlayers);
        presence.partyId = "kingmod-" + std::to_string(Fnv1a64(ipPort));
        presence.joinSecret = BuildJoinSecret(ipPort, password);

        SetPresence(presence);
    }

    void SetNotJoinable(const std::string& details, const std::string& state)
    {
        Presence presence;
        presence.details = details;
        presence.state = state;
        presence.currentPlayers = 1;
        presence.maxPlayers = 1;
        presence.joinSecret.clear();
        SetPresence(presence);
    }
}
