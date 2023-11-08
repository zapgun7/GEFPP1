#pragma once

#include "iProjectile.h"
#include "cArena.h"

class cCruiseMissile : public iProjectile
{
public:
	cCruiseMissile(glm::vec2 position, glm::vec2 direction);
	virtual ~cCruiseMissile();
	virtual void Update(double deltaTime);
	virtual glm::vec2 getPosition();
	virtual void setID(int ID);
	virtual int getID();
	virtual void setType(ProjType type);
	virtual ProjType getType();
	virtual bool ShouldBeDestroyed(); // Way for projectile to terminate itself via the arena

private:
	ProjType m_type;
	glm::vec2 m_pos;
	glm::vec2 m_dir; // The step of the projectile per tick
	int m_EntityID;

	glm::vec2 m_hdir; // Direction bullet goes for the duration of the horizontal period

	int m_XBoundary = 113;
	int m_YBoundary = 55;

	float const m_hspeed = 100.0f; // Horizontal speed
	float const m_BreakHInterval = 0.4f; // 400ms      Time between end and start of horizontal movement
	double m_TimeTillHMove = m_BreakHInterval;         // The current time left between end and start of horizontal movement
	float const m_MoveHInterval = 0.25f;    // Time projectile spends moving horizontally
	double m_TimeTillStopHMove = 0.0f; // Time left able to move horizontally

	float m_vspeed = 15.0f; // Vertical speed




	cArena* m_pTheArena;
};