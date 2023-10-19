#pragma once

#include <glm/vec2.hpp>
#include <vector>

#include "cHuman.h"
#include "iRobotron.h"


class cArena_Implementation
{
public:
	cArena_Implementation();		// Can't be called by anything but "me" (i.e. the cArena class)
	~cArena_Implementation();

	glm::vec2 getClosestHuman(glm::vec2 whereIAm); // For the brains
	glm::vec2 getPlayer(glm::vec2 whereIam); // For most robotrons; will return a unit vector

private:
	std::vector<iRobotron> robotrons; // Vector of all enemies
	std::vector<cHuman> humans; // Vector of all existing humans
};