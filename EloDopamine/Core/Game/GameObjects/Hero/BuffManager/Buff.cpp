#include "Buff.h"

bool Buff::Update(int address) {
	if (this->address == 0)
		this->address = address;

	this->name = memoryManager->ReadStringSized(memoryManager->Read<int>(this->address + 0x8) + 0x4, 30);
	if (this->name.size() < 3)
		return false;;

	memoryManager->ReadBuffer(this->address, this->buff, Buff::buffSize);

	memcpy(&hash, &buff[Offsets::BuffEntryBuff], sizeof(int));
	memcpy(&type, &buff[Offsets::BuffType], sizeof(BYTE));
	memcpy(&startTime, &buff[Offsets::BuffEntryBuffStartTime], sizeof(float));
	memcpy(&endTime, &buff[Offsets::BuffEntryBuffEndTime], sizeof(float));
	memcpy(&count, &buff[Offsets::BuffEntryBuffCount], sizeof(int));
	return true;
}
