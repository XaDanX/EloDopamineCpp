#pragma once
#include "Module.h"
class OrbWalker : public ModuleBase {
public:
	void OnUpdate();
	void OnGui();
	std::string ModuleType();
	std::string GetName();

	void OnInitialize();
	void OnExit();
};

