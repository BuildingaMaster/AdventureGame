#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "PlayerActions.h"
#include "PrintDisplay.h"
#include "NPC.h"
#include "ContextParser.h"
#include "Location.h"
#include "CommonGameObjects.h"
#include "Potion.h"


using namespace std;

PlayerActions::PlayerActions()
{
    healthMGR = BaseHealth(PLAYER_HEALTH);
    playerIsHigh = false;
    worn = none;
    stepsUntilNotHigh = 0;
    firstTimePlayerAttacks = true;
    firstTimePlayerDodges = true;
}

bool PlayerActions::processCommand(vector<string> args)
{
    // PA needs two arguments. If only one is available, bypass.
    if (args.size() == 1)
    {
        PrintDisplay::custom_cout << "\nIt's not clear what you want to " << args[0] << ".\n";
        PrintDisplay::no_effect_flush();
        return false;
    }

    // Check player health [basic]
    if (args[0] == "check" &&  (args[1] == "health" || args[1] == "hp" || args[1] == "self"))
    {
        PrintDisplay::custom_cout << "\nYou can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        PrintDisplay::flush();
        return true;
    }
    else if (args[0] == "check" && args[1]  == "inventory")
    {
        CommonGameObjects::INManager->listInventory();
        return true;
    }
    string entityName = "";

    for (int i = 1; i<args.size(); i++)
    {
        entityName+= args[i] + " ";
    }
    entityName.erase(entityName.end()-1);
    args[1] = entityName;

    // Hit command [base, only the player for now]
    if (args[0] == "hit" &&  args[1] == "self")
    {
        if (healthMGR.removeHP(1)) // The player is dead.
        {
            PrintDisplay::custom_cout << "GAME OVER! ";
            PrintDisplay::flush();
        }
        else
        {
            PrintDisplay::custom_cout << "\nFor some reason, you hit yourself.\n";
            PrintDisplay::custom_cout << "You can withstand "<< healthMGR.checkHP() <<" more hits.\n";
            PrintDisplay::flush();
        }
        return true;
    }
    else if (args[0] == "hit")
    {
        if (NPCManager::scanForNPC(args[1]))
        {
            NPC* character = NPCManager::returnNPC(args[1]);
            if (!character->isDead())
            {
                if (character->recieveAttack())
                {
                    PrintDisplay::custom_cout << "\nYou hit the "<< character->name;
                    if (character->takeDamage(1 + effectManager::attackUpBonus))
                    {
                        PrintDisplay::custom_cout << ".\n";
                        PrintDisplay::flush();
                        
                        PrintDisplay::custom_cout << "The "<< character->name <<" is dead.\n";
                        PrintDisplay::flush();
                    }
                    else
                    {
                        PrintDisplay::custom_cout << ", but it still has " << character->getLives() << " lives remaining.\n";
                        PrintDisplay::flush();
                    }
                }
                /*
                if (character->isHostile)
                {
                    this_thread::sleep_for(chrono::milliseconds(1200));
                    PrintDisplay::custom_cout << "And the "<< character->name <<" attacks you back!\n";
                    int hitCount = PrintDisplay::dodgeScreen();
                    if (hitCount > 0) // The player got hit.
                    {
                        this->hurtPlayer(hitCount);
                        if (!this->thePlayerIsDead())
                        {
                            PrintDisplay::custom_cout << "You can withstand " << this->checkPlayerHealth() << " more hits!" << endl;
                        }
                        PrintDisplay::flush();
                    }
                }     
                */                                       
                
                PrintDisplay::flush();
                return true;
            }
            else
            {
                PrintDisplay::custom_cout << "\nThe "<< character->name <<" is already dead. You can't hit it anymore.\n";
                PrintDisplay::flush();
                return false;
            }
        }
    }

    // Nothing else to do.
    PrintDisplay::custom_cout << "\nYou can't " << args[0] << " that!\n";
    PrintDisplay::no_effect_flush();
    return false;
}

void PlayerActions::changeArmor(armorType newArmor)
{
    healthMGR.changeMaxHP(newArmor);
    worn = newArmor;
}

void PlayerActions::healPlayer(int amount)
{
    healthMGR.addHP(amount);
}

void PlayerActions::hurtPlayer(int amount)
{
    healthMGR.removeHP(amount);
}
int PlayerActions::checkPlayerHealth()
{
    return healthMGR.checkHP();
}

int PlayerActions::checkMaxPlayerHealth()
{
    return healthMGR.checkMaxHP();
}

bool PlayerActions::thePlayerIsDead()
{
    return healthMGR.checkHP() <= 0;
}

bool PlayerActions::isThePlayerHigh()
{
    return playerIsHigh;
}
void PlayerActions::thePlayerIsHigh(bool ishigh)
{
    if (ishigh == false)
    {
        stepsUntilNotHigh = 0;
    }
    playerIsHigh = ishigh;
}

void PlayerActions::highForNMoves(int moves)
{
    stepsUntilNotHigh = abs(moves);
}

void PlayerActions::decrementMovingHigh()
{
    stepsUntilNotHigh = stepsUntilNotHigh-1;
    if (stepsUntilNotHigh <= 0)
    {
        thePlayerIsHigh(false);
    }
}
bool PlayerActions::playAgain()
{
    bool runItBack;
    PrintDisplay::custom_cout << "\n Do you wanna play again? \n";
    PrintDisplay::no_effect_flush();

    // If true, the player want to play again
    // Otherwise close the game
    runItBack = ContextParser::yesNoPrompt();
    if (runItBack == true)
    {
        CommonGameObjects::INManager->dropAllInventory();
        locationManager::updateCurrentLocation(locationManager::locationMap[1]);
        changeArmor(none);
        healthMGR.restoreMaxHP();
        NPCManager::resurrectAllNPCs();
         // bring player back to starting room, reset the inventory & NPCS
    }
    else
    {
        // Goodbye quote
        PrintDisplay::custom_cout << "\nThe difference between the master and the student is that the master has failed far more times than the student.\n";
        PrintDisplay::no_effect_flush();
        PrintDisplay::pause();
    }
    return runItBack;
}

bool PlayerActions::checkAndFlipFirstAttack()
{
    bool r = firstTimePlayerAttacks;
    if (r == true)
    {
        firstTimePlayerAttacks = false;
    }
    return r;
}

bool PlayerActions::checkAndFlipFirstDodge()
{
    bool r = firstTimePlayerDodges;
    if (r == true)
    {
        firstTimePlayerDodges = false;
    }
    return r;
}


