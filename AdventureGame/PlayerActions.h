#pragma once

#include <string>
#include <vector>

#include "BaseHealth.h"

#define PLAYER_HEALTH 3

class PlayerActions // TODO: Please convert to processCommand structure.
{
private:
	BaseHealth healthMGR;
public:
	PlayerActions();
	bool processCommand(std::vector<std::string> args);
	std::string playerActionsValidCommands = "check hit ";

};