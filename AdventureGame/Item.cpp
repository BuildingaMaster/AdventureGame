#include "Item.h"
#include <iostream>

using namespace std;

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