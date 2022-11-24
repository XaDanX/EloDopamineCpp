//
// Created by XaDanX on 11/18/2022.
//

#include "ActiveSpell.h"
#include "../../../Offsets.h"
#include "../../../GameData/GameData.h"

void ActiveSpell::Load(int address) {
    memoryManager->ReadBuffer(address, this->buff, ActiveSpell::activeSpellSize);
    memcpy(&startPos, &buff[Offsets::ActiveSpellStartPos], sizeof(Vector3));
    memcpy(&endPos, &buff[Offsets::ActiveSpellEndPos], sizeof(Vector3));
    memcpy(&startTime, &buff[Offsets::ActiveSpellCastTime], sizeof(float));
    memcpy(&endTime, &buff[Offsets::ActiveSpellEndTime], sizeof(float));

    int info = 0;
    memcpy(&info, &buff[0x8], sizeof(int));
    name = memoryManager->ReadString(info + Offsets::ActiveSpellName);
    this->spellInfo = gameData->GetSpellInfoByName(name);

    if (this->spellInfo->projectDestination) {
        startPos.y += spellInfo->height;

        endPos = Vector3(endPos.x - startPos.x, 0, endPos.z - startPos.z);
        endPos = endPos.normalize();
        endPos.x = endPos.x * spellInfo->castRange + startPos.x;
        endPos.y = startPos.y;
        endPos.z = endPos.z * spellInfo->castRange + startPos.z;
    }

}

Missile ActiveSpell::GetMissile() {
    auto missile = Missile();
    missile.endPos = this->endPos;
    missile.startPos = this->startPos;
    missile.endTime = this->endTime + 10;
    missile.startTime = this->startTime;
    missile.name = this->name;
    missile.spellInfo = this->spellInfo;
    return missile;
}