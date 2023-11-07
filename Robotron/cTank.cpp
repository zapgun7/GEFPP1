// Move in semi-tracking mode to seek out and destroy you
// Move slowly
// Fire orbs at the player that bounce off walls

#include "cTank.h"

cTank::cTank()
{
	m_dir = glm::vec2(0, -1);
	m_pTheArena = cArena::getArena();
	m_IsSpawning = true;
	m_TimeTillSpawned = 0.4f;
}

cTank::~cTank()
{

}

glm::vec2 cTank::getPos()
{
	return m_pos;
}

glm::vec2 cTank::getDir()
{
	return m_dir;
}

int cTank::getID()
{
	return m_EntityID;
}

RoboType cTank::getRoboType()
{
	return m_type;
}

void cTank::Attack()
{
	tankWeapon->Shoot(m_pos, m_dir); // Prob want the dir to be at the player
}

void cTank::Update(double deltaTime)
{
	// Spawning behavior
	if (m_IsSpawning)
	{
		m_TimeTillSpawned -= deltaTime;
		if (m_TimeTillSpawned <= 0)
			m_IsSpawning = false;
		return;
	}



	glm::vec2 playerPos = m_pTheArena->getPlayerPosition();
	glm::vec2 playerDir = glm::normalize(playerPos - m_pos);
	m_dir = playerDir;
	// Move towards player in a tanky way
	// They prefer to move on diagonals, stay around a players diagonal
	// Prefer to keep a certain distance from the player

	m_pos += m_dir * m_speed * (float)deltaTime;


	// Shooting
	m_TimeTillNextShot -= deltaTime;
	if (m_TimeTillNextShot <= 0)
	{
		m_TimeTillNextShot += m_ShootInterval;
		if (rand() % 5 == 0)
		{
			tankWeapon->Shoot(m_pos, playerDir); // Maybe add some noise to playerdir so it doesn't just shoot at where the player was
		}
	}
}

void cTank::setID(int ID)
{
	m_EntityID = ID;
}

void cTank::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cTank::setRoboType(RoboType type)
{
	m_type = type;
}

void cTank::isShot(void)
{
	// nothing
}

bool cTank::isSpawning(void)
{
	// Will actually have a spawning animation much like the enforcers
	return m_IsSpawning;
}

bool cTank::ShouldBeDestroyed()
{
	return false;
}
