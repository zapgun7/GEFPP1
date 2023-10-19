#pragma once

#include <glm/vec2.hpp>
#include <vector>

//#include "cArena_Implementation.h"


class cArena_Implementation;

class cArena
{
public:
	~cArena();
	static cArena* getArena(void);
	glm::vec2 getClosestHuman(glm::vec2 whereIAm); // For the brains
	glm::vec2 getPlayer(glm::vec2 whereIam); // For most robotrons; will return a unit vector

private:
	cArena();
	static cArena* m_pTheOneAndOnlyArena;
	cArena_Implementation* m_pTheAcualArena;

};