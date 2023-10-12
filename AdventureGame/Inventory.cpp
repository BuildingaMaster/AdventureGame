#include "Inventory.h"

Inventory::Inventory()
{

}

void Inventory::addItem(Item toAdd)
{
	currentInventory.push_back(toAdd);
}

Item Inventory::fetchItem(consumableType toFind)
{
	for (int i = 0; i < currentInventory.size(); i++)
	{
		// if(currentInventory[i].)
		// Stuck here
	}
}