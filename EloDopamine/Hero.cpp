#include "Hero.h"
#include "ObjectManager.h"
#include "XorStr.hpp"
bool Hero::Load(unsigned int address, bool deepLoad) {
    if (!this->address)
        this->address = address;
    memoryManager->ReadBuffer(this->address, this->buff, Hero::objectSize);

    memcpy(&index, &buff[Offsets::ObjIndex], sizeof(byte));
    memcpy(&team, &buff[Offsets::ObjTeam], sizeof(short));
    memcpy(&health, &buff[Offsets::ObjHealth], sizeof(float));
    memcpy(&maxHealth, &buff[Offsets::ObjMaxHealth], sizeof(float));
    memcpy(&attackRange, &buff[Offsets::ObjATKRange], sizeof(float));
    memcpy(&targetable, &buff[Offsets::ObjTargetable], sizeof(bool));
    memcpy(&position, &buff[Offsets::ObjPos], sizeof(Vector3));
    memcpy(&visible, &buff[Offsets::ObjVisibility], sizeof(bool));
    memcpy(&actionState, &buff[Offsets::ObjActionState], sizeof(uint16_t));
    memcpy(&spellBookPointers, &buff[Offsets::ObjSpellBOOK], sizeof(int) * 6);
    memcpy(&attackSpeedMult, &buff[Offsets::ObjATKSpeedMulti], sizeof(float));
    memcpy(&buffManagerAddress, &buff[Offsets::ObjBuffManager], sizeof(int));
    memcpy(&buffManagerStart, &buff[Offsets::ObjBuffManager + 0x10], sizeof(int));
    memcpy(&buffManagerEnd, &buff[Offsets::ObjBuffManager + 0x14], sizeof(int));

    bool alive;
    memcpy(&alive, &buff[Offsets::ObjDead], sizeof(BYTE));
    if (alive % 2 == 0) {
        this->isAlive = true;
    } else {
        this->isAlive = false;
    }



    if (championName.empty()) {
        championName = memoryManager->ReadString(this->address + Offsets::ObjName);
    }

    if (this->unitInfo == nullptr)
        this->unitInfo = gameData->GetUnitInfoByName(this->championName);
        
   
    if (this->aiManager.address == 0) {
        this->aiManager.address = this->ReadAiManager();
        //logger->Debug("%#08x", this->aiManager.address);
    }



    this->aiManager.Update();

    this->UpdateSpells();

    return true;
}

void Hero::UpdateSpells() {

    this->Q_SPELL.address = this->spellBookPointers[0];
    this->W_SPELL.address = this->spellBookPointers[1];
    this->E_SPELL.address = this->spellBookPointers[2];
    this->R_SPELL.address = this->spellBookPointers[3];
    this->D_SPELL.address = this->spellBookPointers[4];
    this->F_SPELL.address = this->spellBookPointers[5];
    
    this->Q_SPELL.Update();
    this->W_SPELL.Update();
    this->E_SPELL.Update();
    this->R_SPELL.Update();
    this->D_SPELL.Update();
    this->F_SPELL.Update();
}

Vector2 Hero::GetHealthBarPosition() {
    Vector3 point = position.clone();
    point.y += this->unitInfo->healthBarHeight;

    Vector2 out = engine->WorldToScreen(point);
    out.y -= (engine->WindowHeight() * 0.00083333335f * this->unitInfo->healthBarHeight);
    out.x -= 70.0f;
    return out;
}

float Hero::GetTotalAttackSpeed() {
    float attackSpeed = (this->attackSpeedMult - 1.0) * this->unitInfo->attackSpeedRatio + this->unitInfo->baseAttackSpeed;
    if (attackSpeed <= 2.5) {
        return attackSpeed;
    }
    if (IsLethalTempoActive()) {
        return attackSpeed;
    }
    return 2.5;
}

bool Hero::IsLethalTempoActive() {

    BuffManager heroBuffs = objectManager->GetLocalPlayer().GetBuffManager();

    for (auto buff : heroBuffs.buffList) {
        if (buff.name != XorStr("assets/perks/styles/precision/lethaltempo/lethaltempo.lua").c_str()) continue;
        if (buff.count != 6) continue;
        return true;
    }
    return false;
}

float Hero::DistanceToHero(Hero hero) {
    return sqrt(powf((this->position.x - hero.position.x), 2) + powf((this->position.y - hero.position.y), 2) + powf((this->position.z - hero.position.z), 2));
}

bool Hero::IsValidTarget() {
    if (this->address == objectManager->GetLocalPlayer().address) return false;
    if (!this->visible) return false;
    if (this->team == objectManager->GetLocalPlayer().team) return false;
    if (!this->isAlive) return false;
    return true;
}

bool Hero::IsValidEntity() {
    if (!this->visible) return false;
    if (!this->isAlive) return false;
    return true;
}

bool Hero::IsLocalPlayer() {
    return (this->address == objectManager->GetLocalPlayer().address);
}

int Hero::ReadAiManager() {
    int v1 = memoryManager->Read<__int8>(this->address + Offsets::AIManager);
    int v2 = this->address + Offsets::AIManager - 8;
    int v3 = memoryManager->Read<int>(v2 + 4);
    int v4 = memoryManager->Read<int>((v2 + (4 * v1 + 12)));
    v4 = v4 ^ (~v3);
    return memoryManager->Read<int>(v4 + 8);
}

BuffManager& Hero::GetBuffManager() {
    this->buffManager.Update(this->buffManagerAddress, this->buffManagerStart, this->buffManagerEnd);
    return this->buffManager;
}