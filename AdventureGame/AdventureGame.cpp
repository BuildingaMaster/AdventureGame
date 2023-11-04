// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <istream>

#include "Location.h"
#include "PlayerActions.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
#include "ContextParser.h"
using namespace std;

// Initialize player's inventory object


int main()
{
    if (locationManager::init() == false)
    {
        locationManager::deinit();
        return 1;
    }
    
    locationManager::updateCurrentLocation(locationManager::getCurrentLocation());
    
    PlayerActions playeract;
    Inventory userInventory(&playeract);

    
    string command;
    ContextParser CP(&userInventory,&playeract);
    bool validInput;
    bool stay = true;
    do
    {
        do
        {
            cout << "\nWhat would you like to do?\n> ";
            getline(cin, command);
            // This is temporary, and needs to have CP logic
            if (command == "quit")
            {
                stay =false;
                break;
            }
            validInput = CP.interpretCommand(command);
        } while (validInput == false);
    } while (stay);

    locationManager::deinit();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
