#include "Knight.h"
#include "PrintDisplay.h"

Knight::Knight() : NPC("knight", 4, true) { ; }

void Knight::attackPlayer()
{
    this->AttackAtPlayer(4, true, false, 800);
}

bool Knight::recieveAttack()
{
   return this->PlayerAttacksMe("OOOOOOOOOOOOOOOOOOOO###", 30);
}

void Knight::printIAmDeadMessage()
{
    PrintDisplay::custom_cout << "\nThis knight has already fallen.\nProceed in the castle.\n";
    PrintDisplay::flush();
}