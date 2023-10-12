// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Location.h"
#include "PlayerActions.h"
#include "StartingRoom.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
using namespace std;

Inventory userInventory;

void getUserInput();

map<int, vector<Item>> itemMap;



void backStory()
{
	cout << "You open your eyes and see you are in the middle of a forest. " << endl;
	cout << "Its just you, your thoughts, and the colorful wilderness. " << endl;
	cout << "You ask yourself, how the hell did I get here and what is my purpose here? " << endl;
	cout << "Well, the more you explore, the more you learn about not only where you are, but who you are. " << endl << endl;
}

int main()
{
    itemMap.insert(std::pair<int, vector<Item>>(0, vector<Item>()));
    itemMap[0].insert(itemMap[0].begin(), Item());

    // itemMap[0][0].print();


    // Starting Room ID = 0
    
    // itemMap.insert(itemMap.begin(), new vector<Item>);

    // itemMap[0] = new vector<Item>;
	backStory();

	Location startingRoom;

	startingRoom.setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
	cout << endl;
	startingRoom.printLocation();
	cout << endl;
	startingRoom.choice();
}

void getUserInput()
{
    cout << "What would you like to do?\n";
    string input;
    cin >> input;
    if (input == "pick apple")
    {
        if (itemMap[0].size() > 0)
        {
            userInventory.addItem(itemMap[0][0]);
            cout << "\nYou grab an apple from the tree.\n";
        }
        else
        {
            cout << "\nThere is no apple for you to take!\n";
        }
    }
    else if (input == "eat apple")
    {
        if(userInventory)
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
