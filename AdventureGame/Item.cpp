#include "Item.h"
#include <iostream>

using namespace std;


std::map<std::string,  std::pair<std::string,std::string>> itemDescription::itemTag = {
    {"apple", std::pair<std::string,std::string>{"There is one apple that has fallen from the tree.", "There are a few apples that has fallen from the tree."}},
    {"mushroom", std::pair<std::string,std::string>{"Looking down, you see a small mushroom that's likely safe to eat.", "Looking down, you see a few wild mushrooms growing."}},
};

Item::Item()
{
    weight = 0.0;
    currentState = inWorld;
}

Item::Item(itemType initType)
{
    thisType = initType;
    weight = 0.0;
}

Item::Item(itemType initType, itemState initState)
{
    currentState= initState;
    thisType = initType;
    weight = 0.0;
}

itemType Item::getType()
{
    return thisType;
}

itemState Item::getState()
{
    return currentState;
}

void Item::setState(itemState newState)
{
    currentState = newState;
}

void Item::setWeight(double initWeight)
{
    weight = initWeight;
}

void Item::setItemName(string newName)
{
    itemName = newName;
}

string Item::getItemName()
{
    return itemName;
}