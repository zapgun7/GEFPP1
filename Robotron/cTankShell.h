#pragma once

#include "iProjectile.h"
#include "cArena.h"

class cTankShell : public iProjectile
{
public:
	cTankShell(glm::vec2 position, glm::vec2 direction);
	virtual ~cTankShell();
	virtual void Update(double deltaTime);
	virtual glm::vec2 getPosition();
	virtual void setID(int ID);
	virtual int getID();
	virtual void setType(ProjType type);
	virtual ProjType getType();
	virtual bool ShouldBeDestroyed(); // Way for projectile to terminate itself via the arena

	bool bShouldBeDestroyed = false; // Triggers if it hits the border enough times

private:
	ProjType m_type;
	glm::vec2 m_pos;
	glm::vec2 m_dir; // The step of the projectile per tick
	int m_EntityID;


	float m_speed;
	double m_TimeAlive;

	int m_XBoundary = 113;
	int m_YBoundary = 55;





	//cArena* m_pTheArena;

};