#include "Princess.h"

#include <iostream>
#include <string>
#include "PrintDisplay.h"
#include "CommonGameObjects.h"
using namespace std;

Princess::Princess() : NPC("princess", 1, false) {}

bool Princess::rizzTime()
{
    if (this->secondTry == true)
    {
        PrintDisplay::custom_cout << "\nYou have returned to the room of the Princess of Papettia.\n";
    }
    else
    {
        PrintDisplay::custom_cout << "\nAfter your long journey, you finally found the Princess of Papettia.\n";
    }
    
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "\nPrincess:";
    PrintDisplay::no_effect_flush();
    if (this->secondTry == true)
    {
        PrintDisplay::custom_cout << "\n\t\"Why are you still here!?! I thought I told you to leave!\"";
        PrintDisplay::custom_cout << "\n\t\"Doesn't matter, but";
    }
    else
    {
        PrintDisplay::custom_cout << "\n\t\"So,";
    }
    PrintDisplay::custom_cout << " you had to go and kill my new boyfriend, huh?\"";
    PrintDisplay::custom_cout << "\n\t\"Did you really think you would just walk in and simply win me back?\"\n\n";
    PrintDisplay::flush();
    PrintDisplay::custom_cout << "**Time to win her back! What do you say?** \n";
    PrintDisplay::no_effect_flush();    

    PrintDisplay::custom_cout << "Option 1: ";
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "\"Yes.\"\n";
    PrintDisplay::flush();    

    PrintDisplay::custom_cout << "Option 2: ";
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "\"LOVE ME! I'm begging you!\"\n";
    PrintDisplay::flush();

    PrintDisplay::custom_cout << "Option 3: ";
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "*You ignore the Princess*\n";
    PrintDisplay::flush();    
    
    int answer = PrintDisplay::optionParser(3);

    PrintDisplay::custom_cout << "\n";

    if (answer == 1 && !CommonGameObjects::PAManager->isThePlayerHigh())
    {
        PrintDisplay::custom_cout << "Princess:\n\t\"You know me so well!\"\n\tKilling the dragon and my new boyfriend was so hot!\"\n\n";
        PrintDisplay::custom_cout << "You and the Princess begin to embrace.\n";
        PrintDisplay::custom_cout << "You and the Princess reconcile and live happily ever after!\n\n";
        PrintDisplay::custom_cout << "GOOD ENDING\n\n";
        PrintDisplay::no_effect_flush();
        return true;
    }
    else if (answer == 2 || (answer == 1 && CommonGameObjects::PAManager->isThePlayerHigh()))
    {
        PrintDisplay::custom_cout << "Princess:\n\t\"Get your pathetic ass out of my castle!\"\n";
        PrintDisplay::custom_cout << "You:\n\t\"...okay.\"\n\n";
        PrintDisplay::custom_cout << "You run off into the forest as the pain of rejection fills your soul.\n";
        PrintDisplay::custom_cout << "You weep and run as far as you can, never to be seen again.\n\n";
        PrintDisplay::custom_cout << "BAD ENDING\n\n";
        PrintDisplay::no_effect_flush();
        return true;
    }
    else if (answer == 3)
    {
        PrintDisplay::custom_cout << "Princess:\n\t\"If you haven't got the guts to say anything,\n";
        PrintDisplay::custom_cout << "\tthe get your pathetic ass out of my castle!\"\n\n";
        PrintDisplay::no_effect_flush();
        this->secondTry = true;
        return false;
    }
    return false;
}
