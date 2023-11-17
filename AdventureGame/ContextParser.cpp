#include "ContextParser.h"

#include <ctype.h>
#include <vector>
#include <string>
#include <regex>

#include "PrintDisplay.h"

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
    if (formattedCmd.empty())
    {
        return false;
    }

    if (formattedCmd[0].size() < 2)
    {
        PrintDisplay::custom_cout << "\nI don't know what that is!\n";
        PrintDisplay::no_effect_flush();
        return false;
    }

    if (formattedCmd[0] == "help")
    {
        // Handles the "help" command
        PrintDisplay::custom_cout << "Here is a list of commands that might be useful: \n\n";
        PrintDisplay::no_effect_flush();
        PrintDisplay::custom_cout << "Movements\n move/go/walk/travel north/east/south/west/above/below \n\nActions\n pick/grab/eat/consume apple/mushroom\n hit self\n check health \n\nSurroundings\n visualize,look,see,describe \n\nquit\n";
        PrintDisplay::no_effect_flush();    
        return true;
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

    PrintDisplay::custom_cout << "\nI don't know what that is!\n";
    PrintDisplay::no_effect_flush();
    return false;
}

bool ContextParser::yesNoPrompt()
{
    string command;
    do
    {
        PrintDisplay::custom_cout << "\nYes or no?\n> ";
        PrintDisplay::no_effect_flush();
        command = PrintDisplay::inputValidation(false);
        if (command == "yes" || command == "y" || command == "ye")
        {
            return CPResponse::Response::YES;
        }
        else if (command == "no" || command == "n")
        {
            return CPResponse::Response::NO;
        }
    }while (true);
    /*
    string unfilteredCommand;
    string command;
    bool validInput = false;
    do
    {
        unfilteredCommand = "";
        command = "";
        PrintDisplay::custom_cout << "\nYes or no?\n> ";
        PrintDisplay::no_effect_flush();
        getline(cin, unfilteredCommand);
        cin.clear();
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
    } while (true);*/
}