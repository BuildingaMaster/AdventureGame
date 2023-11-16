#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "BaseHealth.h"
#include "NPC.h"


#define PLAYER_HEALTH 3

class PlayerActions
{
#ifdef GTESTING
public:
#else
private:
#endif
	BaseHealth healthMGR;
	bool playerIsHigh;
	int stepsUntilNotHigh;
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

	/// @brief Checks if the player is dead. Who killed him?
	/// @return true if the player is dead.
	bool thePlayerIsDead();

	/// @brief Is the player high?
	/// @return True if yes
	bool isThePlayerHigh();

	/// @brief Sets if the player is "high"
	/// @param ishigh - true if high
	void thePlayerIsHigh(bool);

	/// @brief Sets the number of moves before the effect wears off.
	/// @param moves Number of moves
	void highForNMoves(int);

	/// @brief The effect slowly wears off.
	void decrementMovingHigh();
	std::string playerActionsValidCommands = "check hit ";

	/// @brief The player is asked to play the game again
	bool playAgain();
};