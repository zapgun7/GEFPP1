#pragma once

#include <string>
#include "cArena.h"
#include "cWeaponFactory.h"
#include "cMeshFactory.h"


class cCharacterBuilder
{
public:
	cCharacterBuilder();
	void makeCharacter(std::string character);

private:
	cArena* m_pTheArena;
	cWeaponFactory* m_pWeaponFactory;
	cMeshFactory* m_pMeshFactory;
};