#pragma once
#include "GameObject.h"
#include "MemoryManager.h"
#include "Offsets.h"
#include "Vector.h"
#include "Spell.h"

class Hero : public GameObject {
private:
    int spellBookPointers[6]; // 6 spells, spell = pointer
public:
    std::string championName;

    Spell Q_SPELL = Spell();
    Spell W_SPELL = Spell();
    Spell E_SPELL = Spell();
    Spell R_SPELL = Spell();
    Spell D_SPELL = Spell();
    Spell F_SPELL = Spell();
public:
    bool Load(unsigned int address, bool deepLoad);
    void UpdateSpells();
};
