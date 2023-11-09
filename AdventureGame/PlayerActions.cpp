#include "PlayerActions.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

PlayerActions::PlayerActions()
{
	healthMGR = BaseHealth(PLAYER_HEALTH);
}

bool PlayerActions::processCommand(vector<string> args)
{
    if (args[0] == "check" &&  args[1] == "health")
    {
        cout << "\nYou can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        return true;
    }
    else if (args[0] == "hit" &&  args[1] == "self")
    {
        if (healthMGR.removeHP(1))
        {
            cout << "\nFor some reason, you hit yourself, and you slapped yourself to death. You win.\n";
        }
        else
        {
            cout << "\nFor some reason, you hit yourself.\n";
            cout << "You can withstand "<< healthMGR.checkHP() <<" more hits.\n";
        }
        return true;
    }
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
