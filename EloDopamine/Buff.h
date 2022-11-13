#pragma once
#include <string>
#include <iostream>
#include "MemoryManager.h"
#include "Offsets.h"
class Buff {
protected:
protected:
	static const SIZE_T buffSize = 0x100;
	BYTE buff[buffSize];
public:
	int address = 0;

	int hash;
	BYTE type;
	float startTime;
	float endTime;
	int count;
	std::string name;

	bool Update(int address);
};

