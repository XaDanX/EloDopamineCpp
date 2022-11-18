#pragma once
#pragma once
#include "Windows.h"
#include "../../../Utils/Logger.h"
#include "psapi.h"
#include <vector>
#include <TlHelp32.h>

class MemoryManager {
private:
    HANDLE hProcess{ nullptr };
    DWORD pid{ 0 };
    HWND hWindow{ nullptr };

    DWORD baseAddress{ 0 };

public:
    bool Initialize();

    DWORD BaseAddress();

    template<typename T>
    T Read(DWORD addy) { // Has to be inplace (sadly) or it's causing LNK2019
        T buffer;
        ReadProcessMemory(this->hProcess, (LPVOID)addy, &buffer, sizeof(T), NULL);
        if (buffer) { return buffer; }
        else { return NULL; }

    }

    void ReadBuffer(DWORD addr, void* structure, int size);
    std::string ReadString(DWORD address);
    std::string ReadStringSized(DWORD address, int size);
    std::vector<int> ReadTemplate(int address);
    std::vector<int> ReadTemplateSized(int address, int size);
    HWND GetWindowHandle();


};
inline extern std::unique_ptr<MemoryManager> memoryManager = std::make_unique<MemoryManager>();



