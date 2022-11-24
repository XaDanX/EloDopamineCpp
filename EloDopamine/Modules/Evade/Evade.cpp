#include <numbers>
#include "Evade.h"
#include "../../Core/Game/Engine/Engine.h"
#include "../../Core/Game/InputController/InputController.h"
#include "../../Core/Game/Managers/ObjectManager/ObjectManager.h"
#include "../../imgui/imgui.h"
#include "../../Core/Game/Renderer/Renderer.h"
#include "../../Core/Security/XorStr.hpp"
#include "Helpers/EvadeDrawings.h"

void Evade::OnUpdate() {
    this->spellService->Update();
    //logger->Debug("%i", this->spellService->missiles.size());

    for (auto& missile : this->spellService->missiles) {
        auto active = missile.second;

        if (active.spellInfo->width == 0 && active.spellInfo->height == 0) { // circular



        } else { // linear
            if (active.startTime + active.spellInfo->castTime < engine->GameTime()) {
                EvadeDrawings::DrawLinearSpell(active);
            } else {
                auto startPoint = engine->WorldToScreen(active.startPos);
                renderer->GetDrawList()->AddText(ImVec2(startPoint.x, startPoint.y), ImColor(255, 0, 0, 255), "Not yet casted");
            }
        }





    }


}

void Evade::OnGui() {

}

std::string Evade::ModuleType() {
    return "utility";
}

std::string Evade::GetName() {
    return "Evade";

}

void Evade::OnInitialize() {

}

void Evade::OnExit() {

}
