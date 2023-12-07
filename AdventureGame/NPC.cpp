#include "NPC.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include "Location.h"
#include "PlayerActions.h"
#include "PrintDisplay.h"
#include "CommonGameObjects.h"

#include "PrintDisplay.h"

#include "Knight.h"
#include "Princess.h"
#include "Wolf.h"
#include "King.h"
#include "Dragon.h"

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

void NPC::resurrect()
{
    health.restoreMaxHP();
}

void NPC::AttackAtPlayer() {}

void NPC::AttackAtPlayer(
                        int dodge_iterations, 
                        bool dodge_disable_forward_tile, 
                        bool dodge_more_than_one_tile, 
                        int dodge_reaction_time)
{
    /*
    int dodge_iterations
    bool dodge_disable_forward_tile
    bool dodge_more_than_one_tile
    int dodge_reaction_time
    */
    if (isHostile)
    {
        PrintDisplay::custom_cout << "The " << this->name << " begins it's attack!\n";
        this_thread::sleep_for(chrono::milliseconds(700));
        int hitCount = PrintDisplay::dodgeScreen(dodge_iterations, dodge_disable_forward_tile, dodge_more_than_one_tile, dodge_reaction_time);
        if (hitCount > 0) // The player got hit.
        {
            CommonGameObjects::PAManager->hurtPlayer(hitCount);
            if (!CommonGameObjects::PAManager->thePlayerIsDead())
            {
                PrintDisplay::custom_cout << "You can withstand " << CommonGameObjects::PAManager->checkPlayerHealth() << " more hits!" << endl;
            }
            PrintDisplay::flush();
        }
    }
}

bool NPC::PlayerAttacksMe(string strike_hitBox, int strike_time_to_react)
{
    return PrintDisplay::hitScreen(strike_hitBox, strike_time_to_react);
}

bool NPCManager::init()
{
    for (auto const& x : locationManager::locationMap)
    {
        NPCMap.insert(std::pair<int, vector<NPC*>>(x.first, vector<NPC*>()));
        if (x.second->hasAttribute(x.second->WOLVES_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new Wolf());
        }
        else if (x.second->hasAttribute(x.second->KNIGHT_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new Knight());
        }
        else if (x.second->hasAttribute(x.second->PRINCESS_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new Princess());
        }
        else if (x.second->hasAttribute(x.second->DRAGON_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new Dragon());
        }
        else if (x.second->hasAttribute(x.second->KING_THAD_IN_ROOM))
        {
            NPCMap[x.first].insert(NPCMap[x.first].begin(), new King());
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

void NPCManager::resurrectAllNPCs()
{
    for (auto ID : NPCMap)
    {
        for (auto npc : ID.second)
        {
            npc->resurrect();
        }
    }
}

bool NPCManager::fightHostileNPCs()
{
    uint32_t roomID = locationManager::getCurrentLocation()->getLocationID();
    for (auto npc : NPCMap[roomID])
    {
        if (npc->isHostile)
        {
            npc->attackPlayer();
        }
        if (CommonGameObjects::PAManager->thePlayerIsDead())
        {
            return false;
        }
    }
    return true;
}

bool NPCManager::findLiveHostileNPCs()
{
    uint32_t roomID = locationManager::getCurrentLocation()->getLocationID();
    for (auto npc : NPCMap[roomID])
    {
        if (npc->isHostile && !npc->isDead())
        {
            return true;
        }
    }
    return true;
}

map<int, vector<NPC*>> NPCManager::NPCMap;


std::map<std::string,  std::pair<std::string,std::string>> NPCDescription::NPCTag = {
        {"wolf", std::pair<std::string,std::string>{"WOLF!!!! Its time to run or fight!", "WOLVES!!!! Its time to run or fight!"}},
        {"knight", std::pair<std::string,std::string>{"The knight blocks your path!", "The knights surround you and block your path!"}},
        {"dragon", std::pair<std::string,std::string>{"THE DRAGON AWAKES IN RAGE!\nThe dragon roars in anger and blows fire that throws you back.", "THE DRAGON AWAKES IN RAGE!\nThe dragons roar in anger and blows fire that throws you back."}},
        {"king", std::pair<std::string,std::string>{"The king is the only thing between you and Florence!\n", "The king is the only thing between you and Florence!\n"}},
};
