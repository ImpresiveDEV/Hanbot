#include<Windows.h>
#include<iostream>
#include "auth.hpp"
#include <string>
#include "skStr.h"
#include <Windows.h>
#include <chrono>
#include"memory.h"

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace std;
using namespace KeyAuth;
auto name = skCrypt("Hanbot");
auto ownerid = skCrypt("0uZmlfg3fy");
auto secret = skCrypt("988413c497760926b11a7243a5459e4b7bc435ed28c1b717196ae84ec4a49f0d");
auto version = skCrypt("1.0");
auto url = skCrypt("https://keyauth.win/api/1.2/");
bool ServerRiot = false;
bool ServerChina = false;
string LicenseKey;

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());
string randomfile = GenerateRandomString(10);

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

void ReportIssue(const std::string& message, DWORD errorCode) {
    std::string error_message = skCrypt("Error: ").decrypt() + message + skCrypt(" | Code: ").decrypt() + std::to_string(errorCode);
    std::cerr << error_message << std::endl;
}

void NotifyInfo(const std::string& message) {
    std::cout << skCrypt("INFO: ").decrypt() << message << std::endl;
}

void SecureMemoryRelease(HANDLE hProc, void* loc) {

    VirtualFreeEx(hProc, loc, 0, MEM_RELEASE);
}

bool EmbedDynamicLib(const std::wstring& targetProcName, const std::string& libPath) {
    std::cout << skCrypt("Inicjowanie procesu iniekcji biblioteki.").decrypt() << std::endl;

    if (!CheckFilePresence(libPath)) {
        std::cerr << skCrypt("Brak pliku biblioteki").decrypt() << std::endl;
        return false;
    }

    DWORD procPID = DiscoverProcID(targetProcName);
    if (procPID == 0) {
        ReportIssue(skCrypt("Nie znaleziono procesu gry.").decrypt(), GetLastError());
        return false;
    }

    HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, procPID);
    if (!hProc) {
        ReportIssue(skCrypt("OpenProcess nie powiodło się").decrypt(), GetLastError());
        return false;
    }

    void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!loc) {
        ReportIssue(skCrypt("VirtualAllocEx nie powiodło się").decrypt(), GetLastError());
        CloseHandle(hProc);
        return false;
    }

    BOOL wpmResult = WriteProcessMemory(hProc, loc, libPath.c_str(), libPath.size() + 1, NULL);
    if (!wpmResult) {
        ReportIssue(skCrypt("WriteProcessMemory nie powiodło się").decrypt(), GetLastError());
        SecureMemoryRelease(hProc, loc);
        CloseHandle(hProc);
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, NULL);
    if (!hThread) {
        ReportIssue(skCrypt("CreateRemoteThread nie powiodło się").decrypt(), GetLastError());
        SecureMemoryRelease(hProc, loc);
        CloseHandle(hProc);
        return false;
    }

    DWORD waitResult = WaitForSingleObject(hThread, INFINITE);
    if (waitResult != WAIT_OBJECT_0) {
        ReportIssue(skCrypt("WaitForSingleObject nie powiodło się lub wątek nie sygnalizował sukcesu").decrypt(), waitResult);
        SecureMemoryRelease(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }

    DWORD exitCode = 0;
    if (!GetExitCodeThread(hThread, &exitCode) || exitCode == STILL_ACTIVE) {
        ReportIssue(skCrypt("GetExitCodeThread nie powiodło się lub wątek nadal jest aktywny").decrypt(), exitCode);
        SecureMemoryRelease(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }
    else if (exitCode != 0) {
        ReportIssue(skCrypt("DLL nie załadowała się poprawnie").decrypt(), exitCode);
        SecureMemoryRelease(hProc, loc);
        CloseHandle(hThread);
        CloseHandle(hProc);
        return false;
    }

    SecureMemoryRelease(hProc, loc);
    CloseHandle(hThread);
    CloseHandle(hProc);

    NotifyInfo(skCrypt("Iniekcja DLL zakończona pomyślnie.").decrypt());
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
        EmbedDynamicLib(processName2, dllPath2);

        std::cout << skCrypt("DLL injected successfully.").decrypt() << std::endl;
    }
}

void ImplementDriver() {
    randomfile = GenerateRandomString(10);
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
                if (EmbedDynamicLib(Procesqjhd9q, destinationPath)) {
                    ExecuteBotThroughLib();
                }
            }
            else {
                ReportIssue(skCrypt("Failed Load DLL").decrypt(), GetLastError());
                MessageBoxA(NULL, skCrypt("Failed Load DLL").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
                exit(0);
            }
        }
        else if (ServerChina) {
            const char* sourcePath = skCrypt("C:\\Hanbot\\league of legends\\core_cn.dll").decrypt();
            std::string stringdestinationPath = skCrypt("C:\\Hanbot\\league of legends\\").decrypt() + randomfile + skCrypt(".dll").decrypt();
            const char* destinationPath = stringdestinationPath.c_str();
            BOOL result = CopyFileA(sourcePath, destinationPath, FALSE);
            if (result) {
                if (EmbedDynamicLib(Procesqjhd9q, destinationPath)) {
                    ExecuteBotThroughLib();
                }
            }
            else {
                ReportIssue(skCrypt("Failed Load DLL").decrypt(), GetLastError());
                MessageBoxA(NULL, skCrypt("Failed Load DLL").decrypt(), skCrypt("Hanbot").decrypt(), MB_OK | MB_ICONERROR | MB_APPLMODAL);
                exit(0);
            }
        }
        else if (!ServerRiot && !ServerChina) {
            exit(0);
        }
    }
}

int main()
{
    ::ShowWindow(GetConsoleWindow(), SW_HIDE);

    KeyAuthApp.init();
    if (!KeyAuthApp.data.success)
    {
        exit(0);
    }
    else
    {
        if (FileExist(skCrypt("C:\\Hanbot.lic").decrypt()))
        {
            std::ifstream inputFile(skCrypt("C:\\Hanbot.lic").decrypt());
            if (inputFile.is_open()) {
                std::string line;
                while (std::getline(inputFile, LicenseKey))
                {

                }
                inputFile.close();
            }
            KeyAuthApp.license(LicenseKey);
            if (!KeyAuthApp.data.success)
            {
                exit(0);
            }
        }
        else
        {
            exit(0);
        }
        ImplementDriver();
    }

}
