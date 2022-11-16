#include "ModuleManager.h"
#include "imgui/imgui.h"

void ModuleManager::RegisterModule(ModuleBase* module) {

	if (module->ModuleType() != "utility") {
		if (objectManager->GetLocalPlayer().championName == module->ModuleType()) {
			this->moduleList.emplace_back(module);
			logger->Info("Script loaded: %s | For champion: %s", module->GetName().c_str(), module->ModuleType().c_str());
		}
		else {
			delete module; 
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
	this->RegisterModule(new OrbWalker());
	this->RegisterModule(new SpellTracker());
	this->RegisterModule(new Avareness());
}

void ModuleManager::Initialize() {
	this->RegisterModules();
	for (auto& currentModule : this->moduleList) {
		currentModule->OnInitialize();
	}
}

void ModuleManager::UpdateModules() {
	for (auto &currentModule : this->moduleList) {
		currentModule->OnUpdate();
	}
}

void ModuleManager::UpdateModulesGui() {
	for (auto& currentModule : this->moduleList) {
		if (ImGui::CollapsingHeader(currentModule->GetName().c_str())) {
			currentModule->OnGui();
		}
	}
}

void ModuleManager::OnExit() {
	for (auto& currentModule : this->moduleList) {
		currentModule->OnExit();
	}
}
