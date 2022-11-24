#include "EloDopamine.h"
#include "../Game/Renderer/Renderer.h"
#include "../Game/Managers/ModuleManager/ModuleManager.h"
#include <thread>
#include "numbers"
#include "../Game/Managers/TextureManager/TextureManager.h"

void EloDopamine::OnUpdate() {
    moduleManager->UpdateModules();
    renderer->DrawCircleAt(engine->MouseWorldPos(), 30, true, 100,
                           engine->IsNotWall(engine->MouseWorldPos()) ? ImColor(0, 255, 0, 150) : ImColor(255, 0, 0,
                                                                                                          150), 1);
    /*
    for (Hero& hero : objectManager->GetHeroList()) {
        auto active = hero.GetActiveSpell();
        if (active.has_value()) {
            if (active->startTime + active->spellInfo->castTime < engine->GameTime()) {
                if (engine->GameTime() > active->endTime - active->spellInfo->castTime) continue;

                auto direction = active->endPos.sub(active->startPos).normalize();

                auto deltaTime = (engine->GameTime() - active->startTime);
                if (deltaTime - active->spellInfo->delay < 0.0) {continue;}
                auto centerPos = active->startPos.add(direction.mult(active->spellInfo->speed * (deltaTime - active->spellInfo->castTime)));

                auto width = active->spellInfo->width;
                auto height = active->spellInfo->height;

                auto startCenter = centerPos.sub(direction.mult(height / 2).rotate_y(std::numbers::pi));
                auto length = startCenter.distance(active->endPos);


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
                renderer->GetDrawList()->AddConvexPolyFilled(points, 5, ImColor(2555, 255, 255, 190));


                renderer->GetDrawList()->AddLine(ImVec2(a1.x, a1.y), ImVec2(a2.x, a2.y),
                                                 ImColor(0, 0, 255, 150), 3);
                renderer->GetDrawList()->AddLine(ImVec2(a1.x, a1.y), ImVec2(a3.x, a3.y),
                                                 ImColor(0, 0, 255, 150), 3);
                renderer->GetDrawList()->AddLine(ImVec2(a4.x, a4.y), ImVec2(a3.x, a3.y),
                                                 ImColor(0, 0, 255, 150), 3);
                renderer->GetDrawList()->AddLine(ImVec2(a2.x, a2.y), ImVec2(a4.x, a4.y),
                                                 ImColor(0, 0, 255, 150), 3);
            } else {
                auto startPoint = engine->WorldToScreen(active->startPos);
                renderer->GetDrawList()->AddText(ImVec2(startPoint.x, startPoint.y), ImColor(255, 0, 0, 255), "Not yet casted");
            }

        }

    }*/

}

void EloDopamine::OnGui() {
    moduleManager->UpdateModulesGui();
}



void EloDopamine::Update() {

    auto timeBegin = std::chrono::high_resolution_clock::now();
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        this->isGuiOpen = !this->isGuiOpen;
        this->overlay->ToggleTransparent();
        this->overlay->Show();
    }

    objectManager->Update();

    this->overlay->StartFrame();
    this->OnUpdate();

    if (this->isGuiOpen) {
        ImGui::SetNextWindowPos(ImVec2(134, 56));
        ImGui::SetNextWindowSize(ImVec2(570, 774));
        ImGui::Begin(XorStr("EloDopamine | DEV").c_str());
        this->OnGui();
        ImGui::End();
    }

    std::chrono::duration<float, std::milli> dur = std::chrono::high_resolution_clock::now() - timeBegin;

    ImGui::SetNextWindowSize({ 231.f ,109.f});
    ImGui::SetNextWindowPos(ImVec2(1382, 893));
    ImGui::SetNextWindowBgAlpha(0.5);
    ImGui::Begin(XorStr("Permashow").c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text(XorStr("Update: %f ms").c_str(), (float)dur.count());
    ImGui::Separator();
    ImGui::End();

    this->overlay->RenderFrame();

}

void EloDopamine::Initialize() {
    bool memoryCreateResult{false};
    while (memoryCreateResult == false) {
        memoryCreateResult = memoryManager->Initialize();
        Sleep(1000);
    }
    engine->Update();
    while (engine->GameTime() < 2.0) {
        engine->Update();
        Sleep(1000);
    }


    SetActiveWindow(memoryManager->GetWindowHandle());
    this->overlay = new Overlay();
    this->overlay->Init();
    this->overlay->ToggleTransparent();

    gameData->Load(deployablePath);




    logger->Info(XorStr("Initializing modules..").c_str());
    engine->Update();
    objectManager->Update();

    /*
    logger->Info("Loading resources..");
    std::string path = "C:\\Deployable\\icons_spells";
    for (const auto& entry : fs::directory_iterator(path)) {
        textureManager->LoadTexture(entry.path().stem().string(), entry.path().string().c_str());
    }*/

    std::thread engineUpdateThread = engine->spawn();
    std::thread inputUpdateThread = inputController->spawn();
    engineUpdateThread.detach();
    inputUpdateThread.detach();

    moduleManager->Initialize();

    logger->Info(XorStr("Initialization done!").c_str());

}

void EloDopamine::OnExit(int i) {
    moduleManager->OnExit();
}
