#pragma once
#include "Windows.h"

enum Team {
    UNKNOWN = 0, // meant to use for jungle monsters etc.
    BLUE = 100,
    RED = 200
};

class GameObject {
protected:
    static const SIZE_T objectSize = 0x4000;
    BYTE buff[objectSize];
private:
    unsigned int address{};
public:
    int index{};
    float health{};
    float maxHealth{};
    Team team{};
    float attackRange{};
    bool targetable{};


    virtual bool Load(unsigned int address, bool deepLoad);





};

