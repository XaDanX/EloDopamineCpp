#pragma once
#include <vector>
#include "Hero.h"
#include "MemoryManager.h"
#include "Offsets.h"

class ObjectManager {
private:
    std::vector<Hero> heroList;

    int heroListPtr;

    int localPlayerPointer{ 0 };
    Hero localPlayer;


public:
    std::vector<Hero> GetHeroList();

    Hero GetLocalPlayer();

    void Update();
};
inline extern std::unique_ptr<ObjectManager> objectManager = std::make_unique<ObjectManager>();


