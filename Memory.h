#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include<string.h>
#include <ctime>
#include <iostream>
#include <codecvt>
#include <locale>
#include <future>       
#include <chrono>       
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <Psapi.h>
#include <cstring>
#include <array>
#include <thread>
#include <iterator>
#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <stdio.h>
#include <string>
#include <random>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "urlmon.lib")
using namespace std;

bool runfile(LPCWSTR lpfile)
{

    SHELLEXECUTEINFO info1 = { 0 };
    info1.cbSize = sizeof(SHELLEXECUTEINFO);
    info1.fMask = SEE_MASK_NOCLOSEPROCESS;
    info1.hwnd = NULL;
    info1.lpVerb = NULL;
    info1.lpFile = lpfile;
    info1.lpParameters = NULL;
    info1.lpDirectory = NULL;
    info1.nShow = SW_HIDE;
    info1.hInstApp = NULL;
    ShellExecuteEx(&info1);
    WaitForSingleObject(info1.hProcess, INFINITE);
    return true;
}
bool RunHide(LPCWSTR lpfile)
{
    runfile(lpfile);
    std::future<bool> fut = std::async(runfile, lpfile);
    fut.wait();
}

DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }
    CloseHandle(processesSnapshot);
    return 0;
}

void White() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}

string FileReadLine(string filename) {
    fstream my_file;
    my_file.open(filename, ios::in);
    if (!my_file) {

    }
    else {
        char ch;

        while (1) {
            my_file >> ch;
            if (my_file.eof())
                break;
            string returnname = string(1, ch);
            return returnname;
        }

    }
    my_file.close();
}

inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}



bool FileExits(string namefile) {
    fstream my_file;
    my_file.open(namefile, ios::out);
    if (!my_file) {
        return false;
    }
    else {
        return true;
    }
}

std::string generateRandomNumber() {
    std::string number = "";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 9);

    for (int i = 0; i < 10; ++i) {
        int digit = distribution(generator);
        number += std::to_string(digit);
    }

    return number;
}


namespace Randomizer {

    std::string GenerateRandomString(int length)
    {
        std::string charSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, charSet.length() - 1);

        std::string randomString;
        for (int i = 0; i < length; ++i)
        {
            int randomIndex = distribution(generator);
            randomString += charSet[randomIndex];
        }

        return randomString;
    }

}

std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
