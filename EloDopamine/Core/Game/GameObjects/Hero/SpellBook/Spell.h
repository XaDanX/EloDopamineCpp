#pragma once
#include "Windows.h"
#include <string>
#include "../../../Managers/MemoryManager/MemoryManager.h"
#include "../../../Offsets.h"
#include "../../../Engine/Engine.h"

class Spell {
public:
	Spell(){}

private:
	static const SIZE_T spellSlotSize = 0x150;
	BYTE buff[spellSlotSize];

public:
	int address{0};

	std::string name{};
	int level = 0;
	float readyAt = 0;

	void Update();
	bool IsReady();
	int Cooldown();

};

