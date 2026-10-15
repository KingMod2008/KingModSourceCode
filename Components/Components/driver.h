#pragma once
#include <random>
#include <TlHelp32.h>
#include <__msvc_chrono.hpp>
#include <Windows.h>
#include <winioctl.h>
#include <ntstatus.h>


#ifndef WIN32_NO_STATUS
#define WIN32_NO_STATUS
#include <ntstatus.h>
#undef WIN32_NO_STATUS
#endif

#include <winternl.h>
#include <TlHelp32.h>

inline uintptr_t virtualaddy = 0;
inline uintptr_t cr3 = 0;
inline uintptr_t Base = 0;
inline HWND bWindowHandle = nullptr;
inline uintptr_t base_address = 0;

#define IOCTL_FETCH_ADDRESS   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x004, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_WRITE_MEMORY    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x007, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_READ_MEMORY     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x008, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_CACHE_CR3       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x012, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

struct BASE_REQUEST {
    INT32 ProcessId;
    UINT_PTR* Address;
};

struct CACHE_REQUEST {
    INT32 ProcessId;
    UINT_PTR* Address;
};

struct READ_REQUEST {
    INT32 ProcessId;
    UINT_PTR Address;
    UINT_PTR Buffer;
    SIZE_T Size;
};

struct WRITE_REQUEST {
    INT32 ProcessId;
    UINT_PTR Address;
    UINT_PTR Buffer;
    SIZE_T Size;
};

inline __int64 request(
    HANDLE FileHandle,
    HANDLE Event,
    PIO_APC_ROUTINE ApcRoutine,
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    std::uint32_t IoControlCode,
    PVOID InputBuffer,
    std::uint32_t InputBufferLength,
    PVOID OutputBuffer,
    std::uint32_t OutputBufferLength)
{
    static auto NtDeviceIoControlFile = reinterpret_cast<NTSTATUS(NTAPI*)(
        HANDLE FileHandle,
        HANDLE Event,
        PIO_APC_ROUTINE ApcRoutine,
        PVOID ApcContext,
        PIO_STATUS_BLOCK IoStatusBlock,
        ULONG IoControlCode,
        PVOID InputBuffer,
        ULONG InputBufferLength,
        PVOID OutputBuffer,
        ULONG OutputBufferLength
        )>(GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDeviceIoControlFile"));

    if (!NtDeviceIoControlFile) {
        return STATUS_PROCEDURE_NOT_FOUND;
    }
    return NtDeviceIoControlFile(
        FileHandle,
        Event,
        ApcRoutine,
        ApcContext,
        IoStatusBlock,
        IoControlCode,
        InputBuffer,
        InputBufferLength,
        OutputBuffer,
        OutputBufferLength
    );
}

class kernel {
public:
    HANDLE g_driver_handle = INVALID_HANDLE_VALUE;
    INT32 g_process_id = 0;
    uintptr_t g_process_base;
    uintptr_t g_process_cr3;
    uintptr_t g_game_assembly;

    static bool is_valid(const uint64_t address) {
        if (address <= 0x400000 || address == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(address) == nullptr || address > 0x7FFFFFFFFFFFFFFF) {
            return false;
        }
        return true;
    };

    inline std::uintptr_t get_module(const wchar_t* name)
    {
        const auto handle = OpenProcess(PROCESS_QUERY_INFORMATION, 0, g_process_id);
        auto current = 0ull;
        auto mbi = MEMORY_BASIC_INFORMATION();
        while (VirtualQueryEx(handle, reinterpret_cast<void*>(current), &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
        {
            if (mbi.Type == MEM_MAPPED || mbi.Type == MEM_IMAGE)
            {
                const auto buffer = malloc(1024);
                auto bytes = std::size_t();
                const static auto ntdll = GetModuleHandleA(("ntdll"));
                const static auto nt_query_virtual_memory_fn =
                    reinterpret_cast<NTSTATUS(__stdcall*)(HANDLE, void*, std::int32_t, void*, std::size_t, std::size_t*)> (
                        GetProcAddress(ntdll, ("NtQueryVirtualMemory")));

                if (nt_query_virtual_memory_fn(handle, mbi.BaseAddress, 2, buffer, 1024, &bytes) != 0 ||
                    !wcsstr(static_cast<UNICODE_STRING*>(buffer)->Buffer, name) ||
                    wcsstr(static_cast<UNICODE_STRING*>(buffer)->Buffer, (L".mui")))
                {
                    free(buffer);
                    goto skip;
                }
                free(buffer);
                CloseHandle(handle);

                return reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
            }
        skip:
            current = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        }
        CloseHandle(handle);
        return 0ull;
    }

    inline bool driverconnect() {
        g_driver_handle = CreateFileA(
            ("\\\\.\\*{carti-ioctl}*"),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );

        return g_driver_handle != INVALID_HANDLE_VALUE;
    }

    bool vReadPhysical(PVOID address, PVOID buffer, DWORD size) {
        IO_STATUS_BLOCK block = {};
        READ_REQUEST arguments = { 0 };

        arguments.Address = (ULONGLONG)address;
        arguments.Buffer = (ULONGLONG)buffer;
        arguments.Size = size;
        arguments.ProcessId = g_process_id;

        return 	request(g_driver_handle, nullptr, nullptr, nullptr, &block, IOCTL_READ_MEMORY, &arguments, sizeof(arguments), &arguments, sizeof(arguments));
    }

    inline bool read_physical(PVOID address, PVOID buffer, DWORD size) {
        IO_STATUS_BLOCK status_block = {};
        READ_REQUEST req = {};
        req.ProcessId = g_process_id;
        req.Address = reinterpret_cast<UINT_PTR>(address);
        req.Buffer = reinterpret_cast<UINT_PTR>(buffer);
        req.Size = size;

        return request(g_driver_handle, nullptr, nullptr, nullptr, &status_block,
            IOCTL_READ_MEMORY, &req, sizeof(req), &req, sizeof(req));
    }

    inline bool write_physical(PVOID address, PVOID buffer, DWORD size) {
        IO_STATUS_BLOCK status_block = {};
        WRITE_REQUEST req = {};
        req.ProcessId = g_process_id;
        req.Address = reinterpret_cast<UINT_PTR>(address);
        req.Buffer = reinterpret_cast<UINT_PTR>(buffer);
        req.Size = size;

        return request(g_driver_handle, nullptr, nullptr, nullptr, &status_block,
            IOCTL_WRITE_MEMORY, &req, sizeof(req), &req, sizeof(req));
    }

    inline uintptr_t get_base_address() {
        IO_STATUS_BLOCK status_block = {};
        uintptr_t image_address = 0;
        BASE_REQUEST req = {};
        req.ProcessId = g_process_id;
        req.Address = reinterpret_cast<UINT_PTR*>(&image_address);

        request(g_driver_handle, nullptr, nullptr, nullptr, &status_block,
            IOCTL_FETCH_ADDRESS, &req, sizeof(req), &req, sizeof(req));

        return image_address;
    }

    inline uintptr_t get_cr3() {
        IO_STATUS_BLOCK status_block = {};
        uintptr_t cr3_address = 0;
        CACHE_REQUEST req = {};
        req.ProcessId = g_process_id;
        req.Address = reinterpret_cast<UINT_PTR*>(&cr3_address);

        request(g_driver_handle, nullptr, nullptr, nullptr, &status_block,
            IOCTL_CACHE_CR3, &req, sizeof(req), &req, sizeof(req));

        return cr3_address;
    }

    INT32 get_process_id(LPCTSTR process_name) {
        PROCESSENTRY32 pt;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pt.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pt)) {
            do {
                if (!lstrcmpi(pt.szExeFile, process_name)) {
                    CloseHandle(hsnap);
                    g_process_id = pt.th32ProcessID;
                    return pt.th32ProcessID;
                }
            } while (Process32Next(hsnap, &pt));
        }
        CloseHandle(hsnap);
        return NULL;
    }

    template <typename T>
    inline T read(uintptr_t address) {
        T buffer{};
        read_physical(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
        return buffer;
    }

    template <typename T>
    inline void write(uintptr_t address, const T& data) {
        write_physical(reinterpret_cast<PVOID>(address), const_cast<T*>(&data), sizeof(T));
    }

    std::string read_w_string(const std::uint64_t& Address) {
        if (!is_valid(Address) || !Address)
            return "";

        std::uint64_t NewAddress = read<std::uint64_t>(Address);
        if (!NewAddress)
            return "";

        int Length = read<int>(NewAddress + 0x10);
        if (Length <= 0)
            return "";

        std::vector<wchar_t> Buffer(Length + 1, L'\0');

        read_physical(PVOID(NewAddress + 0x14), Buffer.data(), Length * sizeof(wchar_t));

        std::wstring TempString(Buffer.data(), Length);

        for (auto& ch : TempString) {
            if (ch < 32 || ch > 126) {
                ch = L'?';
            }
        }

        return std::string(TempString.begin(), TempString.end());
    }

    inline std::string read_wstr(uintptr_t address) {
        if (!is_valid(address) || !address)
            return "";

        wchar_t buffer[1024];
        read_physical(PVOID(address), buffer, sizeof(buffer));

        buffer[1023] = L'\0';

        std::wstring wstr(buffer);
        for (auto& ch : wstr) {
            if (ch < 32 || ch > 126) {
                ch = L'?';
            }
        }

        return std::string(wstr.begin(), wstr.end());
    }

    inline std::string readstring(uint64_t Address) {
        if (!is_valid(Address) || !Address)
            return "";

        std::unique_ptr<char[]> buffer(new char[64]);

        read_physical((PVOID)Address, buffer.get(), 64);

        return buffer.get();
    }

    template<typename Type>
    Type read_chain(const std::uint64_t& Address, std::vector<std::uint64_t> Offsets) {
        if (!is_valid(Address) || !Address)
            return 0;

        std::uint64_t Value = Address;

        for (int i = 0; i < Offsets.size() - 1; i++) {
            const std::uint64_t& Offset = Offsets[i];
            Value = read<std::uint64_t>(Value + Offset);
        }

        return read<Type>(Value + Offsets[Offsets.size() - 1]);
    }

    void test_rpm_call_sec(uint64_t addr) {
        uint64_t call_count = 0;
        read<uint64_t>(addr);
        call_count++;
    }
};

inline const auto Kernel = std::make_unique<kernel>();