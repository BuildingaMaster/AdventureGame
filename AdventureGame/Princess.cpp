#include "Princess.h"

#include <iostream>
#include <string>
#include "PrintDisplay.h"
using namespace std;

Princess::Princess() : NPC("princess", 1, false) {}

bool Princess::rizzTime()
{
    PrintDisplay::custom_cout << "Princess: So you had to go and kill my new boyfriend, huh? Did you think you would just win me back?\n\n";
    PrintDisplay::custom_cout << "Time to win her back! What do you say?: \n";
    PrintDisplay::flush();

    PrintDisplay::custom_cout << "1: ";
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "Yes.\n";
    PrintDisplay::flush();    

    PrintDisplay::custom_cout << '2: ';
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "LOVE ME! I'm begging you!\n";
    PrintDisplay::flush();

    PrintDisplay::custom_cout << "3: ";
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "*You ignore the Princess*\n";
    PrintDisplay::flush();    
    
    int answer = PrintDisplay::optionParser(3);

    PrintDisplay::custom_cout << "\\n";

    if (answer == 1)
    {
        PrintDisplay::custom_cout << "Princess: You know me so well! Killing the dragon and my new boyfriend was so hot!\\n";
        PrintDisplay::custom_cout << "You and the Princess begin to embrace.\\n";
        PrintDisplay::custom_cout << "You and the Princess reconcile and live happily ever after!\\n\\n";
        PrintDisplay::custom_cout << "GOOD ENDING\\n\\n";
        return true;
    }
    else if (answer == 2)
    {
        PrintDisplay::custom_cout << "Princess: Get your pathetic ass out of my castle!\\n";
        PrintDisplay::custom_cout << "You: ok.\\n";
        PrintDisplay::custom_cout << "You weep off into the forest as the pain of rejection fills your soul. You weep and run as far as you can";
        PrintDisplay::custom_cout << " never to be seen again.\\n\\n";
        PrintDisplay::custom_cout << "BAD ENDING\\n\\n";
        return true;
    }
    return false;
}
