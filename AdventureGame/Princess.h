#pragma once
#include "NPC.h"
class Princess :
    public NPC
{
public:
    Princess();
    bool rizzTime(); //Triggers ending
    virtual void nothing() {}; // Does nothing
};

