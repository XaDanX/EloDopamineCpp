#pragma once
#include "Overlay.h"
#include "ObjectManager.h"

class EloDopamine {
private:
	Overlay overlay;
	bool isGuiOpen = false;
public:
	void Initialize();

	void Update();
	void OnUpdate();
	void OnGui();

};
inline extern std::unique_ptr<EloDopamine> eloDopamine = std::make_unique<EloDopamine>();