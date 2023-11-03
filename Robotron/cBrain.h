#pragma once

#include "iRobotron.h"
#include "cArena.h"
#include "iWeapon.h"

class cBrain : public iRobotron
{
public:
	cBrain();
	virtual ~cBrain();


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
	//virtual void setArena(cArena* arena);

	iWeapon* brainWeapon;

private:
	

	RoboType m_type;
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;


	float const m_speed = 13.0f;
	float const m_ShootInterval = 1.0f; // Time between moving
	float m_TimeToNextShoot = m_ShootInterval;

	cArena* m_pTheArena;
};

