#include "Consumable.h"

Consumable::Consumable(consumableType initType, double initWeight)
{
	itemType = initType;
	setWeight(initWeight);
}

Consumable::~Consumable()
{
	
}

void Consumable::consume()
{
	if (itemType == Apple)
	{
		// Implement eating apple functionality here!

		delete this;
	}
}

consumableType Consumable::getType()
{
	return itemType;
}