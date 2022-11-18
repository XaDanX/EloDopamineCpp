#include "BuffManager.h"

void BuffManager::Update(int buffManager, int startAddress, int endAddress) {


	this->buffList.clear();

	if (startAddress != 0 && endAddress != 0) {
		for (int i = 0; i < (endAddress - startAddress); i += 0x08) {
			int buffAddress = memoryManager->Read<int>(startAddress + i);

			if (buffAddress < 0x1000)
				continue;

			Buff buffObj = Buff();
			if (buffObj.Update(buffAddress)) {
				this->buffList.push_back(buffObj);
			}
			
		}
	}
}
