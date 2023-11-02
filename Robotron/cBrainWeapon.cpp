
#include "cBrainWeapon.h"

cBrainWeapon::cBrainWeapon()
{
	// Brain weapon created
}

cBrainWeapon::~cBrainWeapon()
{
	delete pProjectilePrinter;
}

void cBrainWeapon::Shoot(glm::vec2 pos, glm::vec2 dir)
{
	pProjectilePrinter->makeProjectile("brain", pos, dir);
}

void cBrainWeapon::setProjectilePrinter(cProjectileFactory* newPrinter)
{
	pProjectilePrinter = newPrinter;
}

