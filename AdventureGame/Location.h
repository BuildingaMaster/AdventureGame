#pragma once

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
			return true;
		}
		cout << "\nWhat do you want to "<<args[0]<<"?\n";
		return false;
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