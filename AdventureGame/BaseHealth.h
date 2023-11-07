#pragma once

class BaseHealth
{
#ifdef GTESTING
public:
#else
private:
#endif
    int health;
    int maxHealth;

public:
    /// @brief Default Constructor for BaseHealth
    BaseHealth();
    
    /// @brief Constructor for BaseHealth, supplying max health
    /// @param amount Max HP
    BaseHealth(int);
    
    /// @brief adds HP to an entity's health
    void addHP(int);
    
    /// @brief 
    /// @return Health of entity
    int checkHP();
    
    /// @brief Removes 1 HP from entity
    /// @return Does the entity have 0 health
    bool removeHP(int);
    
    /// @brief Checks the max health
    /// @return Max health of entity
    int checkMaxHP();

    /// @brief Restores an entity's health to it's max.
    void restoreMaxHP();

    bool playerDead();
    

};