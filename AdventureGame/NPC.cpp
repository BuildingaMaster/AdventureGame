
#include <iostream>
#include <string>
#include <vector>

#include "NPC.h"

NPC::NPC(int initialLives) : lives(initialLives) {}

bool NPC::takeDamage(int damage) 
{
    lives -= damage;
    return lives <= 0;
}

bool NPC::isDead() 
{
    return lives <= 0;
}

int NPC::getLives() 
{
    return lives;
}








