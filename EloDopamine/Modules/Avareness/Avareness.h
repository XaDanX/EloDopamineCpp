#pragma once
#include "../../Core/Game/Managers/ModuleManager/Module.h"
class Avareness : public ModuleBase {
public:
	void OnUpdate();
	void OnGui();
	std::string ModuleType();
	std::string GetName();
	void OnInitialize();
	void OnExit();
};

