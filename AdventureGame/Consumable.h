#pragma once
#include "Item.h"
#include "PlayerActions.h"
#include <random>

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
	// for good / bad shroom 50 50 chance, static so the same seed isn't created
	// everytime a shroom is eaten
	static std::random_device rd;
	static std::uniform_int_distribution<int> dist;
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

