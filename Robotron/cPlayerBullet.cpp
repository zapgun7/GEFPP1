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

void cPlayerBullet::Update(double deltaTime)
{
	pos += dir * speed * (float)deltaTime;
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

void cPlayerBullet::setType(ProjType type)
{
	m_type = type;
}

ProjType cPlayerBullet::getType()
{
	return m_type;
}
