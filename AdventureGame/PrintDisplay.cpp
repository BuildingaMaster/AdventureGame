#include "PrintDisplay.h"
#include "CommonGameObjects.h"

#ifndef _WIN32
#include <ncurses.h>
#include <locale.h>

#else
#include <conio.h>
#define getch() _getwch()
#endif
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <regex>

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
    string temp(str);
    str.clear();
    regex_replace(back_inserter(str),temp.begin(),temp.end(),regex("\\n"),"\n\r");
#endif
    std::cout << str << std::flush;
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
    cout << "\033[0J" << std::flush;
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
        else if (ch == '\x1b' && readCH() == '[') //ANSI escape code, could happen if input is very fast
        {
            ch = readCH();
            isScanCode = true;
        }
#endif

        if (ch == '\b' || ch == '\x7f') // Captured backspace
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

            cout << "\0338"<< std::flush; //Restore cursor Position
            // Delay the terminal for about 10ms
            this_thread::sleep_for(chrono::milliseconds(20));
            continue;
            
        }
#ifdef _WIN32
        else if ((ch == 'D' || ch == 'K') && isScanCode == true) // Left arrow key
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
        else if ((ch == 'C' || ch == 'M') && isScanCode == true) // Right arrow key
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
        else if ((ch == 'A' || ch == 'H') && isScanCode == true) // Up arrow key
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
        else if ((ch == 'B' || ch == 'P') && isScanCode == true) // Down arrow key
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
    PrintDisplay::custom_cout << "\nPress any key to continue . . .";
    PrintDisplay::no_effect_flush();
    readCH();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();
}

bool PrintDisplay::hitScreen(int MAX_RED)
{
    // Tell player how this works.
    PrintDisplay::custom_cout << "Strike with any key when Green!" << '\n';
    PrintDisplay::no_effect_flush();
    
    // Number of lines allowed
    int TOTAL_LINE = 25;
    //int MAX_RED = 20;

    // Pre-write the colors,
    // this prevents the terminal from being overwritten with collor
    for (int i = 0; i<MAX_RED; i++) 
    {
            // Space, then go back
            PrintDisplay::custom_cout << ' ' << '\b';
            PrintDisplay::no_effect_flush();

            // Red Background
            cout << "\033[41m" << std::flush; // Red BG
            PrintDisplay::custom_cout << ' ';
            PrintDisplay::no_effect_flush();

            // No Background
            cout << "\033[0m" << std::flush; // Clear BG
            PrintDisplay::no_effect_flush();
    }
    for (int i = 0; i<(TOTAL_LINE-MAX_RED); i++) 
    {
            // Space, then go back
            PrintDisplay::custom_cout << ' ' << '\b';
            PrintDisplay::no_effect_flush();

            // Bright Green Background 
            cout << "\033[102m" << std::flush; // Bright Green BG
            PrintDisplay::custom_cout << ' ';
            PrintDisplay::no_effect_flush();
            cout << "\033[0m" << std::flush; // Clear BG
            PrintDisplay::no_effect_flush();
    }

    // Add an extra space 
    // Prevents the whole terminal from being colored.
    PrintDisplay::custom_cout << ' ';
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "\r";
    PrintDisplay::no_effect_flush();

    int a = 0;

    // Instead of waiting for the system to get a key press
    // We want to know if a key press happens every ~50ms.
    // If not, it returns nothing (or null)
    nodelay(stdscr, TRUE);

    // If the user doesn't type anything,
    // continue the loop
    while (getch() == ERR) // AKA: The user didn't press a key.
    {
        if (a > (MAX_RED-1)) // Cursor on green
        {
            cout << "\033[102m" << std::flush;
            PrintDisplay::custom_cout << ' ';
            PrintDisplay::no_effect_flush();
            //cout << "\033[0m" << std::flush;
            PrintDisplay::no_effect_flush();
        }

        else // Cursor on red
        {
            cout << "\033[41m" << std::flush;
            PrintDisplay::custom_cout << ' ';
            PrintDisplay::no_effect_flush();
            //cout << "\033[0m" << std::flush;
            PrintDisplay::no_effect_flush();
        }
        a++; // Move to next block
        if (a>TOTAL_LINE-1) // Go back to the start.
        {
            cout << "\033[0m" << std::flush;
            PrintDisplay::custom_cout << "\r";
            PrintDisplay::no_effect_flush();
            a=0;
        }
        this_thread::sleep_for(chrono::milliseconds(50)); // Pause by 50ms
    }
    // Return to the regular character waiting mode.
    nodelay(stdscr, FALSE);

    // Hit marker: on the current space, color the background grey.
    cout << "\033[48;5;252m" << std::flush;
    PrintDisplay::custom_cout << "#";
    PrintDisplay::no_effect_flush();

    // Stop coloring.
    cout << "\033[0m" << std::flush;

    bool hitLanded = false;
    if (a < MAX_RED)
    {
        PrintDisplay::custom_cout << "\nYou MISSED!\n";
        hitLanded = false;
    }
    else
    {
        PrintDisplay::custom_cout << "\nNice hit!\n";
        hitLanded = true;
    } 
    PrintDisplay::no_effect_flush();
    return hitLanded;
}

