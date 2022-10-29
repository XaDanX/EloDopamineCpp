#include "ObjectManager.h"

void ObjectManager::Update() {

    this->heroList.clear();

    int heroListPtr = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::HeroInterface);
    auto pointers = memoryManager->ReadTemplate(heroListPtr);

    for (int n : pointers) {
        Hero currentHero = Hero();
        currentHero.Load(n, false);
        this->heroList.emplace_back(currentHero);
    }

    if (this->localPlayerPointer == 0) {
        this->localPlayerPointer = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::LocalPlayer);
        this->localPlayer = new Hero(); // allocate at stack;
        this->localPlayer->Load(localPlayerPointer, true);
    }

}

Hero* ObjectManager::GetLocalPlayer() {
    return this->localPlayer;
}

std::vector<Hero> ObjectManager::GetHeroList() {
    return this->heroList;
}
