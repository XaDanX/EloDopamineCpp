#include "SpellTracker.h"
#include "ObjectManager.h"
#include "Engine.h"
#include "Renderer.h"

namespace SpellTrackerOptions {
	auto enabled = true;
	auto readyColor = ImColor(1, 110, 23, 255);
	auto coolDownColor = ImColor(110, 1, 1, 255);
}

void SpellTracker::OnUpdate() {
	if (!SpellTrackerOptions::enabled) return;
	ImGui::PushFont(Fonts::font11);
	for (auto hero : objectManager->GetHeroList()) {
		if (!hero.IsValidTarget()) continue;
		auto healthBarPos = hero.GetHealthBarPosition();
		healthBarPos.x += 24;
		healthBarPos.y -= 3.5;

		auto q = hero.Q_SPELL;
		auto w = hero.W_SPELL;
		auto e = hero.E_SPELL;
		auto r = hero.R_SPELL;


		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x, healthBarPos.y), ImVec2(healthBarPos.x + 97, healthBarPos.y + 10), ImColor(59, 59, 59, 255), 1.2);

		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), q.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9); //23 2 2 2
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 4, healthBarPos.y + 14), ImColor(255, 255, 255, 255), std::to_string(q.Cooldown()).c_str());
		healthBarPos.x += 24;
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), w.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9); //23 2 2 2 
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 4, healthBarPos.y + 14), ImColor(255, 255, 255, 255), std::to_string(w.Cooldown()).c_str());
		healthBarPos.x += 24;
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), e.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9); //23 2 2 2 
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 4, healthBarPos.y + 14), ImColor(255, 255, 255, 255), std::to_string(e.Cooldown()).c_str());
		healthBarPos.x += 24;
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), r.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9);
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 4, healthBarPos.y + 14), ImColor(255, 255, 255, 255), std::to_string(r.Cooldown()).c_str());


	}
	ImGui::PopFont();
}

void SpellTracker::OnGui() {
	ImGui::Checkbox("Enabled", &SpellTrackerOptions::enabled);
	ImGui::Separator();
}

std::string SpellTracker::ModuleType()
{
	return "utility";
}

std::string SpellTracker::GetName()
{
	return "SpellTracker";
}

void SpellTracker::OnInitialize()
{
}

void SpellTracker::OnExit()
{
}
