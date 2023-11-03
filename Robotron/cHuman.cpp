#include "cHuman.h"
#include <random>



cHuman::cHuman()
{
	//srand(time(NULL));
	// Randomize the human's starting direction
	m_dir = glm::vec2(rand() %10 + 1, rand() %10 + 1);

	if (rand() % 2 == 0)
		m_dir.x *= -1;
	if (rand() % 2 == 0)
		m_dir.y *= -1;

	m_dir = glm::normalize(m_dir);


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

void cHuman::Update(double deltaTime) // Walk in a straight line until it comes close to a boarder, then pick a new dir?
{
	if ((abs(m_pos.x) > m_XBoundary - 1) || (abs(m_pos.y) > m_YBoundary - 1))
	{
		findNewDirection(); // Might set a new direction
	}


	m_pos += m_dir * m_Speed * (float)deltaTime;

	return;
}

// Checks to see if the current direction is in the direction of a wall they are adjacent to, if they are it rerolls their direction
void cHuman::findNewDirection()
{
	bool isXProblem = false;
	bool isYProblem = false;
	if (abs(m_pos.x) > m_XBoundary - 1) // X-Boundary problem
	{
		if ((m_pos.x < 0) && (m_dir.x < 0)) // Left-side screen issue
		{
			isXProblem = true;
			m_dir.x = rand() % 10 + 1;
		}
		else if ((m_pos.x > 0) && (m_dir.x > 0)) // Right-side screen issue
		{
			isXProblem = true;
			m_dir.x = (rand() % 10 + 1) * -1;
		}
	}
	if (abs(m_pos.y) > m_YBoundary - 1)// Y-Boundary problem
	{
		if ((m_pos.y < 0) && (m_dir.y < 0)) // Bottom of screen issue
		{
			isYProblem = true;
			m_dir.y = rand() % 10 + 1;
		}
		else if ((m_pos.y > 0) && (m_dir.y > 0)) // Top of screen issue
		{
			isYProblem = true;
			m_dir.y = (rand() % 10 + 1) * -1;
		}
	}
	if ((isXProblem) && (!isYProblem)) // Only x problem
	{ // So randomize new y dir in any direction
		m_dir.y = rand() % 11;
		if (rand() % 2 == 0)
			m_dir.y *= -1;
	}
	else if ((!isXProblem) && (isYProblem)) // Only y problem
	{ // So randomize new x dir in any direction
		m_dir.x = rand() % 11;
		if (rand() % 2 == 0)
			m_dir.x *= -1;
	}
	if ((isXProblem) || (isYProblem))
	{
		m_dir = glm::normalize(m_dir);
	}

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
