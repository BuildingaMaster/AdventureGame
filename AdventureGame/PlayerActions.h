#pragma once

#include <iostream>
#include <string>
#include "Location.h"
using namespace std;
// Derived from Location
class Action : public Location // TODO: Please convert to processCommand structure.
{
public:
	string move;
	// move to a cpp file 
	// Allows player to move around the map
	void Move()
	{
		bool validInput = false;
		do
		{
			cout << "Where to? ";
			cin >> move;
			if (move == "N" || move == "n")
			{
				validInput = false;
			}
			else if (move == "S" || move == "s")
			{
				validInput = false;
			}
			else if (move == "E" || move == "e")
			{
				validInput = false;
			}
			else if (move == "W" || move == "w")
			{
				validInput = false;
			}
			// displays where the is user 
			else if (move == "Look" || move == "look")
			{
				cout << endl << description << endl;
				validInput = false;
			}
			else
			{
				cout << "Invalid input for a direction to go. " << endl;
				cout << "To go North, enter: N or n" << endl;
				cout << "To go South, enter: S or s" << endl;
				cout << "To go East, enter: E or e" << endl;
				cout << "To go West, enter: W or w" << endl;

				validInput = false;
			}
		} while (validInput == false);
	}


};