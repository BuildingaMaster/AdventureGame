#pragma once

#include <string>

enum itemState { inWorld, inInventory };
enum itemType { consumable, weapon };

class  Item
{
public:
    Item(itemType,itemState);
    Item(itemType);
    Item();
    void setWeight(double);
    itemState getState();
    void setState(itemState);
    itemType getType();
    void setItemName(std::string);
    std::string getItemName();
protected:
    itemType thisType;
    double weight;
    std::string itemName;
private:
    itemState currentState;
};

