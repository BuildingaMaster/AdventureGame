#pragma once
#include "Item.h"
// Apples, Mushrooms
enum consumableType { Apple, Mushroom };

class Consumable : protected Item
{
private:
	consumableType itemType;
public:
	consumableType getType();
	Consumable(consumableType, double);
	void consume();
	~Consumable();
};

