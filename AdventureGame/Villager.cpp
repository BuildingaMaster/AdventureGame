#include "Villager.h"
#include "PrintDisplay.h"

Villager::Villager() : NPC("villager", 1, false) {}

void Villager::attackPlayer()
{
    this->AttackAtPlayer(1, true, false, 800);
}

bool Villager::recieveAttack()
{
    return this->PlayerAttacksMe("OOOOOOOOO#############", 50);
}

void Villager::printIAmDeadMessage()
{
    PrintDisplay::custom_cout << "\nThis villager has already fallen.\nThe other villagers don't seem to like that.\n";
    PrintDisplay::flush();
}
