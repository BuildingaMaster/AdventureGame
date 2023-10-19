#pragma once
#include "Item.h"
// Apples, Mushrooms
enum consumableType { apple, mushroom };

class Consumable : public Item
{
private:
	consumableType itemType;
public:
	consumableType getConsumType();
	Consumable(consumableType, double);
	void consume();
	~Consumable();
	Consumable();
};

