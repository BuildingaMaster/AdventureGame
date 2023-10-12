#pragma once
#include <iostream>
#include "Item.h"
#include "Consumable.h"
#include <vector>

using namespace std;
class Inventory
{
public:
	void listInventory();

	//void addItem(Item toAdd, enum, int);
	void addItem(Item toAdd)
	{
		// Add item and erase item
	}
	void removeItem(Item toRemove);
	
private:
	vector<Item*> currentInventory;

	//currentInventory[0] = iteminRoom[42][0]
	//iteminRoom.erase(iteminRoom.begin())




	/*
	> eat apple

	
	
	*/
};