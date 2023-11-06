#include "ContextParser.h"

#include <ctype.h>
#include <vector>
#include <string>
#include <regex>

using namespace std;

ContextParser::ContextParser(Inventory* inv, PlayerActions* pact)
{
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
        // Splitting up the string into multiple smaller strings by checking if they are separated by spaces
        if (temp.length() > 0 && isspace(character))
        {
            // Add the string to the vector.
            formattedCmd.push_back(temp);
            temp.clear();
            continue;
        }
        else if (isspace(character))
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

    if (formattedCmd[0].size() < 2)
    {
        cout << "\nI don't know what that is!\n";
        return false;
    }

    // RegEx query to match the whole world.
    regex exp ("\\b("+formattedCmd[0]+")\\b");

    // Figure out what command this is for.

    if (regex_search(locationManager::getValidCommands(), exp))
    {
        return locationManager::processCommand(formattedCmd);
    }
    else if (regex_search(inventoryMGR->inventoryValidCommands,exp))
    {
        return inventoryMGR->processCommand(formattedCmd);
    }
    else if (regex_search(playerActionsMGR->playerActionsValidCommands,exp))
    {
        return playerActionsMGR->processCommand(formattedCmd);
    }

    cout << "\nI don't know what that is!\n";
    return false;
}

bool ContextParser::yesNoPrompt()
{
    string unfilteredCommand;
    string command;
    bool validInput = false;
    do
    {
        unfilteredCommand = "";
        command = "";
        cout << "\nYes or no?\n> ";
        getline(cin, unfilteredCommand);
        for (auto &character : unfilteredCommand) 
        {
            character = tolower(character);
            if (isspace(character))
            {
                // The string has a space, don't include it.
                continue;
            }
            command.push_back(character);
        }
        if (command == "yes" || command == "y" || command == "ye")
        {
            return CPResponse::Response::YES;
        }
        else if (command == "no" || command == "n")
        {
            return CPResponse::Response::NO;
        }
    } while (true);
}