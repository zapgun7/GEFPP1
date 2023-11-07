// Created by the spheroids
// Track the player or move in an erratic manner
// Fire spinning x-shaped shots (visually spinning)
// Have it shoot somewhere within a range of the player, to add to randomness; this way, sometimes the enforcer will lead its shot to hit a movign player

#include "cEnforcer.h"
#include <random>

cEnforcer::cEnforcer()
{
	m_pTheArena = cArena::getArena();
	// Randomize direction
	m_dir = glm::vec2(rand() % 9 + 1, rand() % 9 + 1);
	m_dir /= 10;
	if (rand() % 2 == 0) m_dir.x *= -1;
	if (rand() % 2 == 0) m_dir.y *= -1;
	m_dir = glm::normalize(m_dir);

	m_state = Closest; // Set a state (any) to start
	m_speed = 5.0f;
	m_rotate = 0;
	m_IsSpawning = true;
	m_TimeTillSpawned = 1.0f;
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
	// Spawning behavior
	if (m_IsSpawning)
	{
		m_TimeTillSpawned -= deltaTime;
		if (m_TimeTillSpawned <= 0)
			m_IsSpawning = false;
		return;
	}

	// Moves towards player (only so close)
	// Sometimes zips off somewhere else (erratic movement)
	glm::vec2 playerPos = m_pTheArena->getPlayerPosition();
	float playerDist = glm::distance(playerPos, m_pos);
	int randStateChange = rand() % 500;
	enforcerState newState = m_state;

	// Choosing new states (Chance and distance based)
	if ((playerDist < 35) && (randStateChange < 25))
		newState = Closest;
	else if ((playerDist < 80) && (randStateChange < 10))
		newState = Closer;
	else if ((playerDist >= 80) && (randStateChange < 17))
		newState = Far;


	if (newState == Closest) // Closest
	{
		m_speed = 15.0f;
		if (m_state != Closest) // Pick new dir
		{
			m_state = Closest;
			glm::vec2 dirNoise = glm::vec2(rand() % 15, rand() % 15);
			if (rand() % 2 == 0) dirNoise.x *= -1;
			if (rand() % 2 == 0) dirNoise.y *= -1;
			m_dir = glm::normalize((playerPos + dirNoise) - m_pos);
		}
	}
	else if (newState == Closer) // Closer
	{
		m_speed = 50.0f;
		if (m_state != Closer) // Pick new dir
		{
			m_state = Closer;
			glm::vec2 dirNoise = glm::vec2(rand() % 15, rand() % 15);
			if (rand() % 2 == 0) dirNoise.x *= -1;
			if (rand() % 2 == 0) dirNoise.y *= -1;
			m_dir = glm::normalize((playerPos + dirNoise) - m_pos);
		}
	}
	else if (newState == Far) // Far
	{
		m_speed = 70.0f;
		if (m_state != Far) // Pick new dir
		{
			m_state = Far;
			glm::vec2 dirNoise = glm::vec2(rand() % 15, rand() % 15);
			if (rand() % 2 == 0) dirNoise.x *= -1;
			if (rand() % 2 == 0) dirNoise.y *= -1;
			m_dir = glm::normalize((playerPos + dirNoise) - m_pos);
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




	// Take care of shooting down here
	m_TimeTillNextShot -= deltaTime;
	if (m_TimeTillNextShot <= 0)
	{
		m_TimeTillNextShot += m_ShotCooldown;
		int randShoot = 0;
		if (m_state == Far)
			randShoot = rand() % 500;
		else if (m_state == Closer)
			randShoot = rand() % 300;
		else if (m_state == Closest)
			randShoot = rand() % 100;

		if (randShoot < 50)
		{
			enforcerWeapon->Shoot(m_pos, glm::normalize(playerPos - m_pos));
		}
	}
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

bool cEnforcer::isSpawning(void)
{
	return m_IsSpawning;
}

bool cEnforcer::ShouldBeDestroyed()
{
	return false;
}
