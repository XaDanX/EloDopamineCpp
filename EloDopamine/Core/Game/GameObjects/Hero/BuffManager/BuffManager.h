#pragma once
#include "Buff.h"
#include <vector>
#include "../../../Managers/MemoryManager/MemoryManager.h"
#include "../../../Offsets.h"
class BuffManager {
public:
	std::vector<Buff> buffList;

	void Update(int buffManager, int startAddress, int endAddress);
};

