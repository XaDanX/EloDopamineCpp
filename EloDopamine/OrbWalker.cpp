#include "OrbWalker.h"
#include "Engine.h"
#include "InputController.h"
#include "ObjectManager.h"
#include "imgui/imgui.h"

namespace OrbWalkerOptions {
	bool enabled = false;
	float ping = 50.0;
}

namespace OrbWalkerUtils {

	float lastAutoAttackTick = 0;
	float lastMoveTick = 0;

	int GetAttackDelay() {
		return (int)(1000.0f / objectManager->GetLocalPlayer().GetTotalAttackSpeed());
	}
	float GetWindupTime() {
		return (1 / objectManager->GetLocalPlayer().GetTotalAttackSpeed() * 1000) * objectManager->GetLocalPlayer().unitInfo->basicAttackWindup;
	}

	bool CanAttack() {
		return lastAutoAttackTick + GetAttackDelay() + OrbWalkerOptions::ping / 2 < GetTickCount64();
	}

	bool CanMove() {
		return lastMoveTick < GetTickCount64();
	}

	Hero& GetTargetTest() {
		float old_distance = FLT_MAX;
		Vector3 localPlayerPos = objectManager->GetLocalPlayer().position;
		Hero target = objectManager->GetLocalPlayer();

		for (auto hero : objectManager->GetHeroList()) {
			if (hero.address == objectManager->GetLocalPlayer().address) continue;
			if (hero.visible == false) continue;
			if (hero.team == objectManager->GetLocalPlayer().team) continue;
			auto distance = objectManager->GetLocalPlayer().DistanceToHero(hero);
			if (distance < old_distance) {
				old_distance = distance;
				target = hero;
			}
		}
		return target;



	}
}


void OrbWalker::OnUpdate() {
	if (!OrbWalkerOptions::enabled) return;
	ImDrawList* canvas = ImGui::GetBackgroundDrawList();

	auto target = OrbWalkerUtils::GetTargetTest();

	auto player_w = engine->WorldToScreen(objectManager->GetLocalPlayer().position);
	auto target_w = engine->WorldToScreen(target.position);

	canvas->AddLine(ImVec2(player_w.x, player_w.y), ImVec2(target_w.x, target_w.y), ImColor(255, 255, 255, 150), 2);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (target.address != objectManager->GetLocalPlayer().address) {
			if (OrbWalkerUtils::CanAttack()) {
				inputController->IssueClickAt(target_w.x, target_w.y);
				OrbWalkerUtils::lastAutoAttackTick = GetTickCount64();
				OrbWalkerUtils::lastMoveTick = GetTickCount64() + OrbWalkerUtils::GetWindupTime();
			}
			if (OrbWalkerUtils::CanMove()) {
				inputController->IssueClick();
				OrbWalkerUtils::lastMoveTick = GetTickCount64() + 60;
			}
		}

	}
}

void OrbWalker::OnGui() {
	ImGui::Begin("Orbwalker++");
	ImGui::Checkbox("Enabled", &OrbWalkerOptions::enabled);
	ImGui::Separator();
	ImGui::SliderFloat("Ping", &OrbWalkerOptions::ping, 5, 200);
	ImGui::End();
}

std::string OrbWalker::ModuleType() {
	return "utility";
}

std::string OrbWalker::GetName() {
	return "OrbWalker++";
}
