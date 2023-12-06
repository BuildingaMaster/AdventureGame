#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "BaseHealth.h"
#include "PlayerActions.h"

using namespace std;

class NPC {
private:
    BaseHealth health;
public:
    NPC(string name ,int initialLives, bool hostile);
    string name;
    bool isHostile;
    bool takeDamage(int damage);
    bool isDead();
    int getLives();
};

class NPCManager
{
public:
    static bool init();
    static bool scanForNPC(string);
    static vector<NPC*>& getNPCsInRoom();
    static map<int, vector<NPC*>> NPCMap;
    static NPC* returnNPC(string);
    static void deinit();
};

class NPCDescription
{
    public:
        /// @brief The NPC's description, first singular, second is plural
        static std::map<std::string,  std::pair<std::string,std::string>> NPCTag;
};