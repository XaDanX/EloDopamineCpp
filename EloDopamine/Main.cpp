#include <iostream>
#include "Logger.h"
#include "Offsets.h"
#include "EloDopamine.h"

int main() {
    logger->SetLevel(LogLevel::Debug);
    eloDopamine->Initialize();

    auto localPlayer = objectManager->GetLocalPlayer();

    logger->Debug("index: %i", localPlayer->index);
    logger->Debug("health: %f", localPlayer->health);
    logger->Debug("max health: %f", localPlayer->maxHealth);
    logger->Debug("team: %i", localPlayer->team);
    logger->Debug("attack range: %f", localPlayer->attackRange);
    logger->Debug("targetable: %s", localPlayer->targetable ? "true" : "false");
    logger->Debug("champion name: %s", localPlayer->championName.c_str());
    


   

    for (auto hero : objectManager->GetHeroList()) {
        logger->Info(hero.championName.c_str());
    }

    
    
    while (true) {
        eloDopamine->Update();
        Sleep(1); // let the processor rest ;3

    }

     



}