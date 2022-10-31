#include "Hero.h"

bool Hero::Load(unsigned int address, bool deepLoad) {
    this->address = address;
    memoryManager->ReadBuffer(address, this->buff, Hero::objectSize);

    memcpy(&index, &buff[Offsets::ObjIndex], sizeof(byte));
    memcpy(&team, &buff[Offsets::ObjTeam], sizeof(int));
    memcpy(&health, &buff[Offsets::ObjHealth], sizeof(float));
    memcpy(&maxHealth, &buff[Offsets::ObjMaxHealth], sizeof(float));
    memcpy(&attackRange, &buff[Offsets::ObjATKRange], sizeof(float));
    memcpy(&targetable, &buff[Offsets::ObjTargetable], sizeof(bool));
    memcpy(&position, &buff[Offsets::ObjPos], sizeof(Vector3));
    memcpy(&visible, &buff[Offsets::ObjVisibility], sizeof(bool));
    memcpy(&spellBookPointers, &buff[Offsets::ObjSpellBOOK], sizeof(int) * 6);

    if (championName.empty()) {
        championName = memoryManager->ReadString(this->address + Offsets::ObjName);
    }


    this->Q_SPELL.address = this->spellBookPointers[0];
    this->W_SPELL.address = this->spellBookPointers[1];
    this->E_SPELL.address = this->spellBookPointers[2];
    this->R_SPELL.address = this->spellBookPointers[3];
    this->D_SPELL.address = this->spellBookPointers[4];
    this->F_SPELL.address = this->spellBookPointers[5];
    this->UpdateSpells();



    return true;
}

void Hero::UpdateSpells() {
    
    this->Q_SPELL.Update();
    this->W_SPELL.Update();
    this->E_SPELL.Update();
    this->R_SPELL.Update();
    this->D_SPELL.Update();
    this->F_SPELL.Update();
}

Vector2 Hero::GetHealthBarPosition() {
    Vector3 point = position.clone();
    point.x += 85.0; // health bar height, but i haven't implemented these yet (85 is for twitch xd)

    Vector2 out = engine->WorldToScreen(point);
    out.y -= (engine->WindowHeight() * 0.00083333335f * 85.0);
    out.x -= 70.0f;
}
