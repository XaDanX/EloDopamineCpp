#include "Buff.h"

void Buff::Update(int address) {
	if (this->address == 0)
		this->address = address;
	memoryManager->ReadBuffer(this->address, this->buff, Buff::buffSize);

	memcpy(&hash, &buff[Offsets::BuffEntryBuff], sizeof(int));
	memcpy(&type, &buff[Offsets::BuffType], sizeof(BYTE));
	memcpy(&startTime, &buff[Offsets::BuffEntryBuffStartTime], sizeof(float));
	memcpy(&endTime, &buff[Offsets::BuffEntryBuffEndTime], sizeof(float));
	memcpy(&count, &buff[Offsets::BuffEntryBuffCount], sizeof(int));
	this->name = memoryManager->ReadStringSized(this->address + 0x4, 30);
}
