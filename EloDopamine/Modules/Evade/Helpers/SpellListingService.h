//
// Created by XaDanX on 11/20/2022.
//

#include <vector>
#include <map>
#include "../../../Core/Game/GameData/Missile.h"

class SpellListingService {
public:
    std::map<std::string, Missile> missiles;

    void Update();



private:
    void UpdateActiveSpell();
    void ValidateSpells();

};
