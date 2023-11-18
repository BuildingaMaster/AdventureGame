#include "PrintDisplay.h"
#include "CommonGameObjects.h"

#ifndef _WIN32
#include <ncurses.h>
#else
#include <conio.h>
#define getch() _getwch()
#endif
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#ifdef GTESTING
std::string PrintDisplay::GT_inStr = "";

void PrintDisplay::GT_setString(std::string s)
{
    // Load the string into the "buffer"
    GT_inStr = s;
}
char PrintDisplay::GT_getch()
{
    if (GT_inStr.empty() == false)
    {
        // Get the first character from the "buffer"
        char r = GT_inStr[0];
        // Delete the first character from the "buffer"
        GT_inStr.erase(GT_inStr.begin());
        return r;
    }
    return '\xff'; // No characters left in the "buffer"
}
#endif


using namespace std;

std::ostringstream PrintDisplay::custom_cout;
std::vector<std::string> PrintDisplay::commandHistory;
std::vector<std::string> PrintDisplay::logCommandVector;

char readCH()
{
#ifdef GTESTING
        return PrintDisplay::GT_getch();
#else
        return getch();
#endif
}

void PrintDisplay::flush()
{
    PrintDisplay::common_flush(false);
}

void PrintDisplay::no_effect_flush()
{
    PrintDisplay::common_flush(true);
}

void printToScreen(string str)
{
#if !defined _WIN32 && !defined GTESTING
    refresh();
    printw("%s", str.c_str());
    refresh();
#else
    std::cout << str << std::flush;
#endif
}

void PrintDisplay::common_flush(bool forceNormal)
{
        string str(custom_cout.str());
        if (CommonGameObjects::PAManager == nullptr || forceNormal == true) // If we are printing without PA, just print the string
        {
            printToScreen(str);            
            custom_cout.str("");
            return;
        }

        if (CommonGameObjects::PAManager->isThePlayerHigh() == false)
        {
            printToScreen(str);
        } 
        else
        {
            // Choose 2 random characters then them.
            for (int i = 0; i < (str.size()/6); i++)
            {
                int a = rand() % (str.size());
                int b = rand() % (str.size());
                if ((str[a] == '\n' || str[b] == '\n') || (str[a] == ' ' || str[b] == ' ')) // We keep endlines and spaces as is
                {
                    i--;
                    continue;
                }
                std::swap(str[a], str[b]);
            }
            printToScreen(str);
        }
        // Clear the stringstream
        custom_cout.str("");
}

void clear(const string &command)
{
    PrintDisplay::custom_cout << "\r";
    PrintDisplay::no_effect_flush();
#ifndef _WIN32
    clrtobot();
#else
    cout << "\033[0J" << std::flush;
#endif  
    PrintDisplay::custom_cout << "> " << command;
    PrintDisplay::no_effect_flush();
}

string PrintDisplay::inputValidation(bool noHistory)
{
    string command; // The command that user typed
    int indexOfHistory = -1; // The index of the commandHistory vector
    char ch = 0; // The character the user entered.
    int interator = -1; // Where the cursor should be

    /* The following is VERY complicated. Happy reading! */

    while (ch != '\n') // New lines indincate the end of the input.
    {
        bool isScanCode = false; // For windows Only.

        // The user types a character
        ch = readCH();

        if (ch == '\xff') // Bad character, ignore.
        {
            continue;
        }

#ifdef _WIN32
        else if (ch == -32) // KeyCode incoming. Catch and read next character.
        {
            isScanCode = true;
            ch = readCH(); // Should be a keycode or arrow key
        }
#endif

#ifdef _WIN32
        if (ch == '\b') // Captured backspace
#else
        if (ch == '\x7f') // Captured backspace
#endif
        {
            if (interator == -1) // We are at the start of the prompt, dont do anything.
            {
                continue;
            }                  
            // Erase the character from the string
            command.erase(command.begin()+interator); 
            interator--;

            // Move the cursror by one character
            PrintDisplay::custom_cout << "\b";
            PrintDisplay::no_effect_flush();

            cout << "\0337" << std::flush;//Save cursor Position

            // Clear screen from cursor down
            clear(command);

            cout << "\0338"<< std::flush; //Save cursor Position
            // Delay the terminal for about 10ms
            this_thread::sleep_for(chrono::milliseconds(30));
            continue;
            
        }
#ifdef _WIN32
        else if (ch == 'K' && isScanCode == true) // Left arrow key
#else

        else if (ch == '\x04') // Left arrow key
#endif
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
#ifdef _WIN32
        else if (ch == 'M' && isScanCode == true) // Right arrow key
#else
        else if (ch == '\x05') // Right arrow key
#endif
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
#ifdef _WIN32
        else if (ch == 'H' && isScanCode == true) // Up arrow key
#else
        else if (ch == '\x03') // Up arrow key
#endif
        {
            // Ignore and warn user in case:
            // - History is disabled
            // - There is no history
            // - The inter is at the last element
            if (noHistory == true || PrintDisplay::commandHistory.empty() == true || PrintDisplay::commandHistory.size() - 1 == indexOfHistory)
            {
                // Bell, should play sound, if not, that's fine.
                cout << '\a' << std::flush;
                continue;
            }

            // Set the command to the last command.
            command = PrintDisplay::commandHistory[++indexOfHistory];

            // Clear entire line, and reprint command.
            clear(command);
            interator = command.size()-1;
            continue;
        }
#ifdef _WIN32
        else if (ch == 'P' && isScanCode == true) // Down arrow key
#else
        else if (ch == '\x02') // Down arrow key
#endif
        {
            // History disabled, ignore.
            if (noHistory == true)
            {
                cout << '\a' << std::flush;
                continue;
            }
            // If the index is less than or equal to 0
            if (indexOfHistory <= 0)
            {
                if (command.empty() == true) // Empty command, just warn user.
                {
                    cout << '\a' << std::flush;
                    indexOfHistory = -1; // Do this just in case.
                    continue;
                }
                command="";
                indexOfHistory = -1;
            }
            else
            {
                // Get the next recent command in history.
                command = PrintDisplay::commandHistory[--indexOfHistory];
            }
            // Clear entire line, and reprint command.
            clear(command);
            interator = command.size()-1;
            continue;

        }

        // Mainly for Windows
        // Windows typically uses carriage returns, we're using newlines instead.
        if (ch == '\r')
        {
            ch = '\n';
        }
        
        // If the command string is GEQ the max size,
        // Let the user know.
        // However, if the character is a new line, skip this check.
        if (command.size() >= MAX_COMMAND_SIZE && ch != '\n')
        {
            cout << '\a' << std::flush;
            continue;
        }

        if (ch != '\n') // Ignore all new lines, it acts as return.
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

        // Redundant flush JIC
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
    }
    // At this point, the user wants to submit a command.

    // Remove the new line, we don't want it.
    command.replace(command.find('\n'),1,"");

    // Log the command to the text file, even if invalid.
    PrintDisplay::logCommandVector.insert(PrintDisplay::logCommandVector.begin(), command);
    return command;
}

void PrintDisplay::pause()
{
    PrintDisplay::custom_cout << "\nPress any key to continue...\n";
    PrintDisplay::no_effect_flush();
    getch();
}

