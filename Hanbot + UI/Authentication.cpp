#include <iostream>
#include <windows.h>
#include <vector>
#include <d3d9.h>
#include <string.h>
#include "auth.h"
#include <TlHelp32.h>
#include <string>
#include "skStr.h"
#include <globals.h>
#include <Vanguard.h>

typedef LONG(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

using namespace std;
using namespace KeyAuth;

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

auto name = skCrypt("Hanbot");
auto ownerid = skCrypt("0uZmlfg3fy");
auto secret = skCrypt("988413c497760926b11a7243a5459e4b7bc435ed28c1b717196ae84ec4a49f0d");
auto version = skCrypt("1.1");
auto url = skCrypt("https://keyauth.win/api/1.2/");

bool CheckLic = true;

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), skCrypt("%a %m/%d/%y %H:%M").decrypt(), &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10);

    return (time_t)cv;
}

namespace Authentication {

    void AuthenticationInitialize() {
        KeyAuthApp.init();
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

    void LicenseAuth()
    {
        if (!CheckLic)
        {
            exit(0);
        }

        std::string decryptedPath = skCrypt("C:\\Hanbot.lic").decrypt();
        if (!FileExist(decryptedPath))
        {
            exit(0);
        }

        std::ifstream inputFile(decryptedPath);
        if (!inputFile.is_open())
        {
            exit(0);
        }

        std::string LicenseKey;
        if (!std::getline(inputFile, LicenseKey))
        {
            inputFile.close();
            exit(0);
        }

        inputFile.close();
        KeyAuthApp.license(LicenseKey);
        if (!KeyAuthApp.data.success)
        {
            exit(0);
        }


        for (const auto& sub : KeyAuthApp.data.subscriptions)
        {
            std::cout << skCrypt("Welcome to Hanshield, ").decrypt();
            std::cout << skCrypt("version: ").decrypt(); std::cout << KeyAuthApp.version; std::cout << skCrypt(". ").decrypt();
            HMODULE hMod = GetModuleHandleW(skCrypt(L"ntdll.dll").decrypt());
            if (hMod) {
                RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hMod, skCrypt("RtlGetVersion").decrypt());
                if (pRtlGetVersion != nullptr) {
                    RTL_OSVERSIONINFOW rovi = {};
                    rovi.dwOSVersionInfoSize = sizeof(rovi);
                    if (pRtlGetVersion(&rovi) == 0) {
                        std::cout << skCrypt("Windows build: ").decrypt() << rovi.dwMajorVersion << "." << rovi.dwMinorVersion << "." << rovi.dwBuildNumber << std::endl;
                    }
                    else {
                        std::cout << skCrypt("Windows build: Unknown").decrypt() << std::endl;
                    }
                }
            }
            std::cout << skCrypt("Using scripting platform: Hanbot").decrypt() << std::endl;
            std::string currentVersion = skCrypt("1.1").decrypt();
            if (currentVersion != KeyAuthApp.version)
            {
                exit(0);
            }
            else 
            {
                std::cout << skCrypt("No updates required.").decrypt() << std::endl;
                std::cout << skCrypt("").decrypt() << std::endl;
            }
            std::cout << skCrypt("Your subscribtion is still valid for: ").decrypt() << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry))) << std::endl;
        }
    }

    void LicenseInit()
    {
        if (!CheckLic)
        {
            exit(0);
        }

        std::string decryptedPath = skCrypt("C:\\Hanbot.lic").decrypt();
        if (!FileExist(decryptedPath))
        {
            exit(0);
        }

        std::ifstream inputFile(decryptedPath);
        if (!inputFile.is_open())
        {
            exit(0);
        }

        std::string LicenseKey;
        if (!std::getline(inputFile, LicenseKey))
        {
            inputFile.close();
            exit(0);
        }

        inputFile.close();
        KeyAuthApp.license(LicenseKey);
        if (!KeyAuthApp.data.success)
        {
            exit(0);
        }
    }


    void LoadLicense() {
        std::ifstream LicenseFile(skCrypt("C:\\Hanbot.lic").decrypt());
        if (LicenseFile.is_open()) {
            std::string line;
            if (std::getline(LicenseFile, line)) {
                strncpy_s(globals.license, line.c_str(), sizeof(globals.license));
            }
            LicenseFile.close();
        }
        else {
            std::cerr << skCrypt(" ").decrypt() << std::endl;
        }
    }

}

bool isLeagueOfLegendsRunning() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe32)) {
            do {
                if (std::wstring(pe32.szExeFile) == skCrypt(L"League of Legends.exe").decrypt()) {
                    CloseHandle(hSnapshot);
                    return true;
                }
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
    return false;
}

namespace League {

    void waitForLeagueOfLegends() {
        while (true) {
            if (isLeagueOfLegendsRunning()) {
                std::cout << skCrypt("League of Legends has started. Hanshield Init\n").decrypt();
                CoreHelper::VanguardInit();
                break;
            }
        }
    }

}

namespace Security {
    void checkForMonitoringTools() {
        std::vector<std::string> monitoringTools = {
            skCrypt("fiddler").decrypt(),
            skCrypt("httpdebugger").decrypt(),
            skCrypt("wireshark").decrypt(),
            skCrypt("charles").decrypt(),
            skCrypt("burpsuite").decrypt(),
            skCrypt("tcpdump").decrypt(),
            skCrypt("ettercap").decrypt(),
            skCrypt("cain & abel").decrypt(),
            skCrypt("network miner").decrypt(),
            skCrypt("paros proxy").decrypt(),
            skCrypt("owasp zap").decrypt(),
            skCrypt("postman").decrypt(),
            skCrypt("telerik fiddler").decrypt(),
            skCrypt("mitmproxy").decrypt(),
            skCrypt("debugbar").decrypt(),
            skCrypt("firebug").decrypt(),
            skCrypt("gdb").decrypt(),
            skCrypt("ollydbg").decrypt(),
            skCrypt("x64dbg").decrypt(),
            skCrypt("ida pro").decrypt(),
            skCrypt("radare2").decrypt(),
            skCrypt("frida").decrypt()
        };

        HWND hwnd;
        for (const auto& tool : monitoringTools) {
            hwnd = FindWindowA(NULL, tool.c_str());
            if (hwnd) {
                std::cout << skCrypt(" ").decrypt() << tool << std::endl;
                exit(0);
            }
        }
    }
}
