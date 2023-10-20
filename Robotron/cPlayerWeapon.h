#pragma once

#include <glm/vec2.hpp>
#include "cProjectileFactory.h"
#include "iWeapon.h"

class cPlayerWeapon : public iWeapon
{
public:
	cPlayerWeapon();
	virtual ~cPlayerWeapon();
	virtual void Shoot(glm::vec2 pos, glm::vec2 dir); // Calls bullet factory; character controls the amount this function is called
	virtual void setProjectilePrinter(cProjectileFactory* newPrinter);
	cProjectileFactory* pProjectilePrinter;


private:
	
};