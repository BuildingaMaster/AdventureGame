#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cctype>
using namespace std;

enum cardinalDirection { North = 0, South = 1, East = 2, West = 3, Above = 4, Below = 5, Invalid = -1 };

namespace fileParse
{
	// Define map file header structure
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

	// Define map layout structure
	#pragma pack(push, 1)
	struct roomLayout
	{
		uint32_t id = 0;
		uint32_t direction[6] = { 0, 0, 0, 0, 0, 0 }; // North South East West Above Below
		uint32_t attributes[2] = { 0, 0 };
	};
	#pragma pack(pop)

	// Define map file structure
	#pragma pack(push, 1)
	struct mapFile 
	{
		mapFileHeader header;
		roomLayout layout[2000];
		
	};
	#pragma pack(pop)

	// Define room description structure
	#pragma pack(push, 1)
	struct roomDes
	{
		uint32_t id = 0;
		uint32_t stringSize = 0;
		char description[400];
	};
	#pragma pack(pop)

	// Define map description file structure
	#pragma pack(push, 1)
	struct mapDescFile
	{
		mapFileHeader header;
		roomDes descLayout[2000];
	};
	#pragma pack(pop)
};

class Location
{
public:

	/// @brief Initializes a new Location with nullptr connections
	Location(int ID);

	/// @brief Initializes a new Location with nullptr connections
	/// @param desc - set to description of Location
	Location(int ID, string desc);

	/// @brief cout the description of the location
	void printLocation();
	
	/// @brief Sets the location description
	/// @param desc - set to description of Location
	void setDescription(string desc);
		

	/// 
	void setAdjacent(Location*, cardinalDirection);
	void setAdjacent(Location*, cardinalDirection, bool);
	Location* checkAdjacent(cardinalDirection);
	int getLocationID();
private:
	int roomID;
	void initializeLocation();
	string description;
	Location* locationConnections[6];
	// When the player can't go in a direction.		
};

class locationManager
{
public:
	static bool init();
	static void deinit();
	// Contains a string containing all accepted player commands
	const static string locationValidCommands;

	static string getValidCommands();
	static Location* getCurrentLocation();
	static void updateCurrentLocation(Location*);
	// Initialize map of location pointers with location ID integers
	static map<int, Location*> locationMap;
	/// @brief Processes Location-based commands
	/// @param args - the vector of strings that contain filtered commands
	static bool processCommand(vector<string>);
#ifdef GTESTING
public:
#else
private:
#endif
	static Location* currentLocation;
	const static string directionStrings[6];
	static cardinalDirection stringToDirection(string);
	static fileParse::mapFile map;
	static fileParse::mapDescFile mapDesc;
};
#endif // !LOCATION_H