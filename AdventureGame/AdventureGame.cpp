// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <istream>
#include <ctime>
#include <random>
#include <stdio.h>

#include <thread>
#include <chrono>

#ifndef WIN32
#include <ncurses.h>
#else
#include <condio.h>
#define getch() _getch()
#endif

#include "Location.h"
#include "PlayerActions.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
#include "ContextParser.h"

#include "CommonGameObjects.h"
#include "NPC.h"
using namespace std;

// Initialize player's inventory object

#include "PrintDisplay.h"

int main()
{    
    #ifndef WIN32
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    scrollok(stdscr, TRUE);
    cout << "\033[?47l"<<flush; // Normal Screen Buffer
    cout << "\033[?20l"<<flush; // New line
    cout << "\033[?2006h"<<flush;
    #endif

    srand(time(0));
    if (locationManager::init() == false || NPCManager::init() == false)
    {
        locationManager::deinit();
        return 1;
    }

    // Print the first description, and verify we are in the first room
    locationManager::updateCurrentLocation(locationManager::getCurrentLocation());
    
    PlayerActions playeract;
    CommonGameObjects::PAManager = &playeract;

    Inventory userInventory(&playeract);
    CommonGameObjects::INManager = &userInventory;
    BaseHealth check;
    
    string command;
    ContextParser CP(&userInventory,&playeract);
    bool validInput;
    bool stay = true;
    int indexOfHistory;
    do
    {
        do
        {
            indexOfHistory = -1; // The index the history is on.
            if (playeract.thePlayerIsDead())
            {
                PrintDisplay::custom_cout << "\nYOU DID NOT SURVIVE!\n";
                PrintDisplay::no_effect_flush();
                if (!playeract.playAgain())
                {
                    stay = false;
                    break;
                }
            }
            PrintDisplay::custom_cout << "\nWhat would you like to do?\n> ";
            PrintDisplay::no_effect_flush();
            command = PrintDisplay::inputValidation();

            /*#ifndef WIN32
            char ch = 0; // The character the user entered.
            int interator = -1;
            // The following is complicated. Happy reading!
            while (ch != '\n')
            {
                // The user types a character
                ch = getch();
    
                // Delay the terminal for about 10ms
                this_thread::sleep_for(chrono::milliseconds(10));
                if (ch == '\xff') // Bad character, ignore.
                {
                    continue;
                }

                if (ch == '\x7f') // Captured backspace
                {
                    if (interator == -1)
                    {
                        continue;
                    }                  
                    command.erase(command.begin()+(interator)); 
                    interator--;
                    cout << "\033[2K\r"<<flush;
                    PrintDisplay::custom_cout << "> " << command;
                    PrintDisplay::no_effect_flush();
                    for (int a = command.size()-2; a>=interator; a--)
                    {
                        PrintDisplay::custom_cout << '\b';
                        PrintDisplay::no_effect_flush();
                    }
                    continue;
                }
                else if (ch == '\x04') // Left arrow key
                {
                    // Ignore if at the start of the string.
                    if (interator == -1)
                    {
                        continue;
                    }
                    // Move cursor back.
                    ch = '\b';
                    PrintDisplay::custom_cout << ch;
                    PrintDisplay::no_effect_flush();
                    interator--;
                    continue;
                }
                else if (ch == '\x05') // Right arrow key
                {
                    // Ignore if at the end of the string.
                    if (interator == command.size() -1)
                    {
                        continue;
                    }
                    // "move" cursor to right
                    // Aka, overwrite letter at new position.
                    PrintDisplay::custom_cout << command[++interator];
                    PrintDisplay::no_effect_flush();
                    continue;
                }
                else if (ch == '\x03') // Up arrow key
                {
                    if (commandHistory.size() == 0)// No commands, ignore
                    {
                        // Bell, should play sound.
                        cout << '\a' <<flush;
                        continue;
                    }
                    else if (commandHistory.size()-1 == indexOfHistory) // End of history, ignore
                    {
                        // Bell, should play sound.
                        cout << '\a' <<flush;
                        continue;
                    }
                    //TODO index bounds check
                    command = commandHistory[++indexOfHistory];

                    // Clear entire line, and reprint command.
                    cout << "\033[2K\r"<<flush;
                    PrintDisplay::custom_cout << "> " << command;
                    PrintDisplay::no_effect_flush();
                    interator = command.size()-1;
                    continue;
                }
                else if (ch == '\x02') // Down arrow key
                {
                    // If the index is less than or equal to 0
                    if (indexOfHistory <= 0)
                    {
                        if (command.empty() == true) // Empty command, warn user.
                        {
                            cout << '\a' <<flush;
                            indexOfHistory = -1;
                            continue;
                        }
                        command="";
                    }
                    else
                    {
                        // Get the next recent command in history.
                        command = commandHistory[--indexOfHistory];
                    }
                    // Clear entire line, and reprint command.
                    cout << "\033[2K\r" << flush;
                    PrintDisplay::custom_cout << "> " << command;
                    PrintDisplay::no_effect_flush();
                    interator = command.size()-1;
                    continue;

                }

                if (ch != '\n') // Ignore all new lines, acts as return.
                {
                    PrintDisplay::custom_cout << ch;
                }

                // Insert character to command.
                command.insert(command.begin()+(++interator),ch);
                
                // If the cursor is not the end of the string...
                // incert the character at the string.
                // AKA: print character, then print the rest of the string.
                int temp = interator;
                bool checkMove = temp<(command.size()-1);
                int move_count = -1;

                // While we are not at the end of the spring:
                while (temp<(command.size()-1))
                {
                    PrintDisplay::custom_cout << command[++temp];
                    PrintDisplay::no_effect_flush();
                    move_count++;
                }
                // Return cursor to original position if needed.
                if (checkMove && ch != '\n')
                {
                    for (;move_count>=0;move_count--)
                    {
                        PrintDisplay::custom_cout << '\b';
                        PrintDisplay::no_effect_flush();
                    }
                }
                PrintDisplay::no_effect_flush();

                // If the user types in a new line
                // AKA: submit command
                if (ch == '\n')
                {
                    // Print the new line
                    PrintDisplay::custom_cout << ch;
                    PrintDisplay::no_effect_flush();
                    // Print carriage return.
                    PrintDisplay::custom_cout << "\r";
                    PrintDisplay::no_effect_flush();
                }
                PrintDisplay::no_effect_flush();
            }
            // Remove the new line, we don't want it.
            command.replace(command.find('\n'),1,"");
            
            #else*/
            //getline(cin, command);
            //cin.clear();
            //#endif
            // This is temporary, and needs to have CP logic
            if (command == "quit")
            {
                stay = false;
                break;
            }
            // TODO: how do we restart the game? not make it a harsh exit of the game 
            validInput = CP.interpretCommand(command);
        } while (validInput == false);
        
        // If there is no history, or the most recent command is not the newest one..
        if (PrintDisplay::commandHistory.size() == 0 || PrintDisplay::commandHistory[0] != command)
        {
            // Add it to the history.
            PrintDisplay::commandHistory.insert(PrintDisplay::commandHistory.begin(),command);   
        }
        playeract.decrementMovingHigh();
    } while (stay);

    locationManager::deinit();
    #ifndef WIN32
    endwin();
    #endif    
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
