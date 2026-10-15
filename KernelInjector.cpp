                                              
                                                                             

#include <Windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include "Components/Components/driver.h"

                        
namespace InjectorLog
{
    void Write(const std::string& msg)
    {
        std::cout << "[+] " << msg << std::endl;
    }
    
    void Error(const std::string& msg)
    {
        std::cerr << "[-] " << msg << std::endl;
    }
    
    void Success(const std::string& msg)
    {
        std::cout << "[*] " << msg << std::endl;
    }
}

class SimpleKernelInjector
{
private:
    HANDLE m_driver_handle;
    INT32 m_target_pid;
    uintptr_t m_target_base;
    
public:
    SimpleKernelInjector() 
        : m_driver_handle(INVALID_HANDLE_VALUE)
        , m_target_pid(0)
        , m_target_base(0)
    {
    }
    
    ~SimpleKernelInjector()
    {
        if (m_driver_handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_driver_handle);
        }
    }
    
    bool Initialize(const std::string& target_process)
    {
        InjectorLog::Write("Connecting to kernel driver...");
        
                            
        if (!Kernel->driverconnect())
        {
            InjectorLog::Error("Failed to connect to driver!");
            InjectorLog::Error("Make sure driver.sys is loaded with: sc start [driver-service-name]");
            return false;
        }
        
        m_driver_handle = Kernel->g_driver_handle;
        InjectorLog::Success("Driver connected!");
        
                              
        InjectorLog::Write("Looking for process: " + target_process);
        m_target_pid = Kernel->get_process_id(target_process.c_str());
        
        if (m_target_pid == 0)
        {
            InjectorLog::Error("Process not found! Is Rocket League running?");
            return false;
        }
        
        InjectorLog::Success("Found process with PID: " + std::to_string(m_target_pid));
        
                           
        m_target_base = Kernel->get_base_address();
        if (m_target_base == 0)
        {
            InjectorLog::Error("Failed to get process base address!");
            return false;
        }
        
        char hex[32];
        sprintf_s(hex, "0x%llX", m_target_base);
        InjectorLog::Success(std::string("Process base: ") + hex);
        
                                    
        uintptr_t cr3 = Kernel->get_cr3();
        char hex_cr3[32];
        sprintf_s(hex_cr3, "0x%llX", cr3);
        InjectorLog::Success(std::string("CR3 cached: ") + hex_cr3);
        
        return true;
    }
    
    bool InjectDLL(const std::wstring& dll_path)
    {
        if (!std::filesystem::exists(dll_path))
        {
            InjectorLog::Error("DLL file not found!");
            return false;
        }
        
        InjectorLog::Write("Reading DLL from disk...");
        
                        
        FILE* file = nullptr;
        _wfopen_s(&file, dll_path.c_str(), L"rb");
        if (!file)
        {
            InjectorLog::Error("Failed to open DLL file!");
            return false;
        }
        
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        std::vector<uint8_t> dll_data(file_size);
        fread(dll_data.data(), 1, file_size, file);
        fclose(file);
        
        InjectorLog::Success("DLL loaded, size: " + std::to_string(file_size) + " bytes");
        
                           
        auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(dll_data.data());
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        {
            InjectorLog::Error("Invalid DOS signature!");
            return false;
        }
        
        auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>(dll_data.data() + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
        {
            InjectorLog::Error("Invalid NT signature!");
            return false;
        }
        
        size_t image_size = nt->OptionalHeader.SizeOfImage;
        InjectorLog::Write("Image size: " + std::to_string(image_size) + " bytes");
        
                                                          
        uintptr_t remote_base = 0x50000000;                    
        
        InjectorLog::Write("Allocating memory in target process...");
        
                                                     
        uint8_t test = 0;
        if (Kernel->read_physical(PVOID(remote_base), &test, 1))
        {
            InjectorLog::Error("Target address appears occupied, trying different address...");
            remote_base = 0x60000000;
        }
        
        char hex[32];
        sprintf_s(hex, "0x%llX", remote_base);
        InjectorLog::Success(std::string("Using remote base: ") + hex);
        
                        
        InjectorLog::Write("Writing PE headers...");
        size_t headers_size = nt->OptionalHeader.SizeOfHeaders;
        if (!Kernel->write_physical(PVOID(remote_base), dll_data.data(), headers_size))
        {
            InjectorLog::Error("Failed to write headers!");
            return false;
        }
        
                         
        InjectorLog::Write("Writing sections...");
        auto section = IMAGE_FIRST_SECTION(nt);
        for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++, section++)
        {
            if (section->SizeOfRawData == 0) continue;
            
            uintptr_t dest = remote_base + section->VirtualAddress;
            const uint8_t* src = dll_data.data() + section->PointerToRawData;
            
            if (!Kernel->write_physical(PVOID(dest), const_cast<uint8_t*>(src), section->SizeOfRawData))
            {
                InjectorLog::Error("Failed to write section!");
                return false;
            }
            
            char name[9] = {0};
            memcpy(name, section->Name, 8);
            InjectorLog::Write("  Written: " + std::string(name));
        }
        
        InjectorLog::Success("All sections written!");
        
                                                        
                                                                      
                                                      
                                                
        
                                                                   
        HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_target_pid);
        if (!h_process || h_process == INVALID_HANDLE_VALUE)
        {
            InjectorLog::Error("Failed to open process for thread creation!");
            return false;
        }
        
        uintptr_t entry_point = remote_base + nt->OptionalHeader.AddressOfEntryPoint;
        
        sprintf_s(hex, "0x%llX", entry_point);
        InjectorLog::Write(std::string("Creating remote thread at: ") + hex);
        
        HANDLE h_thread = CreateRemoteThread(
            h_process,
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(entry_point),
            reinterpret_cast<LPVOID>(remote_base),
            0,
            nullptr
        );
        
        if (!h_thread || h_thread == INVALID_HANDLE_VALUE)
        {
            InjectorLog::Error("Failed to create remote thread! Error: " + std::to_string(GetLastError()));
            CloseHandle(h_process);
            return false;
        }
        
        InjectorLog::Success("Remote thread created!");
        InjectorLog::Write("Waiting for DLL initialization...");
        
        WaitForSingleObject(h_thread, 5000);
        
        CloseHandle(h_thread);
        CloseHandle(h_process);
        
        InjectorLog::Success("Injection completed!");
        return true;
    }
};

int main(int argc, char* argv[])
{
    std::cout << R"(
╔═══════════════════════════════════════╗
║   KingMod Kernel Injector v1.0        ║
║   EAC Bypass via Kernel Driver        ║
╚═══════════════════════════════════════╝
)" << std::endl;
    
                   
    std::wstring dll_path;
    if (argc > 1)
    {
        std::string arg = argv[1];
        dll_path = std::wstring(arg.begin(), arg.end());
    }
    else
    {
                                                             
        wchar_t exe_path[MAX_PATH];
        GetModuleFileNameW(nullptr, exe_path, MAX_PATH);
        std::filesystem::path exe_dir = std::filesystem::path(exe_path).parent_path();
        dll_path = (exe_dir / L"newkingmod.dll").wstring();
    }
    
    InjectorLog::Write("Target DLL: " + std::string(dll_path.begin(), dll_path.end()));
    
    if (!std::filesystem::exists(dll_path))
    {
        InjectorLog::Error("DLL not found!");
        InjectorLog::Error("Usage: KernelInjector.exe [path_to_dll]");
        std::cout << "\nPress Enter to exit...";
        std::cin.get();
        return 1;
    }
    
                            
    SimpleKernelInjector injector;
    
    if (!injector.Initialize("RocketLeague.exe"))
    {
        InjectorLog::Error("Initialization failed!");
        std::cout << "\nPress Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    if (!injector.InjectDLL(dll_path))
    {
        InjectorLog::Error("Injection failed!");
        std::cout << "\nPress Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    std::cout << "\n[*] All done! KingMod should be loaded in Rocket League." << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}
