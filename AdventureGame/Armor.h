#pragma once
#include "Item.h"
#include "PlayerActions.h"
#include "PrintDisplay.h"

class Armor : public Item
{
#ifdef GTESTING
public:
#else
private:
#endif
	armorType itemType;
public:
	armorType getArmorType();
	Armor(armorType, double);
	void equip(PlayerActions*);
	virtual void action() {}//does nothing
	~Armor();
	Armor();
};