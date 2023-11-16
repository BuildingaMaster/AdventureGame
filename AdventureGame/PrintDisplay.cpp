#include "PrintDisplay.h"

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
            std::cout << str << std::flush;
            custom_cout.str("");
            return;
        }

        if (CommonGameObjects::PAManager->isThePlayerHigh() == false)
        {
            std::cout << str << std::flush;
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
            std::cout << str << std::flush;
        }
        // Clear the stringstream
        custom_cout.str("");
}



