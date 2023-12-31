#include "cHulk.h"
#include <random>
// Indestructible, follow the player slowly
// Shooting them slows them further
// Moves randomly in 4 cardinal directions

cHulk::cHulk()
{
	m_dir.x = rand() % 2;
	if (m_dir.x == 0)
	{
		if (rand() % 2 == 0)
			m_dir.y = 1;
		else
			m_dir.y = -1;
	}
	else
	{
		if (rand() % 2 == 0)
			m_dir.x *= -1;
		m_dir.y = 0;
	}
	// Just randomizes direction on spawn

}

cHulk::~cHulk()
{

}

glm::vec2 cHulk::getPos()
{
	return m_pos;
}

glm::vec2 cHulk::getDir()
{
	return m_dir;
}

int cHulk::getID()
{
	return m_EntityID;
}

RoboType cHulk::getRoboType()
{
	return m_type;
}

void cHulk::Attack()
{
	// Hulk doesn't really attack
}

void cHulk::Update(double deltaTime)
{
	// If near the border, changes direction
	// Mostly just wanders around, completely in its own world

	if (rand() % (200 - m_oddsAdjuster) == 0) // Chance to abruptly change directions
	{
		m_oddsAdjuster = 0;
		if (abs(m_pos.y) > m_YBoundary - 3) // If right on a border, have them travel away from it
		{
			m_dir.x = 0;
			if (m_pos.y > 0)
				m_dir.y = -1;
			else
				m_dir.y = 1;
		}
		else if (abs(m_pos.x) > m_XBoundary - 3) // If right on a border, have them travel away from it
		{
			m_dir.y = 0;
			if (m_pos.x > 0)
				m_dir.x = -1;
			else
				m_dir.x = 1;
		}
		else if ((abs(m_pos.x) < m_XBoundary - 3) && (abs(m_pos.y) < m_YBoundary - 3))// Regular random movement
		{
			m_dir = glm::vec2(0.0f);
			m_dir.x = rand() % 2;
			if (m_dir.x == 0)
			{
				if (rand() % 2 == 0)
					m_dir.y = 1;
				else
					m_dir.y = -1;
			}
			else
			{
				if (rand() % 2 == 0)
					m_dir.x *= -1;
			}
		}
	}

	if ((abs(m_pos.x) > m_XBoundary - 3) || (abs(m_pos.y) > m_YBoundary - 3))
	{
		findNewDirection(); // Might set a new direction
	}
	else
		m_oddsAdjuster = 0; // Don't need heightened chances of dir change if not close to a border

	if (m_timeToRecovery <= 0)
	{
		if (m_speed < m_maxSpeed)
			m_speed += m_speedRecovery * (float)deltaTime;
		if (m_speed > m_maxSpeed) // Make sure speed doesn't go over cap
			m_speed = m_maxSpeed;
	}
	else
	{
		m_timeToRecovery -= deltaTime;
	}
	m_pos += m_dir * m_speed * float(deltaTime);

	// Make sure hulk gets stopped by the border
	if (abs(m_pos.x) > m_XBoundary)
	{
		m_pos.x = m_XBoundary * (m_pos.x / abs(m_pos.x));
	}
	if (abs(m_pos.y) > m_YBoundary)
	{
		m_pos.y = m_YBoundary * (m_pos.y / abs(m_pos.y));
	}

	return;

}

// Changes direction around the area border
void cHulk::findNewDirection(void)
{
	// This only gets triggered when the hulk is near enough to a border
	// Checks if it is actively moving towards a wall that is too close, then forces a direction change
	// Otherwise if just moving along a wall encourages it to change direction by incrementing m_oddsAdjuster, which increases chance of movement in its Update()

	if (m_oddsAdjuster < 150) // Increases chance that hulk moves away from the wall the more they're against the wall
		m_oddsAdjuster++;

	if (m_dir.x == 0) // Vertical moving robit
	{
		if ((m_dir.y > 0) && (m_pos.y > m_YBoundary - 2)) // If moving up into the border
		{ // Set new direction to left, right, or down
			int randDir = rand() % 3;
			if (randDir == 0) // Set to down
			{
				m_dir.y = -1;
			}
			else if (randDir == 1) // Set to right
			{
				m_dir.y = 0;
				if (m_pos.x < m_XBoundary - 3) // Make sure it's not too close to the right wall
					m_dir.x = 1;
				else
					m_dir.x = -1;
			}
			else
			{
				m_dir.y = 0;
				if (m_pos.x < -m_XBoundary + 3) // Make sure not too close to left wall
					m_dir.x = -1;
				else
					m_dir.x = 1;
			}
		}
		else if ((m_dir.y < 0) && (m_pos.y < -m_YBoundary + 2)) // If moving down into the border
		{ // Set new direction to left, right, or up
			int randDir = rand() % 3;
			if (randDir == 0) // Set to up
			{
				m_dir.y = 1;
			}
			else if (randDir == 1) // Set to right
			{
				m_dir.y = 0;
				if (m_pos.x < m_XBoundary - 3) // Make sure it's not too close to the right wall
					m_dir.x = 1;
				else
					m_dir.x = -1;
			}
			else
			{
				m_dir.y = 0;
				if (m_pos.x < -m_XBoundary + 3) // Make sure not too close to left wall
					m_dir.x = -1;
				else
					m_dir.x = 1;
			}
		}
	}
	else // Horizontal moving robit
	{
		if ((m_dir.x > 0) && (m_pos.x > m_XBoundary - 2)) // If moving right into the border
		{ // Set new direction to up, down or left
			int randDir = rand() % 3;
			if (randDir == 0) // Set to left
			{
				m_dir.x = -1;
			}
			else if (randDir == 1) // Set to up
			{
				m_dir.x = 0;
				if (m_pos.y < m_YBoundary - 3) // Make sure not too close to ceiling
					m_dir.y = 1;
				else
					m_dir.y = -1;
				
			}
			else // Set to down
			{
				m_dir.x = 0;
				if (m_pos.y > -m_YBoundary + 3) // Make sure not too close to floor
					m_dir.y = -1;
				else
					m_dir.y = 1;
				
			}
		}
		else if ((m_dir.x < 0) && (m_pos.x < -m_XBoundary + 2)) // If moving left into the border
		{ // Set new direction to up, down or right
			int randDir = rand() % 3;
			if (randDir == 0) // Set to right
			{
				m_dir.x = 1;
			}
			else if (randDir == 1) // Set to up
			{
				m_dir.x = 0;
				if (m_pos.y < m_YBoundary - 3) // Make sure not too close to ceiling
					m_dir.y = 1;
				else
					m_dir.y = -1;
			}
			else // Set to down
			{
				m_dir.x = 0;
				if (m_pos.y > -m_YBoundary + 3) // Make sure not too close to floor
					m_dir.y = -1;
				else
					m_dir.y = 1;
			}
		}
	}
}


void cHulk::setID(int ID)
{
	m_EntityID = ID;
	return;
}

void cHulk::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
	return;
}

void cHulk::setRoboType(RoboType type)
{
	m_type = type;
	return;
}

void cHulk::isShot(glm::vec2 shotDir)
{
	m_speed -= 2.0f;
	if (m_speed < m_minSpeed)
		m_speed = m_minSpeed;

	// Make recovery delay proportional to how much it got shot
	m_timeToRecovery = (m_maxSpeed - m_speed)/3; // At most 3.33s delay

	// Hulk gets pushed a little by the bullet

	m_pos += shotDir;


	// Make sure hulk gets stopped by the border
	if (abs(m_pos.x) > m_XBoundary)
	{
		m_pos.x = m_XBoundary * (m_pos.x / abs(m_pos.x));
	}
	if (abs(m_pos.y) > m_YBoundary)
	{
		m_pos.y = m_YBoundary * (m_pos.y / abs(m_pos.y));
	}
}

bool cHulk::isSpawning(void)
{
	return false;
}

bool cHulk::ShouldBeDestroyed()
{
	return false;
}
