#pragma once
#include "Windows.h"

enum Team {
    UNKNOWN = 0, // meant to use for jungle monsters etc.
    BLUE = 100,
    RED = 200
};

class GameObject {
protected:
    static const SIZE_T objectSize = 0x4000;
    BYTE buff[objectSize];
public:
    int address{};
    int index{};
    int networkId{};
    float health{};
    float maxHealth{};
    Team team{};
    float attackRange{};
    bool targetable{};
    char name{};
    float baseAttack{};
    float bonusAttack{};
    float armor{};
    float bonusArmor{};
    float lethality{};
    float magicRes{};
    bool isVisible{};
    float crit{};
    float critMult{};
    float abilityPower{};
    float magicPenMulti{};
    float magicPen{};
    float attackSpeedMulti{};
    float movementSpeed{};
    int spawnCount{};
    bool isAlive{};
    float attackRange{};
    bool isTargetable{};
    float level{};
    float mana{};
    float gameplayRadius{};
    int sourceIdX{};
    int destIdX{};
    float healthRegen{};
    float baseMoveSpeed{};
    float attackSpeed{};
    float attackSpeedRatio{};
    float basicAttackMissileSpeed{};
    float basicAttackWindUp{};
    int unitType{};
    bool recallState{};
    /*
    Tags                 []string
	AiManager            AiManager
	Icon                 *.Image
	Buffs                []Buff
	Spells               [6]Spell
	ItemSlot             [6]ItemSlot
	WindUpModifier       float32
    */
    unsigned int address{};


    virtual bool Load(unsigned int address, bool deepLoad);
};

