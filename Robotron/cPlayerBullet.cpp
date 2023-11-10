#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(glm::vec2 position, glm::vec2 direction)
{
	m_pos = position;
	m_dir = direction;
	//speed = 1.0f;
}

cPlayerBullet::~cPlayerBullet()
{
	// bullet is destroyed
}

void cPlayerBullet::Update(double deltaTime)
{
	// What a simple projectile :)

	m_pos += m_dir * speed * (float)deltaTime;
	return;
}

glm::vec2 cPlayerBullet::getPosition()
{
	return m_pos;
}

glm::vec2 cPlayerBullet::getDir()
{
	return m_dir;
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

bool cPlayerBullet::ShouldBeDestroyed()
{
	return false;
}
