
#include "cCharacterBuilder.h"

#include "cPlayer.h"
#include "iRobotron.h"
#include "cGrunt.h"

cCharacterBuilder::cCharacterBuilder()
{
	m_pTheArena = cArena::getArena();
	m_pWeaponFactory = new cWeaponFactory();
	m_pMeshFactory = new cMeshFactory();
}

void cCharacterBuilder::makeCharacter(std::string character)
{
// 	if (m_pTheArena == NULL)
// 		m_pTheArena = cArena::getArena();
	AnimationInfo* newAnimInfo;

	if (character == "player")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iWeapon* newWeapon = m_pWeaponFactory->makeWeapon(character);
		cPlayer* newPlayer = new cPlayer();
		newPlayer->playerWeapon = newWeapon;
		m_pTheArena->setPlayer(newPlayer, newAnimInfo);
		return;
	}
	if (character == "grunt")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iRobotron* newRobo = new cGrunt();
		m_pTheArena->addRobotron(newRobo, newAnimInfo);
		return;
	}
}
