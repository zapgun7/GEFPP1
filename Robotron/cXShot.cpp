// Initializes with random accel in some direction on top of regular velocity towards shooting location

#include "cXShot.h"

cXShot::cXShot(glm::vec2 position, glm::vec2 direction)
{
	m_pos = position;
	m_dir = direction;
	m_pTheArena = cArena::getArena();
	// When this gets created, randomize private values to influence how it flies (random scalars for sin and cos (maybe tan??))
}

cXShot::~cXShot()
{

}

void cXShot::Update(double deltaTime)
{
	// Moves relative to the initial position
	// Changes weirdly: Keep original direction, add to position some multiple of the direction, plus some sin/cos shit to the perpendicular direction, to make it all wacky
	// For now, have it shoot in a straight line

	m_pos += m_dir * m_speed * (float)deltaTime;
}

glm::vec2 cXShot::getPosition()
{
	return m_pos;
}

void cXShot::setID(int ID)
{
	m_EntityID = ID;
}

int cXShot::getID()
{
	return m_EntityID;
}

void cXShot::setType(ProjType type)
{
	m_type = type;
}

ProjType cXShot::getType()
{
	return m_type;
}
