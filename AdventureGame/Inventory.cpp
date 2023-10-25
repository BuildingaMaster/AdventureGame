#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"

Inventory::Inventory()
{
    itemMap.insert(std::pair<int, vector<Item>>(0, vector<Item>()));
    itemMap[0].insert(itemMap[0].begin(), Consumable(apple,1));
}

void Inventory::addItem(Item toAdd)
{
	currentInventory.push_back(toAdd);
	currentInventory[currentInventory.size()-1].setState(inInventory);
}


bool Inventory::processCommand(vector<string> args)
{
	//TODO Apple is in every room
	if (args.size() == 1)
	{
		cout << "\nIt's not clear what you want to "<< args[0] <<".\n";
		return false;
	}
	if (args[0] == "pick" || args[0] == "grab")
	{
		for (int i = 0; i < itemMap[0].size(); i++) //We are assuming 0 is the current room.
		{
			if (itemMap[0][i].getItemName() == args[1])
			{
				addItem(itemMap[0][i]);
				itemMap[0].erase(itemMap[0].begin()+i);
				cout << "\nYou pick an apple from the tree.\n";
				return true;
			}
		}
		cout << "\nThere is no "<< args[1] <<" for you to "<< args[0] <<"!\n";
		return false;
	}

	else if (args[0] == "eat" || args[0] == "consume")
	{
		for (int i = 0; i < currentInventory.size(); i++)
		{
			if (currentInventory[i].getItemName() == args[1])
			{
				if (currentInventory[i].getType() == consumable)
				{
					currentInventory.erase(currentInventory.begin()+i);
					cout << "\nYou eat the "<< args[1] <<"!\n";
					return true;
				}
				else
				{
					cout << "\nYou can't eat that!\n";
					return false;
				}
			}

		}
		cout << "\nYou don't have an "<< args[1] <<".\n";
		return false;

	}
	return true;
}