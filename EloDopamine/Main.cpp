#include <iostream>
#include "Logger.h"
#include "Offsets.h"
#include "EloDopamine.h"
#include "GameData.h"

using namespace std::chrono_literals;

int main() {
    logger->SetLevel(LogLevel::Debug);
    logger->Info("Waiting for the game.");
    eloDopamine->Initialize();

    while (true) {
        eloDopamine->Update();
        std::this_thread::sleep_for(1ms);
    }
}