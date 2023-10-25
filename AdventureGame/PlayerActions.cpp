#include "PlayerActions.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Constructor 
/// @brief sets HealthMGR equal to BaseHealth(PLAYER_HEALTH)
PlayerActions::PlayerActions()
{
	healthMGR = BaseHealth(PLAYER_HEALTH);
}

// Function
/// @brief Allows player to check their health
/// @args What the player inputs
bool PlayerActions::processCommand(vector<string> args)
{
    if (args[0] == "check" &&  args[1] == "health")
    {
        cout << "\nYou can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        return true;
    }
    else if (args[0] == "hit" &&  args[1] == "self")
    {
        if (healthMGR.removeHP())
        {
            cout << "\nFor some reason, you still hit yourself, even though you have no more HP.\n";
        }
        else
        {
            cout << "\nFor some reason, you hit yourself.\n";
        }
        cout << "You can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        return true;
    }
    return false;
}