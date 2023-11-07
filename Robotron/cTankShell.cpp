
#include "cTankShell.h"

cTankShell::cTankShell(glm::vec2 position, glm::vec2 direction)
{
	m_pos = position;
	m_dir = direction;

	m_speed = 80.0f;
	bShouldBeDestroyed = false;

	m_TimeAlive = 8.0f; // 8s of bullet time, border hits reducing it
}

cTankShell::~cTankShell()
{

}

void cTankShell::Update(double deltaTime)
{
	// Move in direction, bounce off border

	m_pos += m_dir * m_speed * (float)deltaTime;

	if (abs(m_pos.x) > m_XBoundary - 1)
	{
		m_TimeAlive -= 2;
		m_pos.x = (m_XBoundary - 1) / (m_pos.x / abs(m_pos.x));
		m_dir.x *= -1;
	}
	if (abs(m_pos.y) > m_YBoundary - 1)
	{
		m_TimeAlive -= 2;
		m_pos.y = (m_YBoundary - 1) / (m_pos.y / abs(m_pos.y));
		m_dir.y *= -1;
	}

	if (m_TimeAlive <= 0)
		bShouldBeDestroyed = true;
}

glm::vec2 cTankShell::getPosition()
{
	return m_pos;
}

void cTankShell::setID(int ID)
{
	m_EntityID = ID;
}

int cTankShell::getID()
{
	return m_EntityID;
}

void cTankShell::setType(ProjType type)
{
	m_type = type;
}

ProjType cTankShell::getType()
{
	return m_type;
}

bool cTankShell::ShouldBeDestroyed()
{
	return bShouldBeDestroyed;
}

