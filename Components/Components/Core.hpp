#pragma once
#include "../Component.hpp"
#include <string>
#include <cstdint>                          

enum class Platform {
    Epic,
    Steam,
    Unknown
};

                                                                                                
class CoreComponent : public Component
{
private:
    HANDLE MainThread;
    Platform currentPlatform;

public:
    CoreComponent();
    ~CoreComponent() override;

public:
    void OnCreate() override;
    void OnDestroy() override;

public:
    void InitializeThread();
    void DestroyThread();
    Platform DetectPlatform();
    std::string GetCurrentProcessPath();
    static void InitializeGlobals(HMODULE hModule);
    static bool TamperingDetected;
    static std::string TheGoldenRuler;
    static bool AreGlobalsValid();
    static bool AreGObjectsValid();
    static bool AreGNamesValid();

private:
                                                        
    static uintptr_t FindPattern(const char* pattern);
                                                                             
    static uintptr_t FindPatternWithMask(const char* pattern, const char* mask);
                                                                  
    static uintptr_t ResolveRipRelativeAddress(uintptr_t instructionAddr, int offsetInInstruction, int nextInstructionSize);
};

extern class CoreComponent Core;