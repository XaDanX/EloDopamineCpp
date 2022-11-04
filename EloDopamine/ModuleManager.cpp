#include "ModuleManager.h"


void ModuleManager::RegisterModule(ModuleBase* module) {

	if (module->ModuleType() != "utility") {
		if (objectManager->GetLocalPlayer().championName == module->ModuleType()) {
			this->moduleList.emplace_back(module);
			logger->Info("Script loaded: %s | For champion: %s", module->GetName().c_str(), module->ModuleType().c_str());
		}
		else {
			delete module; // delete from heap to avoid memory usage from unused modules
		}
	}
	else {
		this->moduleList.emplace_back(module);
		logger->Info("Utility script loaded: %s", module->GetName().c_str(), module->ModuleType().c_str());
	}
}

void ModuleManager::RegisterModules() {
	/*
		Append all modules here
	*/
	this->RegisterModule(new ObjectView());
}

void ModuleManager::Initialize() {
	this->RegisterModules();
}

void ModuleManager::UpdateModules() {
	for (auto &currentModule : this->moduleList) {
		currentModule->OnUpdate();
	}
}

void ModuleManager::UpdateModulesGui() {
	for (auto& currentModule : this->moduleList) {
		currentModule->OnGui();
	}
}
