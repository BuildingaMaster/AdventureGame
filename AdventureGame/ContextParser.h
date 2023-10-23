#ifndef CONTEXTPARSER_H
#define CONTEXTPARSER_H

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
        bool interpretCommand(Location*, std::string);
        ContextParser(Inventory*, PlayerActions*);
};
#endif // !CONTEXTPARSER_H