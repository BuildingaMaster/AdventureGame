#pragma once
#include "Item.h"
// Apples, Mushrooms
enum consumableType { apple, mushroom };

class Consumable : public Item
{
#ifdef GTESTING
public:
#else
private:
#endif
	consumableType itemType;
public:
	consumableType getConsumType();
	Consumable(consumableType, double);
	void consume();
	~Consumable();
	Consumable();
	virtual void action() {}; // Does nothing
};

