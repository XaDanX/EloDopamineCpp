#pragma once
#include "GameObject.h"
#include "MemoryManager.h"
#include "Offsets.h"
#include "Vector.h"
#include "Spell.h"
#include "Engine.h"
#include "GameData.h"
#include "AiManager.h"
#include "BuffManager.h"

class Hero : public GameObject {
private:
    int spellBookPointers[6];
    BuffManager buffManager = BuffManager();

    int buffManagerAddress;
    int buffManagerStart;
    int buffManagerEnd;

public:
    std::string championName;
    float attackSpeedMult;
    bool isAlive;

    Spell Q_SPELL = Spell();
    Spell W_SPELL = Spell();
    Spell E_SPELL = Spell();
    Spell R_SPELL = Spell();
    Spell D_SPELL = Spell();
    Spell F_SPELL = Spell();

    AiManager aiManager = AiManager();

public:
    bool Load(unsigned int address, bool deepLoad);
    void UpdateSpells();

    Vector2 GetHealthBarPosition();

    float GetTotalAttackSpeed();
    bool IsLethalTempoActive();
    float DistanceToHero(Hero hero); 

    bool IsValidTarget();
    bool IsValidEntity();
    bool IsLocalPlayer();

    int ReadAiManager();

    BuffManager& GetBuffManager();


};
