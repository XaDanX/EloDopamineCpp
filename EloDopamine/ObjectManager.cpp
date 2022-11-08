#include "ObjectManager.h"

void ObjectManager::Update() {


    int heroListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::HeroInterface);
    int minionListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::MinionInterface);


    this->heroList.clear();
    this->minionList.clear();
    this->enemyMininList.clear();
    this->allyMinionList.clear();

    auto heroPointers = memoryManager->ReadTemplate(heroListPtr);

    for (int n : heroPointers) {
        Hero currentHero = Hero();
        currentHero.Load(n, false);
        this->heroList.emplace_back(currentHero);
    }

    auto minionPointers = memoryManager->ReadTemplate(minionListPtr);

    for (int n : minionPointers) {
        Minion currentMinion = Minion();
        currentMinion.Load(n, false);
        if (currentMinion.team == Team::BLUE || currentMinion.team == Team::RED) {
            if (currentMinion.team == this->GetLocalPlayer().team)
                this->allyMinionList.emplace_back(currentMinion);
            else
                this->enemyMininList.emplace_back(currentMinion);
            this->minionList.emplace_back(currentMinion);
        }
    }

}

Hero ObjectManager::GetLocalPlayer() {
    return this->heroList.at(0);
}

std::vector<Hero> ObjectManager::GetHeroList() {
    return this->heroList;
}

std::vector<Minion> ObjectManager::GetMinionList()
{
    return this->minionList;
}


