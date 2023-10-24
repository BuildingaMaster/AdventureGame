#include "ContextParser.h"

#include <vector>
#include <string>

using namespace std;

ContextParser::ContextParser(Location* loc, Inventory* inv, PlayerActions* pact)
{
    locationMGR = loc;
    inventoryMGR = inv;
    playerActionsMGR = pact;
}

bool ContextParser::interpretCommand(string unfilteredCmd)
{
    vector<string> formattedCmd;

    string temp = "";
    for (auto &character : unfilteredCmd)
    {
        // Convert the character to lowercase before parsing.
        character = tolower(character);
        if (temp.length() > 0 && character == ' ')
        {
            // Add the string to the vector.
            formattedCmd.push_back(temp);
            temp.clear();
            continue;
        }
        else if (character == ' ')
        {
            // The string has an extra space, don't include it.
            continue;
        }
        temp.push_back(character);
    }

    if (temp.length() > 0)
    {
        formattedCmd.push_back(temp);
        temp.clear();
    }

    // The program will crash if the vector is empty.
    if (formattedCmd.size() == 0)
    {
        return false;
    }

    if (formattedCmd[0].size() < 3)
    {
        cout << "\nI don't know what that is!\n";
        return false;
    }

    // Figure out what command this is for.
    if (locationMGR->locationValidCommands.find(formattedCmd[0]+" ") != std::string::npos)
    {
        return locationMGR->processCommand(formattedCmd);
    }
    else if (inventoryMGR->inventoryValidCommands.find(formattedCmd[0]+" ") != std::string::npos)
    {
        return inventoryMGR->processCommand(formattedCmd);
    }
    else if (playerActionsMGR->playerActionsValidCommands.find(formattedCmd[0]+" ") != std::string::npos)
    {
        return playerActionsMGR->processCommand(formattedCmd);
    }
    cout << "\nI don't know what that is!\n";
    return false;
}