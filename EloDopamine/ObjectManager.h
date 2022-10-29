#pragma once
#include <vector>
#include "Hero.h"
#include "MemoryManager.h"
#include "Offsets.h"

class ObjectManager {
private:
    std::vector<Hero> heroList;

    int heroListPtr;


public:
    std::vector<Hero> GetHeroList();

    void Update();
};
inline extern std::unique_ptr<ObjectManager> objectManager = std::make_unique<ObjectManager>();


