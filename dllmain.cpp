#include "Components/Includes.hpp"
#include <Windows.h>
#include <process.h>

extern GUIComponent GUI;

unsigned __stdcall InitializeGlobalsThread(void* param)
{
    HMODULE hModule = static_cast<HMODULE>(param);

    Core.InitializeGlobals(hModule);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        GUIComponent::DllModule = hModule;

        HANDLE hThread = (HANDLE)_beginthreadex(
            nullptr,
            0,
            InitializeGlobalsThread,
            hModule,
            0,
            nullptr
        );
        if (hThread) CloseHandle(hThread);
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
    }

    return TRUE;
}