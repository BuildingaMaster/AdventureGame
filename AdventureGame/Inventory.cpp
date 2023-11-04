#include "Inventory.h"

#include "ContextParser.h"
#include "Item.h"
#include "Consumable.h"
#include "Location.h"

Inventory::Inventory(PlayerActions* pd)
{
    playerData = pd;
    for (auto const& x : locationManager::locationMap)
    {
        itemMap.insert(std::pair<int, vector<Item*>>(x.first, vector<Item*>())); 
    }
    // itemMap[i].insert(itemMap[i].begin(), Consumable(item,weight)) i = room number
    // TODO how do we assign items to west, east rooms?
	itemMap[2].insert(itemMap[2].begin(), new Consumable(mushroom, 1)); //add mushroom
    itemMap[3].insert(itemMap[3].begin(), new Consumable(apple, 1));
    itemMap[3].insert(itemMap[3].begin(), new Consumable(apple, 1));
    itemMap[3].insert(itemMap[3].begin(), new Consumable(apple, 1));
    itemMap[3].insert(itemMap[3].begin(), new Consumable(apple, 1));
    itemMap[3].insert(itemMap[3].begin(), new Consumable(apple, 1));
}

Inventory::~Inventory()
{
    // Delete all dynamic data from map
    for (auto &entry : itemMap)
    {
        for (auto obj : entry.second)
        {
            delete obj;
        }
        entry.second.clear();
    }

    // Delete all dynamic data from inventory
    for (auto x : currentInventory)
    {
        delete x;
    }
    currentInventory.clear();
}

void Inventory::addItem(Item* toAdd)
{
	currentInventory.push_back(toAdd);
	currentInventory[currentInventory.size()-1]->setState(inInventory);
}

map<int, vector<Item*>> Inventory::itemMap;


bool Inventory::discardItem(string method, string item, int roomID)
{
    for (int i = 0; i<currentInventory.size(); i++)
    {
        if (currentInventory[i]->getItemName() == item)
        {
            itemMap[roomID].push_back(currentInventory[i]);
            itemMap[roomID][itemMap.size()-1]->setState(inWorld);
            currentInventory.erase(currentInventory.begin()+i);
            cout << "\nYou " << method << " the " << item << "!\n";
            return true;
        }
    }
    cout << "\nYou don't have a(n) " << item << ".\n";
    return false;
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
            if (itemMap[roomID][i]->getItemName() == args[1])
            {
                // player picks a mushroom
                if (itemMap[roomID][i]->getItemName() == "mushroom" && itemMap[roomID][i]->getType() == consumable)
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
            // Is the item in the inventory
            if (currentInventory[i]->getItemName() == args[1])
            {
                // Is it a consumable?
                if (currentInventory[i]->getType() == consumable)
                {
                    // Is the player already at max health?
                    if (playerData->checkPlayerHealth() == playerData->checkMaxPlayerHealth())
                    {
                        cout << "\nYou already have max health, are you sure you want to eat the " << args[1] <<"?\n";
                        if (ContextParser::yesNoPrompt() == CPResponse::Response::NO)
                        {
                            return true;
                        }
                    }
                    // https://stackoverflow.com/questions/19501838/get-derived-type-via-base-class-virtual-function
                    Consumable& item = dynamic_cast<Consumable&>(*currentInventory[i]);
                    cout << "\nYou eat the " << args[1] << "!\n";
                    item.consume(playerData);
                    delete currentInventory[i];
                    currentInventory.erase(currentInventory.begin()+i);
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
    else if ( args[0] == "drop" || args[0] == "throw" || args[0] == "discard")
    {
        discardItem(args[0], args[1], roomID);
    }
    
    return true;
}