#pragma once
#include <vector>
#include "Module.h"
#include <iostream>
#include <iostream>
#include "../../../Utils/Logger.h"
#include "../ObjectManager/ObjectManager.h"
#include "../../../../Modules/OrbWalker/OrbWalker.h"
#include "../../../../Modules/SpellTracker/SpellTracker.h"
#include "../../../../Modules/Avareness/Avareness.h"


class ModuleManager {
private:
	std::vector<std::unique_ptr<ModuleBase>> moduleList;
	void RegisterModules();

public:
	void Initialize();
	void UpdateModules();
	void UpdateModulesGui();
	void OnExit();
	void RegisterModule(ModuleBase* module);
};
inline extern std::unique_ptr<ModuleManager> moduleManager = std::make_unique<ModuleManager>();

