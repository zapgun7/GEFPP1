#include "cCruiseMissile.h"

// These move fast horizontally, but slow vertically
// If not on the same y as the player, they are always moving vertically
// They move set distances horizontally on intervals

cCruiseMissile::cCruiseMissile(glm::vec2 position, glm::vec2 direction)
{
	m_pTheArena = cArena::getArena();
	m_pos = position;
	m_vspeed = rand() % 12 + 6; // Randomize vertical speed
}

cCruiseMissile::~cCruiseMissile()
{

}

void cCruiseMissile::Update(double deltaTime)
{
	// Always is moving vertically if y is different than the players
	// Rapidly moves horizontally in controlled-randomized intervals

	glm::vec2 playerDir = m_pTheArena->getPlayerPosition();
	playerDir = glm::normalize(playerDir - m_pos);
	////////// VERTICAL MOVEMENT /////////
	if (playerDir.y > 0) // If player is above proj
		m_pos.y += m_vspeed * deltaTime;
	else
		m_pos.y -= m_vspeed * deltaTime;


	///////// HORIZONTAL MOVEMENT //////////
	if (m_TimeTillStopHMove > 0.0f) // If we're currently moving horizontally
	{
		m_pos.x += m_hdir.x * m_hspeed * deltaTime;
		m_TimeTillStopHMove -= deltaTime;

		if (m_TimeTillStopHMove <= 0.0f) // Prepare behavior for next frame
		{
			float hTimeRand = rand() % 25;
			hTimeRand /= 100;
			if ((rand() % 100) < 50)
				hTimeRand *= -1;

			m_TimeTillStopHMove = 0;
			m_TimeTillHMove = m_BreakHInterval + hTimeRand;
		}
	}
	else // If in-between moving horizontally
	{
		m_TimeTillHMove -= deltaTime;

		if (m_TimeTillHMove <= 0.0f) // Prepare for moving h next frame
		{
			m_TimeTillHMove = 0;
			float hTimeRand = rand() % 15;
			hTimeRand /= 100;
			if ((rand() % 100) < 50)
				hTimeRand *= -1;
			m_TimeTillStopHMove = m_MoveHInterval + hTimeRand;
			if (playerDir.x < 0) // If player to the left
				m_hdir.x = -1;
			else
				m_hdir.x = 1;
		}
	}
	// Make sure missile gets stopped by the border
	if (abs(m_pos.x) > m_XBoundary)
	{
		m_pos.x = m_XBoundary * (m_pos.x / abs(m_pos.x));
	}
	if (abs(m_pos.y) > m_YBoundary)
	{
		m_pos.y = m_YBoundary * (m_pos.y / abs(m_pos.y));
	}
}

glm::vec2 cCruiseMissile::getPosition()
{
	return m_pos;
}

void cCruiseMissile::setID(int ID)
{
	m_EntityID = ID;
}

int cCruiseMissile::getID()
{
	return m_EntityID;
}

void cCruiseMissile::setType(ProjType type)
{
	m_type = type;
}

ProjType cCruiseMissile::getType()
{
	return m_type;
}

bool cCruiseMissile::ShouldBeDestroyed()
{
	return false;
}

