#include "Potion.h"
#include "PrintDisplay.h"
#include "Location.h"
#include "CommonGameObjects.h"

Potion::Potion(potionType initType, double initWeight) : Item(potion)
{
	itemType = initType;
	setWeight(initWeight);
    switch (initType)
    {
        case strength:
		    itemName = "potion of strength";
            break;
        case mobility:
		    itemName = "potion of mobility";
            break;
        case sobriety:
		    itemName = "potion of sobriety";
            break;
        case teleportation:
		    itemName = "potion of teleportation";
            break;
    }
}

Potion::Potion() : Item(potion)
{
	itemType = strength;
	setWeight(1);
	itemName = "potion of strength";
}

Potion::~Potion()
{
	
}

void Potion::action()
{
    PrintDisplay::custom_cout << "\nYou drank the "<< itemName <<"!\n";
    PrintDisplay::no_effect_flush();
    switch (itemType)
    {
        case strength:
        {
            effectManager::addStrength();
            break;
        }
        case mobility:
        {
            effectManager::slowDownTime();
            break;
        }
        case sobriety:
        {
            effectManager::soberUp();
            break;
        }
        case teleportation:
        {
            effectManager::warp();
            break;
        }
    } 
}

void effectManager::wearDownSlow()
{
    slowDownTurns--;

    if (effectManager::slowDownTurns == 0)
    {
        PrintDisplay::custom_cout << "\nThe effects from the Potion of Mobility wore off!\n";
        PrintDisplay::no_effect_flush(); 
    }

    if (slowDownTurns < -1)
    {
        slowDownTurns = -1;
    }

}

void effectManager::wearDownStrength()
{
    strengthTurns--;

    if (effectManager::strengthTurns == 0)
    {
        effectManager::attackUpBonus = false;
        PrintDisplay::custom_cout << "\nThe effects from the Potion of Strength wore off!\n";
        PrintDisplay::no_effect_flush(); 
    }
    if (strengthTurns < -1)
    {
        strengthTurns = -1;
    }


}

int effectManager::strengthTurns = 0;
int effectManager::slowDownTurns = 0;
bool effectManager::attackUpBonus = false;
bool effectManager::shouldSlowDown = false;

void effectManager::addStrength()
{
    if (effectManager::slowDownTurns > 0)
    {
        PrintDisplay::custom_cout << "\nYou should have read the warning label.";
        PrintDisplay::custom_cout << "\nYou exploded at the sheer power of both potions.\n";
        CommonGameObjects::PAManager->hurtPlayer(999999);
        PrintDisplay::no_effect_flush();
    }
    effectManager::attackUpBonus = true;
    PrintDisplay::custom_cout << "\nYou now have a stronger attack!\n";
    effectManager::strengthTurns = 5;
    PrintDisplay::flush();
}

void effectManager::slowDownTime()
{
    if (effectManager::slowDownTurns > 0)
    {
        PrintDisplay::custom_cout << "\nYou should have read the warning label.";
        PrintDisplay::custom_cout << "\nYou exploded at the sheer power of both potions.\n";
        CommonGameObjects::PAManager->hurtPlayer(999999);
        PrintDisplay::no_effect_flush();
        return;
    }
    effectManager::shouldSlowDown = true;
    effectManager::slowDownTurns = 3;
    PrintDisplay::custom_cout << "\nYou now have the ability to slow down time!\n";
    PrintDisplay::flush();

}

void effectManager::soberUp()
{
    CommonGameObjects::PAManager->thePlayerIsHigh(false);
    PrintDisplay::custom_cout << "\nAfter drinking the potion, you feel a lot better about yourself.\n";
    PrintDisplay::flush();
}

void effectManager::warp()
{
    PrintDisplay::custom_cout << "\nAfter drinking the potion, you blacked out!\n";
    PrintDisplay::custom_cout << "Once you regain consciousness, you realize you are in a different place.\n";
    PrintDisplay::flush();
    locationManager::updateCurrentLocation(locationManager::locationMap[1]);
}

