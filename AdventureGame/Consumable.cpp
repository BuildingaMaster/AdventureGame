#include "Consumable.h"

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
		default:
			break;
	}
}

consumableType Consumable::getConsumType()
{
	return itemType;
}