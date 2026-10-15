#pragma once
#include <string>
#include <fstream>
#include <mutex>

class PsyNetDumper
{
public:
    static void Enable();
    static void Disable();
    static bool IsEnabled();
    
    static void DumpRequest(const std::string& service, const std::string& body);
    static void DumpResponse(const std::string& service, const std::string& body);
    
private:
    static inline bool enabled = false;
    static inline std::ofstream dumpFile;
    static inline std::mutex dumpMutex;
    
    static void Write(const std::string& direction, const std::string& service, const std::string& body);
};
