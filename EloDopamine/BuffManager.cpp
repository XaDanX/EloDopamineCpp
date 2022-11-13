#include "BuffManager.h"

void BuffManager::Update(int buffManager, int startAddress, int endAddress) {


	this->buffList.clear();
	
	int currentAddress = startAddress;
	if (startAddress != 0 && endAddress != 0) {
		for (int i = 0; i < (endAddress - startAddress); i += 0x08) {
			int buffAddress = memoryManager->Read<int>(startAddress + i);

			if (buffAddress < 0x1000)
				continue;

			Buff buffObj = Buff();
			if (buffObj.Update(buffAddress))
				this->buffList.push_back(buffObj);
		}
	}

	/*
	while (currentAddress != endAddress) {
		int buffAddr = memoryManager->Read<int>(currentAddress);
		if (buffAddr) {
			int buffEntry = memoryManager->Read<int>(buffAddr + 0x8);
			if (buffEntry) {
				Buff buffObj = Buff();
				buffObj.Update(buffEntry);
				this->buffList.push_back(buffObj);
			}
		}
		currentAddress += 0x8;

	}*/


}
