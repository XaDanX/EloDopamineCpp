#include "EloDopamine.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "ObjectView.h"
#include <chrono>
#include "ModuleManager.h"
#include "GameData.h"
#include <thread>
#include <iostream>
#include "TextureManager.h"
#include <filesystem>
namespace fs = std::filesystem;

void EloDopamine::OnUpdate() {
    moduleManager->UpdateModules();
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
        ImGui::Begin("EloDopamine");
        this->OnGui();
        ImGui::End();
    }

    std::chrono::duration<float, std::milli> dur = std::chrono::high_resolution_clock::now() - timeBegin;

    ImGui::SetNextWindowSize({ 231.f ,109.f / 2});

    ImGui::Begin("Permashow", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::SetCursorPos({ 7.f,28.f });
    ImGui::PushItemWidth(119.000000);
    ImGui::Text("Update: %f ms", (float)dur.count());
    ImGui::PopItemWidth();
    /*
    ImGui::SetCursorPos({ 7.f,52.f });
    ImGui::PushItemWidth(119.000000);
    ImGui::PopItemWidth();
    */
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




    logger->Info("Initializing modules..");
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

    logger->Info("Initialization done!");

}