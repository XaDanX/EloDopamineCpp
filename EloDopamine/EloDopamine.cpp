#include "EloDopamine.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "ObjectView.h"
#include <chrono>
#include "ModuleManager.h"
#include "GameData.h"


void EloDopamine::OnUpdate() {
    moduleManager->UpdateModules();
}

void EloDopamine::OnGui() {
    moduleManager->UpdateModulesGui();
}



void EloDopamine::Update() {
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        this->isGuiOpen = !this->isGuiOpen;
        this->overlay->ToggleTransparent();
        this->overlay->Show();
    }

    engine->Update();
    objectManager->Update();

    this->overlay->StartFrame();
    this->OnUpdate();

    if (this->isGuiOpen) {
        this->OnGui();
    }

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

    logger->Info("Initializing modules..");

    this->Update(); // initial update

    moduleManager->Initialize();

    logger->Info("Initialization done!");

}
