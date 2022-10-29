#include "ObjectManager.h"

void ObjectManager::Update() {

    this->heroList.clear();

    int heroListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::HeroInterface);
    auto pointers = memoryManager->ReadTemplate(heroListPtr);

    for (int n : pointers) {
        Hero currentHero = Hero();
        currentHero.Load(n, false);
        heroList.emplace_back(currentHero);
    }

}

std::vector<Hero> ObjectManager::GetHeroList() {
    return this->heroList;
}