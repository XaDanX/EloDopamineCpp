#include <iostream>
#include "Logger.h"
#include "Offsets.h"
#include "EloDopamine.h"
#include "GameData.h"


int main() {
    logger->SetLevel(LogLevel::Debug);
    logger->Info("Waiting for the game.");
    eloDopamine->Initialize();

    while (true) {
        eloDopamine->Update();
    }
}