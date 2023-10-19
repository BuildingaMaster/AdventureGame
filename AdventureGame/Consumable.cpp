#include "Consumable.h"

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
	itemName = "apple";
}

Consumable::~Consumable()
{
	
}

void Consumable::consume()
{
	if (itemType == apple)
	{
		// Implement eating apple functionality here!
	}
}

consumableType Consumable::getConsumType()
{
	return itemType;
}