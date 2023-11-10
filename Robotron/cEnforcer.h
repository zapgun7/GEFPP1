#pragma once

#include "iRobotron.h"
#include "cArena.h"
#include "iWeapon.h"

enum enforcerState
{
	Far,
	Closer,
	Closest
};

class cEnforcer : public iRobotron
{
public:
	cEnforcer();
	virtual ~cEnforcer();


	virtual glm::vec2 getPos();
	virtual glm::vec2 getDir();
	virtual int getID();
	virtual RoboType getRoboType();



	virtual void Attack(); // Does nothing as a grunt
	virtual void Update(double deltaTime); // Moves closer to the player
	virtual void setID(int ID);
	virtual void setPos(glm::vec2 newPos);
	virtual void setRoboType(RoboType type);
	virtual void isShot(glm::vec2 shotDir);
	virtual bool isSpawning(void);
	virtual bool ShouldBeDestroyed();
	//virtual void setArena(cArena* arena);

	iWeapon* enforcerWeapon;

private:
	enforcerState m_state;
	RoboType m_type;
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;

	int m_XBoundary = 113;
	int m_YBoundary = 55;
	
	bool m_IsSpawning;
	double m_TimeTillSpawned;

	float m_speed;
	int m_rotate; // Direction specified by end of zooming state, which the enforcer strafes the player
	float m_ShotCooldown = 0.75f; // CHANCE to fire every .75 seconds
	double m_TimeTillNextShot = m_ShotCooldown;

	cArena* m_pTheArena;
};