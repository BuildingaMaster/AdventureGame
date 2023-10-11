#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <iostream>
using namespace std;

class Location
{
protected:
	// pure virtual function
	virtual void printLocation() {	}
public:
	Location()
	{
		// print current location
	}
};
#endif // !LOCATION_H