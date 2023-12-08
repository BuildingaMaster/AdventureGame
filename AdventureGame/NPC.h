#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "BaseHealth.h"
#include "PlayerActions.h"

using namespace std;

class NPC {
#ifdef GTESTING
public:
#else
private:
#endif
    BaseHealth health;
public:
    NPC(string name ,int initialLives, bool hostile);
    string name;
    bool isHostile;
    bool takeDamage(int damage);
    bool isDead();
    int getLives();
    /// @brief Give the NPC all their health back.
    void resurrect();
    virtual void nothing() {}; // Does nothing
    /// @brief A callback if the attack misses/fails.
    virtual void attackFailed() = 0;
    virtual void attackPlayer() = 0;
    virtual bool recieveAttack() = 0;
    virtual void printIAmDeadMessage() = 0;
    void AttackAtPlayer();

    /// @brief Displays the dodgeUI for the player when NPC is attacked
    /// @param iterations How many times the enemy can have sucessive attacks
    /// @param disable_forward_tile Should the player be able to dodge forward?
    /// @param more_than_one_tile Multi-tile mode
    /// @param reaction_time How fast should the player react? (1111 is ideal.)
    /// @return HP lost
    void AttackAtPlayer(int,bool,bool,int);

    bool PlayerAttacksMe(string, int);
    virtual ~NPC() = default;
    
};

class NPCManager
{
public:
    static bool init();
    static bool scanForNPC(string);
    static map<int, vector<NPC*>> NPCMap;
    static NPC* returnNPC(string);
    static void resurrectAllNPCs();
    static bool fightHostileNPCs();
    static bool findLiveHostileNPCs();
    static void deinit();
};

class NPCDescription
{
    public:
        /// @brief The NPC's description, first singular, second is plural
        static std::map<std::string,  std::pair<std::string,std::string>> NPCTag;
};