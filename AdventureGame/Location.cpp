#include "Location.h"
#include <iostream>
#include <fstream>

using namespace std;

// Default Constructor
Location::Location(int ID)
{
	roomID = ID;
	description = "";
	initializeLocation();
}

// Constructor with Description
Location::Location(int ID, string desc)
{
	roomID = ID;
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

const string locationManager::locationValidCommands = "look see describe visualize north south east west above below go walk travel move ";

string locationManager::getValidCommands()
{
	return locationValidCommands;
}

const string locationManager::directionStrings[] = { "north", "south", "east", "west", "above", "below" };

// Outputs the description of the Location
void Location::printLocation()
{
	cout << endl << description << endl;
}

void Location::setDescription(string s)
{
	description = s; 
}

bool locationManager::processCommand(vector<string> args)
{
	// Run the "look" command
	if (args[0] == "look" || args[0] == "see" || args[0] == "visualize")
	{
		currentLocation->printLocation();
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
			updateCurrentLocation(currentLocation->checkAdjacent(arg0Direction));
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
					updateCurrentLocation(currentLocation->checkAdjacent(arg1Direction));
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

int Location::getLocationID()
{
	return roomID;
}

// Initializes the current Location
Location* locationManager::currentLocation = currentLocation = nullptr;

// Updates the current Location to a new Location
void locationManager::updateCurrentLocation(Location* newLocation)
{
	currentLocation = newLocation;
}

// Returns the current player Location
Location* locationManager::getCurrentLocation()
{
	return currentLocation;
}

// Converts user input string into readable cardinal direction enum
cardinalDirection locationManager::stringToDirection(string str)
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

map<int, Location*> locationManager::locationMap;
fileParse::mapFile locationManager::map;
fileParse::mapDescFile locationManager::mapDesc;

bool locationManager::init()
{
	// Reading from Map Files
    ifstream in;
    // mbm map files contain location connections
    // Convert mbm data to map structures
    in.open("map.mbm", ifstream::in | ifstream::binary);
    if (!in.is_open())
    {
        cout << "Could not open map.mbm.\n";
        return false;
    }
    std::vector<char>mapBytes(
        (std::istreambuf_iterator<char>(in)),
        (std::istreambuf_iterator<char>()));
    memcpy(&map, mapBytes.data(), mapBytes.size());
    in.close();
    // mbd map files contain location descriptions
    // Convert mbd data to description structures
    in.open("map.mbd", ifstream::in | ifstream::binary);
    if (!in.is_open())
    {
        cout << "Could not open map.mbd.\n";
        return false;
    }
    std::vector<char> descBytes(
        (std::istreambuf_iterator<char>(in)),
        (std::istreambuf_iterator<char>()));
    memcpy(&mapDesc, descBytes.data(), descBytes.size());
    in.close();

    // Converting data read from files to initialize Location objects
    for (int i = 0; i < map.header.roomCount; i++)
    {
        locationManager::locationMap.insert(std::pair<int, Location*>(map.layout[i].id, new Location(map.layout[i].id, mapDesc.descLayout[i].description)));
    }
    // Connect the initialized rooms
    for (int i = 0; i < map.header.roomCount; i++)
    {
        for (int j = 0; j < sizeof(map.layout[i].direction) / sizeof(uint32_t); j++)
        {
            // If there's no connection, skip
            if (map.layout[i].direction[j] == 0)
            {
                continue;
            }
            locationManager::locationMap[map.layout[i].id]->setAdjacent(locationManager::locationMap[map.layout[i].direction[j]], static_cast<cardinalDirection>(j));
        }
    }

    // Set the starting location to the player location and print the description
    updateCurrentLocation(locationManager::locationMap[1]);
    //locationMap[1]->getCurrentLocation()->printLocation();
	return true;
}

void locationManager::deinit()
{
    // Destroying the map pointers so there are no memory leaks
    for (int i = 0; i < map.header.roomCount; i++)
    {
        delete locationManager::locationMap[map.layout[i].id];
        locationManager::locationMap[map.layout[i].id] = nullptr;
    }
}