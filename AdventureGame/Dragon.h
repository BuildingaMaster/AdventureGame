#pragma once
#include "NPC.h"
class Dragon :
    public NPC
{
public:
    /// @brief Create a dragon object (3 health, hostile)
    Dragon();
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed() {};
    virtual void attackPlayer();
    virtual bool recieveAttack();
    virtual void printIAmDeadMessage();
    virtual ~Dragon() = default;
};

