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


using namespace std;

PlayerActions::PlayerActions()
{
    healthMGR = BaseHealth(PLAYER_HEALTH);
    playerIsHigh = false;
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
    if (args[0] == "check" &&  args[1] == "health")
    {
        PrintDisplay::custom_cout << "\nYou can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        PrintDisplay::flush();
        return true;
    }
    // Hit command [base, only the player for now]
    else if (args[0] == "hit" &&  args[1] == "self")
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
    else if (args[0] == "hit" && args[1] == "wolf")
    {
        if (NPCManager::scanForNPC(args[1]))
        {
            NPC* wolf = NPCManager::returnNPC(args[1]);
            if (!wolf->isDead())
            {
                if (PrintDisplay::hitScreen("OOOOOOOOOOOOOOOOOOOO#####", 50))
                {
                    if (wolf->takeDamage(1))
                    {
                        PrintDisplay::custom_cout << "\nYou hit the wolf. It has " << wolf->getLives() << " lives remaining.\n";
                        PrintDisplay::flush();
                        if (wolf->isDead())
                        {
                            PrintDisplay::custom_cout << "The wolf is dead.\n";
                            PrintDisplay::flush();
                            return true; 
                        }
                    }
                    else
                    {
                        PrintDisplay::custom_cout << "\nYou hit the wolf, but it still has " << wolf->getLives() << " lives remaining.\n";
                        PrintDisplay::flush();
                                            
                    }
                    this_thread::sleep_for(chrono::milliseconds(1500));
                }
                
                if (wolf->isHostile)
                {
                    PrintDisplay::custom_cout << "The wolf attacks you back!\n";
                    int hitCount = PrintDisplay::dodgeScreen();
                    if (hitCount > 0) // The player got hit.
                    {
                        this->hurtPlayer(hitCount);
                        if (this->checkPlayerHealth() != 0)
                        {
                            PrintDisplay::custom_cout << "You can withstand " << this->checkPlayerHealth() << " more hits!" << endl;
                        }
                        PrintDisplay::flush();
                    }
                }
                
                PrintDisplay::flush();
                return true;
            }
            else
            {
                PrintDisplay::custom_cout << "\nThe wolf is already dead. You can't hit it anymore.\n";
                PrintDisplay::flush();
                return false;
            }
        }
    }
    else if (args[0] == "hit" && args[1] == "knight")
    {
        if (NPCManager::scanForNPC(args[1]))
        {
            NPC* knight = NPCManager::returnNPC(args[1]);
            if (!knight->isDead())
            {
                if (PrintDisplay::hitScreen("OOOOOOOOOOOOOOOOOOOOOO###", 50))
                {
                    if (knight->takeDamage(1))
                    {
                        PrintDisplay::custom_cout << "\nYou hit the knight. It has " << knight->getLives() << " lives remaining.\n";
                        PrintDisplay::flush();
                        if (knight->isDead())
                        {
                            PrintDisplay::custom_cout << "The knight is dead.\n";
                            PrintDisplay::flush();
                            return true; 
                        }
                    }
                    else
                    {
                        PrintDisplay::custom_cout << "\nYou hit the knight, but it still has " << knight->getLives() << " lives remaining.\n";
                        PrintDisplay::flush();
                                            
                    }
                    this_thread::sleep_for(chrono::milliseconds(1500));
                }

                if (knight->isHostile)
                {   
                    PrintDisplay::custom_cout << "The knight attacks you back!\n";
                    int hitCount = PrintDisplay::dodgeScreen();
                    if (hitCount > 0) // The player got hit.
                    {
                        this->hurtPlayer(hitCount);
                        if (this->checkPlayerHealth() != 0)
                        {
                            PrintDisplay::custom_cout << "You can withstand " << this->checkPlayerHealth() << " more hits!" << endl;
                        }
                        PrintDisplay::flush();
                    }
                }
                PrintDisplay::flush();
                return true;
            }
            else
            {
                PrintDisplay::custom_cout << "\nYou have already defeated the knight. Move on to finish your journey to the princess.\n";
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
        stepsUntilNotHigh = 0;
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
        healthMGR.restoreMaxHP();
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


