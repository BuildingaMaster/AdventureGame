#pragma once
#include <iostream>
#include "Item.h"
#include "Consumable.h"
#include <vector>

using namespace std;
class Inventory
{
public:
	Inventory();

	void listInventory();

	//void addItem(Item toAdd, enum, int);
	void addItem(Item toAdd);
	void removeItem(Item toRemove);
	Item fetchItem(consumableType);

private:
	vector<Item> currentInventory;

	//currentInventory[0] = iteminRoom[42][0]
	//iteminRoom.erase(iteminRoom.begin())




	/*
	> eat apple

	
	
	*/
};