#pragma once

#include <string>

#include "Location.h"
#include "Inventory.h"

using namespace std;

class ContextParser
{
    private:
        Location* locationMGR;
        Inventory* inventoryMGR;
    public:
        bool interpretCommand(std::string);
        ContextParser(Location*, Inventory*);
};