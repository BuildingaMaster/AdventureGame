#pragma once
#include <random>

#include "Item.h"
#include "PlayerActions.h"
#include "PrintDisplay.h"

// Fists, Boomerang, Legendary Sword, and the Fake Legendary Sword
enum weaponType { fists, boomerang, legendarysword, chinesesword };

class Weapon : public Item
{
#ifdef GTESTING
public:
#else
private:
#endif
	weaponType itemType;
	int damageAmount;
public:
	weaponType getWeaponType();
	Weapon(weaponType, double);
    Weapon();
	int getDamageAmount();

	virtual ~Weapon() = default;
	virtual void action();
};

class WeaponManager
{
public:
    static bool swapWeapon(Weapon*);
    static Weapon* getCurrentWeapon();
	static void swapWeapontoFists();
    static bool init();
	static void deinit();
	//  15% chance of a bad toss, even if OK.
	static std::uniform_int_distribution<int> dist;   
	static std::random_device rd;
#ifdef GTESTING
public:
#else
private:
#endif
	static Weapon* fistsStandard;
    static Weapon* currentWeapon; 
};

