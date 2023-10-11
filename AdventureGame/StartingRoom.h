#ifndef STARTINGROOM_H
#define STARTINGROOM_H
#include <iostream>
#include <string>
#include "Location.h"
#include "PlayerActions.h"
using namespace std;

class StartingRoom : public Location
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
		cout << "Well, the more you explore, the more you learn about not only where you are, but who you are. " << endl << endl;
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



