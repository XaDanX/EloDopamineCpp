#pragma once
#include "../../../Managers/MemoryManager/MemoryManager.h"
#include "../../../../Math/Vector.h"
#include "../../../GameData/SpellInfo.h"
#include "../../../GameData/Missile.h"


class ActiveSpell {
protected:
    static const SIZE_T activeSpellSize = 0x500;
    BYTE buff[activeSpellSize];
public:
    Vector3 startPos;
    Vector3 endPos;
    std::string name;
    float startTime;
    float endTime;
    SpellInfo* spellInfo{};

    void Load(int address);

    Missile GetMissile();

};

