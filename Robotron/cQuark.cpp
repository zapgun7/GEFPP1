// Pulsing square, aka cubeoid
// Move quickly and erratically around the screen creating tanks
// Will disappear if not destroyed or sufficient tanks created

#include "cQuark.h"

cQuark::cQuark()
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
	m_pTankSpawner = new cCharacterBuilder();

	// Randomize # of enforcers it's able to spawn before fricking off
	m_TanksInStock = rand() % 3 + 4;

	m_speed = rand() % 10 + 15;
}

cQuark::~cQuark()
{
	delete m_pTankSpawner;
}

glm::vec2 cQuark::getPos()
{
	return m_pos;
}

glm::vec2 cQuark::getDir()
{
	return m_dir;
}

int cQuark::getID()
{
	return m_EntityID;
}

RoboType cQuark::getRoboType()
{
	return m_type;
}

void cQuark::Attack()
{
	// Spawn tank
}

void cQuark::Update(double deltaTime)
{
	// Moves very erratically, choosing a new direction and speed on a whim (every 0.5s a 1/3 chance)
	// Disappears from the arena upon running out of enforcers left to spawn

	m_TimeTillDirChange -= deltaTime;
	if (m_TimeTillDirChange <= 0)
	{
		m_TimeTillDirChange += m_DirChangeInterval;

		if (rand() % 3)
		{
			// Randomize direction
			m_dir.x = (rand() % 99 + 1);
			m_dir.y = (rand() % 99 + 1);
			m_dir.x /= 100;
			m_dir.y /= 100;
			if (rand() % 2 == 0) m_dir.x *= -1;
			if (rand() % 2 == 0) m_dir.y *= -1;
			m_dir = glm::normalize(m_dir);

			// Now randomize speed
			m_speed = rand() % 70 + 20;
		}
	}

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
	m_TimeTillTankSpawn -= deltaTime;
	if (m_TimeTillTankSpawn <= 0)
	{
		m_TimeTillTankSpawn += m_TankSpawnInterval;
		if (rand() % 10 == 0)
		{
			m_TanksInStock--;
			m_pTankSpawner->makeCharacter("tank", m_pos);
			if (m_TanksInStock == 0)
			{
				m_ShouldBeDestroyed = true;
			}
		}
	}
}

void cQuark::setID(int ID)
{
	m_EntityID = ID;
}

void cQuark::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cQuark::setRoboType(RoboType type)
{
	m_type = type;
}

void cQuark::isShot(glm::vec2 shotDir)
{
	// Dies?
}

bool cQuark::isSpawning(void)
{
	// No spawning animation
	return false;
}

bool cQuark::ShouldBeDestroyed()
{
	return m_ShouldBeDestroyed;
}
