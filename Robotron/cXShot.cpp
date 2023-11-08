// Initializes with random accel in some direction on top of regular velocity towards shooting location

#include "cXShot.h"
#include <random>

cXShot::cXShot(glm::vec2 position, glm::vec2 direction)
{
	float playerDist = glm::length(direction); // Speed will scale off distance to the player
	m_pos = position;
	m_dir = glm::normalize(direction);
	//m_pTheArena = cArena::getArena();
	// When this gets created, randomize private values to influence how it flies (random scalars for sin and cos (maybe tan??))
	// Property randomization
	
	m_speed = rand() % 20 + 20 + (playerDist * 0.7f);
	m_curve = (rand() % 10 + 1);
	m_curve /= 10; // Base curve influence reduction

	while (rand() % 10 < 7) // Push odds in favor of having the curve influence less; super curved shots are rarer
		m_curve /= 2;
	if (rand() % 2 == 0)
		m_curve *= -1;

}

cXShot::~cXShot()
{

}

void cXShot::Update(double deltaTime)
{
	// Pretty funky little projectile: Fires in a direction with a little noise added
	// Upon being made generates a "curve" strength, which adds perpendicular (to its current direction) force to its direction
	// If against the wall for long enough, expires
	// Possible for it to be perpetually spinning (not able to hit the wall for long enough), but it's rare so I thought it was fun

	bool isHittingBorder = false;
	
	glm::vec2 curve;
	if (m_curve < 0)
		curve = glm::vec2(m_dir.y, -m_dir.x);
	else
		curve = glm::vec2(-m_dir.y, m_dir.x);

	m_dir *= 100;
	m_dir += curve * abs(m_curve);
	m_dir = glm::normalize(m_dir);



	m_pos += m_dir * m_speed * (float)deltaTime;

	// Make sure xshot gets stopped by the border
	if (abs(m_pos.x) > m_XBoundary)
	{
		m_pos.x = m_XBoundary * (m_pos.x / abs(m_pos.x));
		isHittingBorder = true;
	}
	if (abs(m_pos.y) > m_YBoundary)
	{
		m_pos.y = m_YBoundary * (m_pos.y / abs(m_pos.y));
		isHittingBorder = true;
	}
	if (isHittingBorder)
		m_BorderHits++;
	else if (m_BorderHits > 0) // Make it so bullets can rarely loop in the arena
		m_BorderHits--;
	if (m_BorderHits > 200)
		bShouldBeDestroyed = true;
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

bool cXShot::ShouldBeDestroyed()
{
	return bShouldBeDestroyed;
}
