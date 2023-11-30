#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "NPC.h"
#include "Location.h"
#include "Princess.h"
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
        else if (x.second->hasAttribute(x.second->PRINCESS_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new Princess());
        }
        else if (x.second->hasAttribute(x.second->DRAGON_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new NPC("dragon", 5, true));
        }
        else if (x.second->hasAttribute(x.second->KING_THAD_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new NPC("king", 6, true));
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


std::map<std::string,  std::pair<std::string,std::string>> NPCDescription::NPCTag = {
        {"wolf", std::pair<std::string,std::string>{"WOLF!!!! Its time to run or fight!", "WOLVES!!!! Its time to run or fight!"}},
        {"knight", std::pair<std::string,std::string>{"The knight blocks your path!", "The knights surround you and block your path!"}},
        {"dragon", std::pair<std::string,std::string>{"THE DRAGON AWAKES IN RAGE!\nThe dragon roars in anger and blows fire that throws you back.", "THE DRAGON AWAKES IN RAGE!\nThe dragons roar in anger and blows fire that throws you back."}},
        {"king", std::pair<std::string,std::string>{"The king is the only thing between you and Florence!\n", "The king is the only thing between you and Florence!\n"}},
};
