#include "Princess.h"

#include <iostream>
#include <string>
#include "PrintDisplay.h"
#include "CommonGameObjects.h"
using namespace std;

Princess::Princess() : NPC("princess", 1, false) { ; }

bool Princess::rizzTime()
{
    if (this->secondTry == true)
    {
        PrintDisplay::custom_cout << "\nYou have returned to the room of the Princess of Papettia, the lovely Florence.\n";
    }
    else
    {
        PrintDisplay::custom_cout << "\nAfter your long journey, you finally found the Princess of Papettia.\n";
    }
    
    PrintDisplay::no_effect_flush();
    PrintDisplay::custom_cout << "\nPrincess Florence:";
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
    PrintDisplay::custom_cout << "*You ignore Princess Florence*\n";
    PrintDisplay::flush();    
    
    int answer = PrintDisplay::optionParser(3);

    PrintDisplay::custom_cout << "\n";

    if (answer == 1 && !CommonGameObjects::PAManager->isThePlayerHigh())
    {
        PrintDisplay::custom_cout << "Princess Florence:\n\t\"You know me so well!\"\n\tKilling the dragon and my new boyfriend was so hot!\"\n\n";
        PrintDisplay::custom_cout << "You and the Princess begin to embrace.\n";
        PrintDisplay::custom_cout << "You and the Princess reconcile and live happily ever after!\n\n";
        PrintDisplay::custom_cout << "GOOD ENDING\n\n";
        PrintDisplay::no_effect_flush();
        return true;
    }
    else if (answer == 2 || (answer == 1 && CommonGameObjects::PAManager->isThePlayerHigh()))
    {
        PrintDisplay::custom_cout << "Princess Florence:\n\t\"Get your pathetic ass out of my castle!\"\n";
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
        PrintDisplay::custom_cout << "\tthen get your pathetic ass out of my castle!\"\n\n";
        PrintDisplay::no_effect_flush();
        PrintDisplay::custom_cout << "She charges towards you!\n";
        if(PrintDisplay::dodgeScreen(1, true, true, 700))
        {
            PrintDisplay::custom_cout << "You got pushed out the window!\n";
            PrintDisplay::custom_cout << "Fortunately, you've landed in the moat!\n";
            PrintDisplay::custom_cout << "However, she knows you cant swim...\n";
            PrintDisplay::no_effect_flush();
            CommonGameObjects::PAManager->hurtPlayer(999999);
            return true;
        }
        PrintDisplay::no_effect_flush();
        this->secondTry = true;
        return false;
    }
    return false;
}

void Princess::attackFailed()
{
    PrintDisplay::custom_cout << "Princess:\n\t\"Are you joking?\"";
    PrintDisplay::custom_cout << "\n\t\"You've come ALL this way to kill me, and you MISS?\"";
    PrintDisplay::custom_cout << "\n\t\"I'll admit exiling you was mercy, which was an obvious mistake.\"";
    PrintDisplay::custom_cout << "\n\t\"But unlike you, I learn from them.\"";
    PrintDisplay::custom_cout << "\n\t\"GUARDS!\"\n\n";

    PrintDisplay::custom_cout << "You turn a see a legion of guards surrounding you.\n";
    PrintDisplay::custom_cout << "Before you could even make a move, you felt a slice on your neck.\n";
    PrintDisplay::no_effect_flush();
    CommonGameObjects::PAManager->hurtPlayer(999999);
}

bool Princess::recieveAttack()
{
   return this->PlayerAttacksMe("OOO#OOO", 20);
}
