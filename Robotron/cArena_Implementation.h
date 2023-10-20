#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <map>

#include "cHuman.h"
#include "iRobotron.h"
#include "cPlayer.h"
#include "cMeshFactory.h"
#include "cGraphicsMain.h"


class cArena_Implementation
{
public:
	cArena_Implementation();		// Can't be called by anything but "me" (i.e. the cArena class)
	~cArena_Implementation();

	glm::vec2 getClosestHuman(glm::vec2 whereIAm); // For the brains
	glm::vec2 getPlayer(glm::vec2 whereIam); // For most robotrons; will return a unit vector
	void Initialize();
	void storeKeys(std::vector<bool> keys); // GLFW call back calls this to store key inputs for later parsing
	void Update();

private:
	AnimationInfo* findAnimInfoByID(int ID);

	std::vector<bool> m_keysPressed; // Last recorded user input
	std::vector<iRobotron*> m_robotrons; // Vector of all enemies
	std::vector<cHuman*> m_humans; // Vector of all existing humans
	cPlayer* m_thePlayer;
	double lastTime; // Time at last update; used for delta time
	int nextID = 0; // Unique ID assigned to each entity
	std::map<int, AnimationInfo*> m_spriteIDMap; // Map matching unique ID to sprite information
	cMeshFactory* m_meshFactory;
	cGraphicsMain* m_graphMain;
};