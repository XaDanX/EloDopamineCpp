#pragma once
#include "../Game/Renderer/Overlay/Overlay.h"
#include "../Game/Managers/ObjectManager/ObjectManager.h"
#include "../Game/Engine/Engine.h"
#include "../Game/InputController/InputController.h"
#include "../Security/XorStr.hpp"

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

};
inline extern std::unique_ptr<EloDopamine> eloDopamine = std::make_unique<EloDopamine>();