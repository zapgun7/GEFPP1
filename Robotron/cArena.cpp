#include"cArena.h"
#include "cArena_Implementation.h"
#include<iostream>

cArena* cArena::m_pTheOneAndOnlyArena = NULL;




cArena::~cArena()
{
	delete this->m_pTheOneAndOnlyArena;
}

cArena* cArena::getArena(void)
{
	if (cArena::m_pTheOneAndOnlyArena == NULL)
	{
		cArena::m_pTheOneAndOnlyArena = new cArena();
	}
	return cArena::m_pTheOneAndOnlyArena;
}


glm::vec2 cArena::getClosestHuman(glm::vec2 whereIAm)
{
	this->m_pTheAcualArena->getClosestHuman(whereIAm);
}

glm::vec2 cArena::getPlayer(glm::vec2 whereIam)
{
	this->m_pTheAcualArena->getPlayer(whereIam);
}


cArena::cArena()
{
	std::cout << "cArena created." << std::endl;

	// Make the implementation
	this->m_pTheAcualArena = new cArena_Implementation();
}

