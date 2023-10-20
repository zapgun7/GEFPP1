#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(glm::vec2 position, glm::vec2 direction)
{
	pos = position;
	dir = direction;
	//speed = 1.0f;
}

cPlayerBullet::~cPlayerBullet()
{
	// bullet is destroyed
}

void cPlayerBullet::Update()
{
	pos += dir*speed;
	return;
}

glm::vec2 cPlayerBullet::getPosition()
{
	return pos;
}

void cPlayerBullet::setID(int ID)
{
	entityID = ID;
}

int cPlayerBullet::getID()
{
	return entityID;
}
