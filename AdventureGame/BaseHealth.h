#pragma once

class BaseHealth
{
private:
    int health;
    int maxHealth;

public:
    /// @brief Default Constructor for BaseHealth
    BaseHealth();
    
    /// @brief Constructor for BaseHealth, supplying max health
    /// @arg max healh
    BaseHealth(int);
    
    /// @brief adds HP to an entity's health
    void addHP(int);
    
    /// @brief 
    /// @return Health of entity
    int checkHP();
    
    /// @brief Removes 1 HP from entity
    /// @return Does the entity have 0 health
    bool removeHP();
    
    /// @brief Restores an entity's health to it's max.
    void restoreMaxHP();
    

};