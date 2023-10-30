#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum cardinalDirection { North = 0, South = 1, East = 2, West = 3, Above = 4, Below = 5, Invalid = -1 };

class Location
{
public:

	// Contains a string containing all accepted player commands
	const static string locationValidCommands;

	string getValidCommands();

	/// @brief Initializes a new Location with nullptr connections
	Location();

	/// @brief Initializes a new Location with nullptr connections
	/// @param desc - set to description of Location
	Location(string desc);

	/// @brief cout the description of the location
	void printLocation();
	
	/// @brief Sets the location description
	/// @param desc - set to description of Location
	void setDescription(string desc);
		
	/// @brief Processes Location-based commands
	/// @param args - the vector of strings that contain filtered commands
	bool processCommand(vector<string>);

	/// 
	void setAdjacent(Location*, cardinalDirection);
	void setAdjacent(Location*, cardinalDirection, bool);
	Location* checkAdjacent(cardinalDirection);
	void updateCurrentLocation(Location*);
	static Location* getCurrentLocation();
private:
	void initializeLocation();

	static Location* currentLocation;
	string description;
	Location* locationConnections[6];
	// When the player can't go in a direction.
	const static string directionStrings[6];
	cardinalDirection stringToDirection(string);
};
#endif // !LOCATION_H