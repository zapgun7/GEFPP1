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
	return this->m_pTheAcualArena->getClosestHuman(whereIAm);
}

glm::vec2 cArena::getPlayer(glm::vec2 whereIam)
{
	return this->m_pTheAcualArena->getPlayer(whereIam);
}


void cArena::Initialize()
{
	this->m_pTheAcualArena->Initialize();
	return;
}

void cArena::storeKeys(std::vector<bool> keys)
{
	this->m_pTheAcualArena->storeKeys(keys);
	return;
}

void cArena::Update()
{
	this->m_pTheAcualArena->Update();
	return;
}

cArena::cArena()
{
	std::cout << "cArena created." << std::endl;

	// Make the implementation
	this->m_pTheAcualArena = new cArena_Implementation();
}

