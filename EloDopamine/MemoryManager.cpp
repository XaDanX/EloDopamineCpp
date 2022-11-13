#include "MemoryManager.h"
#include "StringUtils.h"
#pragma comment (lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI NtReadVirtualMemory(HANDLE, PVOID, PVOID, ULONG, PULONG);

bool MemoryManager::Initialize() {

    hWindow = FindWindowA("RiotWindowClass", nullptr);
    if (!hWindow) {
        logger->Debug("Couldn't find window class.");
        return false;
    }

    GetWindowThreadProcessId(hWindow, &pid);
    if (pid == NULL) {
        logger->Debug("Couldn't retrieve league process id");
        return false;

    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        logger->Debug("Couldn't open league process");
        return false;
    }

    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        baseAddress = (DWORD)hMods[0];
    }
    else {
        logger->Debug("Couldn't retrieve league base address");
        return false;
    }

    logger->Debug("Base Address: %#08x", this->baseAddress);

    return true;
}

DWORD MemoryManager::BaseAddress() {
    return this->baseAddress;
}

void MemoryManager::ReadBuffer(DWORD addr, void* structure, int size) {
    SIZE_T bytesRead = 0;
    //ReadProcessMemory(this->hProcess, (DWORD*)addr, structure, size, &bytesRead);
    NtReadVirtualMemory(this->hProcess, (DWORD*)addr, structure, size, (PULONG)&bytesRead);
}

std::string MemoryManager::ReadString(DWORD address) { // Ghetto as fuck but riot uses std::string/charmaps randomly and i want one universal method to read them, it works XD
    char nameBuff[50];
    std::string ret;
    int addr;

    auto len = this->Read<int>(address + 16);

    if (len < 1 or len > 50) {
        len = this->Read<int>(address + 4);
        addr = this->Read<int>(address);
    }
    else {
        if (len >= 16) {
            addr = this->Read<int>(address);
        }
        else {
            addr = address;
        }
    }

    memoryManager->ReadBuffer(addr, nameBuff, 50);
    if (StringUtils::IsASCII(nameBuff, 50))
        ret = StringUtils::ToLower(std::string(nameBuff));
    else
        ret = std::string("");
    return ret;
}

std::string MemoryManager::ReadStringSized(DWORD address, int size)
{
    char nameBuff[150];
    memoryManager->ReadBuffer(address, nameBuff, 150);
    if (StringUtils::IsASCII(nameBuff, 150)) {
        return StringUtils::ToLower(std::string(nameBuff));
    }
    else {
        return std::string("");
    }
}

std::vector<int> MemoryManager::ReadTemplate(int address) {
    int template_array = memoryManager->Read<int>(address + 0x4);
    int template_array_length = memoryManager->Read<int>(address + 0x8);
    std::vector<int> pointerList;
    for (int index = 0; index < template_array_length; index++) {
        int objectPointer = memoryManager->Read<int>(template_array + (index * 4));
        pointerList.emplace_back(objectPointer);
    }


    return pointerList;
}

std::vector<int> MemoryManager::ReadTemplateSized(int address, int size) {
    int template_array = memoryManager->Read<int>(address + 0x4);
    std::vector<int> pointerList;
    for (int index = 0; index < size; index++) {
        int objectPointer = memoryManager->Read<int>(template_array + (index * 4));
        pointerList.emplace_back(objectPointer);
    }


    return pointerList;
}

HWND MemoryManager::GetWindowHandle() {
    return this->hWindow;
}