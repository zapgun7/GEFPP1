#pragma once

#include "iProjectile.h"
#include <glm/vec2.hpp>

class cPlayerBullet : public iProjectile
{
public:
	cPlayerBullet(glm::vec2 position, glm::vec2 direction);
	virtual ~cPlayerBullet();
	virtual void Update();
	virtual glm::vec2 getPosition();
	virtual void setID(int ID);
	virtual int getID();

private:
	glm::vec2 pos;
	glm::vec2 dir; // The step of the projectile per tick
	float const speed = 3.0f;
	int entityID;
};