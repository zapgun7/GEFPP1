// Seek out humans and reprogram them
// If no humans left, will seek player and destroy them
// Fire cruise missiles -> move very slowly vertically, but much faster horizontally
#include "cBrain.h"

cBrain::cBrain()
{
	m_dir = glm::vec2(0, -1);
	m_pTheArena = cArena::getArena();
}

cBrain::~cBrain()
{

}

glm::vec2 cBrain::getPos()
{
	return m_pos;
}

glm::vec2 cBrain::getDir()
{
	return m_dir;
}

int cBrain::getID()
{
	return m_EntityID;
}

RoboType cBrain::getRoboType()
{
	return m_type;
}

void cBrain::Attack()
{
	brainWeapon->Shoot(m_pos, m_dir);
}

void cBrain::Update(double deltaTime)
{
	// Move toward human if they exist
	// Move (toward player/randomly?) and shoot at them otherwise
	glm::vec2 humanPos = m_pTheArena->getClosestHuman(m_pos);

	if (humanPos.x == 999) // No more humans
	{

	}
	else // Move towards human
	{
		glm::vec2 newDir = glm::normalize(humanPos - m_pos);
		if (abs(newDir.x) > .75f) // Horizontal dominant, remove y component and renormalize
		{
			newDir.y = 0;
			newDir = glm::normalize(newDir);
		}
		else if (abs(newDir.y) > .75f) // Vertical dominant, do same for above but vertically
		{
			newDir.x = 0;
			newDir = glm::normalize(newDir);
		}
		else // Neither are dominant, equate their abs
		{
			newDir.x /= abs(newDir.x);
			newDir.y /= abs(newDir.y);
			newDir = glm::normalize(newDir);
		}
		m_dir = newDir;
	}
	

	m_pos += m_dir * m_speed * (float)deltaTime;
}

void cBrain::setID(int ID)
{
	m_EntityID = ID;
}

void cBrain::setPos(glm::vec2 newPos)
{
	m_pos = newPos;
}

void cBrain::setRoboType(RoboType type)
{
	m_type = type;
}

void cBrain::isShot(void)
{
	// Does nothing
}
