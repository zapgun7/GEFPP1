#include "cWeaponFactory.h"

#include "cPlayerWeapon.h"
#include "cBrainWeapon.h"
#include "cEnforcerWeapon.h"
#include "cTankWeapon.h"
#include "cProjectileFactory.h"


// Sets up different kinds of weapons; they're kinda all the same, except which kinds of projectils it makes with its printers
// Basic ol' factory I guess
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
	if (weapon == "brain")
	{
		weaponToMake = new cBrainWeapon();
		weaponToMake->setProjectilePrinter(newPrinter);
		return weaponToMake;
	}
	if (weapon == "enforcer")
	{
		weaponToMake = new cEnforcerWeapon();
		weaponToMake->setProjectilePrinter(newPrinter);
		return weaponToMake;
	}
	if (weapon == "tank")
	{
		weaponToMake = new cTankWeapon();
		weaponToMake->setProjectilePrinter(newPrinter);
		return weaponToMake;
	}

	//delete weaponToMake;
	delete newPrinter;
	return NULL;
}
