#include "PlayerActions.h"

#include <iostream>
#include <string>
#include <vector>

#include "PrintDisplay.h"
using namespace std;

PlayerActions::PlayerActions()
{
	healthMGR = BaseHealth(PLAYER_HEALTH);
    playerIsHigh = false;
    stepsUntilNotHigh = 0;
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
    // Hit command [base]
    else if (args[0] == "hit" &&  args[1] == "self")
    {
        if (healthMGR.removeHP(1)) // The player is dead.
        {
            PrintDisplay::custom_cout << "\nFor some reason, you hit yourself, and you slapped yourself to death. You win.\n";
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
