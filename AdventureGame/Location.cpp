#include "Location.h"
#include <iostream>

using namespace std;

// Default Constructor
Location::Location()
{
	description = "";
	locationValidCommands = "look see describe visualize north south east west above below ";
	
	// Initialize connection array to nullptrs
	for (int i = 0; i < 6; i++)
	{
		locationConnections[i] = nullptr; // If not set to null program will crash
	}
}

// Outputs the description of the Location
void Location::printLocation()
{
	cout << description;
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
	if (args[0] == "north")
	{
		if (currentLocation->checkAdjacent(North) == nullptr)
		{
			cout << "\nYou can't go North!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(North));
			currentLocation->printLocation();
			return true;
		}
	}
	if (args[0] == "south")
	{
		if (currentLocation->checkAdjacent(South) == nullptr)
		{
			cout << "\nYou can't go South!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(South));
			currentLocation->printLocation();
			return true;
		}
	}
	if (args[0] == "east")
	{
		if (currentLocation->checkAdjacent(East) == nullptr)
		{
			cout << "\nYou can't go East!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(East));
			currentLocation->printLocation();
			return true;
		}
	}
	if (args[0] == "west")
	{
		if (currentLocation->checkAdjacent(West) == nullptr)
		{
			cout << "\nYou can't go West!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(West));
			currentLocation->printLocation();
			return true;
		}
	}
	if (args[0] == "above")
	{
		if (currentLocation->checkAdjacent(Above) == nullptr)
		{
			cout << "\nYou can't go above!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(Above));
			currentLocation->printLocation();
			return true;
		}
	}
	if (args[0] == "below")
	{
		if (currentLocation->checkAdjacent(Below) == nullptr)
		{
			cout << "\nYou can't go below!\n\n";
			return true;
		}
		else
		{
			updateCurrentLocation(checkAdjacent(Below));
			currentLocation->printLocation();
			return true;
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