#include <iostream>
#include "Logger.h"
#include "MemoryManager.h"
#include "Offsets.h"
#include "Hero.h"
#include "ObjectManager.h"

int main() {
    logger->SetLevel(LogLevel::Debug);
    memoryManager->Initialize();
    
    int localPlayerAddr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::LocalPlayer);
    logger->Debug("local player address: %#08x", localPlayerAddr);

    Hero localPlayer = Hero();

    localPlayer.Load(localPlayerAddr, false);

    logger->Debug("index: %i", localPlayer.index);
    logger->Debug("health: %f", localPlayer.health);
    logger->Debug("max health: %f", localPlayer.maxHealth);
    logger->Debug("team: %i", localPlayer.team);
    logger->Debug("attack range: %f", localPlayer.attackRange);
    logger->Debug("targetable: %s", localPlayer.targetable ? "true" : "false");
    logger->Debug("champion name: %s", localPlayer.championName.c_str());
    


    objectManager->Update();

    for (auto hero : objectManager->GetHeroList()) {
        logger->Info(hero.championName.c_str());
    }
     



}