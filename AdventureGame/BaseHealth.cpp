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
    if ((health + amount) >= maxHealth)
    {
        restoreMaxHP();
    }
    else
    {
        health = health + amount;
    }
}

int BaseHealth::checkHP()
{
    return health;
}

bool BaseHealth::removeHP(int amount)
{
    health = health - amount;
    return (health <= 0);
}

int BaseHealth::checkMaxHP()
{
    return maxHealth;
}

void BaseHealth::restoreMaxHP()
{
    health = maxHealth;
}