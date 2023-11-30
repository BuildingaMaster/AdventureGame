#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NPC.h"
#include "Location.h"
#include "PlayerActions.h"
#include "PrintDisplay.h"

using namespace std;

NPC::NPC(string npcname, int initialLives, bool hostile) : health(initialLives) { name = npcname; isHostile = hostile; }

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

bool NPCManager::init()
{
    for (auto const& x : locationManager::locationMap)
    {
        NPCMap.insert(std::pair<int, vector<NPC*>>(x.first, vector<NPC*>()));
        if (x.second->hasAttribute(x.second->WOLVES_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new NPC("wolf", 3, true));
        }
        else if (x.second->hasAttribute(x.second->KNIGHT_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new NPC("knight", 4, true));
        }
    }
    return true;
}

void NPCManager::deinit()
{
    for (auto &x : NPCMap)
    {
        for (auto y : x.second)
        {
            delete y;
        }
        x.second.clear();
    }
    NPCMap.clear();
}

NPC* NPCManager::returnNPC(string NPCname)
{
    uint32_t roomID = locationManager::getCurrentLocation()->getLocationID();

    for (int i = 0; i < NPCMap[roomID].size(); i++) // Grab pass
    {
        if (NPCMap[roomID][i]->name == NPCname)
        {
            return NPCMap[roomID][i];
        }
    }
    return nullptr;
}

bool NPCManager::scanForNPC(string NPCname)
{
    return returnNPC(NPCname) != nullptr;
}

map<int, vector<NPC*>> NPCManager::NPCMap;