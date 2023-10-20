#pragma once

#include "iWeapon.h"
#include <string>

class cWeaponFactory
{
public:
	iWeapon* makeWeapon(std::string weapon);
};