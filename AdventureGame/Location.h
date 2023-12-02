#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cctype>
using namespace std;

#define CURRENT_MBM_VERSION 0
#define CURRENT_MBD_VERSION 1

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
		//uint32_t attributes[2] = { 0, 0 };
		//uint64_t attributes[1] = { 0 };
		uint64_t attributes = 0 ;
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
		uint32_t altstringSize = 0;
		char altdescription[400];
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
	enum roomAttributes : uint64_t
	{
		APPLE_TREE_IN_ROOM = 1,
		MUSHROOMS_IN_ROOM = 2,
		WOLVES_IN_ROOM = 3,
		KNIGHT_IN_ROOM = 4,
		INSTANT_KILL_ROOM = 9,
		PRINCESS_IN_ROOM = 10,
		DRAGON_IN_ROOM = 11,
		ARMOR_1 = 6,
		ARMOR_2 = 7,
		ARMOR_3 = 8,
		KING_THAD_IN_ROOM = 12,
		AAAA = 64,
		NONE = 0
	};

	/// @brief Initializes a new Location with nullptr connections
	Location(int ID);

	/// @brief Initializes a new Location with nullptr connections
	/// @param desc - set to description of Location
	/// @param altDesc - set to description of Location
	/// @param attrib - the attributes of the room
	Location(int ID, string desc, string altDesc, uint64_t attrib);

	/// @brief cout the description of the location
	void printLocation();
	
	/// @brief Sets the location description
	/// @param desc - set to description of Location
	void setDescription(string desc);

	/// @brief Sets the alternae location description (not the first time)
	/// @param desc - set the alt description of Location
	void setAltDescription(string desc);

	void justVisitedRoom();

	/// @brief Sets a new connection from the current room to a new room based off of the direction you want to go
	/// @param adjRoom The room to connect to
	/// @param dir The direction of the connection
	void setAdjacent(Location*, cardinalDirection);

	///  @brief Sets a new connection from the current room to a new room based off of the direction you want to go
	/// @param adjRoom The room to connect to
	/// @param dir The direction of the connection
	/// @param twoWay Should the opposite room be connected?
	void setAdjacent(Location*, cardinalDirection, bool);
	Location* checkAdjacent(cardinalDirection);
	int getLocationID();
	uint64_t getNumberOfTimesEntered();
	void addNumberOfTimesEntered();

	bool hasAttribute(roomAttributes);

	static void setTimeDescription(string);
	
#ifdef GTESTING
public:
#else
private:
#endif
	int roomID;
	uint64_t number_of_times_entered;
	bool firstTime = true;
	uint64_t roomAttrs;
	map<uint64_t,bool> attributeMap;
	void initializeLocation();

	/// @brief 
	void initializeAttribMap();
	string description;
	string altDescription;
	static string timeDescription;
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
	/// @brief Increments the current time by a constant interval
	static void updateCurrentTime();
	/// @return The current world time
	static int getCurrentTime();
	// Initialize map of location pointers with location ID integers
	static map<int, Location*> locationMap;
	/// @brief Processes Location-based commands
	/// @param args - the vector of strings that contain filtered commands
	static bool processCommand(vector<string>);
	static cardinalDirection stringToDirection(string);
#ifdef GTESTING
public:
#else
private:
#endif
	static Location* currentLocation;
	const static string directionStrings[6];
	static fileParse::mapFile map;
	static fileParse::mapDescFile mapDesc;
	// Current time is read in military time 0 - 23:59, in hourly increments
	static int currentTime;
};
#endif // !LOCATION_H