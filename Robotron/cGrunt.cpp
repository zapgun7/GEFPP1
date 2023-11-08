// Track and destroy the player

#include <cGrunt.h>

cGrunt::cGrunt()
{
	m_dir = glm::vec2(0, -1);
	m_pTheArena = cArena::getArena();
}

cGrunt::~cGrunt()
{

}



glm::vec2 cGrunt::getPos()
{
	return m_pos;
}

glm::vec2 cGrunt::getDir()
{
	return m_dir;
}

int cGrunt::getID()
{
	return m_EntityID;
}

RoboType cGrunt::getRoboType()
{
	return m_type;
}

void cGrunt::Attack()
{
	// grunts don't really attack..
}

void cGrunt::Update(double deltaTime) 
{
	m_TimeToNextMove -= deltaTime;
	m_TimeToSpeedUp -= deltaTime;

	if (m_TimeToSpeedUp <= 0)
	{
		m_TimeToSpeedUp += m_SpeedUpInterval;
		m_MoveInterval -= (0.05 / (rand() % 5 + 2));

		if (m_MoveInterval < 0.15) m_MoveInterval = 0.2f;
	}

	if (m_TimeToNextMove <= 0)
	{
		m_TimeToNextMove += m_MoveInterval;
		glm::vec2 moveDir = m_pTheArena->getPlayerPosition();
		moveDir = glm::normalize(moveDir - m_pos);

		// Grunts only move on diagonals, so modify moveDir accordingly
		if (abs(moveDir.x) > 0) // If some x 
			moveDir.x = abs(moveDir.x) / moveDir.x;
		else // If no x movement
			moveDir.x = 1.0f;
		if (abs(moveDir.y) > 0) // If some y 
			moveDir.y = abs(moveDir.y) / moveDir.y;
		else // If no y movement
			moveDir.y = 1.0f;

		moveDir = glm::normalize(moveDir);

		m_pos += moveDir * m_speed;
	}
}

void cGrunt::setID(int ID)
{
	m_EntityID = ID;
}

void cGrunt::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cGrunt::setRoboType(RoboType type)
{
	m_type = type;
}

void cGrunt::isShot(void)
{
	// Nothing for now...
}

bool cGrunt::isSpawning(void)
{
	return false;
}

bool cGrunt::ShouldBeDestroyed()
{
	return false;
}

