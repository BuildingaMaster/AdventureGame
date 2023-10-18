#include "Item.h"
#include <iostream>

using namespace std;

Item::Item()
{
    weight = 0.0;
}

Item::Item(itemType initType)
{
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

void Item::print()
{
    cout << endl <<"we win";
}

void Item::setWeight(double initWeight)
{
    weight = initWeight;
}