#include "Villager.h"

#include <iostream>
#include <string>
#include "PrintDisplay.h"
#include "Location.h"
#include "CommonGameObjects.h"

Villager::Villager(string vn) : NPC("villager", 1, false) { villagername = vn; }

void Villager::loredump()
{
    if (villagername == "Trevor")
    {
        PrintDisplay::custom_cout << "\nHello traveler, I'm in need of some help.";
        PrintDisplay::custom_cout << "\nThe wolves ate my children and I want revenge.";
        PrintDisplay::custom_cout << "\nI am just a wimpy villager though.";
        PrintDisplay::custom_cout << "\nWould you be willing to slaughter some ?";
        PrintDisplay::custom_cout << "\nI left some armor at the end of the cave.";
        PrintDisplay::custom_cout << "\nFeel free to take it after killing some wolves.";
        PrintDisplay::custom_cout << "\nGo north and you'll find them.\n";
    }
    else if (villagername == "Juan")
    {
        PrintDisplay::custom_cout << "\nYou've got some never coming here.";
        PrintDisplay::custom_cout << "\nAfter what you did,";
        PrintDisplay::custom_cout << "\nI thought you would've been executed.\n";
    }
    else if (villagername == "Eric")
    {
        PrintDisplay::custom_cout << "\nThe princess was a baddie man.";
        PrintDisplay::custom_cout << "\nYou are a fool.\n";
    }
    else if (villagername == "Nick P")
    {
        PrintDisplay::custom_cout << "\nAre you looking at your own wanted poster?";
        PrintDisplay::custom_cout << "\nI could get you arrested right now but";
        PrintDisplay::custom_cout << "\nI ain't no snitch.\n";
    }
    else if (villagername == "Nick T")
    {
        PrintDisplay::custom_cout << "\nKing Thadeus is a snack!";
        PrintDisplay::custom_cout << "\nTen times the man you are!";
        PrintDisplay::custom_cout << "\nI'm glad the princess dumped you!";
        PrintDisplay::custom_cout << "\nYou Hobnocker!\n";
    }
    else if (villagername == "John")
    {
        PrintDisplay::custom_cout << "\nSo you're back to square one, huh?";
        PrintDisplay::custom_cout << "\nJust to think, this could've all been avoided if";
        PrintDisplay::custom_cout << "\nyou didn't sleep with the princess' cousin.\n";
    }
    else if (villagername == "Tiffany")
    {
        PrintDisplay::custom_cout << "\nSo you're back to square one, huh?";
        PrintDisplay::custom_cout << "\nJust to think, this could've all been avoided if";
        PrintDisplay::custom_cout << "\nyou didn't sleep with the princess' cousin.\n";
    }
}

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
