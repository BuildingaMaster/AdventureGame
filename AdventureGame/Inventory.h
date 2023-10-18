#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Item.h"
#include "Consumable.h"

using namespace std;
class Inventory
{
public:
	Inventory();
	//void addItem(Item toAdd, enum, int);
	void addItem(Item toAdd);
	bool processCommand(vector<string> args);
	string inventoryValidCommands = "pick grab eat consume ";

private:
	vector<Item> currentInventory;
	// This is temporary for POC and should be moved somewhere else.
	map<int, vector<Item>> itemMap;

	//currentInventory[0] = iteminRoom[42][0]
	//iteminRoom.erase(iteminRoom.begin())




	/*
	> eat apple

	
	
	*/
};