#pragma once

//#include <glm/vec2.hpp>
//#include "cArena.h"
#include "iRobotron.h"
#include "cCharacterBuilder.h" // Because it spawns enforcers

class cSphereoid : public iRobotron
{
public:
	cSphereoid();
	virtual ~cSphereoid();


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

	RoboType m_type;
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;
	
	glm::vec2 m_NewDir; // Direction for m_dir to gravitate towards

	bool m_ShouldBeDestroyed; // Is true when there's no enforcers left
	int m_EnforcersInStock; // number of enforcers left to spawn

	float const m_EnforcerSpawnInterval = 0.3f;
	double m_TimeTillEnforcerSpawn = m_EnforcerSpawnInterval;

	float const m_ChangeDirInterval = 0.1f;
	double m_TimeTillDirChange = m_ChangeDirInterval;

	// Map boundary
	int m_XBoundary = 113;
	int m_YBoundary = 55;

	float const m_speed = 30.0f;


	cCharacterBuilder* m_pEnforcerSpawner;

};