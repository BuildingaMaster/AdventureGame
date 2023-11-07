#include "Consumable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

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

Consumable::~Consumable()
{
	
}

void Consumable::consume(PlayerActions* player)
{
	switch (itemType)
	{
		case apple:
		{
			player->healPlayer(1);
			cout << "\nYou healed by 1 HP!\n";
			break;
		}
		case mushroom:
		{
			// Implement eating mushroom functionality here!
			player->healPlayer(1);
			cout << "\nYou healed by 1 HP!\n";
			break;
		}
		case badmushroom:
		{
			// creating seed
			srand(time(0));
			int random = rand() % 3 + 1;
			player->hurtPlayer(random);
			
			cout << "You were hurt by " << random << " HP";
		}
		default:
			break;
	}
}

consumableType Consumable::getConsumType()
{
	return itemType;
}