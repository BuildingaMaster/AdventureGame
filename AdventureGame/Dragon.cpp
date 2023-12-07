#include "Dragon.h"

#include "PrintDisplay.h"

Dragon::Dragon() : NPC("dragon", 5, true) {}

void Dragon::attackPlayer()
{
    this->AttackAtPlayer(3, true, true, 800);
}

bool Dragon::recieveAttack()
{
   return this->PlayerAttacksMe("OOOOOOOOOOOOOOOOOOOOOOOO#", 50);
}

void Dragon::printIAmDeadMessage()
{
    PrintDisplay::custom_cout << "\nYou have already slayed the dragon.\nThere is a secret passage east of here. Do you dare to take it?\n";
    PrintDisplay::flush();
}