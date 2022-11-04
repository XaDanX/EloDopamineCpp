#include "Spell.h"

void Spell::Update() {
	memoryManager->ReadBuffer(this->address, this->buff, this->spellSlotSize);

	memcpy(&this->level, &buff[Offsets::SpellSlotLevel], sizeof(int));
	memcpy(&this->readyAt, &buff[Offsets::SpellSlotTime], sizeof(float));



	if (name.empty()) {
		int nameAddress = 0;
		memcpy(&nameAddress, &buff[Offsets::SpellSlotSpellInfo], sizeof(int));
		this->name = memoryManager->ReadString(nameAddress + 0x18);
	}
}

bool Spell::IsReady() {
	return (engine->GameTime() - this->readyAt) > 0;
}