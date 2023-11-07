#pragma once

#include <glm/vec2.hpp>
enum ProjType
{
	PBullet,
	CMissile,
	XShot
};

class iProjectile
{
public:
	virtual ~iProjectile() {};

	virtual void Update(double deltaTime) = 0; // To increment movement
	virtual glm::vec2 getPosition() = 0; // For mediator to check for hits
	virtual void setID(int ID) = 0;
	virtual int getID() = 0;
	virtual void setType(ProjType type) = 0;
	virtual ProjType getType() = 0;
	virtual bool ShouldBeDestroyed() = 0;
	//virtual void Destroy() = 0; // For mediator to call when projectile hits something that would destroy it
};