#include "ObjectManager.h"

void ObjectManager::Update() {

    if (heroListPtr == 0 || minionListPtr == 0) {
        heroListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::HeroInterface);
        minionListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::MinionInterface);
    }

    this->minionList.clear();
    this->enemyMinionList.clear();
    this->allyMinionList.clear();
    this->wardList.clear();

    if (this->heroList.size() < 9) {
        this->heroList.clear();
        auto heroPointers = memoryManager->ReadTemplate(heroListPtr);

        for (int n : heroPointers) {
            Hero currentHero = Hero();
            currentHero.Load(n, false);
            this->heroList.emplace_back(currentHero);
        }
    } else {
        for (Hero& hero : this->heroList) {
            hero.Load(NULL, false); // It is a NULL (0) cuz hero already knows his address.
        }
    }

    auto minionPointers = memoryManager->ReadTemplate(minionListPtr);

    for (int n : minionPointers) {
        Minion currentMinion = Minion();
        currentMinion.Load(n, false);
        if ((currentMinion.team == Team::BLUE || currentMinion.team == Team::RED)
                && currentMinion.name.find("trinket") == std::string::npos
                && currentMinion.name.find("jammerdevice") == std::string::npos
                   && currentMinion.name.find("minion") != std::string::npos) {
            if (currentMinion.team == this->GetLocalPlayer().team)
                this->allyMinionList.emplace_back(currentMinion);
            else
                this->enemyMinionList.emplace_back(currentMinion);
            this->minionList.emplace_back(currentMinion);
        } else if (currentMinion.name.find("trinket") != std::string::npos || currentMinion.name.find("jammerdevice") != std::string::npos) {
            this->wardList.emplace_back(currentMinion);
        }
    }

}

Hero ObjectManager::GetLocalPlayer() {
    return this->heroList.at(0);
}

std::vector<Hero> ObjectManager::GetHeroList() {
    return this->heroList;
}

std::vector<Minion> ObjectManager::GetMinionList() {
    return this->minionList;
}

std::vector<Minion> ObjectManager::GetAllyMinionList() {
    return this->allyMinionList;
}

std::vector<Minion> ObjectManager::GetEnemyMinionList() {
    return this->enemyMinionList;
}

std::vector<Minion> ObjectManager::GetWardList() {
    return this->wardList;
}


