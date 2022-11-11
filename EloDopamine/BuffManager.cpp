#include "BuffManager.h"

void BuffManager::Update(int buffManager, int startAddress, int endAddress) {


	this->buffList.clear();
	
	int currentAddress = startAddress;

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

	}


}
