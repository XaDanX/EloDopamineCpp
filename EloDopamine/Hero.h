#pragma once
#include "GameObject.h"
#include "MemoryManager.h"
#include "Offsets.h"

class Hero : public GameObject {
public:
    std::string championName;
public:
    bool Load(unsigned int address, bool deepLoad);
};
