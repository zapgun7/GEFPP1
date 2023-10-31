#include "cHuman.h"
#include <random>



cHuman::cHuman()
{
	m_dir = glm::vec2(0, -1);
	//m_pTheArena = cArena::getArena();
}

cHuman::~cHuman()
{

}

// Player wants to save these
// Stationary? Player gets 1000 points for saving one, 2000 for one more, etc up to 5000
// Can get turned into an enemy by the brains

glm::vec2 cHuman::getPos()
{
	return m_pos;
}

glm::vec2 cHuman::getDir()
{
	return m_dir;
}

int cHuman::getID()
{
	return m_EntityID;
}

void cHuman::Update(double deltaTime)
{
	if (rand() % 50 == 1)
	{
		// Change dir to some other direction
	}
	m_pos += m_dir * m_Speed;

	return;
}

void cHuman::setID(int ID)
{
	m_EntityID = ID;
}

void cHuman::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}
