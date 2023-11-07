
#include "cTankWeapon.h"

cTankWeapon::cTankWeapon()
{

}

cTankWeapon::~cTankWeapon()
{
	delete m_pProjectilePrinter;
}

void cTankWeapon::Shoot(glm::vec2 pos, glm::vec2 dir)
{
	m_pProjectilePrinter->makeProjectile("tankshell", pos, dir);
}

void cTankWeapon::setProjectilePrinter(cProjectileFactory* newPrinter)
{
	m_pProjectilePrinter = newPrinter;
}

