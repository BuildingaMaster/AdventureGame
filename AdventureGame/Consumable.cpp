#include "Consumable.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;

random_device Consumable::rd;
uniform_int_distribution<int> Consumable::dist(1, 100);

Consumable::Consumable(consumableType initType, double initWeight) : Item(consumable)
{
	itemType = initType;
	setWeight(initWeight);
	if (initType == apple)
	{
		itemName = "apple";
	}
	else if (initType == mushroom) 
	{
		itemName = "mushroom";
	}
}

Consumable::Consumable() : Item(consumable)
{
	itemType = apple;
	setWeight(1);
	itemName = "apple";
}

void Consumable::consume(PlayerActions* player)
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

consumableType Consumable::getConsumType()
{
	return itemType;
}