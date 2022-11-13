#include <iostream>
#include "Logger.h"
#include "Offsets.h"
#include "EloDopamine.h"
#include "GameData.h"
#include <cstdlib>
#include <csignal>

using namespace std::chrono_literals;

int main() {
    logger->SetLevel(LogLevel::Debug);
    logger->Info("Waiting for the game.");
    eloDopamine->Initialize();
    // register every closing scenario ;o
    signal(SIGINT, EloDopamine::OnExit);
    signal(SIGABRT, EloDopamine::OnExit);
    signal(SIGTERM, EloDopamine::OnExit);
    signal(SIGBREAK, EloDopamine::OnExit);


    while (true) {
        eloDopamine->Update();
        Sleep(1);
    }
}