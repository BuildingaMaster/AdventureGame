#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "BaseHealth.h"

class NPC {
private:
    BaseHealth health;
public:
    NPC(int initialLives);
    bool takeDamage(int damage);
    bool isDead();
    int getLives();
};


