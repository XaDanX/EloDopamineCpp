#include "OrbWalker.h"
#include "../../Core/Game/Engine/Engine.h"
#include "../../Core/Game/InputController/InputController.h"
#include "../../Core/Game/Managers/ObjectManager/ObjectManager.h"
#include "../../imgui/imgui.h"
#include "../../Core/Game/Renderer/Renderer.h"
#include "../../Core/Security/XorStr.hpp"

namespace OrbWalkerOptions {
	bool enabled = false;
	float ping = 50.0;
	int hotKey = 0x4E;
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
		return lastAutoAttackTick + GetAttackDelay() + OrbWalkerOptions::ping / 2 < GetTickCount();
	}

	bool CanMove() {
		return lastMoveTick < GetTickCount();
	}

	Hero GetBestTarget() {
		float oldDistance = FLT_MAX;
		Hero bestTarget = objectManager->GetLocalPlayer();
		for (auto& unit : objectManager->GetHeroList())
		{
			if (!unit.IsValidTarget()) continue;

			if (!unit.targetable) continue;

			if (!renderer->IsWorldPointOnScreen(unit.position, 0, 0)) continue;

			if (unit.DistanceToHero(objectManager->GetLocalPlayer()) - unit.GetUnitInfo()->gameplayRadius > (objectManager->GetLocalPlayer().attackRange + objectManager->GetLocalPlayer().GetUnitInfo()->gameplayRadius)) continue;

			auto distance = objectManager->GetLocalPlayer().DistanceToHero(unit);

			if (distance < oldDistance) {
				oldDistance = distance;
				bestTarget = unit;
			}
		}
		return bestTarget;
	}
}


void OrbWalker::OnUpdate() {

	if (!OrbWalkerOptions::enabled) return;
	ImDrawList* canvas = ImGui::GetBackgroundDrawList();

	auto target = OrbWalkerUtils::GetBestTarget();

	auto player_w = engine->WorldToScreen(objectManager->GetLocalPlayer().position);
	auto target_w = engine->WorldToScreen(target.position);

#if DEBUG
	canvas->AddLine(ImVec2(player_w.x, player_w.y), ImVec2(target_w.x, target_w.y), ImColor(255, 255, 255, 150), 2);
#endif
	if (GetAsyncKeyState(OrbWalkerOptions::hotKey) & 0x8000) {
		if (!target.IsLocalPlayer() && target.IsValidTarget()) {
			if (OrbWalkerUtils::CanAttack()) {
				inputController->IssueClickAt(target_w.x, target_w.y);
				OrbWalkerUtils::lastAutoAttackTick = GetTickCount();
				OrbWalkerUtils::lastMoveTick = GetTickCount() + OrbWalkerUtils::GetWindupTime();
				return;
			}
		}
		if (OrbWalkerUtils::CanMove()) {
			inputController->IssueClick();
			OrbWalkerUtils::lastMoveTick = GetTickCount() + 80;
			return;
		}


	}

}

void OrbWalker::OnGui() {
	ImGui::Checkbox(XorStr("Enabled").c_str(), &OrbWalkerOptions::enabled);
	ImGui::Separator();
	ImGui::SliderFloat(XorStr("Ping").c_str(), &OrbWalkerOptions::ping, 5, 200);
	ImGui::PushFont(Fonts::font19);
	ImGui::TextColored(ImColor(252, 218, 0, 255), XorStr("OrbWalker key").c_str());
	ImGui::PopFont();
	ImGui::SameLine();
	renderer->CustomGuiHotkey(&OrbWalkerOptions::hotKey);
}

std::string OrbWalker::ModuleType() {
	return XorStr("utility");
}

std::string OrbWalker::GetName() {
	return XorStr("SpaceWalker++");
}

void OrbWalker::OnInitialize()
{
}

void OrbWalker::OnExit()
{
}