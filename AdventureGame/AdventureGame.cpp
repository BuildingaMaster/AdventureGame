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

#ifndef _WIN32
#include <ncurses.h>
#else
#include <Windows.h>
#endif

#include "Location.h"
#include "PlayerActions.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
#include "ContextParser.h"

#include "CommonGameObjects.h"
#include "NPC.h"
#include "Princess.h"
#include "PrintDisplay.h"


using namespace std;

#ifdef _WIN32
// https://stackoverflow.com/questions/23471873/change-console-code-page-in-windows-c/55171823#55171823
class UTF8CodePage {
public:
    UTF8CodePage() : m_old_code_page(::GetConsoleOutputCP()) {
        ::SetConsoleOutputCP(CP_UTF8);
    }
    ~UTF8CodePage() { ::SetConsoleOutputCP(m_old_code_page); }

private:
    UINT m_old_code_page;
};
#endif // _WIN32


int main()
{    
#ifndef _WIN32
#ifndef GTESTING
    // Curses initalization.
    setlocale(LC_ALL, "");        // Accept all types of characters.
    initscr();                    // Start curses
    keypad(stdscr, TRUE);         // Capture all keys
    noecho();                     // Dont echo keypresses, PrintDisplay handles it.
    scrollok(stdscr, TRUE);       // Scrolling is OK
    cout << "\033[?47l"<<flush;   // Normal Screen Buffer
    cout << "\033[?20l"<<flush;   // New line
    cout << "\033[?2006h"<<flush; // Enable readline newline pasting
#endif //GTESTING
#else
    UTF8CodePage use;
   
    PrintDisplay::no_effect_flush();
    // Set output mode to handle virtual terminal sequences,
    // From https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        cout << "An error occurred, please try rerunning the app." << endl;
        PrintDisplay::pause();
        return false;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        cout << "An error occurred, please try rerunning the app." << endl;
        PrintDisplay::pause();
        return false;
    }

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        cout << "An error occurred, please try rerunning the app." << endl;
        PrintDisplay::pause();
        return false;
    }
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        cout << "An error occurred, please try rerunning the app." << endl;
        PrintDisplay::pause();
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            cout << "An error occurred, please try rerunning the app." << endl;
            PrintDisplay::pause();
            return -1;
        }
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        cout << "An error occurred, please try rerunning the app." << endl;
        PrintDisplay::pause();
        return -1;
    }
#endif
    time_t starttime = time(0);
    srand(starttime);
    if (locationManager::init() == false || NPCManager::init() == false)
    {
        locationManager::deinit();
        PrintDisplay::pause();
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
    do
    {
        do
        {
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

            if (NPCManager::scanForNPC("princess"))
            {
                dynamic_cast<Princess&>(*NPCManager::returnNPC("princess")).rizzTime();
            }

            PrintDisplay::custom_cout << "\nWhat would you like to do?\n> ";
            PrintDisplay::no_effect_flush();

            // Handle Input, 
            command = PrintDisplay::inputValidation(false);

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
        if (PrintDisplay::commandHistory.empty() == true || PrintDisplay::commandHistory[0] != command)
        {
            // Add it to the history.
            PrintDisplay::commandHistory.insert(PrintDisplay::commandHistory.begin(),command);   
        }
        playeract.decrementMovingHigh();
    } while (stay);

    locationManager::deinit();
    NPCManager::deinit();

    // Save the commands to a file.
    ofstream cmdHistoryFile;
    cmdHistoryFile.open("command_history.txt");
    cmdHistoryFile << starttime << "\n";
    for (uint64_t i = 0; i< PrintDisplay::logCommandVector.size(); i++)
    {
        cmdHistoryFile << PrintDisplay::logCommandVector[PrintDisplay::logCommandVector.size()-1-i] << "\n";
    }
    cmdHistoryFile.close();
    PrintDisplay::commandHistory.clear();
    PrintDisplay::logCommandVector.clear();
#ifndef _WIN32
    // End curses control. 
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
