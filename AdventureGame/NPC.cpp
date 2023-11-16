
#include <iostream>
#include <string>
#include <vector>

#include "NPC.h"

NPC::NPC(int initialLives) : health(initialLives) {}

bool NPC::takeDamage(int damage) 
{
    return health.removeHP(damage);
}

bool NPC::isDead() 
{
    return health.checkHP() <= 0;
}

int NPC::getLives() 
{
    return health.checkHP();
}








