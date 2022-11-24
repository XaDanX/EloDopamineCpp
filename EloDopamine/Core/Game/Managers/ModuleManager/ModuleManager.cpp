#include "ModuleManager.h"
#include "../../../../imgui/imgui.h"
#include "../../../Security/XorStr.hpp"
#include "../../../../Modules/Evade/Evade.h"

void ModuleManager::RegisterModule(ModuleBase* module) {

	if (module->ModuleType() != XorStr("utility").c_str()) {
		if (objectManager->GetLocalPlayer().championName == module->ModuleType()) {
			this->moduleList.emplace_back(module);
			logger->Info(XorStr("Script loaded: %s | For champion: %s").c_str(), module->GetName().c_str(), module->ModuleType().c_str());
		}
		else {
			delete module; 
		}
	}
	else {
		this->moduleList.emplace_back(module);
		logger->Info(XorStr("Utility script loaded: %s").c_str(), module->GetName().c_str(), module->ModuleType().c_str());
	}
}

void ModuleManager::RegisterModules() {
	/*
		Append all modules here
	*/
	this->RegisterModule(new SpellTracker());
	this->RegisterModule(new OrbWalker());
	this->RegisterModule(new Avareness());
    this->RegisterModule(new Evade());
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
