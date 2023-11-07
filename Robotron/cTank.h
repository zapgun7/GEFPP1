#pragma once


#include "iRobotron.h"
#include "iWeapon.h"
#include "cArena.h"

class cTank : public iRobotron
{
public:
	cTank();
	virtual ~cTank();


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

	iWeapon* tankWeapon;

private:
	RoboType m_type;
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;


	bool m_IsSpawning;
	double m_TimeTillSpawned;

	int m_XBoundary = 113;
	int m_YBoundary = 55;

	float const m_DirChangeInterval = 0.5f;
	double m_TimeTillNextDir = m_DirChangeInterval;

	float const m_ShootInterval = 2.0f;
	double m_TimeTillNextShot = m_ShootInterval;

	float const m_speed = 20.0f;


	cArena* m_pTheArena;
};