#pragma once
#include "Module.h"
#include "ModuleManager.h"
class ObjectView : public ModuleBase {
public:
	void OnUpdate();
	void OnGui();
	std::string ModuleType();
	std::string GetName();
	void OnInitialize();
	void OnExit();
};

