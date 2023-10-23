#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum cardinalDirection { North = 0, South = 1, East = 2, West = 3, Above = 4, Below = 5 };

class Location
{
public:
	Location();
	string locationValidCommands;
	bool processCommand(vector<string>);
	void setDescription(string);
	void printLocation();

	void setAdjacent(Location*, cardinalDirection);
	Location* checkAdjacent(cardinalDirection);

	void updateCurrentLocation(Location*);
	static Location* getCurrentLocation();
private:
	static Location* currentLocation;
	string description;
	Location* locationConnections[6];
};
#endif // !LOCATION_H