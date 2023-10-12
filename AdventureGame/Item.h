#pragma once

enum itemState { inWorld, inInventory };

class Item
{
public:
   
    Item(itemState);
    void print();
    void setWeight(double);
    itemState getState();
    void setState(itemState);
private:
    itemState currentState;
    double weight;
};

