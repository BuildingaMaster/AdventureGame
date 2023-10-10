#ifndef ACTION_H
#define ACTION_H
#include <iostream>
#include <string>
using namespace std;

class Action
{
protected:
	char move;

	void Move()
	{
		bool validInput = true;
		do
		{
			cout << "Where to? ";
			cin >> move;
			if (move == 'N' || move == 'n')
			{

			}
			else if (move == 'S' || move == 's')
			{

			}
			else if (move == 'E' || move == 'e')
			{

			}
			else if (move == 'W' || move == 'w')
			{

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
		}while (validInput == false);
	}
public:
	Action()
	{

	}

};
#endif // !ACTION_H
