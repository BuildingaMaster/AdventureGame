#include "Location.h"
#include <iostream>

using namespace std;

// Default Constructor
Location::Location()
{
	description = "";
	locationValidCommands = "look see describe visualize ";
	
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