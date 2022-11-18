#pragma once
#include "../../Core/Game/Managers/ModuleManager/Module.h"
class SpellTracker : public ModuleBase {
public:
	void OnUpdate() override;
	void OnGui() override;
	std::string ModuleType() override;
	std::string GetName() override;
	void OnInitialize() override;
	void OnExit() override;
};

