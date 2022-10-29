#include "EloDopamine.h"


void EloDopamine::OnUpdate() {

    /*
        Execute modules here.
    */

}

void EloDopamine::OnGui() {

    /*
        Draw guis here.
    */
    ImGui::Begin("Test window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::Button("Button")) {}
    ImGui::Text("Hello :D");
    ImGui::End();

}



void EloDopamine::Update() {

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        this->isGuiOpen = !this->isGuiOpen;
        this->overlay.ToggleTransparent();
        this->overlay.Show();
    }

    objectManager->Update();

    this->overlay.StartFrame(); // start frame
    this->OnUpdate();

    if (this->isGuiOpen) {
        this->OnGui();
    }

    this->overlay.RenderFrame(); // end frame


}

void EloDopamine::Initialize() {
    bool memoryCreateResult{false};
    while (memoryCreateResult == false) {
        memoryCreateResult = memoryManager->Initialize();
        Sleep(1000);
    }

    // TODO:: ADD CHECKS FOR GAME TIME!



    SetActiveWindow(memoryManager->GetWindowHandle());
	this->overlay = Overlay();
	this->overlay.Init();
    this->overlay.ToggleTransparent();
    
    this->Update(); // initial update
}
