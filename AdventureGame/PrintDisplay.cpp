#include "PrintDisplay.h"
#include "CommonGameObjects.h"

#ifndef WIN32
#include <ncurses.h>
#else
#include <condio.h>
#define getch() _getch()
#endif
#include <iostream>
#include <string>
#include <thread>
#include <chrono>


using namespace std;

std::ostringstream PrintDisplay::custom_cout;
std::vector<std::string> PrintDisplay::commandHistory;

void PrintDisplay::flush()
{
    PrintDisplay::common_flush(false);
}

void PrintDisplay::no_effect_flush()
{
    PrintDisplay::common_flush(true);
}

void PrintDisplay::common_flush(bool forceNormal)
{
        string str(custom_cout.str());
        if (CommonGameObjects::PAManager == nullptr || forceNormal == true) // If we are printing without PA, just print the string
        {
            #ifndef WIN32
            refresh();
            printw("%s",str.c_str());
            refresh();
            #else
            std::cout << str << std::flush;
            #endif
            
            custom_cout.str("");
            return;
        }

        if (CommonGameObjects::PAManager->isThePlayerHigh() == false)
        {
            #ifndef WIN32
            refresh();
            printw("%s",str.c_str());
            refresh();
            #else
            std::cout << str << std::flush;
            #endif
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
            #ifndef WIN32
            refresh();
            printw("%s",str.c_str());
            refresh();
            #else
            std::cout << str << std::flush;
            #endif
        }
        // Clear the stringstream
        custom_cout.str("");
}

string PrintDisplay::inputValidation(bool noHistory)
{
    string command;
    int indexOfHistory = -1;
    char ch = 0; // The character the user entered.
    int interator = -1;
    // The following is complicated. Happy reading!
    while (ch != '\n')
    {
        // The user types a character
        ch = getch();
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
            PrintDisplay::custom_cout << "\b";
            PrintDisplay::no_effect_flush();

            cout<< "\0337" << std::flush;//Save cursor Position
            PrintDisplay::custom_cout << "\r"; 
            PrintDisplay::no_effect_flush();

            #ifndef WIN32
            clrtobot();
            #else
            cout << "\033[0J" << std::flush;
            #endif            

            PrintDisplay::custom_cout << "\r"; 
            PrintDisplay::no_effect_flush();

            PrintDisplay::custom_cout << "> " << command;
            PrintDisplay::no_effect_flush();
            cout << "\0338"<< std::flush; //Save cursor Position
            // Delay the terminal for about 10ms
            this_thread::sleep_for(chrono::milliseconds(30));
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
            if (noHistory == true)
            {
                cout << '\a' << std::flush;
                continue;
            }
            if (PrintDisplay::commandHistory.size() == 0)// No commands, ignore
            {
                // Bell, should play sound.
                cout << '\a' << std::flush;
                continue;
            }
            else if (PrintDisplay::commandHistory.size()-1 == indexOfHistory) // End of history, ignore
            {
                // Bell, should play sound.
                cout << '\a' << std::flush;
                continue;
            }
            //TODO index bounds check
            command = PrintDisplay::commandHistory[++indexOfHistory];

            // Clear entire line, and reprint command.
            #ifndef WIN32
            PrintDisplay::custom_cout << "\r";
            PrintDisplay::no_effect_flush();
            clrtobot();
            #else
            cout << "\033[0J" << std::flush;
            #endif  
            PrintDisplay::custom_cout << "> " << command;
            PrintDisplay::no_effect_flush();
            interator = command.size()-1;
            continue;
        }
        else if (ch == '\x02') // Down arrow key
        {
            if (noHistory == true)
            {
                cout << '\a' << std::flush;
                continue;
            }
            // If the index is less than or equal to 0
            if (indexOfHistory <= 0)
            {
                if (command.empty() == true) // Empty command, warn user.
                {
                    cout << '\a' << std::flush;
                    indexOfHistory = -1;
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
            #ifndef WIN32
            PrintDisplay::custom_cout << "\r";
            PrintDisplay::no_effect_flush();
            clrtobot();
            #else
            cout << "\033[0J" << std::flush;
            #endif  
            PrintDisplay::custom_cout << "> " << command;
            PrintDisplay::no_effect_flush();
            interator = command.size()-1;
            continue;

        }
        if (command.size() >= 30 && ch != '\n')
        {
            cout << '\a' << std::flush;
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
    return command;
}



