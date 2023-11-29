#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "BaseHealth.h"

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
    static map<int, vector<NPC*>> NPCMap;
    static NPC* returnNPC(string);
};