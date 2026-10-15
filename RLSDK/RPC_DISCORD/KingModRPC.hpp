#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace KingModRPC
{
    // Discord application:
    // Configured through KINGMOD_DISCORD_APPLICATION_ID
    //
    // Rich Presence asset keys expected in the Discord Developer Portal:
    //   large image: "kingmod"
    //   small image: "kmoctane"
    //
    // The project embeds discord-rpc.dll as an RCDATA resource. Initialize()
    // materializes the correct architecture into a private temporary file,
    // loads it with LoadLibraryExW, resolves the exported RPC API, and starts
    // a lightweight callback pump. No discord-rpc.dll is required beside
    // KingMod.dll at runtime.

    using JoinCallback = std::function<void(const std::string& joinSecret)>;

    struct Presence
    {
        std::string details = "Rocket League";
        std::string state   = "KingMod";

        int currentPlayers = 1;
        int maxPlayers     = 8;

        // Empty = KingModRPC generates a deterministic party id.
        std::string partyId;

        // Non-empty = Discord can expose its native Join action.
        std::string joinSecret;

        // Unix seconds. 0 = timestamp captured by Initialize().
        std::int64_t startTimestamp = 0;

        bool instance = true;
    };

    // Loads the embedded Discord RPC library and starts its callback pump.
    bool Initialize();

    // Clears presence, shuts Discord RPC down, unloads the embedded module,
    // and removes the temporary materialized DLL.
    void Shutdown();

    // True after Discord invokes its READY callback and until it reports a
    // disconnect/error. Initialize() itself can succeed while Discord is closed.
    bool IsConnected();

    // Returns a diagnostic string for the most recent Initialize/load failure.
    std::string GetLastErrorMessage();

    void SetPresence(const Presence& presence);
    void ClearPresence();

    // ACTIVITY_JOIN / joinGame callback. The callback is dispatched from the
    // KingMod RPC callback worker, so callers should queue Unreal work to the
    // game thread (the existing CustomMatch path already does this).
    void SetJoinCallback(JoinCallback callback);

    void SetJoinableServer(
        const std::string& ipPort,
        const std::string& password,
        int currentPlayers,
        int maxPlayers,
        const std::string& details = "Hosting a Private Match",
        const std::string& state = "KingMod Server"
    );

    void SetNotJoinable(
        const std::string& details = "Playing Rocket League",
        const std::string& state = "KingMod"
    );

    std::string BuildJoinSecret(
        const std::string& ipPort,
        const std::string& password
    );

    bool ParseJoinSecret(
        const std::string& secret,
        std::string& outIpPort,
        std::string& outPassword
    );
}
