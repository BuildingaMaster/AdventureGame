#pragma once

#include <string>

#include "Location.h"
#include "Inventory.h"
#include "PlayerActions.h"


class ContextParser
{
    private:
        Location* locationMGR;
        Inventory* inventoryMGR;
        PlayerActions* playerActionsMGR;
    public:
        /// @brief Reads a command from the user than breaks it appart.
        bool interpretCommand(std::string);
        ContextParser(Location*, Inventory*, PlayerActions*);
};