#include "Spell.h"

void Spell::Update() {
	memoryManager->ReadBuffer(this->address, this->buff, this->spellSlotSize);
	int test = 0;
	memcpy(&test, &buff[Offsets::SpellSlotSpellInfo], sizeof(int));
	char nameBuff[16];
	memoryManager->ReadBuffer(test + 0x18, nameBuff, 16);

	auto test1 = memoryManager->ReadString(test + 0x18);
}
