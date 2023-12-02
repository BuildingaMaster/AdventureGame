#pragma once
#include "NPC.h"
class Princess :
    public NPC
{
public:
    Princess();
    /// @brief The ending of the game dialog.
    /// @return True if end game, false if continue.
    bool rizzTime(); //Triggers ending
    virtual void nothing() {}; // Does nothing
    virtual void attackFailed();
    virtual void attackPlayer() {};
    virtual bool recieveAttack();
    virtual ~Princess() = default;

#ifdef GTESTING
public:
#else
private:
#endif
    bool secondTry = false;
};

