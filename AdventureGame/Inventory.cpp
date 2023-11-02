#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Location.h"

Inventory::Inventory()
{
    for (auto const& x : locationManager::locationMap)
    {
        itemMap.insert(std::pair<int, vector<Item>>(x.first, vector<Item>())); 
    }
    // itemMap[i].insert(itemMap[i].begin(), Consumable(item,weight)) i = room number
    // TODO how do we assign items to west, east rooms?
	itemMap[2].insert(itemMap[2].begin(), Consumable(mushroom, 1)); //add mushroom
    itemMap[3].insert(itemMap[3].begin(), Consumable(apple, 1));
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
        cout << "\nIt's not clear what you want to " << args[0] << ".\n";
        return false;
    }

    int roomID = locationManager::getCurrentLocation()->getLocationID();

    if (args[0] == "pick" || args[0] == "grab")
    {
        for (int i = 0; i < itemMap[roomID].size(); i++) //We are assuming 0 is the current room.
        {
            if (itemMap[roomID][i].getItemName() == args[1])
            {
                // player picks a mushroom
                if (itemMap[roomID][i].getItemName() == "mushroom" && itemMap[roomID][i].getType() == consumable)
                {
                    addItem(itemMap[roomID][i]);
                    itemMap[roomID].erase(itemMap[roomID].begin()+i);
                    cout << "\nYou pick a " << args[1] << " from the ground.\n";
                    return true;
                }
                // player picks an apple
                addItem(itemMap[roomID][i]);
                itemMap[roomID].erase(itemMap[roomID].begin() + i);
                cout << "\nYou pick an " << args[1] << " from the tree.\n";
                return true;
            }
        }
        cout << "\nThere is no " << args[1] << " for you to " << args[0] << "!\n";
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
                    cout << "\nYou eat the " << args[1] << "!\n";
                    return true;
                }
                else
                {
                    cout << "\nYou can't eat that!\n";
                    return false;
                }
            }
        }
        cout << "\nYou don't have a(n) " << args[1] << ".\n";
        return false;
    }
    return true;
}