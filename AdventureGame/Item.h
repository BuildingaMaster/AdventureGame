#pragma once

#include <string>
#include <map>

enum itemState { inWorld, inInventory };
enum itemType { consumable, weapon , armor};

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
    virtual void action() {};  // Does nothing
#ifdef GTESTING
public:
#else
protected:
#endif
    itemType thisType;
    double weight;
    std::string itemName;
#ifdef GTESTING
public:
#else
private:
#endif
    itemState currentState;
};

class itemDescription
{
    public:
        /// @brief The item's description, first singular, second is plural
        static std::map<std::string,  std::pair<std::string,std::string>> itemTag;
};

