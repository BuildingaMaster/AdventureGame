#include "Armor.h"

Armor::Armor() : Item(armor)
{
	itemType = none;
	setWeight(1);
	itemName = "none";
}

Armor::Armor(armorType initType, double initweight) : Item(armor)
{
	itemType = initType;
	setWeight(initweight);
	if (initType == leather)
	{
		itemName = "leather";
	}
	else if (initType == chain)
	{
		itemName = "chainmail";
	}
	else if (initType == iron)
	{
		itemName = "iron";
	}
	else
	{
		itemName = "none";
	}
}

armorType Armor::getArmorType()
{
	return itemType;
}

void Armor::equip(PlayerActions* pact)
{
	if (itemType != none)
	{
		pact->changeArmor(itemType);
		PrintDisplay::custom_cout << "\nYou have equipped the " << itemName << " armor!" << endl;
	}
}

Armor::~Armor()
{

}