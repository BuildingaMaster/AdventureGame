#include "Location.h"
#include <iostream>

using namespace std;

// Default Constructor
Location::Location()
{
	description = "";
	locationValidCommands = "look see describe visualize north south east west above below go walk travel move ";
	
	// Initialize connection array to nullptrs
	for (int i = 0; i < 6; i++)
	{
		locationConnections[i] = nullptr; // If not set to null program will crash
	}
}

// Constructor with Description
Location::Location(string desc)
{
	description = desc;
	locationValidCommands = "look see describe visualize north south east west above below go walk travel move ";

	// Initialize connection array to nullptrs
	for (int i = 0; i < 6; i++)
	{
		locationConnections[i] = nullptr; // If not set to null program will crash
	}
}

// Outputs the description of the Location
void Location::printLocation()
{
	cout << endl << description << endl;
}

// Sets the location description to the string s
void Location::setDescription(string s)
{
	description = s; 
}

// Processes Location-based commands
bool Location::processCommand(vector<string> args)
{
	if (args[0] == "look")
	{
		cout << endl << description << endl;
		return true;
	}

	cardinalDirection arg0Direction = stringToDirection(args[0]);
	string directionStrings[6] = { "North", "South", "East", "West", "above", "below" };

	if (arg0Direction >= 0 && arg0Direction <= 5)
	{
		if (currentLocation->checkAdjacent(arg0Direction) == nullptr)
		{
			cout << "\nYou can't go " << directionStrings[arg0Direction] << "!\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(arg0Direction));
			currentLocation->printLocation();
			return true;
		}
	}

	if (args[0] == "go" || args[0] == "travel" || args[0] == "walk" || args[0] == "move")
	{
		if (args.size() > 1)
		{
			cardinalDirection arg1Direction = stringToDirection(args[1]);
			if (arg1Direction >= 0 && arg1Direction <= 5)
			{
				if (currentLocation->checkAdjacent(arg1Direction) == nullptr)
				{
					cout << "\nYou can't go " << directionStrings[arg1Direction] << "!\n";
					return true;
				}
				else
				{
					updateCurrentLocation(checkAdjacent(arg1Direction));
					currentLocation->printLocation();
					return true;
				}
			}

		}
	}

	cout << "\nWhat do you want to " << args[0] << "?\n";
	return false;
}

// Sets a new connection from the current room to a new room based off of the direction you want to go
void Location::setAdjacent(Location* adjRoom, cardinalDirection dir)
{
	// Input Validation for cardinalDirection
	if (dir >= 0 && dir <= 5)
	{
		locationConnections[dir] = adjRoom;
	}
	else
	{
		cout << "Invalid direction!\n";
	}
}

// Sets a new connection from the current room to a new room in direction dir, either one way or two way
void Location::setAdjacent(Location* adjRoom, cardinalDirection dir, bool twoWay)
{
	// Input Validation for cardinalDirection
	if (dir >= 0 && dir <= 5)
	{
		locationConnections[dir] = adjRoom;
	}
	else
	{
		cout << "Invalid direction!\n";
		return;
	}
	if (twoWay)
	{
		cardinalDirection dirOpp;
		if (dir % 2)
		{
			dirOpp = static_cast<cardinalDirection>(dir - 1);
		}
		else
		{
			dirOpp = static_cast<cardinalDirection>(dir + 1);
		}
		adjRoom->setAdjacent(this, dirOpp, false);
	}
}

// Returns a pointer to a Location in the direction of dir from the current Location
Location* Location::checkAdjacent(cardinalDirection dir)
{
	// Input Validation for cardinalDirection & locationConnections
	if (dir >= 0 && dir <= 5 && locationConnections[dir] != nullptr)
	{
		return locationConnections[dir];
	}
	else
	{
		return nullptr;
	}
}

// Initializes the current Location
Location* Location::currentLocation = currentLocation = nullptr;

// Updates the current Location to a new Location
void Location::updateCurrentLocation(Location* newLocation)
{
	currentLocation = newLocation;
}

// Returns the current player Location
Location* Location::getCurrentLocation()
{
	return currentLocation;
}

cardinalDirection Location::stringToDirection(string str)
{
	string stringDirections[6] = { "north", "south", "east", "west", "above", "below" };
	cardinalDirection enumDirections[6] = { North, South, East, West, Above, Below };
	for (int i = 0; i < 6; i++)
	{
		if (str == stringDirections[i])
		{
			return enumDirections[i];
		}
	}
	return Invalid;
}