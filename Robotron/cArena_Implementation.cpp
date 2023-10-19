#include "cArena_Implementation.h"

#include <iostream>

cArena_Implementation::cArena_Implementation()
{
	std::cout << "cArena_Implementation created." << std::endl;
	//this->pTheWeaponFactory = new cWeaponMaker();
	//this->m_arenaSizeInMeters = 0.0f;
}

cArena_Implementation::~cArena_Implementation()
{
	//delete this->pTheWeaponFactory;
}

glm::vec2 cArena_Implementation::getClosestHuman(glm::vec2 whereIAm)
{
	glm::vec2 closestCoord = glm::vec2(999, 999);
	if (humans.size() == 0)
		return closestCoord; // Returns something outside the arena when no humans, will check for this
	closestCoord = humans[0].getPos();
	for (unsigned int i = 1; i < humans.size(); i++)
	{
		//		if()
	}
	return closestCoord;
}

glm::vec2 cArena_Implementation::getPlayer(glm::vec2 whereIam)
{

}
