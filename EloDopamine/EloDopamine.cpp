#include "EloDopamine.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "ObjectView.h"
#include <chrono>
#include "GameData.h"
namespace {
    ObjectView objectView = ObjectView();
}

void EloDopamine::OnUpdate() {

    /*
        Execute modules here.
    */
    Hero hero = objectManager->GetLocalPlayer();

    renderer->DrawCircleAt(hero.position, hero.GetUnitInfo()->gameplayRadius + hero.attackRange, false, 190, ImColor(255, 0, 0, 120), 5);

    ImDrawList* e = ImGui::GetBackgroundDrawList();
    auto healthBarPosition = hero.GetHealthBarPosition();

    e->AddText(ImVec2(healthBarPosition.x, healthBarPosition.y), ImColor(255, 0, 0, 255), hero.CanAttack() ? "true"  : "false");

}

void EloDopamine::OnGui() {

    /*
        Draw guis here.
    */
    objectView.OnGui();

}



void EloDopamine::Update() {
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        this->isGuiOpen = !this->isGuiOpen;
        this->overlay.ToggleTransparent();
        this->overlay.Show();
    }

    engine->Update();
    objectManager->Update();

    this->overlay.StartFrame();
    this->OnUpdate();

    if (this->isGuiOpen) {
        this->OnGui();
    }

    this->overlay.RenderFrame(); 

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
	this->overlay = Overlay();
	this->overlay.Init();
    this->overlay.ToggleTransparent();
    
    gameData->Load(deployablePath);

    logger->Info("Initialized!");

    this->Update(); // initial update
}
