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

bool CheckFilePresence(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void NotifyInfo(const std::string& message) {
    std::cout << skCrypt("State: ").decrypt() << message << std::endl;
}

void SecureMemoryRelease(HANDLE hProc, void* loc) {
    if (loc != nullptr) {
        VirtualFreeEx(hProc, loc, 0, MEM_RELEASE);
    }
}

bool x7Gh5JkLmN(const std::wstring& a1Zx9vB3Qr, const std::string& s5dP4kL8mN) {

    if (!CheckFilePresence(s5dP4kL8mN)) {
        return false;
    }

    DWORD p9Tg5lBv3c = DiscoverProcID(a1Zx9vB3Qr);
    if (p9Tg5lBv3c == 0) {
        return false;
    }

    HANDLE h2Gj9kL5zD = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, p9Tg5lBv3c);
    if (h2Gj9kL5zD == nullptr) {
        return false;
    }

    auto r4Tg6hJ9kL = std::unique_ptr<void, decltype(&CloseHandle)>(h2Gj9kL5zD, CloseHandle);

    uintptr_t q8Rf4gT5hJ = reinterpret_cast<uintptr_t>(VirtualAllocEx(h2Gj9kL5zD, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (q8Rf4gT5hJ == 0) {
        return false;
    }

    BOOL n4Bv7cX2zL = WriteProcessMemory(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ), s5dP4kL8mN.c_str(), s5dP4kL8mN.size() + 1, nullptr);
    if (!n4Bv7cX2zL) {
        SecureMemoryRelease(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ));
        return false;
    }

    DWORD k5Mh7gJ2lD;
    VirtualProtectEx(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ), MAX_PATH, PAGE_EXECUTE_READ, &k5Mh7gJ2lD);

    HANDLE l3Km8hJ6vG = CreateRemoteThread(h2Gj9kL5zD, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), reinterpret_cast<void*>(q8Rf4gT5hJ), 0, nullptr);
    if (l3Km8hJ6vG == nullptr) {
        SecureMemoryRelease(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ));
        return false;
    }

    auto m8Nj7bH6kL = std::unique_ptr<void, decltype(&CloseHandle)>(l3Km8hJ6vG, CloseHandle);

    WaitForSingleObject(l3Km8hJ6vG, INFINITE);

    VirtualProtectEx(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ), MAX_PATH, PAGE_READWRITE, &k5Mh7gJ2lD);

    SecureMemoryRelease(h2Gj9kL5zD, reinterpret_cast<void*>(q8Rf4gT5hJ));
    NotifyInfo(skCrypt("Init").decrypt());
    return true;
}




DWORD WINAPI InitBotActivity(PVOID) {


}

void ExecuteBotThroughLib() {
    struct bypass_load_data {
        void* bot_module;
        char bot_directory[MAX_PATH];
        char bot_user[40];
        void* fn_get_key_state;
        void* fn_issue_order;
        void* fn_cast_spell;
        void* fn_update_spell;
        bool use_configer;
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
    strcpy_s(request.bot_user, (skCrypt("D134869D963C3F865FA0D9570C71B9E9").decrypt()));
    request.fn_get_key_state = GetAsyncKeyState;

    auto pStartRoutine = GetProcAddress(hBotModule, skCrypt("setup").decrypt());
    if (!pStartRoutine) {
        MessageBoxA(NULL, skCrypt("Failed 2").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
        exit(0);
    }

    std::cout << skCrypt("Start routine found successfully.").decrypt() << std::endl;

    reinterpret_cast<int(_cdecl*)(PVOID, DWORD_PTR, DWORD_PTR, DWORD_PTR)>(pStartRoutine)(&request, 0, 0, 0);
    std::wstring processName2 = skCrypt(L"League of Legends.exe").decrypt();
    if (hBotModule && pStartRoutine) {
        x7Gh5JkLmN(processName2, dllPath2);

        std::cout << skCrypt("DLL injected successfully.").decrypt() << std::endl;
    }
}

void ImplementDriver() {
    randomfile = Randomizer::GenerateRandomString(10);
    std::wstring Procesqjhd9q = skCrypt(L"League of Legends.exe").decrypt();
    DWORD procP2ID = DiscoverProcID(Procesqjhd9q);
    if (procP2ID == 0) {
        MessageBoxA(NULL, skCrypt("Could Not Found Game").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
        exit(0);
    }
    else {
        if (ServerRiot) {
            const char* sourcePath = skCrypt("C:\\Hanbot\\league of legends\\core.dll").decrypt();
            std::string stringdestinationPath = skCrypt("C:\\Hanbot\\league of legends\\").decrypt() + randomfile + skCrypt(".dll").decrypt();
            const char* destinationPath = stringdestinationPath.c_str();
            BOOL result = CopyFileA(sourcePath, destinationPath, FALSE);
            if (result) {
                if (x7Gh5JkLmN(Procesqjhd9q, destinationPath)) {
                    ExecuteBotThroughLib();
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

inline bool FileExist(const std::string& name) {
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

namespace CoreHelper {
    void VanguardInit() {

        Authentication::AuthenticationInitialize();
        Authentication::LicenseInit();
        ImplementDriver();
    }
}
