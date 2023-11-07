#pragma once

#include "iWeapon.h"


class cTankWeapon : public iWeapon
{
public:
	cTankWeapon();
	virtual ~cTankWeapon();
	virtual void Shoot(glm::vec2 pos, glm::vec2 dir); // Calls bullet factory; character controls the amount this function is called
	virtual void setProjectilePrinter(cProjectileFactory* newPrinter);



private:
	cProjectileFactory* m_pProjectilePrinter;

};