#pragma once
#include <vector>
#include "Hero.h"
#include "MemoryManager.h"
#include "Offsets.h"
#include "Minion.h"

class ObjectManager {
private:
    std::vector<Hero> heroList;

    std::vector<Minion> allyMinionList;
    std::vector<Minion> enemyMininList;
    std::vector<Minion> minionList;

    int heroListPtr;
    int minionListPtr;

    int localPlayerPointer{ 0 };
    Hero localPlayer;


public:
    std::vector<Hero> GetHeroList();

    std::vector<Minion> GetMinionList();
    std::vector<Minion> GetAllyMinionList();
    std::vector<Minion> GetEnemyMinionList();

    Hero GetLocalPlayer();

    void Update();
};
inline extern std::unique_ptr<ObjectManager> objectManager = std::make_unique<ObjectManager>();


