#pragma once
#include "NPC.h"
class Wolf :
    public NPC
{
public:
    /// @brief Create a wolf object (3 health, hostile)
    Wolf();
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed() {};
    virtual void attackPlayer();
    virtual bool recieveAttack();
    virtual void printIAmDeadMessage();
    virtual ~Wolf() = default;
};

