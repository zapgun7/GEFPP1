// Move around the screen creating enforcer robotrons

#include "cSpheroid.h"
#include <random>
#include <glm/geometric.hpp>

cSphereoid::cSphereoid()
{
	// Randomize initial direction
	m_dir.x = (rand() % 9 + 1);
	m_dir.y = (rand() % 9 + 1);
	m_dir.x /= 10;
	m_dir.y /= 10;
	if (rand() % 2 == 0) m_dir.x *= -1;
	if (rand() % 2 == 0) m_dir.y *= -1;
	m_dir = glm::normalize(m_dir);
	m_NewDir = m_dir;
	m_ShouldBeDestroyed = false;
	m_pEnforcerSpawner = new cCharacterBuilder();

	// Randomize # of enforcers it's able to spawn before fricking off
	m_EnforcersInStock = rand() % 3 + 4;
}

cSphereoid::~cSphereoid()
{
	delete m_pEnforcerSpawner;
}

glm::vec2 cSphereoid::getPos()
{
	return m_pos;
}

glm::vec2 cSphereoid::getDir()
{
	return m_dir;
}

int cSphereoid::getID()
{
	return m_EntityID;
}

RoboType cSphereoid::getRoboType()
{
	return m_type;
}

void cSphereoid::Attack()
{
	// Spawn enforcer
}

void cSphereoid::Update(double deltaTime)
{
	// Similar to quarks, but with a bit more control, and smoother turning
	// Every 0.1s has a 1/10 chance to have a new target direction
	// Every update, shifts its actual direction a little closer to the target
	// Changes have to be more than 50 degrees from the last target direction


	m_TimeTillDirChange -= deltaTime;
	if (m_TimeTillDirChange <= 0)
	{
		m_TimeTillDirChange += m_ChangeDirInterval;
		if (rand() % 10 == 0) // Change direction
		{
			m_NewDir = m_dir;
			//acos(glm::dot(newDir, m_dir)/ glm::dot(glm::length(newDir), glm::length(m_dir)))
			float tempFlt = 0;
			while (tempFlt < 50) // Makes sure newDir is at least 60 degrees different than the old direction
			{
				m_NewDir.x = (rand() % 99 + 1);
				m_NewDir.x /= 100;
				m_NewDir.y = (rand() % 99 + 1);
				m_NewDir.y /= 100;
				if (rand() % 2 == 0) m_NewDir.x *= -1;
				if (rand() % 2 == 0) m_NewDir.y *= -1;
				m_NewDir = glm::normalize(m_NewDir);
				tempFlt = glm::degrees(abs(acos(glm::dot(m_NewDir, m_dir) / glm::length(m_NewDir) * glm::length(m_dir))));
			}
		}
	}

	// Graviatate towards newDir
	glm::vec2 travelDir = m_NewDir - m_dir;
	travelDir /= 30;
	m_dir += travelDir;


	m_pos += m_dir * m_speed * (float)deltaTime;

	// Make sure it stays within bounds
	if (abs(m_pos.x) > m_XBoundary)
	{
		m_pos.x = m_XBoundary * (m_pos.x / abs(m_pos.x));
	}
	if (abs(m_pos.y) > m_YBoundary)
	{
		m_pos.y = m_YBoundary * (m_pos.y / abs(m_pos.y));
	}


	// Spawning enforcers
	m_TimeTillEnforcerSpawn -= deltaTime;
	if (m_TimeTillEnforcerSpawn <= 0)
	{
		m_TimeTillEnforcerSpawn += m_EnforcerSpawnInterval;
		if (rand() % 10 == 0)
		{
			m_EnforcersInStock--;
			m_pEnforcerSpawner->makeCharacter("enforcer", m_pos);
			if (m_EnforcersInStock == 0)
			{
				m_ShouldBeDestroyed = true;
			}
		}
	}

}




void cSphereoid::setID(int ID)
{
	m_EntityID = ID;
	return;
}

void cSphereoid::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
	return;
}

void cSphereoid::setRoboType(RoboType type)
{
	m_type = type;
	return;
}

void cSphereoid::isShot(glm::vec2 shotDir)
{
	// aaahhh dies bleh
}

bool cSphereoid::isSpawning(void)
{
	// No spawning animation
	return false;
}

bool cSphereoid::ShouldBeDestroyed()
{
	return m_ShouldBeDestroyed; // Return a variable
}
