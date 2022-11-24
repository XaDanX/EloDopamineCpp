#pragma once

#include <numbers>
#include "../../../Core/Game/Engine/Engine.h"
#include "../../../Core/Game/GameData/Missile.h"
#include "../../../imgui/imgui.h"
#include "../../../Core/Game/Renderer/Renderer.h"

namespace EvadeDrawings {
    void DrawLinearSpell(Missile& missile) {

        auto direction = missile.endPos.sub(missile.startPos).normalize();

        auto deltaTime = (engine->GameTime() - missile.startTime);
        if (deltaTime - missile.spellInfo->delay < 0.0) { return; }
        auto centerPos = missile.startPos.add(
                direction.mult(missile.spellInfo->speed * (deltaTime - missile.spellInfo->castTime)));

        auto width = missile.spellInfo->width;
        auto height = missile.spellInfo->height;

        auto startCenter = centerPos.sub(direction.mult(height / 2).rotate_y(std::numbers::pi));
        auto length = startCenter.distance(missile.endPos);


        auto startLower = startCenter.add(direction.mult(width).rotate_y(std::numbers::pi / 2));
        auto startUpper = startCenter.add(direction.mult(width).rotate_y(std::numbers::pi * 3 / 2));
        auto endLower = startLower.add(direction.mult(length));
        auto endUpper = startUpper.add(direction.mult(length));


        auto a1 = engine->WorldToScreen(startLower);
        auto a2 = engine->WorldToScreen(startUpper);
        auto a3 = engine->WorldToScreen(endLower);
        auto a4 = engine->WorldToScreen(endUpper);
        static ImVec2 points[5];
        points[0] = ImVec2(a1.x, a1.y);
        points[1] = ImVec2(a2.x, a2.y);
        points[3] = ImVec2(a3.x, a3.y);
        points[2] = ImVec2(a4.x, a4.y);
        points[4] = ImVec2(a1.x, a1.y);
        renderer->GetDrawList()->AddConvexPolyFilled(points, 5, ImColor(200, 255, 200, 20));
        renderer->GetDrawList()->AddPolyline(points, 5, ImColor(204, 0, 204, 255), 0, 3);

        /*
        renderer->GetDrawList()->AddLine(ImVec2(a1.x, a1.y), ImVec2(a2.x, a2.y),
                                         ImColor(204, 0, 204, 255), 2);
        renderer->GetDrawList()->AddLine(ImVec2(a1.x, a1.y), ImVec2(a3.x, a3.y),
                                         ImColor(204, 0, 204, 255), 2);
        renderer->GetDrawList()->AddLine(ImVec2(a4.x, a4.y), ImVec2(a3.x, a3.y),
                                         ImColor(204, 0, 204, 255), 2);
        renderer->GetDrawList()->AddLine(ImVec2(a2.x, a2.y), ImVec2(a4.x, a4.y),
                                         ImColor(204, 0, 204, 255), 2);*/

        renderer->DrawCircleAt(centerPos, missile.spellInfo->width, false, 70, ImColor(204, 0, 204, 255), 3);

    }
    void DrawCircularSpell(Missile& missile) {

    }
}