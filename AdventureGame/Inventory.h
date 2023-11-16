#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Item.h"
#include "Consumable.h"
#include "PlayerActions.h"

using namespace std;
class Inventory
{
public:
	Inventory(PlayerActions*);
	~Inventory();
	//void addItem(Item toAdd, enum, int);
	void addItem(Item* toAdd);
	/// @brief Discards an item from the inventory to the room
	/// @param args The arguements from CP
	/// @param roomID The room the user is currently in
	/// @return If discarding worked.
	bool discardItem(vector<string> args, int roomID);
	bool processCommand(vector<string> args);
	string inventoryValidCommands = "pick grab take eat consume drop throw discard";
	static map<int, vector<Item*>> itemMap;
	void clearInventory();

#ifdef GTESTING
public:
#else
private:
#endif
	PlayerActions* playerData;
	vector<Item*> currentInventory;
	// This is temporary for POC and should be moved somewhere else.

	//currentInventory[0] = iteminRoom[42][0]
	//iteminRoom.erase(iteminRoom.begin())




	/*
	> eat apple

	
	
	*/
};