// Track and destroy the player

#include <cGrunt.h>

cGrunt::cGrunt()
{

}

cGrunt::~cGrunt()
{

}



bool cGrunt::isDead()
{
	return isDestroyed;
}

glm::vec2 cGrunt::getLocation()
{
	return pos;
}

void cGrunt::Action()
{

}

void cGrunt::Update() // Should pass it a position to its nearest target, or have a function call in the mediator for different requests
{

}
