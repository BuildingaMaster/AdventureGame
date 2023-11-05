#pragma once

#include <string>
#include <vector>

#include "BaseHealth.h"

#define PLAYER_HEALTH 3

class PlayerActions
{
#ifdef GTESTING
public:
#else
private:
#endif
	BaseHealth healthMGR;
public:
	// Constructor 
	/// @brief sets HealthMGR equal to BaseHealth(PLAYER_HEALTH)
	PlayerActions();

	// Function
	/// @brief Allows player to check their health
	/// @param args What the player inputs
	bool processCommand(std::vector<std::string> args);
	std::string playerActionsValidCommands = "check hit ";

};