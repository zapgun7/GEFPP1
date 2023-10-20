#pragma once

#include <glm/vec2.hpp>
#include <string>
//#include "cArena.h"
#include "cMeshFactory.h"

class cProjectileFactory
{
public:
	cProjectileFactory();
	void makeProjectile(std::string proj, glm::vec2 pos, glm::vec2 dir);



private:
	//cArena* m_TheArena;
	cMeshFactory* m_pMeshFactory;
};