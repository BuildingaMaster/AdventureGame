#pragma once

#include <iostream>
#include <string>
using namespace std;

class Action // TODO: Please convert to processCommand structure.
{
protected:
	char move;
	// move to a cpp file 
	void Move()
	{
		bool validInput = false;
		do
		{
			cout << "Where to? ";
			cin >> move;
			if (move == 'N' || move == 'n')
			{
				validInput = true;
			}
			else if (move == 'S' || move == 's')
			{
				validInput = true;
			}
			else if (move == 'E' || move == 'e')
			{
				validInput = true;
			}
			else if (move == 'W' || move == 'w')
			{
				validInput = true;
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
public:
	Action()
	{

	}

};