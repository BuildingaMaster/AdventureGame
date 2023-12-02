#pragma once
#include "NPC.h"
class Knight :
    public NPC
{
public:
    /// @brief Create a Knight object (4 health, hostile)
    Knight();
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed() {};
    virtual void attackPlayer();
    virtual bool recieveAttack();
    virtual ~Knight() = default;
};

