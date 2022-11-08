#pragma once
#include "GameObject.h"
#include "MemoryManager.h"
#include "Offsets.h"

class Minion : public GameObject {
public:
    bool Load(unsigned int address, bool deepLoad);

};
