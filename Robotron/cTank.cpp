// Move in semi-tracking mode to seek out and destroy you
// Move slowly
// Fire orbs at the player that bounce off walls

#include "cTank.h"
#include <random>

cTank::cTank()
{
	m_dir = glm::vec2(0);
	if (rand() % 2 == 0)
		m_dir.x = 1;
	else
		m_dir.y = 1;
	if (rand() % 2 == 0)
		m_dir *= -1;

	m_pTheArena = cArena::getArena();
	m_IsSpawning = true;
	m_TimeTillSpawned = 0.4f;
}

cTank::~cTank()
{
	delete tankWeapon;
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
	// Moves only on diagonals
	// Tries to keep its distance from the player
	// Tries to avoid being on the player's diagonals
	// Zigzags a lot



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
	float playerDist = glm::distance(playerPos, m_pos);

	m_TimeTillNextDir -= deltaTime;
	if (m_TimeTillNextDir <= 0)
	{
		m_TimeTillNextDir += m_DirChangeInterval;
		if (rand() % 10 < 4) // Change dir
		{
			int randDist = rand() % 15 + 10; // Randomize tank behavior based on it's distance to the player relative to this randDist
			if (abs(abs(playerDir.x) - abs(playerDir.y)) < .02f) // If on a diagonal, move perpendicular
			{
				if (rand() % 2 == 0) // Randomize perpendicular direction
				{
					m_dir.x = -playerDir.y / abs(playerDir.y);
					m_dir.y = playerDir.x / abs(playerDir.x);
				}
				else
				{
					m_dir.x = playerDir.y / abs(playerDir.y);
					m_dir.y = -playerDir.x / abs(playerDir.x);
				}
				m_dir = glm::normalize(m_dir);
			}
			else if (abs(playerDir.x) > abs(playerDir.y)) //Horizontal dominant
			{
				// Start by randomizing the y direction
				if (rand() % 2 == 0) m_dir.y = 1;
				else m_dir.y = -1;

				if (playerDir.x > 0) // Left of the player
				{
					if (playerDist <= randDist) m_dir.x = -1; // Too close, move away

					else m_dir.x = 1;

				}
				else // Right of the player
				{
					if (playerDist <= randDist) m_dir.x = 1; // Too close, move away

					else m_dir.x = -1;
				}
			}
			else // Vertical dominant (or equal whatever)
			{
				// Start by randomizing the y direction
				if (rand() % 2 == 0) m_dir.x = 1;
				else m_dir.x = -1;

				if (playerDir.y < 0) // Above the player
				{
					if (playerDist <= randDist) m_dir.y = 1; // Too close, move away

					else m_dir.y = -1;
				}
				else // Below the player
				{
					if (playerDist <= randDist) m_dir.y = -1; // Too close, move away

					else m_dir.y = 1;
				}
			}
			m_dir = glm::normalize(m_dir);
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

	// Shooting
	m_TimeTillNextShot -= deltaTime;
	if (m_TimeTillNextShot <= 0)
	{
		m_TimeTillNextShot += m_ShootInterval;
		if (rand() % 2 == 0)
		{
			glm::vec2 dirNoise;
			// Start by randomly choosing 1 of 2 perpendicular directions to the player direction
			if (rand() % 2 == 0) dirNoise = glm::vec2(-playerDir.y, playerDir.x);
			else dirNoise = glm::vec2(playerDir.y, -playerDir.x);

			// Randomize how much the base direction will be influenced by the noise
			playerDir *= rand() % 5 + 10;

			// Add the noise and normalize
			playerDir += dirNoise;
			playerDir = glm::normalize(playerDir);

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

void cTank::isShot(glm::vec2 shotDir)
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
