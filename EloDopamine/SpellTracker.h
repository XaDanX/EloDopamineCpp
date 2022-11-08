#pragma once
#include "Module.h"
class SpellTracker : public ModuleBase {
public:
	void OnUpdate();
	void OnGui();
	std::string ModuleType();
	std::string GetName();
};

