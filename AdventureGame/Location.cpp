#include "Location.h"
#include <iostream>

using namespace std;

// Default Constructor
Location::Location()
{
	description = "";
	initializeLocation();
}

// Constructor with Description
Location::Location(string desc)
{
	description = desc;
	initializeLocation();
}

// Creates validCommands variable and initializes nullptr array
void Location::initializeLocation()
{
	// Initialize connection array to nullptrs
	for (int i = 0; i < 6; i++)
	{
		locationConnections[i] = nullptr; // If not set to null program will crash
	}
}

const string Location::locationValidCommands = "look see describe visualize north south east west above below go walk travel move ";

string Location::getValidCommands()
{
	return locationValidCommands;
}

const string Location::directionStrings[] = { "north", "south", "east", "west", "above", "below" };

// Outputs the description of the Location
void Location::printLocation()
{
	cout << endl << description << endl;
}

void Location::setDescription(string s)
{
	description = s; 
}

bool Location::processCommand(vector<string> args)
{
	// Run the "look" command
	if (args[0] == "look" || args[0] == "see" || args[0] == "visualize")
	{
		cout << endl << description << endl;
		return true;
	}

	cardinalDirection arg0Direction = stringToDirection(args[0]);

	// Checking for valid direction input, will take just a direction as input 
	if (arg0Direction >= 0 && arg0Direction <= 5)
	{
		// No room in user's direction input (YET)
		if (currentLocation->checkAdjacent(arg0Direction) == nullptr)
		{
			cout << "\nYou can't go " << directionStrings[arg0Direction] << "!\n";
			return true;
		}
		else
		{
			// Move Player to the new location and print out its description
			updateCurrentLocation(checkAdjacent(arg0Direction));
			currentLocation->printLocation();
			return true;
		}
	}
	//arg[0] is the first word the user inputs, then takes the user's direction input
	if (args[0] == "go" || args[0] == "travel" || args[0] == "walk" || args[0] == "move")
	{
		// vector is greater than 1 (has more than 1 room)
		if (args.size() > 1)
		{
			// converts the user's direction input to the cardinal direction eNum
			cardinalDirection arg1Direction = stringToDirection(args[1]);
			// valid input for direction
			if (arg1Direction >= 0 && arg1Direction <= 5)
			{
				// no room connected to user's direction input
				if (currentLocation->checkAdjacent(arg1Direction) == nullptr)
				{
					cout << "\nYou can't go " << directionStrings[arg1Direction] << "!\n";
					return true;
				}
				else // user direction has a room connected 
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

///@brief Sets a new connection from the current room to a new room based off of the direction you want to go
void Location::setAdjacent(Location* adjRoom, cardinalDirection dir)
{
	setAdjacent(adjRoom, dir, false);
}

// Sets a new connection from the current room to a new room in direction dir, either one way or two way
/// @brief Creates a new connection in a set direction 
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

// Converts user input string into readable cardinal direction enum
cardinalDirection Location::stringToDirection(string str)
{
	cardinalDirection enumDirections[6] = { North, South, East, West, Above, Below };
	for (int i = 0; i < 6; i++)
	{
		if (str == directionStrings[i])
		{
			return enumDirections[i];
		}
	}
	return Invalid;
}