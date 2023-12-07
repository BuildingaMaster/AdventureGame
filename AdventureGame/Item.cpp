#include "Item.h"
#include <iostream>

using namespace std;


std::map<std::string,  std::pair<std::string,std::string>> itemDescription::itemTag = {
    {"apple", std::pair<std::string,std::string>{"You see a faint shimmer of light from the apple in front of you.", "You see a few apples in front of you."}},
    {"mushroom", std::pair<std::string,std::string>{"Looking down, you see a small mushroom that's likely safe to eat.", "Looking down, you see a few wild mushrooms growing."}},
    {"boomerang", std::pair<std::string,std::string>{"You have found a sturdy boomerang, which can be used for a weapon.", "You have found a sturdy boomerang, which can be used for a weapon."}},
    {"legendary sword", std::pair<std::string,std::string>{"You now possess the legendary sword, with great power comes great responsibility.", "You now possess the legendary sword, with great power comes great responsibility."}},
    {"chinese sword", std::pair<std::string,std::string>{"You now possess the chinese sword, cheap is good for now, but it might hurt you down the road.", "You now possess the chinese sword, cheap is good for now, but it might hurt you down the road."}},
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