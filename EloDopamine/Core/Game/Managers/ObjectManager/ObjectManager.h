#pragma once
#include <vector>
#include "../../GameObjects/Hero/Hero.h"
#include "../MemoryManager/MemoryManager.h"
#include "../../Offsets.h"
#include "../../GameObjects/Minion/Minion.h"

class ObjectManager {
private:
    std::vector<Hero> heroList;

    std::vector<Minion> allyMinionList;
    std::vector<Minion> enemyMinionList;
    std::vector<Minion> minionList;

    std::vector<Minion> wardList;

    int heroListPtr = 0;
    int minionListPtr = 0;

    Hero localPlayer;


public:
    std::vector<Hero> GetHeroList();

    std::vector<Minion> GetMinionList();
    std::vector<Minion> GetAllyMinionList();
    std::vector<Minion> GetEnemyMinionList();

    std::vector<Minion> GetWardList();

    Hero GetLocalPlayer();

    void Update();
};
inline extern std::unique_ptr<ObjectManager> objectManager = std::make_unique<ObjectManager>();


