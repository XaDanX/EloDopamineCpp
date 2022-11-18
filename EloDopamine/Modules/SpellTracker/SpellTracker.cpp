#include "SpellTracker.h"
#include "../../Core/Game/Managers/ObjectManager/ObjectManager.h"
#include "../../Core/Game/Renderer/Renderer.h"
#include "../../Core/Security/XorStr.hpp"

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
		auto d = hero.D_SPELL;
		auto f = hero.F_SPELL;


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
		healthBarPos.x += 37;
		healthBarPos.y -= 21;
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x, healthBarPos.y), ImVec2(healthBarPos.x + 26, healthBarPos.y + 18), ImColor(59, 59, 59, 255), 2.2);
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), d.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9);
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 30, healthBarPos.y), ImColor(255, 255, 255, 255), std::to_string(d.Cooldown()).c_str());
		healthBarPos.y += 8;
		renderer->GetDrawList()->AddRectFilled(ImVec2(healthBarPos.x + 2, healthBarPos.y + 2), ImVec2(healthBarPos.x + 23, healthBarPos.y + 8), f.IsReady() ? SpellTrackerOptions::readyColor : SpellTrackerOptions::coolDownColor, 2.9);
		renderer->GetDrawList()->AddText(ImVec2(healthBarPos.x + 30, healthBarPos.y), ImColor(255, 255, 255, 255), std::to_string(f.Cooldown()).c_str());






	}
	ImGui::PopFont();
}

void SpellTracker::OnGui() {
	ImGui::Checkbox(XorStr("Enabled").c_str(), &SpellTrackerOptions::enabled);
	ImGui::Separator();
}

std::string SpellTracker::ModuleType()
{
	return XorStr("utility");
}

std::string SpellTracker::GetName()
{
	return XorStr("SpellTracker");
}

void SpellTracker::OnInitialize()
{
}

void SpellTracker::OnExit()
{
}
