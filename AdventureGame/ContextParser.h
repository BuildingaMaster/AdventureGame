#ifndef CONTEXTPARSER_H
#define CONTEXTPARSER_H

#include <string>

#include "Location.h"
#include "Inventory.h"
#include "PlayerActions.h"
#include "PrintDisplay.h"

namespace CPResponse
{
    enum Response{ YES = true, NO = false };
};

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
        /// @brief Displays a standard Yes/No prompt
        /// @return True: yes, false: no
        static bool yesNoPrompt();

};
#endif // !CONTEXTPARSER_H