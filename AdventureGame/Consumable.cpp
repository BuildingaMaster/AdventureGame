#include "Consumable.h"

Consumable::Consumable(consumableType initType, double initWeight)
{
	itemType = initType;
	setWeight(initWeight);
}

Consumable::Consumable()
{
	thisType = consumable;
	itemType = apple;
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