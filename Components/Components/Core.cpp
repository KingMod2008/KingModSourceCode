#include "Core.hpp"
#include "../Includes.hpp"
#include <filesystem>
#include <algorithm>
#include <psapi.h>
#include <vector>
#include <sstream>
#include <iomanip>                                   

                                                    


                                                   


#include <stdexcept>
#include <thread>                                                    
#include <chrono>                                          
#include "../../Modules/Mods/CustomMatch.hpp"
#include "../../RLSDK/RPC_DISCORD/KingModRPC.hpp"

                       

namespace
{
    bool IsReadableMemory(const void* address, size_t byteCount)
    {
        if (!address || byteCount == 0)
            return false;

        MEMORY_BASIC_INFORMATION memoryInfo{};
        if (VirtualQuery(address, &memoryInfo, sizeof(memoryInfo)) != sizeof(memoryInfo))
            return false;

        const DWORD protection = memoryInfo.Protect & 0xFF;
        if (memoryInfo.State != MEM_COMMIT || (memoryInfo.Protect & PAGE_GUARD) != 0 || protection == PAGE_NOACCESS)
            return false;

        const auto begin = reinterpret_cast<uintptr_t>(address);
        const auto end = begin + byteCount;
        const auto regionEnd = reinterpret_cast<uintptr_t>(memoryInfo.BaseAddress) + memoryInfo.RegionSize;
        return end >= begin && end <= regionEnd;
    }

    bool IsExecutableMemory(const void* address)
    {
        if (!address)
            return false;

        MEMORY_BASIC_INFORMATION memoryInfo{};
        if (VirtualQuery(address, &memoryInfo, sizeof(memoryInfo)) != sizeof(memoryInfo))
            return false;

        const DWORD protection = memoryInfo.Protect & 0xFF;
        return memoryInfo.State == MEM_COMMIT && (memoryInfo.Protect & PAGE_GUARD) == 0 &&
            (protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READ ||
             protection == PAGE_EXECUTE_READWRITE || protection == PAGE_EXECUTE_WRITECOPY);
    }

    constexpr int32_t kMaxReasonableGlobalObjectCount = 2'000'000;

    void ShowStartupNotice()
    {
                                                                            
                                                                               
        std::thread([]() {
            MessageBoxW(nullptr,
                L"KingMod is loading.\n\nwait 10-40 sec and the menu will show!",
                L"KingMod",
                MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND);
        }).detach();
    }
}

bool CoreComponent::TamperingDetected = false;

CoreComponent::CoreComponent() : Component("Core", "Initializes globals, components, and modules."), currentPlatform(Platform::Unknown)
{
    OnCreate();
}

CoreComponent::~CoreComponent() {
    OnDestroy();
}

void CoreComponent::OnCreate()
{
    MainThread = nullptr;
    currentPlatform = DetectPlatform();
}

void CoreComponent::OnDestroy() {
    DestroyThread();
}

void CoreComponent::InitializeThread()
{
    MainThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitializeGlobals), nullptr, 0, nullptr);
}

void CoreComponent::DestroyThread()
{
    if (MainThread) {
        CloseHandle(MainThread);
        MainThread = nullptr;
    }
}

Platform CoreComponent::DetectPlatform()
{
    try {
        std::string processPath = GetCurrentProcessPath();
        std::transform(processPath.begin(), processPath.end(), processPath.begin(), ::tolower);
        Console.Write("[Core Module] Process path: " + processPath);
        if (processPath.find("epic") != std::string::npos) {
            Console.Write("[Core Module] Detected platform: Epic Games");
            return Platform::Epic;
        }
        else if (processPath.find("steam") != std::string::npos) {
            Console.Write("[Core Module] Detected platform: Steam");
            return Platform::Steam;
        }
        else {
            return Platform::Unknown;
        }
    }
    catch (...) {
        return Platform::Unknown;
    }
}

std::string CoreComponent::GetCurrentProcessPath()
{
    char processPath[MAX_PATH];
    if (GetModuleFileNameA(NULL, processPath, MAX_PATH) == 0) {
        return "";
    }
    return std::string(processPath);
}

uintptr_t CoreComponent::FindPattern(const char* pattern)
{
    const auto moduleHandle = GetModuleHandle(NULL);
    if (!moduleHandle) return 0;
    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO))) return 0;
    const uintptr_t base = reinterpret_cast<uintptr_t>(moduleHandle);
    const uintptr_t size = moduleInfo.SizeOfImage;
    std::vector<int> patternBytes;
    std::stringstream ss(pattern);
    std::string byteStr;
    while (ss >> byteStr) {
        if (byteStr == "??") patternBytes.push_back(-1);
        else patternBytes.push_back(std::stoi(byteStr, nullptr, 16));
    }
    for (uintptr_t i = 0; i < size - patternBytes.size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < patternBytes.size(); ++j) {
            if (patternBytes[j] != -1 && patternBytes[j] != *reinterpret_cast<const uint8_t*>(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) return base + i;
    }
    return 0;
}

uintptr_t CoreComponent::FindPatternWithMask(const char* pattern, const char* mask)
{
    const auto moduleHandle = GetModuleHandle(NULL);
    if (!moduleHandle) return 0;
    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO))) return 0;
    const uintptr_t base = reinterpret_cast<uintptr_t>(moduleHandle);
    const uintptr_t size = moduleInfo.SizeOfImage;
    size_t maskLen = strlen(mask);
    for (uintptr_t i = 0; i < size - maskLen; ++i) {
        bool found = true;
        for (size_t j = 0; j < maskLen; ++j) {
            if (mask[j] == 'x' && pattern[j] != *reinterpret_cast<const uint8_t*>(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) return base + i;
    }
    return 0;
}

uintptr_t CoreComponent::ResolveRipRelativeAddress(uintptr_t instructionAddr, int offsetInInstruction, int nextInstructionSize)
{
    int32_t ripOffset = *reinterpret_cast<int32_t*>(instructionAddr + offsetInInstruction);
    return instructionAddr + offsetInInstruction + 4 + (ripOffset - (4 - nextInstructionSize));
}

void CoreComponent::InitializeGlobals(HMODULE hModule)
{
    Console.Initialize(std::filesystem::current_path(), "Template.log");
    Console.Write("[Core Module] Starting initialization...");

    ShowStartupNotice();
                                                                           
                                                                               
                                                                          
    std::this_thread::sleep_for(std::chrono::seconds(10));

    uintptr_t gnamesAddress = 0;
    uintptr_t gobjectsAddress = 0;

                                                       
    uintptr_t addr = FindPattern("48 8B 0D ?? ?? ?? ?? 48 8B 0C C1");
    if (addr != 0) {
        int32_t ripOffset = *reinterpret_cast<int32_t*>(addr + 3);
        gnamesAddress = addr + 3 + 4 + ripOffset;
        Console.Write("[Core Module] GNames found via pattern 1 at: " + Format::ToHex(reinterpret_cast<void*>(gnamesAddress)));
    }

                                                                              
    if (gnamesAddress == 0) {
        addr = FindPattern("49 63 06 48 8D 55 E8 48 8B 0D ?? ?? ?? ?? 48 8B 0C C1");
        if (addr != 0) {
            int32_t ripOffset = *reinterpret_cast<int32_t*>(addr + 10);
            gnamesAddress = addr + 10 + 4 + ripOffset;
            Console.Write("[Core Module] GNames found via pattern 2 at: " + Format::ToHex(reinterpret_cast<void*>(gnamesAddress)));
        }
    }

                                                                  
    addr = FindPattern("48 8B C8 48 8B 05 ?? ?? ?? ?? 48 8B 0C C8");
    if (addr != 0) {
        int32_t ripOffset = *reinterpret_cast<int32_t*>(addr + 6);
        gobjectsAddress = addr + 6 + 4 + ripOffset;
        Console.Write("[Core Module] GObjects found via pattern at: " + Format::ToHex(reinterpret_cast<void*>(gobjectsAddress)));
    }

                                         
    if (gnamesAddress != 0 && gobjectsAddress == 0) {
        gobjectsAddress = gnamesAddress + 0x48;
        Console.Write("[Core Module] GObjects calculated from GNames + 0x48: " + Format::ToHex(reinterpret_cast<void*>(gobjectsAddress)));
    }

    if (gnamesAddress == 0) {
        Console.Error("[Core Module] All GNames pattern scans FAILED. The mod cannot continue.");
        MessageBoxA(NULL, "Critical error during initialization (Code: PNF).", "Fatal Error", MB_OK | MB_ICONERROR);
        return;
    }


    if (gnamesAddress == 0) {
        Console.Error("[Core Module] Validation failed or tampering detected. Halting initialization.");
        return;
    }

    Console.Write("[Core Module] Validation successful. Continuing initialization...");

    Console.Notify("[Core Module] Found GNames at: " + Format::ToHex(reinterpret_cast<void*>(gnamesAddress)));
    Console.Notify("[Core Module] Calculated GObjects at: " + Format::ToHex(reinterpret_cast<void*>(gobjectsAddress)));
    GNames = reinterpret_cast<TArray<FNameEntry*>*>(gnamesAddress);
    GObjects = reinterpret_cast<TArray<UObject*>*>(gobjectsAddress);

    if (AreGlobalsValid()) {
        Console.Notify("[Core Module] Global Objects: " + Format::ToHex(GObjects));
        Console.Notify("[Core Module] Global Names: " + Format::ToHex(GNames));
        Console.Write("[Core Module] Initialized!");
        Console.Write("[Core Module] Mapping instances...");
        Instances.Initialize();
        Console.Write("[Core Module] Instances mapped successfully.");
        Console.Write("[Core Module] Resolving ProcessEvent target...");

        UClass* objectClass = UObject::StaticClass();
        if (!objectClass || !IsReadableMemory(objectClass, sizeof(UObject))) {
            Console.Error("[Core Module] UObject class was invalid. The SDK offsets do not match this game build.");
            return;
        }

        void** unrealVTable = reinterpret_cast<void**>(objectClass->VfTableObject.Dummy);
        if (!IsReadableMemory(unrealVTable, sizeof(void*) * 68) || !IsExecutableMemory(unrealVTable[67])) {
            Console.Error("[Core Module] ProcessEvent vtable entry was invalid. The SDK vtable index does not match this game build.");
            return;
        }

        Console.Write("[Core Module] Attaching ProcessEvent detour...");
        if (!EventsComponent::AttachDetour(reinterpret_cast<ProcessEventType>(unrealVTable[67]))) {
            Console.Error("[Core Module] ProcessEvent detour could not be attached. Initialization stopped safely.");
            return;
        }

        Events.Initialize();
        GUI.Initialize();
        Main.Initialize();

                                                                                
                                                                              
                                                                            
                                                                               
                                         
        KingModRPC::SetJoinCallback([](const std::string& joinSecret)
        {
            std::string endpoint;
            std::string password;
            if (!KingModRPC::ParseJoinSecret(joinSecret, endpoint, password))
                return;

            std::string host;
            std::string port;
            if (!CustomMatchModule::NormalizeLanEndpoint(endpoint, "", host, port))
                return;

            CustomMatchModule::JoinLanMatchByIP(host, port, password);
        });

        if (KingModRPC::Initialize())
        {
            KingModRPC::SetNotJoinable("In Main Menu", "KingMod | Rocket League");
            Console.Write("[Discord RPC] Rich Presence initialized (kingmod / kmoctane)");
        }
        else
        {
            Console.Warning("[Discord RPC] Worker could not be started");
        }
    }
    else {
        Console.Error("[Core Module] GObjects and GNames addresses were found but failed validation!");
    }
}

bool CoreComponent::AreGlobalsValid()
{
    return (AreGObjectsValid() && AreGNamesValid());
}

bool CoreComponent::AreGObjectsValid()
{
    auto* objects = UObject::GObjObjects();
    if (!IsReadableMemory(objects, sizeof(*objects)))
        return false;

    const int32_t count = objects->size();
    const int32_t capacity = objects->capacity();
    return count > 0 && count <= kMaxReasonableGlobalObjectCount &&
        capacity >= count && capacity <= kMaxReasonableGlobalObjectCount &&
        IsReadableMemory(objects->data(), sizeof(UObject*) * static_cast<size_t>(count));
}

bool CoreComponent::AreGNamesValid()
{
    auto* names = FName::Names();
    if (!IsReadableMemory(names, sizeof(*names)))
        return false;

    const int32_t count = names->size();
    const int32_t capacity = names->capacity();
    return count > 0 && count <= kMaxReasonableGlobalObjectCount &&
        capacity >= count && capacity <= kMaxReasonableGlobalObjectCount &&
        IsReadableMemory(names->data(), sizeof(FNameEntry*) * static_cast<size_t>(count));
}

CoreComponent Core;
