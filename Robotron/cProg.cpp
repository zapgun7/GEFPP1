// Reprogrammed humans
// Is a flashing human followed by flashing shadows	

#include "cProg.h"

cProg::cProg()
{
	m_dir = glm::vec2(0.0f, 1.0f);
	m_pTheArena = cArena::getArena();
}

cProg::~cProg()
{

}

glm::vec2 cProg::getPos()
{
	return m_pos;
}

glm::vec2 cProg::getDir()
{
	return m_dir;
}

int cProg::getID()
{
	return m_EntityID;
}

RoboType cProg::getRoboType()
{
return m_type;
}

void cProg::Attack()
{

}

void cProg::Update(double deltaTime)
{
	// Moves towards player, only in 4 cardinal directions
	// Should have it travel a distance before being able to change directions
	// Delta time based or something
	glm::vec2 playerDir = m_pTheArena->getPlayerPosition();
	playerDir = glm::normalize(playerDir - m_pos);

	if (abs(playerDir.x) > abs(playerDir.y)) // Horizontal dominant movement
	{
		playerDir.y = 0;
		glm::normalize(playerDir);
	}
	else // Vertical dominant (or equal)
	{
		playerDir.x = 0;
		glm::normalize(playerDir);
	}
	m_dir = playerDir;

	m_pos += m_dir * m_speed * (float)deltaTime;
}

void cProg::setID(int ID)
{
	m_EntityID = ID;
}

void cProg::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cProg::setRoboType(RoboType type)
{
	m_type = type;
}

void cProg::isShot(void)
{
	// Dies
}
