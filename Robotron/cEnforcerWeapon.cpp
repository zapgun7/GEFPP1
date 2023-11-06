#include "cEnforcerWeapon.h"


cEnforcerWeapon::cEnforcerWeapon()
{

}

cEnforcerWeapon::~cEnforcerWeapon()
{

}

void cEnforcerWeapon::Shoot(glm::vec2 pos, glm::vec2 dir)
{
	m_pProjectilePrinter->makeProjectile("xshot", pos, dir);
}

void cEnforcerWeapon::setProjectilePrinter(cProjectileFactory* newPrinter)
{
	m_pProjectilePrinter = newPrinter;
}

