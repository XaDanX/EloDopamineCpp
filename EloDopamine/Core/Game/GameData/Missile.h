#pragma once
#include <string>
#include "../../Math/Vector.h"
#include "SpellInfo.h"

class Missile {
public:
    Vector3 startPos;
    Vector3 endPos;
    std::string name;
    float startTime;
    float endTime;
    SpellInfo* spellInfo;
};



