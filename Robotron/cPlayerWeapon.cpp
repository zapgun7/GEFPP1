#include "cPlayerWeapon.h"

cPlayerWeapon::cPlayerWeapon()
{
	// Player weapon created
}

cPlayerWeapon::~cPlayerWeapon()
{
	delete pProjectilePrinter;
}

void cPlayerWeapon::Shoot(glm::vec2 pos, glm::vec2 dir)
{
	pProjectilePrinter->makeProjectile("player", pos, dir);
}

void cPlayerWeapon::setProjectilePrinter(cProjectileFactory* newPrinter)
{
	pProjectilePrinter = newPrinter;
}
