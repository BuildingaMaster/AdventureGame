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
        // itemMap[i].insert(itemMap[i].begin(), Consumable(item,weight)) i = room number 
        if (x.second->hasAttribute(x.second->APPLE_TREE_IN_ROOM))
        {
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(apple, 1));
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(apple, 1));
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(apple, 1));
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(apple, 1));
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(apple, 1));
        }
        if (x.second->hasAttribute(x.second->MUSHROOMS_IN_ROOM))
        {
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(mushroom, 1)); //add mushroom
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(mushroom, 1)); //add mushroom
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(mushroom, 1)); //add mushroom
            itemMap[x.first].insert(itemMap[x.first].begin(), new Consumable(mushroom, 1)); //add mushroom
        }
    }
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

// The item map, shared.
map<int, vector<Item*>> Inventory::itemMap;


bool Inventory::discardItem(vector<string> args, int roomID)
{
    string itemArg = args[1];
    int count = 0;
    bool multiSelect = false;
    bool found = false;

    // MultiSelect, if all or any is listed
    if (itemArg == "all" || itemArg == "every")
    {
        itemArg = args[2];
        multiSelect = true;
    }

    // MultiSelect, if plural
    if (itemArg[itemArg.size() - 1] == 's')
    {
        itemArg.erase(itemArg.size() - 1, 1);
        multiSelect = true;
    }

    for (int i = 0; i<currentInventory.size(); i++)
    {
        if (currentInventory[i]->getItemName() == itemArg)
        {
            itemMap[roomID].push_back(currentInventory[i]);
            itemMap[roomID][itemMap[roomID].size() - 1]->setState(inWorld);
            if (multiSelect == false)
            {
                currentInventory.erase(currentInventory.begin()+i);
                cout << "\nYou " << args[0] << " the " << itemArg << "!\n";
                return true;
            }
            count=count+1;
            found = true;
        }
    }
    if (found)
    {
        for (int total = count; total!=0; total--)
        {
            for (int i = 0; i<currentInventory.size(); i++)
            {
                if (currentInventory[i]->getItemName() == itemArg)
                {
                    currentInventory.erase(currentInventory.begin()+i);
                    break;
                }
            }
        }
        cout << "\nYou " << args[0] << " " << count << " " << itemArg;
        if (count > 1)
        {
            cout << "s";
        }
        cout << "!\n";
        return true;
    }
    // else
    cout << "\nYou don't have any " << itemArg << "s.\n";
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
    bool multiSelect = false;
    bool found = false;

    string itemArg = args[1];
    int count = 0;
    if (itemArg == "all" || itemArg == "every")
    {
        itemArg = args[2];
        multiSelect = true;
    }
    
    if (itemArg[itemArg.size() - 1] == 's')
    {
        itemArg.erase(itemArg.size() - 1, 1);
        multiSelect = true;
    }

    if (args[0] == "pick" || args[0] == "grab" || args[0] == "take")
    {

        for (int i = 0; i < itemMap[roomID].size(); i++) // Grab pass
        {
            if (itemMap[roomID][i]->getItemName() == itemArg)
            {
                addItem(itemMap[roomID][i]);
                if (multiSelect == false)
                {
                    itemMap[roomID].erase(itemMap[roomID].begin() + i); // Remove pass
                    cout << "\nYou have taken the " << itemArg <<".\n";
                    return true;
                }
                found = true;
                count = count + 1;
                /*
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
                itemMap[roomID].erase(itemMap[roomID].begin()+i);
                cout << "\nYou pick an " << args[1] << " from the tree.\n";
                return true;
                */
            }
        }
        if (found)
        {
            for (int total = count; total!=0; total--)
            {
                for (int i = 0; i < itemMap[roomID].size(); i++) //delete pass
                {
                    itemMap[roomID].erase(itemMap[roomID].begin() + i);
                    break;
                }        
            }
            cout << "\nYou took " << count << " " << itemArg;
            if (count > 1)
            {
                cout << "s";
            }
            cout << "!\n";
            return true;
        }
        else
        {
            cout << "\nThere are no " << itemArg << "s for you to " << args[0] << "!\n";
            return false;
        }
    }
    else if (args[0] == "eat" || args[0] == "consume")
    {
        for (int i = 0; i < currentInventory.size(); i++)
        {
            // Is the item in the inventory
            if (currentInventory[i]->getItemName() == itemArg)
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
        cout << "\nYou don't have any " << itemArg << "s.\n";
        return false;
    }
    else if ( args[0] == "drop" || args[0] == "throw" || args[0] == "discard")
    {
        discardItem(args, roomID);
    }
    
    return true;
}