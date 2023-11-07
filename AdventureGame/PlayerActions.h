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
	void healPlayer(int);

	/// @brief when player is attacked or eats a bad shroom
	void hurtPlayer(int);
	/// @brief Checks the player's health
	/// @return The players current health
	int checkPlayerHealth();

	/// @brief Checks the player's' max health
	/// @return The players max health
	int checkMaxPlayerHealth();
	std::string playerActionsValidCommands = "check hit ";

};