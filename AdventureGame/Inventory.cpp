#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"

Inventory::Inventory()
{
    itemMap.insert(std::pair<int, vector<Item>>(0, vector<Item>()));
    itemMap[0].insert(itemMap[0].begin(), Item(consumable));
}

void Inventory::addItem(Item toAdd)
{
	currentInventory.push_back(toAdd);
}


bool Inventory::processCommand(vector<string> args)
{
	//TODO 
	if (args[0] == "pick" || args[0] == "grab")
	{
		if (args[1] == "apple")
		{
			if (itemMap[0].size() > 0)
			{
				addItem(itemMap[0][0]);
				itemMap[0].pop_back();
				cout << "\nYou pick an apple from the tree.\n";
			}
			else
			{
				cout << "\nThere is no apple for you to take!\n";
			}
		}
	}

	else if (args[0] == "eat" || args[0] == "consume")
	{
		if (args[1] == "apple")
		{
			for (int i = 0; i < currentInventory.size(); i++)
			{
				if (currentInventory[i].getType() == consumable)
				{
					currentInventory.erase(currentInventory.begin()+i);
					cout << "\nYou eat the apple!\n";
					return true;
				}
			}
			cout << "\nYou don't have an apple.\n";
		}
	}
	return true;
}