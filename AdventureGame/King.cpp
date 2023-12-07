#include "King.h"
#include "PrintDisplay.h"

King::King() : NPC("king", 6, true) { ; }

void King::attackPlayer()
{
    this->AttackAtPlayer(6, true, false, 750);
}

bool King::recieveAttack()
{
    bool temp =  this->PlayerAttacksMe("OOOOOOOOOOOOOOOOOOOOOOO##", 25);
    if (this->isDead())
    {
        PrintDisplay::custom_cout << "King Thadeus: NOOOOO! How could this happen!?\n";
        PrintDisplay::flush();
    }
    return temp;
}

void King::printIAmDeadMessage()
{
    PrintDisplay::custom_cout << "\nYou have already defeated the king. Have mercy. You are one step away from accomplishing you mission.\n";
    PrintDisplay::flush();
}