#include "Location.h"
#include <math.h> 

#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <map>

#include "PrintDisplay.h"
#include "CommonGameObjects.h"

using namespace std;

// Default Constructor
Location::Location(int ID)
{
	roomID = ID;
	description = "";
	altDescription = "";
	roomAttrs = 0;
	initializeLocation();
	initializeAttribMap();
}

// Constructor with Description
Location::Location(int ID, string desc, string altDesc, uint64_t attrib)
{
	roomID = ID;
	description = desc;
	altDescription = altDesc;
	roomAttrs = attrib;
	initializeLocation();
	initializeAttribMap();
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

void Location::initializeAttribMap()
{
	// Bit mask. This is required as it needs the uint64_t
	uint64_t mask = 1; 
	for (uint64_t i = 0 ; i < 64 ; ++i)
	{
		// Check from the least significant byte.
		attributeMap.insert({(i+1),(roomAttrs & mask << i)});
	}
}

bool Location::hasAttribute(roomAttributes attrib)
{
	return attributeMap[static_cast<uint64_t>(attrib)];
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
	map<string,int> counter;
	map<string,pair<bool,int>> NPCCounter;
	if (firstTime)
	{
		PrintDisplay::custom_cout << endl << description << endl;
	}
	else
	{
		PrintDisplay::custom_cout << endl << altDescription << endl;
	}

	PrintDisplay::flush();

	// For inventory
	for (auto element : Inventory::itemMap[roomID])
	{
		if (counter.find(element->getItemName()) == counter.end())
		{
			counter.insert(pair<string,int>{element->getItemName(),0});
		}
		counter[element->getItemName()] = counter[element->getItemName()]+1;
	}

	// for NPCs
	for (auto element : NPCManager::NPCMap[roomID])
	{
		if (!element->isDead())
		{
			if (NPCCounter.find(element->name) == NPCCounter.end())
			{
				NPCCounter.insert(pair<string,pair<bool,int>>{element->name,make_pair(element->isHostile,0)});
			}
			NPCCounter[element->name].second =NPCCounter[element->name].second + 1;
		}
	}

	// Items
	if (counter.size() > 0)
	{
		PrintDisplay::custom_cout << endl;
		for (auto element : counter)
		{
			if (element.second > 1)
			{
				PrintDisplay::custom_cout << itemDescription::itemTag[element.first].second << endl;
			}
			else
			{
				PrintDisplay::custom_cout << itemDescription::itemTag[element.first].first << endl;
			}
			PrintDisplay::flush();
		}
	}

	PrintDisplay::custom_cout << timeDescription << endl;
	// NPCS
	if (NPCCounter.size() > 0)
	{
		PrintDisplay::custom_cout << endl;
		for (auto element : NPCCounter)
		{
			if (element.second.second > 1) 
			{
				PrintDisplay::custom_cout << NPCDescription::NPCTag[element.first].second;
			}
			else
			{
				PrintDisplay::custom_cout << NPCDescription::NPCTag[element.first].first;
			}
			PrintDisplay::custom_cout << "\n";
			PrintDisplay::flush();
		}
	}
	PrintDisplay::flush();

}

void Location::setDescription(string s)
{
	description = s; 
}

void Location::setAltDescription(string s)
{
	altDescription = s; 
}

void Location::justVisitedRoom()
{
	firstTime = false;
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
			PrintDisplay::custom_cout << "\nYou can't go " << directionStrings[arg0Direction] << "!\n";
			PrintDisplay::flush();
			return false;
		}
		else if (NPCManager::findLiveHostileNPCs() && currentLocation->checkAdjacent(arg0Direction) != previousLocation)
		{
			PrintDisplay::custom_cout << "\nYou'll need to defeat the enemy first!\n";
			PrintDisplay::flush();
			return false;
		}
		else
		{
			// Move Player to the new location and print out its description
			updateCurrentLocation(currentLocation->checkAdjacent(arg0Direction));
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
					PrintDisplay::custom_cout << "\nYou can't go " << directionStrings[arg1Direction] << "!\n";
					PrintDisplay::flush();
					return false;
				}
				else // user direction has a room connected 
				{
					updateCurrentLocation(currentLocation->checkAdjacent(arg1Direction));
					return true;
				}
			}

		}
	}

	PrintDisplay::custom_cout << "\nWhat do you want to " << args[0] << "?\n";
	PrintDisplay::flush();
	return false;
}


void Location::setAdjacent(Location* adjRoom, cardinalDirection dir)
{
	setAdjacent(adjRoom, dir, false);
}

void Location::setAdjacent(Location* adjRoom, cardinalDirection dir, bool twoWay)
{
	// Input Validation for cardinalDirection
	if (dir >= 0 && dir <= 5)
	{
		locationConnections[dir] = adjRoom;
	}
	else
	{
		PrintDisplay::custom_cout << "Invalid direction!\n";
		PrintDisplay::no_effect_flush();
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

uint64_t Location::getNumberOfTimesEntered()
{
	return number_of_times_entered;
}

void Location::addNumberOfTimesEntered()
{
	number_of_times_entered++;
}

// Initializes the current Location
Location* locationManager::currentLocation = currentLocation = nullptr;

// Initializes the previous Location
Location* locationManager::previousLocation = previousLocation = nullptr;

// Initializes the current Time
int locationManager::currentTime = 8;

// Initializes the time description
string Location::timeDescription = "The sun is high in the sky...";

void locationManager::updateCurrentTime()
{
	// Increments current time by 1, unless it is 24, then goes back to 0 for a new day
	currentTime = ++currentTime % 24;

	switch (currentTime)
	{
	case 6:
		getCurrentLocation()->setTimeDescription("The sun is rising...");
		break;
	case 7:
		getCurrentLocation()->setTimeDescription("The sun is high in the sky...");
		break;
	case 18:
		getCurrentLocation()->setTimeDescription("The sun is setting...");
		break;
	case 19:
		getCurrentLocation()->setTimeDescription("It's dark, and the moon is high in the sky...");
		break;
	}
}

void Location::setTimeDescription(string desc)
{
	timeDescription = desc;
}

int locationManager::getCurrentTime()
{
	return currentTime;
}

// Updates the current Location to a new Location
void locationManager::updateCurrentLocation(Location* newLocation)
{
	previousLocation = currentLocation;
	currentLocation = newLocation;
	updateCurrentTime();
	currentLocation->printLocation();
	currentLocation->justVisitedRoom();
	currentLocation->addNumberOfTimesEntered();
	if (currentLocation->hasAttribute(Location::INSTANT_KILL_ROOM))
	{
		CommonGameObjects::PAManager->hurtPlayer(99999999);
	}
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
        PrintDisplay::custom_cout <<  "Could not open map.mbm.\n";
		PrintDisplay::no_effect_flush();
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
        PrintDisplay::custom_cout << "Could not open map.mbd.\n";
		PrintDisplay::no_effect_flush();
        return false;
    }
    std::vector<char> descBytes(
        (std::istreambuf_iterator<char>(in)),
        (std::istreambuf_iterator<char>()));
    memcpy(&mapDesc, descBytes.data(), descBytes.size());
    in.close();

	if (map.header.version != CURRENT_MBM_VERSION)
	{
		PrintDisplay::custom_cout << "The loaded map file is not compatible with this version of the game.\n";
		PrintDisplay::custom_cout << "Requires MBM version: "<< CURRENT_MBM_VERSION << ", loaded version: " << map.header.version << "\n";
		PrintDisplay::no_effect_flush();
		return false;
	}

	if (mapDesc.header.version != CURRENT_MBD_VERSION)
	{
		PrintDisplay::custom_cout << "The loaded map description file is not compatible with this version of the game.\n";
		PrintDisplay::custom_cout << "Requires MBD version: "<< CURRENT_MBD_VERSION << ", loaded version: " << mapDesc.header.version << "\n";
		PrintDisplay::no_effect_flush();
		return false;
	}

    // Converting data read from files to initialize Location objects
    for (uint32_t i = 0; i < map.header.roomCount; i++)
    {
        locationManager::locationMap.insert(std::pair<int, Location*>(map.layout[i].id, new Location(map.layout[i].id, mapDesc.descLayout[i].description, mapDesc.descLayout[i].altdescription, map.layout[i].attributes)));
    }
    // Connect the initialized rooms
    for (uint32_t i = 0; i < map.header.roomCount; i++)
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
	locationManager::currentLocation = locationManager::locationMap[1];
	descBytes.clear();
	mapBytes.clear();
	return true;
}

void locationManager::deinit()
{
    // Destroying the map pointers so there are no memory leaks
    for (uint32_t i = 0; i < map.header.roomCount; i++)
    {
        delete locationManager::locationMap[map.layout[i].id];
        locationManager::locationMap[map.layout[i].id] = nullptr;
    }
}