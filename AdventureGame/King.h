#pragma once
#include "NPC.h"
class King :
    public NPC
{
public:
    /// @brief Create a King object (6 health, hostile)
    King();
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed() {};
    virtual void attackPlayer();
    virtual bool recieveAttack();
    virtual void printIAmDeadMessage();
    virtual ~King() = default;
};

