#pragma once
#include <vector>
#include "Module.h"
#include <iostream>
#include <iostream>
#include "Logger.h"
#include "ObjectView.h"
#include "ObjectManager.h"
#include "OrbWalker.h"


class ModuleManager {
private:
	std::vector<std::unique_ptr<ModuleBase>> moduleList;
	void RegisterModules();

public:
	void Initialize();
	void UpdateModules();
	void UpdateModulesGui();
	void RegisterModule(ModuleBase* module);
};
inline extern std::unique_ptr<ModuleManager> moduleManager = std::make_unique<ModuleManager>();

