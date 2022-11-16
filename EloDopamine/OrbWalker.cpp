#include "OrbWalker.h"
#include "Engine.h"
#include "InputController.h"
#include "ObjectManager.h"
#include "imgui/imgui.h"
#include "Renderer.h"

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
		return lastAutoAttackTick + GetAttackDelay() + OrbWalkerOptions::ping / 2 < GetTickCount64();
	}

	bool CanMove() {
		return lastMoveTick < GetTickCount64();
	}

	Hero& GetBestTarget() {
		float oldDistance = FLT_MAX;
		Hero bestTarget = objectManager->GetLocalPlayer();
		for (auto& unit : objectManager->GetHeroList())
		{
			if (!unit.IsValidTarget()) continue;

			if (!unit.targetable) continue;

			if (unit.DistanceToHero(objectManager->GetLocalPlayer()) /*- unit.GetUnitInfo()->gameplayRadius*/  > (objectManager->GetLocalPlayer().attackRange + objectManager->GetLocalPlayer().GetUnitInfo()->gameplayRadius)) continue;

			//auto distance = objectManager->GetLocalPlayer().DistanceToHero(unit);

			/*if (distance < oldDistance) {
				oldDistance = distance;
				bestTarget = unit;
			}*/
			if (oldDistance >= unit.health) {
				oldDistance = unit.health;
				bestTarget = unit;
			}
		}
		return bestTarget;
	}
}


void OrbWalker::OnUpdate() {

	if (!OrbWalkerOptions::enabled) return;
	ImDrawList* canvas = ImGui::GetBackgroundDrawList();
	if (GetAsyncKeyState(OrbWalkerOptions::hotKey) & 0x8000) {
		auto player_w = engine->WorldToScreen(objectManager->GetLocalPlayer().position);
		auto target = OrbWalkerUtils::GetBestTarget();
		auto target_w = engine->WorldToScreen(target.position);
		canvas->AddLine(ImVec2(player_w.x, player_w.y), ImVec2(target_w.x, target_w.y), ImColor(255, 255, 255, 150), 2);
		if (!target.IsLocalPlayer() && target.IsValidTarget()) {
			if (OrbWalkerUtils::CanAttack()) {
				inputController->IssueClickAt(target_w.x, target_w.y);
				OrbWalkerUtils::lastAutoAttackTick = GetTickCount64();
				OrbWalkerUtils::lastMoveTick = GetTickCount64() + OrbWalkerUtils::GetWindupTime();
				return;
			}
		}
		if (OrbWalkerUtils::CanMove()) {
			inputController->IssueClick();
			OrbWalkerUtils::lastMoveTick = GetTickCount64() + 60;
			return;
		}
	}
}

void OrbWalker::OnGui() {
	ImGui::Checkbox("Enabled", &OrbWalkerOptions::enabled);
	ImGui::Separator();
	ImGui::SliderFloat("Ping", &OrbWalkerOptions::ping, 5, 200);
	ImGui::PushFont(Fonts::font19);
	ImGui::TextColored(ImColor(252, 218, 0, 255), "OrbWalker key");
	ImGui::PopFont();
	ImGui::SameLine();
	renderer->CustomGuiHotkey(&OrbWalkerOptions::hotKey);
}

std::string OrbWalker::ModuleType() {
	return "utility";
}

std::string OrbWalker::GetName() {
	return "SpaceWalker++";
}

void OrbWalker::OnInitialize()
{
}

void OrbWalker::OnExit()
{
}
