// Created by the spheroids
// Track the player or move in an erratic manner
// Fire spinning x-shaped shots (visually spinning)
// Have it shoot somewhere within a range of the player, to add to randomness; this way, sometimes the enforcer will lead its shot to hit a movign player

#include "cEnforcer.h"

cEnforcer::cEnforcer()
{
	m_pTheArena = cArena::getArena();
	m_dir = glm::vec2(0, -1);
}

cEnforcer::~cEnforcer()
{

}

glm::vec2 cEnforcer::getPos()
{
	return m_pos;
}

glm::vec2 cEnforcer::getDir()
{
	return m_dir;
}

int cEnforcer::getID()
{
	return m_EntityID;
}

RoboType cEnforcer::getRoboType()
{
	return m_type;
}

void cEnforcer::Attack()
{
	enforcerWeapon->Shoot(m_pos, m_dir);
}

void cEnforcer::Update(double deltaTime)
{
	// Moves towards player (only so close)
	// Sometimes zips off somewhere else (erratic movement)

	// Start off by just gravitating towards player
	glm::vec2 playerPos = m_pTheArena->getPlayerPosition();
	m_dir = glm::normalize(playerPos - m_pos);



	m_pos += m_dir * m_speed * (float)deltaTime;
}

void cEnforcer::setID(int ID)
{
	m_EntityID = ID;
}

void cEnforcer::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cEnforcer::setRoboType(RoboType type)
{
	m_type = type;
}

void cEnforcer::isShot(void)
{
	// Dies I guess
}
