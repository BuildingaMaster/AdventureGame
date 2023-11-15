#include "PrintDisplay.h"
#include "CommonGameObjects.h"

#ifndef WIN32
#include <ncurses.h>
#else
#include <condio.h>
#define getch() _getch()
#endif

using namespace std;

std::ostringstream PrintDisplay::custom_cout;

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
            printw("%s",str.c_str());
            refresh();
            #else
            std::cout << str << std::flush;
            #endif
        }
        // Clear the stringstream
        custom_cout.str("");
}



