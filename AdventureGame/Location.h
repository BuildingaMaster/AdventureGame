#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Location
{
private:
	//string description;
public:
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
		// prints out where the user is 
		cout << description;
	}
	
	Location()
	{
		description = "";
	}
};