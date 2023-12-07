#include "Inventory.h"

#include "ContextParser.h"
#include "Item.h"
#include "Consumable.h"
#include "Location.h"

#include "PrintDisplay.h"

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
    clearInventory();
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
                PrintDisplay::custom_cout << "\nYou " << args[0] << " the " << itemArg << "!\n";
                PrintDisplay::flush();
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
        PrintDisplay::custom_cout << "\nYou " << args[0] << " " << count << " " << itemArg;
        if (count > 1)
        {
            PrintDisplay::custom_cout << "s";
        }
        PrintDisplay::custom_cout << "!\n";
        PrintDisplay::flush();
        return true;
    }
    // else
    PrintDisplay::custom_cout << "\nYou don't have any " << itemArg << "s.\n";
    PrintDisplay::flush();
    return false;
}

bool Inventory::processCommand(vector<string> args)
{
    if (args[0] == "inventory" || args[0] == "items")
    {
        listInventory();
        return true;
    }
    if (args.size() == 1)
    {
        PrintDisplay::custom_cout << "\nIt's not clear what you want to " << args[0] << ".\n";
        PrintDisplay::no_effect_flush();
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
                    PrintDisplay::custom_cout << "\nYou have taken the " << itemArg <<".\n";
                    PrintDisplay::flush();
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
                    PrintDisplay::custom_cout << "\nYou pick a " << args[1] << " from the ground.\n";
                    PrintDisplay::flush();
                    return true;
                }
                // player picks an apple
                addItem(itemMap[roomID][i]);
                itemMap[roomID].erase(itemMap[roomID].begin()+i);
                PrintDisplay::custom_cout << "\nYou pick an " << args[1] << " from the tree.\n";
                PrintDisplay::flush();
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
            PrintDisplay::custom_cout << "\nYou took " << count << " " << itemArg;
            if (count > 1)
            {
                PrintDisplay::custom_cout << "s";
            }
            PrintDisplay::custom_cout << "!\n";
            PrintDisplay::flush();
            return true;
        }
        else
        {
            PrintDisplay::custom_cout << "\nThere are no " << itemArg << "s for you to " << args[0] << "!\n";
            PrintDisplay::flush();
            return false;
        }
    }
    else if (args[0] == "eat" || args[0] == "consume")
    {
        if (multiSelect == true)
        {
            PrintDisplay::custom_cout << "\nYou can only eat one " << itemArg << " at a time.\n";
            PrintDisplay::flush();
        }

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
                        PrintDisplay::custom_cout << "\nYou already have max health, are you sure you want to eat the " << itemArg <<"?\n";
                        PrintDisplay::flush();
                        if (ContextParser::yesNoPrompt() == CPResponse::Response::NO)
                        {
                            return true;
                        }
                    }
                    // https://stackoverflow.com/questions/19501838/get-derived-type-via-base-class-virtual-function
                    Consumable& item = dynamic_cast<Consumable&>(*currentInventory[i]);
                    PrintDisplay::custom_cout << "\nYou eat the " << itemArg << "!\n";
                    item.consume(playerData);
                    delete currentInventory[i];
                    currentInventory.erase(currentInventory.begin()+i);
                    return true;
                }
                else
                {
                    PrintDisplay::custom_cout << "\nYou can't eat that!\n";
                    PrintDisplay::flush();
                    return false;
                }
            }
        }
        PrintDisplay::custom_cout << "\nYou don't have any " << itemArg << "s.\n";
        PrintDisplay::flush();
        return false;
    }
    else if ( args[0] == "drop" || args[0] == "throw" || args[0] == "discard")
    {
        discardItem(args, roomID);
    }
    
    return true;
}
void Inventory::clearInventory()
{
    // Delete all dynamic data from inventory
    for (auto x : currentInventory)
    {
        delete x;
    }
    currentInventory.clear();
}

void Inventory::dropAllInventory()
{
    int roomID = locationManager::getCurrentLocation()->getLocationID();
    for (int i = 0; i<currentInventory.size(); i++)
    {
        itemMap[roomID].push_back(currentInventory[i]);
        itemMap[roomID][itemMap[roomID].size() - 1]->setState(inWorld);
    }
    currentInventory.clear();
}

void Inventory::listInventory()
{
    // <item type, quantity>
    map<string, int> tempItemCount;

    if (currentInventory.empty() == true)
    {
        PrintDisplay::custom_cout << "\nYou have no items in the inventory.\n";
        PrintDisplay::no_effect_flush();
        return;
    }

    for (auto item : currentInventory)
    {
        if (tempItemCount.count(item->getItemName()))
        {
            tempItemCount[item->getItemName()]++; 
        }
        else
        {
            tempItemCount.insert(std::pair<string, int>(item->getItemName(), 1));
        }
    }
    PrintDisplay::custom_cout << "\nHere's what you have in your inventory:\n\n";

    for (auto item : tempItemCount)
    {
        PrintDisplay::custom_cout << "- " << item.second << " " << item.first;
        if (item.second > 1)
        {
            PrintDisplay::custom_cout << "s";
        }
        PrintDisplay::custom_cout << "\n";
        PrintDisplay::no_effect_flush();
    }
}
