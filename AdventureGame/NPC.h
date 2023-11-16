#pragma once

#include <iostream>
#include <string>
#include <vector>

class NPC {
private:
    int lives;

public:
    NPC(int initialLives);
    bool takeDamage(int damage);
    bool isDead();
    int getLives();
};


