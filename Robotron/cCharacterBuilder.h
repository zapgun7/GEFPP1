#pragma once

#include <string>
#include <glm/vec2.hpp>
#include "cArena.h"
#include "cWeaponFactory.h"
#include "cMeshFactory.h"


class cCharacterBuilder
{
public:
	cCharacterBuilder();
	void makeCharacter(std::string character, glm::vec2 pos);

private:
	cArena* m_pTheArena;
	cWeaponFactory* m_pWeaponFactory;
	cMeshFactory* m_pMeshFactory;
};