#pragma once
#include "Item.h"
#include "PlayerActions.h"
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
	/// @brief The player can eat the item
	/// @param  player A reference to the PlayerActions object 
	void consume(PlayerActions*);
	~Consumable();
	Consumable();
	virtual void action() {}; // Does nothing
};

