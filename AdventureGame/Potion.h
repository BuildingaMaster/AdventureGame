#include "Item.h"

enum potionType { strength, mobility, sobriety, teleportation };
class Potion : public Item
{
#ifdef GTESTING
public:
#else
private:
#endif
	potionType itemType;
public:
	potionType getConsumType();
	Potion(potionType, double);
	Potion();
	~Potion();
	virtual void action(); // Does nothing
};

class effectManager
{
#ifdef GTESTING
public:
#else
private:
#endif
    static int strengthTurns;
    static int slowDownTurns;
public:
    static void addStrength();
    static void slowDownTime();
    static void soberUp();
    static void warp();
    static void wearDownSlow();
    static void wearDownStrength();
    static bool attackUpBonus;
    static bool shouldSlowDown;
};

