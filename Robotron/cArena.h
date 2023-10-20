#pragma once

#include <glm/vec2.hpp>
#include <vector>

#include "cPlayer.h"
#include "iRobotron.h"
#include "iProjectile.h"
#include "cMeshFactory.h"

//#include "cArena_Implementation.h"


class cArena_Implementation;

class cArena
{
public:
	~cArena();
	static cArena* getArena(void);
	glm::vec2 getClosestHuman(glm::vec2 whereIAm); // For the brains
	glm::vec2 getPlayer(glm::vec2 whereIam); // For most robotrons; will return a unit vector

	void setPlayer(cPlayer* player, AnimationInfo* newInfo);
	void addRobotron(iRobotron* newRobo, AnimationInfo* newInfo);
	void addProjectile(iProjectile* newProjectile, AnimationInfo* newInfo);

	void Initialize();
	void storeKeys(std::vector<bool> keys);
	void Update(); // THE update (loop)

private:
	cArena();
	static cArena* m_pTheOneAndOnlyArena;
	cArena_Implementation* m_pTheAcualArena;

};