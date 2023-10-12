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
		string c;
		cout << "What to do? ";
		cin >> c;
		if (c == "look")
		{
			cout << endl << description;
		}
	}
	Location()
	{
		description = "";
	}
};
#endif // !LOCATION_H