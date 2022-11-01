#pragma once
#include "Windows.h"
#include "Vector.h"
#include "UnitInfo.h"

enum Team {
    UNKNOWN = 0, // meant to use for jungle monsters etc.
    BLUE = 100,
    RED = 200
};

enum CharacterState
{
    CanAttack = 1,
    CanCast = 2,
    CanMove = 4,
    Immovable = 8,
    Unknownz = 16,
    IsStealth = 32,
    Taunted = 64,
    Feared = 128,
    Fleeing = 256,
    Supressed = 512,
    Asleep = 1024,
    NearSight = 2048,
    Ghosted = 4096,
    HasGhost = 8192,
    Charmed = 16384,
    NoRender = 32768,
    DodgePiercing = 131072,
    DisableAmbientGold = 262144,
    DisableAmbientXP = 524288,
    ForceRenderParticles = 65536,
    IsCombatEnchanced = 1048576,
    IsSelectable = 16777216
};

class GameObject {
protected:
    static const SIZE_T objectSize = 0x4000;
    BYTE buff[objectSize];
public:
    int index{};
    float health{};
    float maxHealth{};
    Team team{};
    float attackRange{};
    bool targetable{};
    bool visible{};
    Vector3 position{};
    int actionState{};

    unsigned int address{};

    UnitInfo* unitInfo;


    virtual bool Load(unsigned int address, bool deepLoad);

    bool CanAttack();
    bool CanMove();
    bool CanCast();
    bool CheckState(CharacterState state);
    UnitInfo* GetUnitInfo();


};

