#include "Knight.h"

Knight::Knight() : NPC("knight", 4, true) {}

void Knight::attackPlayer()
{
    this->AttackAtPlayer(3, true, false, 800);
}

bool Knight::recieveAttack()
{
   return this->PlayerAttacksMe("OOOOOOOOOOOOOOOOOOOO###", 30);
}