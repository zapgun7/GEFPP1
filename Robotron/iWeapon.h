#pragma once

#include <glm/vec2.hpp>
#include "cProjectileFactory.h"



class iWeapon
{
public:
	~iWeapon() {};

	virtual void Shoot(glm::vec2 pos, glm::vec2 dir) = 0;
	virtual void setProjectilePrinter(cProjectileFactory* newPrinter) = 0;

};