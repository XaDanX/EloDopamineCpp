#include "Hero.h"
#include <string>
bool Hero::Load(unsigned int address, bool deepLoad) {
    this->address = address;
    memoryManager->ReadBuffer(address, this->buff, Hero::objectSize);

    memcpy(&index, &buff[Offsets::ObjectIndex], sizeof(byte));
    memcpy(&team, &buff[Offsets::ObjectTeam], sizeof(int));
    memcpy(&health, &buff[Offsets::ObjectHealth], sizeof(float));
    memcpy(&maxHealth, &buff[Offsets::ObjectMaxHealth], sizeof(float));
    memcpy(&attackRange, &buff[Offsets::ObjectAttackRange], sizeof(float));
    memcpy(&targetable, &buff[Offsets::ObjectTargetable], sizeof(bool));

    if (championName.empty()) {
        championName = memoryManager->ReadString(this->address + Offsets::ObjectName);
    }
    return true;
}