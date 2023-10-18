#pragma once

enum itemState { inWorld, inInventory };
enum itemType { consumable, weapon };

class  Item
{
public:
   
    Item(itemType);
    Item();
    void print();
    void setWeight(double);
    itemState getState();
    void setState(itemState);
    itemType getType();
protected:
    itemType thisType;
private:
    itemState currentState;
    double weight;
};

