#include<Windows.h>
#include<iostream>
#include <string>
#include "skStr.h"
#include <Windows.h>
#include <chrono>
#include"memory.h"
#include <Authentication.h>


string randomfile = Randomizer::GenerateRandomString(10);

bool ServerRiot = true;


DWORD DiscoverProcID(const std::wstring& processName) {
    DWORD processId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                std::wstring currentProcessName = procEntry.szExeFile;
                if (currentProcessName == processName) {
                    processId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
        CloseHandle(hSnap);
    }
    return processId;
}

bool IsFileAvailable(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void DisplayInformation(const std::string& message) {
    std::cout << skCrypt("INFO: ").decrypt() << message << std::endl;
}

void ReleaseAllocatedMemory(HANDLE hProc, void* loc) {
    // Przywrócenie oryginalnych atrybutów pamięci przed zwolnieniem
    DWORD oldProtect;
    VirtualProtectEx(hProc, loc, 0, PAGE_READWRITE, &oldProtect);

    VirtualFreeEx(hProc, loc, 0, MEM_RELEASE);
}

bool DrTelbi(const std::wstring& targetProcName, const std::string& libPath) {
    std::cout << skCrypt("Initializing DrTelbi...\n").decrypt();

    if (!IsFileAvailable(libPath)) {
        return false;
    }

    DWORD procPID = DiscoverProcID(targetProcName);
    if (procPID == 0) {
        return false;
    }

    HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, procPID);
    if (!hProc) {
        return false;
    }

    SIZE_T pathSize = libPath.size() + 1;
    void* loc = VirtualAllocEx(hProc, nullptr, pathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!loc) {
        CloseHandle(hProc);
        return false;
    }

    if (!WriteProcessMemory(hProc, loc, libPath.c_str(), pathSize, nullptr)) {
        ReleaseAllocatedMemory(hProc, loc);
        CloseHandle(hProc);
        return false;
    }


    HMODULE hKernel32 = GetModuleHandle(skCrypt(L"kernel32.dll").decrypt());
    auto pLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32, skCrypt("LoadLibraryA").decrypt());

    HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0, pLoadLibrary, loc, CREATE_NO_WINDOW, nullptr);
    if (!hThread) {
        ReleaseAllocatedMemory(hProc, loc);
        CloseHandle(hProc);
        return false;
    }

    if (WaitForSingleObject(hThread, INFINITE) != WAIT_OBJECT_0) {
        ReleaseAllocatedMemory(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }

    DWORD exitCode = 0;
    if (!GetExitCodeThread(hThread, &exitCode) || exitCode == STILL_ACTIVE) {
        ReleaseAllocatedMemory(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }

    DWORD oldProtect;
    if (!VirtualProtectEx(hProc, loc, pathSize, PAGE_NOACCESS, &oldProtect)) {
        ReleaseAllocatedMemory(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }

    ReleaseAllocatedMemory(hProc, loc);
    CloseHandle(hThread);
    CloseHandle(hProc);

    std::cout << skCrypt("DrTelbi completed successfully.\n").decrypt();
    return true;
}

DWORD WINAPI InitializeGameEnhancement(PVOID) {
}

void ActivateGameModule() {
    struct bypass_load_data {
        void* bot_module;
        char bot_directory[MAX_PATH];
        char bot_user[40];
        void* fn_get_key_state;
        void* fn_issue_order;
        void* fn_update_spell;
        bool reserved_0[7];
        void* reserved_1;
        void* reserved_2;
        void* reserved_3;
        void* reserved_4;
    } request = {};

    string justpathloader = skCrypt("C:\\Hanbot\\league of legends\\").decrypt() + randomfile + skCrypt(".dll").decrypt();
    const char* dllPath2 = justpathloader.c_str();
    auto hBotModule = LoadLibraryA(dllPath2);
    if (!hBotModule) {
        MessageBoxA(NULL, skCrypt("Failed 1").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
        exit(0);
    }

    std::cout << skCrypt("Bot module loaded successfully.").decrypt() << std::endl;

    request.bot_module = hBotModule;
    strcpy_s(request.bot_directory, (skCrypt("C:\\Hanbot\\league of legends\\").decrypt()));
    strcpy_s(request.bot_user, (skCrypt("EE0BDF0F9CE165532696B5789968D1A6").decrypt()));
    request.fn_get_key_state = GetAsyncKeyState;

    auto pStartRoutine = GetProcAddress(hBotModule, skCrypt("setup").decrypt());
    if (!pStartRoutine) {
        MessageBoxA(NULL, skCrypt("Failed 2").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
        exit(0);
    }

    std::cout << skCrypt("Start routine found successfully.").decrypt() << std::endl;

    reinterpret_cast<int(_cdecl*)(PVOID, DWORD_PTR, DWORD_PTR, DWORD_PTR)>(pStartRoutine)(&request, 0, 0, 0);
}


void SetupGraphicsDriver() {
    randomfile = Randomizer::GenerateRandomString(10);
    std::wstring Procesqjhd9q = skCrypt(L"League of Legends.exe").decrypt();
    DWORD procP2ID = DiscoverProcID(Procesqjhd9q);

    if (procP2ID == 0) {
        exit(0);
    }
    else {
        if (ServerRiot) {
            const char* sourcePath = skCrypt("C:\\Hanbot\\league of legends\\core.dll").decrypt();
            std::string stringdestinationPath = skCrypt("C:\\Hanbot\\league of legends\\").decrypt() + randomfile + skCrypt(".dll").decrypt();
            const char* destinationPath = stringdestinationPath.c_str();
            BOOL result = CopyFileA(sourcePath, destinationPath, FALSE);

            if (result) {
                if (DrTelbi(Procesqjhd9q, destinationPath)) {
                    ActivateGameModule();
                }
            }
            else {
                exit(0);
            }
        }
        else if (!ServerRiot) {
            exit(0);
        }
    }
}


inline bool CheckFileExistence(const std::string& name) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, name.c_str(), skCrypt("r").decrypt());
    if (err == 0 && file != nullptr) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

namespace NvidiaToolkit {
    void InitializeDriver() {

        //Authentication::AuthenticationInitialize();
        //Authentication::LicenseInit();
        SetupGraphicsDriver();
    }
}
