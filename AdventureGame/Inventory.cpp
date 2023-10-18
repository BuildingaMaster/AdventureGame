#include "Inventory.h"

Inventory::Inventory()
{
    itemMap.insert(std::pair<int, vector<Item>>(0, vector<Item>()));
    itemMap[0].insert(itemMap[0].begin(), Item());
}

void Inventory::addItem(Item toAdd)
{
	currentInventory.push_back(toAdd);
}

/*Item Inventory::fetchItem(consumableType toFind)
{
	for (int i = 0; i < currentInventory.size(); i++)
	{
		// if(currentInventory[i].)
		// Stuck here
	}
}*/


bool Inventory::processCommand(vector<string> args)
{
	//TODO 
	if (args[0] == "pick")
	{
		if (args[1] == "apple")
		{
			if (itemMap[0].size() > 0)
			{
				addItem(itemMap[0][0]);
				itemMap[0].pop_back();
				cout << "\nYou grab an apple from the tree.\n";
			}
			else
			{
				cout << "\nThere is no apple for you to take!\n";
			}
		}
	}

	else if (args[0] == "pick")
	{
		if (args[1] == "apple")
		{
			//if(userInventory)
		}
	}
	return true;
}