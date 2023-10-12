#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <iostream>
#include "PlayerActions.h"
using namespace std;

class Location
{
private:
	string description;
public:
	void setDescription(string s)
	{
		description = s; 
	}
	void printLocation()
	{
		cout << description;
	}
	
	void choice()
	{
		bool validInput = false;

		do
		{
			string c;
			cout << "What to do? ";
			cin >> c;
			cin >> c;
			for(auto& character : c)
			{
				character = tolower(character);
			}
			if (c == "look")
			{
				validInput = true;
				cout << endl << description << endl;
			}
			
		}while (validInput == false);
	}
	Location()
	{
		description = "";
	}
};
#endif // !LOCATION_H