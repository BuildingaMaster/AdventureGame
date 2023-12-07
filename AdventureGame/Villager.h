#pragma once
#include "NPC.h"

class Villager:
	public NPC
{
    /// @brief Create a Villager object (1 health, not hostile)
	Villager();
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed() {};
    virtual void attackPlayer();
    virtual bool recieveAttack();
    virtual void printIAmDeadMessage();
    virtual ~Villager() = default;
};

