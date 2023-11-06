#pragma once

#include "iProjectile.h"
#include "cArena.h"


class cXShot : public  iProjectile
{
public:
	cXShot(glm::vec2 position, glm::vec2 direction);
	virtual ~cXShot();
	virtual void Update(double deltaTime);
	virtual glm::vec2 getPosition();
	virtual void setID(int ID);
	virtual int getID();
	virtual void setType(ProjType type);
	virtual ProjType getType();

private:
	ProjType m_type;
	glm::vec2 m_pos;
	glm::vec2 m_dir; // The step of the projectile per tick
	int m_EntityID;

	glm::vec2 m_hdir; // Direction bullet goes for the duration of the horizontal period

	float m_speed = 20.0f;




	cArena* m_pTheArena;
};