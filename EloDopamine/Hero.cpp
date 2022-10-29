#include "Hero.h"
#include <string>
bool Hero::Load(unsigned int address, bool deepLoad) {
    memoryManager->ReadBuffer(address, this->buff, Hero::objectSize);

    memcpy(&index, &buff[Offsets::ObjectIndex], sizeof(byte));
    memcpy(&team, &buff[Offsets::ObjectTeam], sizeof(int));
    memcpy(&health, &buff[Offsets::ObjectHealth], sizeof(float));
    memcpy(&maxHealth, &buff[Offsets::ObjectMaxHealth], sizeof(float));
    memcpy(&attackRange, &buff[Offsets::ObjectAttackRange], sizeof(float));
    memcpy(&targetable, &buff[Offsets::ObjectTargetable], sizeof(bool));

    if (championName.empty()) {
        int championNameAddress;
        memcpy(&championNameAddress, &buff[Offsets::ObjectName], sizeof(int));
        char nameBuff[50];
        championName = memoryManager->ReadString(championNameAddress);
    }


    return true;
}