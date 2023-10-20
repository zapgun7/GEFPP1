#include "cWeaponFactory.h"

#include "cPlayerWeapon.h"
#include "cProjectileFactory.h"

iWeapon* cWeaponFactory::makeWeapon(std::string weapon)
{
	iWeapon* weaponToMake;
	cProjectileFactory* newPrinter = new cProjectileFactory();
	if (weapon == "player")
	{
		weaponToMake = new cPlayerWeapon();
		weaponToMake->setProjectilePrinter(newPrinter);
		return weaponToMake;
	}

	//delete weaponToMake;
	delete newPrinter;
	return NULL;
}
