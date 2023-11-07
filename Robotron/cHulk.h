#pragma once
#include "iRobotron.h"
#include <glm/vec2.hpp>


class cHulk : public iRobotron
{
public:
	cHulk();
	virtual ~cHulk();


	virtual glm::vec2 getPos();
	virtual glm::vec2 getDir();
	virtual int getID();
	virtual RoboType getRoboType();



	virtual void Attack(); // Does nothing as a grunt
	virtual void Update(double deltaTime); // Moves closer to the player
	virtual void setID(int ID);
	virtual void setPos(glm::vec2 newPos);
	virtual void setRoboType(RoboType type);
	virtual void isShot(void);
	virtual bool isSpawning(void);
	virtual bool ShouldBeDestroyed();
	//virtual void setArena(cArena* arena);

private:
	void findNewDirection(void);
	// Map boundary
	int m_XBoundary = 113;
	int m_YBoundary = 55;

	RoboType m_type;
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;

	int m_oddsAdjuster = 0;
	float const m_maxSpeed = 15.0f;
	float const m_minSpeed = 5.0f;
	float const m_speedRecovery = 5.0f;
	double m_timeToRecovery = 0; // Delay speed recovery after getting shot
	float m_speed = m_maxSpeed;


};