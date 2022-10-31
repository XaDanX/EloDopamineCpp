#include "ObjectView.h"
#include "imgui/imgui.h"
#include "ObjectManager.h"

void ObjectView::OnUpdate() {
}

void ObjectView::OnGui() {
	ImGui::Begin("Object view");

	for (Hero hero : objectManager->GetHeroList()) {
		if (ImGui::CollapsingHeader(hero.championName.c_str())) {
			ImGui::Text("Visible: %s", hero.visible ? "true" : "false");
			ImGui::Text("Health: %f/%f", hero.health, hero.maxHealth);
			ImGui::Separator();
			ImGui::Text("Spells");
			ImGui::Separator();
			if (ImGui::CollapsingHeader(hero.Q_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.Q_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.Q_SPELL.readyAt);
			}
			if (ImGui::CollapsingHeader(hero.W_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.W_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.W_SPELL.readyAt);
			}
			if (ImGui::CollapsingHeader(hero.E_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.E_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.E_SPELL.readyAt);
			}
			if (ImGui::CollapsingHeader(hero.R_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.R_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.R_SPELL.readyAt);
			}
			if (ImGui::CollapsingHeader(hero.D_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.D_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.D_SPELL.readyAt);
			}
			if (ImGui::CollapsingHeader(hero.F_SPELL.name.c_str())) {
				ImGui::Text("Level: %i", hero.F_SPELL.level);
				ImGui::Text("ReadyAt: %f", hero.F_SPELL.readyAt);
			}
			ImGui::Separator();

		}
		ImGui::Separator();
	}

	ImGui::End();
}
