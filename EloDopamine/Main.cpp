#include "Core/Utils/Logger.h"
#include "Core/EloDopamine/EloDopamine.h"
#include <csignal>

using namespace std::chrono_literals;

int main() {
    logger->SetLevel(LogLevel::Debug);
    logger->Info("Waiting for the game.");
    eloDopamine->Initialize();
    signal(SIGINT, EloDopamine::OnExit);
    signal(SIGABRT, EloDopamine::OnExit);
    signal(SIGTERM, EloDopamine::OnExit);
    signal(SIGBREAK, EloDopamine::OnExit);


    while (true) {
        eloDopamine->Update();
        Sleep(1);
    }
}