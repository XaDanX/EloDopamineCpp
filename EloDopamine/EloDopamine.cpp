#include "EloDopamine.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include <chrono>

void EloDopamine::OnUpdate() {

    /*
        Execute modules here.
    */

    renderer->DrawCircleAt(objectManager->GetLocalPlayer()->position, 600 + 65, false, 190, ImColor(255, 0, 0, 120), 5);

    ImDrawList* e = ImGui::GetBackgroundDrawList();

    Vector2 pWorld = engine->WorldToScreen(objectManager->GetLocalPlayer()->position);

    e->AddLine(ImVec2(0, 0), ImVec2(pWorld.x, pWorld.y), ImColor(0, 255, 0, 100), 2);
    e->AddLine(ImVec2(1920, 0), ImVec2(pWorld.x, pWorld.y), ImColor(0, 255, 0, 100), 2);
    e->AddLine(ImVec2(0, 1080), ImVec2(pWorld.x, pWorld.y), ImColor(0, 255, 0, 100), 2);
    e->AddLine(ImVec2(1920, 1080), ImVec2(pWorld.x, pWorld.y), ImColor(0, 255, 0, 100), 2);


}

void EloDopamine::OnGui() {

    /*
        Draw guis here.
    */
    ImGui::Begin("Test window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Hello :D");
    ImGui::End();


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
    
    this->Update(); // initial update
}
