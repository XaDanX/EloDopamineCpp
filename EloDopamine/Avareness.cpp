#include "Avareness.h"
#include "ObjectManager.h"
#include "Engine.h"
#include "Renderer.h"
#include "XorStr.hpp"

namespace AvarenessOptions {
	auto enabled = true;
	auto drawRanges = true;
	auto drawAllyRanges = true;
	auto drawEnemyRanges = true;
	auto drawPlayerRanges = true;

	ImVec4 enemyRangesColor = ImGui::ColorConvertU32ToFloat4(ImColor(255, 0, 0, 255));
	ImVec4 allyRangesColor = ImGui::ColorConvertU32ToFloat4(ImColor(0, 255, 0, 255));
	ImVec4 playerRangesColor = ImGui::ColorConvertU32ToFloat4(ImColor(0, 255, 0, 255));


	auto drawPaths = true;
	auto drawAllyPaths = true;
	auto drawEnemyPaths = true;
	auto drawPlayerPaths = true;

	ImVec4 enemyPathsColor = ImGui::ColorConvertU32ToFloat4(ImColor(255, 0, 0, 255));
	ImVec4 allyPathsColor = ImGui::ColorConvertU32ToFloat4(ImColor(0, 255, 0, 255));
	ImVec4 playerPathsColor = ImGui::ColorConvertU32ToFloat4(ImColor(0, 255, 0, 255));

}

namespace AvarenessFunctions {
	void DrawRanges(Hero& hero) {
		if (hero.IsValidEntity() && !hero.IsLocalPlayer()) {
			float radius = hero.unitInfo->gameplayRadius + hero.attackRange;
			bool isAlly = (hero.team == objectManager->GetLocalPlayer().team);
			if (isAlly && AvarenessOptions::drawAllyRanges) {
				renderer->DrawCircleAt(hero.position, radius, false, 90, AvarenessOptions::allyRangesColor, 2);
				return;
			}
			if (!isAlly && AvarenessOptions::drawEnemyRanges) {
				renderer->DrawCircleAt(hero.position, radius, false, 90, AvarenessOptions::enemyRangesColor, 2);
				return;
			}
		}
		if (hero.IsLocalPlayer() && AvarenessOptions::drawPlayerRanges) {
			float radius = hero.unitInfo->gameplayRadius + hero.attackRange;
			renderer->DrawCircleAt(hero.position, radius, false, 90, ImGui::ColorConvertFloat4ToU32(AvarenessOptions::playerRangesColor), 2);
		}
	}
	
	void DrawSinglePath(Hero& hero, ImColor color) {
		Vector3 lastPoint = hero.aiManager.navigationArray.at(0);
		for (Vector3 point : hero.aiManager.navigationArray) {
			Vector2 lastPoint2d = engine->WorldToScreen(lastPoint);
			Vector2 currentPoint2d = engine->WorldToScreen(point);
			renderer->GetDrawList()->AddLine(ImVec2(lastPoint2d.x, lastPoint2d.y), ImVec2(currentPoint2d.x, currentPoint2d.y), color, 2);
			lastPoint = point;

		}
	}

	void DrawPaths(Hero& hero) {
		if (!(hero.aiManager.navigationArray.size() > 1)) return;
		if (hero.IsValidEntity() && !hero.IsLocalPlayer()) {
			bool isAlly = (hero.team == objectManager->GetLocalPlayer().team);
			if (isAlly && AvarenessOptions::drawAllyPaths) {
				AvarenessFunctions::DrawSinglePath(hero, ImGui::ColorConvertFloat4ToU32(AvarenessOptions::allyPathsColor));

				return;
			}
			if (!isAlly && AvarenessOptions::drawEnemyPaths) {
				AvarenessFunctions::DrawSinglePath(hero, ImGui::ColorConvertFloat4ToU32(AvarenessOptions::enemyPathsColor));
				return;
			}
		}
		if (hero.IsLocalPlayer() && AvarenessOptions::drawPlayerPaths) {
			AvarenessFunctions::DrawSinglePath(hero, ImGui::ColorConvertFloat4ToU32(AvarenessOptions::playerPathsColor));
		}

	}
	
}


void Avareness::OnUpdate() {
	if (!AvarenessOptions::enabled) return;


	for (Hero hero : objectManager->GetHeroList()) {
		if (AvarenessOptions::drawRanges) {
			AvarenessFunctions::DrawRanges(hero);
		}
		
		if (AvarenessOptions::drawPaths) {
			AvarenessFunctions::DrawPaths(hero);
		}



	}

}

void Avareness::OnGui() {
	ImGui::Checkbox(XorStr("Enabled").c_str(), &AvarenessOptions::enabled);
	ImGui::Separator();
	if (ImGui::CollapsingHeader(XorStr("Ranges").c_str())) {
		ImGui::Checkbox(XorStr("Enabled").c_str(), &AvarenessOptions::drawRanges);
		ImGui::Separator();

		ImGui::Checkbox(XorStr("Ally Ranges").c_str(), &AvarenessOptions::drawAllyRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#AllyRangesColor").c_str(), &AvarenessOptions::allyRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox(XorStr("Enemy Ranges").c_str(), &AvarenessOptions::drawEnemyRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#EnemyRangesColor").c_str(), &AvarenessOptions::enemyRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox(XorStr("Player Ranges").c_str(), &AvarenessOptions::drawPlayerRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#PlayerRangesColor").c_str(), &AvarenessOptions::playerRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	}

	if (ImGui::CollapsingHeader(XorStr("Paths").c_str())) {

		ImGui::Checkbox(XorStr("Enabled").c_str(), &AvarenessOptions::drawPaths);
		ImGui::Separator();

		ImGui::Checkbox(XorStr("Ally Paths").c_str(), &AvarenessOptions::drawAllyPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#AllyPathsColor").c_str(), &AvarenessOptions::allyPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox(XorStr("Enemy Paths").c_str(), &AvarenessOptions::drawEnemyPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#EnemyPathsColor").c_str(), &AvarenessOptions::enemyPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox(XorStr("Player Paths").c_str(), &AvarenessOptions::drawPlayerPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4(XorStr("#PlayerPathsColor").c_str(), &AvarenessOptions::playerPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	}

}

std::string Avareness::ModuleType()
{
	return XorStr("utility");
}

std::string Avareness::GetName()
{
	return XorStr("Avareness");
}

void Avareness::OnInitialize() {
}

void Avareness::OnExit() {
}
