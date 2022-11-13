#pragma once
#include "Overlay.h"
#include "ObjectManager.h"
#include "Engine.h"
#include "InputController.h"
#include "XorStr.hpp"

namespace {
	std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

class EloDopamine {
private:
	Overlay* overlay;
	bool isGuiOpen = false;
public:
	void Initialize();
	static void OnExit(int i);

	void Update();
	void OnUpdate();
	void OnGui();

	void RegisterModules();

};
inline extern std::unique_ptr<EloDopamine> eloDopamine = std::make_unique<EloDopamine>();