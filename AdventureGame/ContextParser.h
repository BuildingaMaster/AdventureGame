#ifndef CONTEXTPARSER_H
#define CONTEXTPARSER_H

#include <string>

#include "Location.h"
#include "Inventory.h"
#include "PlayerActions.h"


class ContextParser
{
#ifdef GTESTING
    public:
#else
    private:
#endif
        Inventory* inventoryMGR;
        PlayerActions* playerActionsMGR;
    public:
        /// @brief Reads a command from the user than breaks it appart.
        bool interpretCommand(std::string);
        ContextParser(Inventory*, PlayerActions*);
};
#endif // !CONTEXTPARSER_H