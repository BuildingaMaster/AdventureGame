#include "Item.h"
#include <iostream>

using namespace std;


std::map<std::string,  std::pair<std::string,std::string>> itemDescription::itemTag = {
    {"apple", std::pair<std::string,std::string>{"You see a faint shimmer of light from the apple in front of you.", "You see a few apples in front of you."}},
    {"mushroom", std::pair<std::string,std::string>{"Looking down, you see a small mushroom that's likely safe to eat.", "Looking down, you see a few wild mushrooms growing."}},
    {"potion of strength", std::pair<std::string,std::string>{"You spot a bottle with a fiery red liquid: the Potion of Strength.", "You spot some bottles that contain fiery red liquid: the Potion of Strength."}},
    {"potion of mobility", std::pair<std::string,std::string>{"You spot a bottle with a bright blue liquid: the Potion of Mobility.", "You spot some bottles that contain a bright blue liquid: the Potion of Mobility."}},
    {"potion of sobriety", std::pair<std::string,std::string>{"You spot a bottle with a dark green liquid: the Potion of Sobriety.", "You spot some bottles that contain a dark green liquid which can cure your ailment."}},
    {"potion of teleportation", std::pair<std::string,std::string>{"You spot a bottle with a royal purple liquid: the Potion of Teleportation.", "You see spot bottles that contain a royal purple liquid, you'll go to where you woke up."}},
    {"leather", std::pair<std::string,std::string>{"In the midst of the debris, you see what looks to be tattered, but usable leather armor.", "There's an old set of leather armor discarded on the ground."}},
    {"chainmail", std::pair<std::string,std::string>{"Shining in the darkness, you see a set of chainmail armor, good as new.", "There's a shiny set of chainmail armor on the ground"}},
    {"iron", std::pair<std::string,std::string>{"In the corner, you see a polished set of iron armor, sure to protect you from anything.", "There's a heavy set of iron armor in the corner."}},
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