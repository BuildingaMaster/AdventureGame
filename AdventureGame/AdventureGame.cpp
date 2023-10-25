// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <fstream>
#include <istream>

#include "Location.h"
#include "PlayerActions.h"
#include "Item.h"
#include "Inventory.h"
#include "Consumable.h"
#include "ContextParser.h"
using namespace std;

Inventory userInventory;

// Called at start of game, couts initial backstory
void backStory()
{
	cout << "You open your eyes and see you are in the middle of a forest. " << endl;
	cout << "It's just you, your thoughts, and the colorful wilderness. " << endl;
	cout << "You ask yourself: how the hell did I get here, and what is my purpose?" << endl;
	cout << "The more you explore, the more you learn about not only where you are, but who you are. " << endl << endl;
}

#pragma pack(push, 1)
struct mapFileHeader
{
    char magic[4];
    uint16_t endian = 0;
    uint16_t version = 0;
    uint32_t hash = 0;
    uint32_t roomCount = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct roomLayout
{
    uint32_t id = 0;
    uint32_t direction[6] = { 0, 0, 0, 0, 0, 0 }; // North South East West Above Below
    uint32_t attributes[2] = { 0, 0 };
};
#pragma pack(pop)

#pragma pack(push, 1)
struct mapFile 
{
    mapFileHeader header;
    roomLayout layout[2000];
    
};
#pragma pack(pop)

#pragma pack(push, 1)
struct roomDes
{
    uint32_t id = 0;
    uint32_t stringSize = 0;
    char description[400];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct mapDescFile
{
    mapFileHeader header;
    roomDes descLayout[2000];
};
#pragma pack(pop)

map<int, Location*> locationMap;

int main()
{
	backStory();
    
    PlayerActions playeract;

    // Reading from Map File
    ifstream in;
    in.open("map.mbm", ifstream::in | ifstream::binary);
    if (!in.is_open())
    {
        cout << "Could not open map.mbm.\n";
        return 1;
    }
    mapFile map;
    mapDescFile mapDesc;
    std::vector<char>mapBytes(
        (std::istreambuf_iterator<char>(in)),
        (std::istreambuf_iterator<char>()));
    memcpy(&map, mapBytes.data(), mapBytes.size());
    in.close();

    in.open("map.mbd", ifstream::in | ifstream::binary);
    if (!in.is_open())
    {
        cout << "Could not open map.mbd.\n";
        return 1;
    }
    std::vector<char> descBytes(
        (std::istreambuf_iterator<char>(in)),
        (std::istreambuf_iterator<char>()));
    memcpy(&mapDesc, descBytes.data(), mapBytes.size());
    in.close();

    // Converting data read from files to initialize Location objects
    for (int i = 0; i < map.header.roomCount; i++)
    {
        locationMap.insert(std::pair<int, Location*>(map.layout[i].id, new Location(mapDesc.descLayout[i].description)));
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
            locationMap[map.layout[i].id]->setAdjacent(locationMap[map.layout[i].direction[j]], static_cast<cardinalDirection>(j));
        }
    }

    /*
    // Convert to map file
    // Initializing Starting Rooms
	Location* startingRoom = new Location();
    startingRoom->updateCurrentLocation(startingRoom);

    // All it takes to make a Room
    Location* northRoom = new Location();
    northRoom->setDescription("\nThis is a new room!\n\n");
    startingRoom->setAdjacent(northRoom, North, true);

	startingRoom->setDescription("\nYou are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.\n");
	cout << endl;
	startingRoom->printLocation();
	cout << endl;
    */

    Location* getStarted = locationMap[1];
    getStarted->updateCurrentLocation(locationMap[1]);
    getStarted->getCurrentLocation()->printLocation();
    
    string command;
    ContextParser CP(&userInventory,&playeract);
    bool validInput;
    do
    {
        do
        {
            cout << "\n\nWhat would you like to do?\n> ";
            getline(cin, command);
            validInput = CP.interpretCommand(getStarted->getCurrentLocation(), command);
        } while (validInput == false);
    } while (true);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
