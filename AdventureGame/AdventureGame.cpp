// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "Location.h"
#include "PlayerActions.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
#include "ContextParser.h"
using namespace std;

Inventory userInventory;





void backStory()
{
	cout << "You open your eyes and see you are in the middle of a forest. " << endl;
	cout << "It's just you, your thoughts, and the colorful wilderness. " << endl;
	cout << "You ask yourself: how the hell did I get here, and what is my purpose?" << endl;
	cout << "The more you explore, the more you learn about not only where you are, but who you are. " << endl << endl;
}

int main()
{
    // itemMap[0][0].print();


    // Starting Room ID = 0
    
    // itemMap.insert(itemMap.begin(), new vector<Item>);

    // itemMap[0] = new vector<Item>;
	backStory();

	Location startingRoom;

	startingRoom.setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
	cout << endl;
	startingRoom.printLocation();
	cout << endl;
    string command;
    ContextParser CP(&startingRoom,&userInventory);
    bool validInput;
    do
    {
        do
        {
            cout << "What would you like to do?\n> ";
            getline(cin, command);
            validInput = CP.interpretCommand(command);
        } while (validInput == false);
    } while (true);
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
