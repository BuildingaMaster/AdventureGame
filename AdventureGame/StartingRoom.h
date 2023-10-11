#ifndef STARTINGROOM_H
#define STARTINGROOM_H
#include <iostream>
#include <string>
#include "Location.h"
#include "PlayerActions.h"
using namespace std;

class StartingRoom : public Action
{
protected:
	virtual void printLocation()
	{
		cout << "You are in a vibrant, yet desolate forest." << endl;
		cout << "There seems to be no wildlife in sight." << endl;
		cout << "There seems to be a shallow pond to the west, " << endl;
		cout << "a deserted hut to the east, and more wilderness. " << endl;
		cout << "south and north of your location." << endl;
		cout << "Where would you like to go?" << endl;

		Action::Move();
	}
	void backStory()
	{
		cout << "You open your eyes and see you are in the middle of a forest. " << endl;
		cout << "Its just you, your thoughts, and the colorful wilderness. " << endl;
		cout << "You ask yourself, how the hell did I get here and what is my purpose here? " << endl;
		cout << "Well, the more you explore, the more you learn about not only where you are, but who you are. " << endl;
		cout << "You start to find ripped up pieces of paper on the ground, and one piece says in bold ink: WANTED. " << endl;
		cout << "But you cannot seem to make out whose head has the price on it. " << endl;
		cout << "The deeper you go into the game, you start to understand you are the one wanted? But what for? " << endl;
		cout << "Well, you and the princess of the mighty kingdom used to be great lovers, " << endl;
		cout << "but then something happened and now your reputation and life has been flipped upside down. " << endl;
		cout << "You now have to evade angry villagers and when you encounter them, you must fight for survival. " << endl;
		cout << "Your quest is to get into castle and find out what happened to your great relationship with the princess ";
		cout << "and try to win her heart back." << endl << endl;
	}
public:
	StartingRoom()
	{
		backStory();
		// when StartingRoom object (start) is called, the printLocation function runs
		printLocation();
	}
};
#endif // !STARTINGROOM_H



