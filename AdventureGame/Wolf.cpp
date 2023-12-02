#include "Wolf.h"

Wolf::Wolf() : NPC("wolf", 3, true) {}

void Wolf::attackPlayer()
{
    this->AttackAtPlayer(1, true, false, 1111);
}

bool Wolf::recieveAttack()
{
   return this->PlayerAttacksMe("OOOOOOOOOOOOOOOOOOOO#####", 50);
}