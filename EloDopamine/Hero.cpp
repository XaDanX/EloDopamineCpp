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

    if (championName.empty()) {
        championName = memoryManager->ReadString(this->address + Offsets::ObjName);
    }
    return true;
}