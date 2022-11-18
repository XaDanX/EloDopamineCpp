#include "EloDopamine.h"
#include "../Game/Renderer/Renderer.h"
#include "../../imgui/imgui.h"
#include <chrono>
#include "../Game/Managers/ModuleManager/ModuleManager.h"
#include "../Game/GameData/GameData.h"
#include <thread>
#include <iostream>
#include "../Game/Managers/TextureManager/TextureManager.h"
#include <filesystem>

void EloDopamine::OnUpdate() {
    moduleManager->UpdateModules();
    renderer->DrawCircleAt(engine->MouseWorldPos(), 30, true, 100, engine->IsNotWall(engine->MouseWorldPos()) ? ImColor(0, 255, 0, 150) : ImColor(255, 0, 0, 150), 1);

    for (auto& minion : objectManager->GetMinionList()) {
        renderer->DrawCircleAt(minion.position, 30, true, 6, ImColor(255, 0, 255, 150), 1);
    }
    for (auto& minion : objectManager->GetWardList()) {
        renderer->DrawCircleAt(minion.position, 30, true, 6, ImColor(0, 0, 255, 150), 1);
    }

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
