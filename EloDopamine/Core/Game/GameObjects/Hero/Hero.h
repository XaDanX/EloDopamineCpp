#pragma once
#include "../GameObject.h"
#include "../../Managers/MemoryManager/MemoryManager.h"
#include "../../Offsets.h"
#include "../../../Math/Vector.h"
#include "SpellBook/Spell.h"
#include "../../Engine/Engine.h"
#include "../../GameData/GameData.h"
#include "AiManager/AiManager.h"
#include "BuffManager/BuffManager.h"
#include "ActiveSpell/ActiveSpell.h"

class Hero : public GameObject {
private:
    int spellBookPointers[6];
    BuffManager buffManager = BuffManager();

    int buffManagerAddress;
    int buffManagerStart;
    int buffManagerEnd;

    int activeSpellAddress = 0;
    ActiveSpell activeSpell;

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
    bool Load(unsigned int address, bool deepLoad) override;
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

    std::optional<ActiveSpell> GetActiveSpell();


};
