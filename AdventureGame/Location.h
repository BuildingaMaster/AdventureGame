#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <iostream>
#include "PlayerActions.h"
using namespace std;

class Location
{
private:
	string description;
public:
	string locationValidCommands = "look see describe visualize ";
	bool processCommand(vector<string> args)
	{
		if (args[0] == "look")
		{
			cout << endl << description << endl;
		}
		return true;
	}
	void setDescription(string s)
	{
		description = s; 
	}
	void printLocation()
	{
		cout << description;
	}
	
	Location()
	{
		description = "";
	}
};
#endif // !LOCATION_H