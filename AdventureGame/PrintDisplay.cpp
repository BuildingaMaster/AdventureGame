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

/// @brief Remove all formatting from the terminal
void effectReset()
{
    PrintDisplay::no_effect_flush();
    cout << "\033[0m" << std::flush;
    PrintDisplay::no_effect_flush();
}

/// @brief Color the background bright red.
void addRedBackground()
{
    cout << "\033[101m" << std::flush;
    PrintDisplay::no_effect_flush();    
}

/// @brief Adds the color before printing the box.
/// @param shouldColor Should the box be colored.
void preDrawCenter(bool shouldColor)
{
    PrintDisplay::no_effect_flush();
    if (shouldColor)
    {
        addRedBackground();
    }    
}

/// @brief preDrawCenter, but adds a few spaces before preDrawing.
/// @param shouldColor Should the box be colored.
void preDrawUpDown(bool shouldColor)
{
    PrintDisplay::custom_cout << "      ";
    preDrawCenter(shouldColor);
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

bool PrintDisplay::hitScreen(string hitBox, int time_to_react)
{
    // The tutorial, only happens when first triggered.
    if (CommonGameObjects::PAManager->checkAndFlipFirstAttack())
    {
        PrintDisplay::custom_cout << "\nTime to attack!\n";

        PrintDisplay::custom_cout << "Wait until the cursor is over ";

        // Made this text have a Green background.
        PrintDisplay::no_effect_flush();
        cout << "\033[102m" << std::flush; // BG Green
        //PrintDisplay::no_effect_flush();
        PrintDisplay::custom_cout << "the green bar";
        PrintDisplay::no_effect_flush();
        cout << "\033[0m" << std::flush; // BG None
        PrintDisplay::custom_cout << " to attack.\n";

        PrintDisplay::custom_cout << "When that happens, press any key to launch your attack!\n";

        PrintDisplay::custom_cout << "\nIf your cursor is on a ";

        // Made this text have a Red background with white-ish text.
        PrintDisplay::no_effect_flush();
        cout << "\033[41m" << std::flush; // BG Red
        cout << "\033[37m" << std::flush; // FG White
        PrintDisplay::custom_cout << "red tile";
        PrintDisplay::no_effect_flush();
        cout << "\033[0m" << std::flush;  // BG+FG None

        PrintDisplay::custom_cout << ", you missed, and will be vulnerable.\n";
        PrintDisplay::custom_cout << "Good luck, and don't die on the first hit!\n";
        PrintDisplay::pause();
    }
    
    // Tell player how this works.
    PrintDisplay::custom_cout << "Strike with any key when Green!" << '\n';
    PrintDisplay::no_effect_flush();
    
    // Pre-write the colors,
    // this prevents the terminal from being overwritten with collor
    // Number of lines allowed
    int TOTAL_LINE = hitBox.size();

    for (auto &c : hitBox)
    {
        // Space, then go back
        PrintDisplay::custom_cout << ' ' << '\b';
        PrintDisplay::no_effect_flush();
        switch (c)
        {
            case '#':
            {
                cout << "\033[102m" << std::flush; // Bright Green BG
                break;
            }
            default:
            {
                cout << "\033[41m" << std::flush; // Red BG
                break;
            }
        }
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

    int cursorOnColumn = 0;

    // Instead of waiting for the system to get a key press
    // We want to know if a key press happens every ~50ms.
    // If not, it returns nothing (or null)
#ifndef _WIN32
    nodelay(stdscr, TRUE);
#endif

    // If the user doesn't type anything,
    // continue the loop
#ifndef _WIN32

    while (getch() == ERR) // AKA: The user didn't press a key.
#else
    while(!_kbhit()) // AKA: The user didn't press a key.
#endif
    {
        if (hitBox[cursorOnColumn] == '#') // Cursor on green
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
        cursorOnColumn++; // Move to next block
        if (cursorOnColumn>TOTAL_LINE-1) // Go back to the start.
        {
            cout << "\033[0m" << std::flush;
            PrintDisplay::custom_cout << "\r";
            PrintDisplay::no_effect_flush();
            cursorOnColumn=0;
        }
        this_thread::sleep_for(chrono::milliseconds(time_to_react)); // Pause by 50ms
    }
#ifndef _WIN32
    // Return to the regular character waiting mode.
    nodelay(stdscr, FALSE);
#else 
    // Get the character, but ignore it.
    // If not done, a double input would occur.
    getch();
#endif

    // Hit marker: on the current space, color the background grey.
    cout << "\033[48;5;252m" << std::flush;
    PrintDisplay::custom_cout << "#";
    PrintDisplay::no_effect_flush();

    // Stop coloring.
    cout << "\033[0m" << std::flush;

    bool hitLanded = false;
    if (hitBox[cursorOnColumn] != '#')
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

bool PrintDisplay::dodgeScreen()
{
    char ch = 0;
    bool upRed = true;
    bool downRed = false;
    bool leftRed = false;
    bool rightRed = false;

    // How to dodge
    if (CommonGameObjects::PAManager->checkAndFlipFirstDodge() == true) // User never dodged before.
    {
        PrintDisplay::custom_cout << "\nThe enemy fights back!\n";
        PrintDisplay::custom_cout << "Don't worry, you can dodge attacks, but you need to be quick.\n\n";
        PrintDisplay::custom_cout << "When this box appears:\n";
        PrintDisplay::no_effect_flush();

        PrintDisplay::printMoveBox(false,false,false,false); // Just an empty box. 
        
        PrintDisplay::custom_cout << "\nPress any arrow key to dodge the attack.\n";
        PrintDisplay::custom_cout << "However, If the box is colored ";

        PrintDisplay::no_effect_flush();
        cout << "\033[91m" << std::flush;
        PrintDisplay::no_effect_flush();    

        PrintDisplay::custom_cout << "red";
        effectReset();

        PrintDisplay::custom_cout << ", don't dodge in that direction!\n";
        PrintDisplay::custom_cout << "Otherwise, you'll get hit by the enemy.\n";

        PrintDisplay::custom_cout << "Good luck, and don't die on the first hit!\n";
        PrintDisplay::pause();
    }


    // Instead of waiting for the system to get a key press
    // We want to know if a key press happens every ~50ms.
    // If not, it returns nothing (or null)
#ifndef _WIN32
    nodelay(stdscr, TRUE);
#endif

    PrintDisplay::custom_cout << "The enemy prepares their attack...\n";
    PrintDisplay::no_effect_flush();

    this_thread::sleep_for(chrono::milliseconds(rand() % 1400 + 800)); // Pause by 50ms


    PrintDisplay::custom_cout << "THE ENEMY ATTACKS ";
    int attackedat = 0;
    switch (rand() % 3)
    {
        case 0:
        {
            downRed = true;
            attackedat = 0;
            PrintDisplay::custom_cout << "TOWARDS YOU!!!";
            break;
        }
        case 1:
        {
            leftRed = true;
            attackedat = 1;
            PrintDisplay::custom_cout << "TO THE LEFT!!!";
            break;
        }
        case 2:
        {
            rightRed = true;
            attackedat = 2;
            PrintDisplay::custom_cout << "TO THE RIGHT!!!";
            break;
        }
    }
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();
    PrintDisplay::printMoveBox(upRed, downRed, leftRed, rightRed);


    // If the user doesn't type anything,
    // continue the loop
    chrono::milliseconds initTime = chrono::duration_cast< chrono::milliseconds >(
        chrono::system_clock::now().time_since_epoch()
    );
    initTime += chrono::milliseconds(1111);


#ifndef _WIN32
    flushinp();
    while ((ch = readCH()) && ch == ERR && initTime >= chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch())); // AKA: The user didn't press a key.
#else
    // Windows doesn't really have a way to flush anything from readCH().
    // But we can see if the keyboard was hit when the thread was paused,
    // And manually remove characters by reading/ignoring them.
    while (_kbhit())
    {
        readCH();
    }
    while(!_kbhit() && initTime >= chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch())); // AKA: The user didn't press a key.
#endif

// Times up or user entered a key.

#ifdef _WIN32
    // Get the character, if there is one.
    if (_kbhit() == true) 
    {
        ch = readCH(); //Get Scan code
    }

    if (ch == -32) // Not a arrow key.
    {
        ch = readCH(); // Get Key
    }
    // For some reason, readCH DOES return ANSI escape codes for some reason.
    // Maybe it has something to do with _kbhit()?
    else if (ch == '\x1b' && readCH() == '[') //ANSI escape code
    {
        ch = readCH();
    }
    else
    {
        ch = 0; // Did not press a valid key dodge failed.
    }
    
#else 
    // Return to the regular character waiting mode.
    nodelay( stdscr, FALSE);
#endif


// Where did the player dodge to?
#ifdef _WIN32
    if (( ch == 'D' || ch == 'K') && attackedat != 1) // Left arrow key
#else
    if (ch == '\x04'  && attackedat != 1) // Left arrow key
        
#endif
    {
        PrintDisplay::custom_cout <<"Left arrow key\n";
        PrintDisplay::custom_cout <<"You dodged the attack!\n";
        PrintDisplay::no_effect_flush();
        return true;
    }
#ifdef _WIN32
    else if ((ch == 'C' || ch == 'M') && attackedat != 2) // Right arrow key
#else
    else if (ch == '\x05' && attackedat != 2) // Right arrow key
#endif
    {
        PrintDisplay::custom_cout << "Right arrow key\n";
        PrintDisplay::custom_cout << "You dodged the attack!\n";
        PrintDisplay::no_effect_flush();
        return true;
    }
#ifdef _WIN32
    else if (ch == 'A' || ch == 'H') // Up arrow key
#else
    else if (ch == '\x03') // Up arrow key
#endif
    {
        PrintDisplay::custom_cout << "You moved toward the enemy, and definitely got hit.\n";
        PrintDisplay::no_effect_flush();
        return false;
    }
#ifdef _WIN32
    else if ((ch == 'B' || ch == 'P') && attackedat != 0) // Down arrow key
#else
    else if (ch == '\x02' && attackedat != 0) // Down arrow key
#endif
    {
        PrintDisplay::custom_cout << "Down arrow key\n";
        PrintDisplay::custom_cout << "You dodged the attack!\n";
        PrintDisplay::no_effect_flush();
        return true;
    }

    if (ch == -1 || ch == 0)
    {
        PrintDisplay::custom_cout << "You stood still and took the hit.\n";
    }
    else
    {
        PrintDisplay::custom_cout << "You got hit from the attack!\n";
    }
    PrintDisplay::no_effect_flush();
    return false;
}

void PrintDisplay::printMoveBox(bool upRed, bool downRed, bool leftRed, bool rightRed)
{   
    PrintDisplay::no_effect_flush();

    // Print Up arrow box
    preDrawUpDown(upRed);
    PrintDisplay::custom_cout << u8"\u250C\u2500\u2500\u2500\u2510";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    
    preDrawUpDown(upRed);
    PrintDisplay::custom_cout << u8"\u2502 \u039B \u2502";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    preDrawUpDown(upRed);
    PrintDisplay::custom_cout << u8"\u2502 \u2502 \u2502";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    preDrawUpDown(upRed);
    PrintDisplay::custom_cout << u8"\u2514\u2500\u2500\u2500\u2518";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    // Tops of center boxes
    preDrawCenter(leftRed);
    PrintDisplay::custom_cout << u8"\u250C\u2500\u2500\u2500\u2500\u2510"; // L
    effectReset();

    //preDrawCenter(true);
    PrintDisplay::custom_cout << u8"\u250C\u2500\u2500\u2500\u2510"; // C
    effectReset();

    preDrawCenter(rightRed);
    PrintDisplay::custom_cout << u8"\u250C\u2500\u2500\u2500\u2500\u2510";// R
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    // Middles of center boxes
    preDrawCenter(leftRed);
    PrintDisplay::custom_cout << u8"\u2502<\u2500\u2500 \u2502"; // L
    effectReset();

    //preDrawCenter(true);
    PrintDisplay::custom_cout << u8"\u2502YOU\u2502"; // C
    effectReset();

    preDrawCenter(rightRed);
    PrintDisplay::custom_cout << u8"\u2502 \u2500\u2500>\u2502";// R
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();


    // Lowers of center boxes
    preDrawCenter(leftRed);
    PrintDisplay::custom_cout << u8"\u2514\u2500\u2500\u2500\u2500\u2518";
    effectReset();

    //preDrawCenter(true);
    PrintDisplay::custom_cout << u8"\u2514\u2500\u2500\u2500\u2518";
    effectReset();

    preDrawCenter(rightRed);
    PrintDisplay::custom_cout << u8"\u2514\u2500\u2500\u2500\u2500\u2518";
    effectReset();  
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();



    // Print down arrow box
    preDrawUpDown(downRed);
    PrintDisplay::custom_cout << u8"\u250C\u2500\u2500\u2500\u2510";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    preDrawUpDown(downRed);
    PrintDisplay::custom_cout << u8"\u2502 \u2502 \u2502";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();
    
    preDrawUpDown(downRed);
    PrintDisplay::custom_cout << u8"\u2502 V \u2502";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();

    preDrawUpDown(downRed);
    PrintDisplay::custom_cout << u8"\u2514\u2500\u2500\u2500\u2518";
    effectReset();
    PrintDisplay::custom_cout << "\n";
    PrintDisplay::no_effect_flush();
}
