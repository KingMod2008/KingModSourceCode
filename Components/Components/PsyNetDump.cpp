#include "PsyNetDump.hpp"
#include "Console.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

void PsyNetDumper::Enable()
{
    std::lock_guard<std::mutex> lock(dumpMutex);
    
    if (enabled)
    {
        Console.Warning("PsyNet dump already enabled");
        return;
    }
    
                                     
    dumpFile.open("kingmod/psynet_dump.txt", std::ios::out | std::ios::app);
    
    if (!dumpFile.is_open())
    {
        Console.Error("Failed to open psynet_dump.txt");
        return;
    }
    
    enabled = true;
    
                   
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm local;
    localtime_s(&local, &time);
    
    dumpFile << "\n========================================\n";
    dumpFile << "PsyNet Dump Started: " 
             << std::put_time(&local, "%Y-%m-%d %H:%M:%S") << "\n";
    dumpFile << "========================================\n\n";
    dumpFile.flush();
    
    Console.Success("PsyNet dump enabled -> kingmod/psynet_dump.txt");
}

void PsyNetDumper::Disable()
{
    std::lock_guard<std::mutex> lock(dumpMutex);
    
    if (!enabled)
    {
        Console.Warning("PsyNet dump not enabled");
        return;
    }
    
    if (dumpFile.is_open())
    {
        dumpFile << "\n========================================\n";
        dumpFile << "PsyNet Dump Stopped\n";
        dumpFile << "========================================\n";
        dumpFile.flush();
        dumpFile.close();
    }
    
    enabled = false;
    Console.Success("PsyNet dump disabled");
}

bool PsyNetDumper::IsEnabled()
{
    return enabled;
}

void PsyNetDumper::DumpRequest(const std::string& service, const std::string& body)
{
    if (!enabled) return;
    Write("REQUEST", service, body);
}

void PsyNetDumper::DumpResponse(const std::string& service, const std::string& body)
{
    if (!enabled) return;
    Write("RESPONSE", service, body);
}

void PsyNetDumper::Write(const std::string& direction, const std::string& service, const std::string& body)
{
    std::lock_guard<std::mutex> lock(dumpMutex);
    
    if (!dumpFile.is_open()) return;
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm local;
    localtime_s(&local, &time);
    
    dumpFile << "[" << std::put_time(&local, "%H:%M:%S") << "] "
             << direction << " - " << service << "\n"
             << body << "\n"
             << "----------------------------------------\n";
    dumpFile.flush();
}
