#include "Avareness.h"
#include "ObjectManager.h"
#include "Engine.h"
#include "Renderer.h"

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
	ImGui::Checkbox("Enabled", &AvarenessOptions::enabled);
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Ranges")) {
		ImGui::Checkbox("Enabled", &AvarenessOptions::drawRanges);
		ImGui::Separator();

		ImGui::Checkbox("Ally Ranges", &AvarenessOptions::drawAllyRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4("#AllyRangesColor", &AvarenessOptions::allyRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox("Enemy Ranges", &AvarenessOptions::drawEnemyRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4("#EnemyRangesColor", &AvarenessOptions::enemyRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox("Player Ranges", &AvarenessOptions::drawPlayerRanges);
		ImGui::SameLine();
		ImGui::ColorEdit4("#PlayerRangesColor", &AvarenessOptions::playerRangesColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	}

	if (ImGui::CollapsingHeader("Paths")) {

		ImGui::Checkbox("Enabled", &AvarenessOptions::drawPaths);
		ImGui::Separator();

		ImGui::Checkbox("Ally Paths", &AvarenessOptions::drawAllyPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4("#AllyPathsColor", &AvarenessOptions::allyPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox("Enemy Paths", &AvarenessOptions::drawEnemyPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4("#EnemyPathsColor", &AvarenessOptions::enemyPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

		ImGui::Checkbox("Player Paths", &AvarenessOptions::drawPlayerPaths);
		ImGui::SameLine();
		ImGui::ColorEdit4("#PlayerPathsColor", &AvarenessOptions::playerPathsColor.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	}

}

std::string Avareness::ModuleType()
{
	return "utility";
}

std::string Avareness::GetName()
{
	return "Avareness";
}

void Avareness::OnInitialize() {
}

void Avareness::OnExit() {
}
