#include "Weapon.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include "PrintDisplay.h"
#include "CommonGameObjects.h"

using namespace std;

random_device WeaponManager::rd;

uniform_int_distribution<int> WeaponManager::dist(1, 15);

Weapon::Weapon(weaponType initType, double initWeight) : Item(weapon)
{
	itemType = initType;
	setWeight(initWeight);
	if (initType == fists)
	{
		itemName = "fists";
		damageAmount = 1;
	}
	else if (initType == boomerang) 
	{
		itemName = "boomerang";
		damageAmount = 1;
	}
}

Weapon::Weapon() : Item(weapon)
{
	itemType = fists;
	setWeight(0);
	itemName = "fists";
}
/*
void Weapon::consume(PlayerActions* player)
{
	switch (itemType)
	{
		case apple:
		{
			player->healPlayer(1);
			PrintDisplay::custom_cout << "\nYou healed by 1 HP!\n";
			PrintDisplay::flush();
			break;
		}
		case mushroom: // creating a 50 50 chance of a good / bad shroom
		{
			// generating a rand # from 1 - 100
			int randNum = dist(rd);
			if (randNum < 50)
			{
				// Implement eating mushroom functionality here!
				player->healPlayer(1);
				PrintDisplay::custom_cout << "\nYou healed by 1 HP!\n";
				PrintDisplay::flush();
				break;
			}
			else
			{
				// using seed
				int random = rand() % 2 + 1;
				switch(random)
				{
					case 1:
					{
						random = rand() % 3 + 1;
						player->hurtPlayer(random);

						PrintDisplay::custom_cout << "\nYou were hurt by " << random << " HP!\n";
						PrintDisplay::flush();
						break;
					}
					case 2:
					{
						PrintDisplay::custom_cout << "\nThe mushroom tasted fine, but you don't feel right...\n";
						PrintDisplay::flush();
						player->thePlayerIsHigh(true);
						player->highForNMoves(rand() % 10 + 5);
						break;
					}
				}
				break;

			}	
		}
		default:
			break;
	}
}
*/
weaponType Weapon::getWeaponType()
{
	return itemType;
}

int Weapon::getDamageAmount()
{
	return damageAmount;
}

void Weapon::action()
{
	if (itemType == boomerang)
	{
		vector<NPC*>& temp = NPCManager::getNPCsInRoom();
		if (temp.empty())
		{
			PrintDisplay::custom_cout << "\nThere were no enemies to hit!\n";
		}
		else if (WeaponManager::dist(WeaponManager::rd) == 1)
		{
			PrintDisplay::custom_cout << "\nA strong breeze altered the boomerang's trajectory!\n";
			PrintDisplay::custom_cout << "It caused the boomerang to miss!\n";
			PrintDisplay::custom_cout << "THWACK! It hit you square in the face.\n";
			CommonGameObjects::PAManager->hurtPlayer(1);
		}
		else
		{
			for (auto &a : temp)
			{
				a->takeDamage(1);
			}
			PrintDisplay::custom_cout << "\nThe boomerang hit " << temp.size() << "beings!\n";
			CommonGameObjects::PAManager->hurtPlayer(1);
		}
		PrintDisplay::flush();
	}
}



bool WeaponManager::swapWeapon(Weapon* newWeapon)
{
    WeaponManager::currentWeapon = newWeapon;
    return true;
}

Weapon* WeaponManager::getCurrentWeapon()
{
    return WeaponManager::currentWeapon;
}
bool WeaponManager::init()
{
    WeaponManager::fistsStandard = new Weapon();
	
	WeaponManager::swapWeapontoFists();
    return true;
}

void WeaponManager::deinit()
{
	delete WeaponManager::fistsStandard;
}

void WeaponManager::swapWeapontoFists()
{
	currentWeapon = *&fistsStandard;
}
Weapon* WeaponManager::currentWeapon = nullptr;
Weapon* WeaponManager::fistsStandard = nullptr;