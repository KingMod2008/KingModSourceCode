#include "MatchmakingShield.hpp"

#include <Windows.h>
#include <atomic>
#include <algorithm>

namespace MatchmakingShield
{
    namespace
    {
        std::atomic<bool> g_enabled{ false };
        std::atomic<int> g_joinKey{ VK_F8 };
        std::atomic<UOnlineGameJoinGame_X*> g_pendingJoin{ nullptr };
        std::atomic<bool> g_allowNextTravel{ false };
        std::atomic<ULONGLONG> g_pendingSince{ 0 };
        std::atomic<bool> g_autoAccept{ false };
        std::atomic<ULONGLONG> g_autoAcceptDelayMs{ 3000 };
        std::atomic<ULONGLONG> g_holdTimeoutMs{ 45000 };

        bool g_previousKeyState = false;                         
        UFunction* g_fnTravelToServer = nullptr;                           


        UOnlineGame_X* GetOnlineGame()
        {
            return APlayerController_X::GetOnlineGame();
        }

        UOnlineGameJoinGame_X* GetCurrentJoinGame()
        {
            UOnlineGame_X* onlineGame = GetOnlineGame();
            return onlineGame ? onlineGame->JoinGame : nullptr;
        }

        bool IsPendingJoinValid(UOnlineGameJoinGame_X* pending)
        {
            if (!pending)
                return false;

            UOnlineGameJoinGame_X* current = GetCurrentJoinGame();
            return current && current == pending;
        }

        UFunction* GetTravelFunction()
        {
            if (!g_fnTravelToServer)
            {
                g_fnTravelToServer = UFunction::FindFunction(
                    "Function ProjectX.OnlineGameJoinGame_X.TravelToServer");
            }
            return g_fnTravelToServer;
        }

        void ClearPending()
        {
            g_pendingJoin.store(nullptr, std::memory_order_release);
            g_pendingSince.store(0, std::memory_order_release);
            g_allowNextTravel.store(false, std::memory_order_release);
        }
    }

    void SetEnabled(bool enabled)
    {
        const bool old = g_enabled.exchange(enabled, std::memory_order_acq_rel);
        if (old == enabled)
            return;

        if (!enabled)
        {
                                                                              
                                                                    
            if (g_pendingJoin.load(std::memory_order_acquire))
                AcceptPendingJoin();
            g_previousKeyState = false;
        }
    }

    bool IsEnabled()
    {
        return g_enabled.load(std::memory_order_acquire);
    }

    void SetJoinKey(int virtualKey)
    {
        if (virtualKey <= 0)
            return;
        g_joinKey.store(virtualKey, std::memory_order_release);
        g_previousKeyState = false;
    }

    int GetJoinKey()
    {
        return g_joinKey.load(std::memory_order_acquire);
    }

    bool IsWaitingForJoin()
    {
        return g_pendingJoin.load(std::memory_order_acquire) != nullptr;
    }

    float GetPendingSeconds()
    {
        const ULONGLONG since = g_pendingSince.load(std::memory_order_acquire);
        if (since == 0)
            return 0.0f;
        const ULONGLONG now = GetTickCount64();
        return static_cast<float>(now >= since ? now - since : 0) / 1000.0f;
    }

    void SetAutoAccept(bool enabled, float delaySeconds)
    {
        g_autoAccept.store(enabled, std::memory_order_release);
        const float clamped = (std::max)(0.25f, (std::min)(delaySeconds, 30.0f));
        g_autoAcceptDelayMs.store(static_cast<ULONGLONG>(clamped * 1000.0f), std::memory_order_release);
    }

    bool IsAutoAcceptEnabled()
    {
        return g_autoAccept.load(std::memory_order_acquire);
    }

    float GetAutoAcceptDelay()
    {
        return static_cast<float>(g_autoAcceptDelayMs.load(std::memory_order_acquire)) / 1000.0f;
    }

    void SetHoldTimeout(float seconds)
    {
        const float clamped = (std::max)(5.0f, (std::min)(seconds, 180.0f));
        g_holdTimeoutMs.store(static_cast<ULONGLONG>(clamped * 1000.0f), std::memory_order_release);
    }

    float GetHoldTimeout()
    {
        return static_cast<float>(g_holdTimeoutMs.load(std::memory_order_acquire)) / 1000.0f;
    }

    bool AcceptPendingJoin()
    {
        UOnlineGameJoinGame_X* pending =
            g_pendingJoin.exchange(nullptr, std::memory_order_acq_rel);
        g_pendingSince.store(0, std::memory_order_release);

        if (!pending || !IsPendingJoinValid(pending))
        {
            g_allowNextTravel.store(false, std::memory_order_release);
            return false;
        }

                                                                              
        g_allowNextTravel.store(true, std::memory_order_release);
        pending->TravelToServer();

                                                                       
        g_allowNextTravel.store(false, std::memory_order_release);
        return true;
    }

    void CancelPendingJoin()
    {
        UOnlineGameJoinGame_X* current = GetCurrentJoinGame();
        ClearPending();

        if (current && current->IsJoiningGame())
            current->CancelJoin();
    }

    void Tick()
    {
        if (!IsEnabled())
        {
            g_previousKeyState = false;
            return;
        }

        UOnlineGameJoinGame_X* pending =
            g_pendingJoin.load(std::memory_order_acquire);

        if (pending)
        {
            if (!IsPendingJoinValid(pending))
            {
                ClearPending();
                pending = nullptr;
            }
            else
            {
                const ULONGLONG since = g_pendingSince.load(std::memory_order_acquire);
                const ULONGLONG now = GetTickCount64();
                if (since != 0 && now - since > g_holdTimeoutMs.load(std::memory_order_acquire))
                {
                                                                                 
                                                                                 
                    CancelPendingJoin();
                    pending = nullptr;
                }
                else if (g_autoAccept.load(std::memory_order_acquire) &&
                    since != 0 && now - since >= g_autoAcceptDelayMs.load(std::memory_order_acquire))
                {
                    AcceptPendingJoin();
                    pending = nullptr;
                }
            }
        }

        const int key = GetJoinKey();
        const bool keyDown = key > 0 && (GetAsyncKeyState(key) & 0x8000) != 0;
        const bool keyPressed = keyDown && !g_previousKeyState;
        g_previousKeyState = keyDown;

        if (keyPressed && pending)
            AcceptPendingJoin();
    }

    bool OnProcessEventPre(UObject* object, UFunction* function, void* params)
    {
        (void)params;

        if (!IsEnabled() || !object || !function)
            return false;

        UFunction* travelFunction = GetTravelFunction();
        if (!travelFunction || function != travelFunction ||
            !object->IsA<UOnlineGameJoinGame_X>())
        {
            return false;
        }

        auto* joinGame = static_cast<UOnlineGameJoinGame_X*>(object);

        if (g_allowNextTravel.exchange(false, std::memory_order_acq_rel))
            return false;

                                                                                
        g_pendingJoin.store(joinGame, std::memory_order_release);
        g_pendingSince.store(GetTickCount64(), std::memory_order_release);
        MessageBeep(MB_ICONINFORMATION);
        return true;
    }

    void Reset()
    {
        ClearPending();
        g_previousKeyState = false;
    }
}
