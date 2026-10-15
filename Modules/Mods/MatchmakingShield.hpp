#pragma once

#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"

namespace MatchmakingShield
{
    void SetEnabled(bool enabled);
    bool IsEnabled();

    void SetJoinKey(int virtualKey);
    int GetJoinKey();

    bool IsWaitingForJoin();
    float GetPendingSeconds();
    void SetAutoAccept(bool enabled, float delaySeconds);
    bool IsAutoAcceptEnabled();
    float GetAutoAcceptDelay();
    void SetHoldTimeout(float seconds);
    float GetHoldTimeout();

                                            
    void Tick();

    bool AcceptPendingJoin();
    void CancelPendingJoin();

                                                           
    bool OnProcessEventPre(UObject* object, UFunction* function, void* params);

    void Reset();
}
