#include "BaseHealth.h"

BaseHealth::BaseHealth()
{
    health = 3;
    maxHealth = 3;
}

BaseHealth::BaseHealth(int amount)
{
    health = amount;
    maxHealth = amount;
}

void BaseHealth::addHP(int amount)
{
    health = health + amount;
}

int BaseHealth::checkHP()
{
    return health;
}

bool BaseHealth::removeHP()
{
    health = health - 1;
    return (health <= 0);
}

void BaseHealth::restoreMaxHP()
{
    health = maxHealth;
}