// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "Location.h"
#include "PlayerActions.h"
#include "StartingRoom.h"
using namespace std;

void backStory()
{
	cout << "You open your eyes and see you are in the middle of a forest. " << endl;
	cout << "Its just you, your thoughts, and the colorful wilderness. " << endl;
	cout << "You ask yourself, how the hell did I get here and what is my purpose here? " << endl;
	cout << "Well, the more you explore, the more you learn about not only where you are, but who you are. " << endl << endl;
}
int main()
{
	backStory();

	Location startingRoom;

	startingRoom.setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
	cout << endl;
	startingRoom.printLocation();
	cout << endl;
	startingRoom.choice();
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
