
#include "cCharacterBuilder.h"


#include "cPlayer.h"
#include "iRobotron.h"
#include "cGrunt.h"
#include "cHuman.h"
#include "cHulk.h"
#include "cBrain.h"
#include "cProg.h"

cCharacterBuilder::cCharacterBuilder()
{
	m_pTheArena = cArena::getArena();
	m_pWeaponFactory = new cWeaponFactory();
	m_pMeshFactory = new cMeshFactory();
}

void cCharacterBuilder::makeCharacter(std::string character, glm::vec2 pos)
{
// 	if (m_pTheArena == NULL)
// 		m_pTheArena = cArena::getArena();
	AnimationInfo* newAnimInfo;

	if (character == "player")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iWeapon* newWeapon = m_pWeaponFactory->makeWeapon(character);
		cPlayer* newPlayer = new cPlayer();
		newPlayer->setPos(pos);
		newPlayer->playerWeapon = newWeapon;
		m_pTheArena->setPlayer(newPlayer, newAnimInfo);
		return;
	}
	if (character == "grunt")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iRobotron* newRobo = new cGrunt();
		newRobo->setPos(pos);
		newRobo->setRoboType(Grunt);
		m_pTheArena->addRobotron(newRobo, newAnimInfo);
		return;
	}
	if (character == "human")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		cHuman* newHuman = new cHuman();
		newHuman->setPos(pos);
		m_pTheArena->addHuman(newHuman, newAnimInfo);
		return;
	}
	if (character == "hulk")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iRobotron* newRobo = new cHulk();
		newRobo->setPos(pos);
		newRobo->setRoboType(Hulk);
		m_pTheArena->addRobotron(newRobo, newAnimInfo);
		return;
	}
	if (character == "brain")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iWeapon* newWeapon = m_pWeaponFactory->makeWeapon(character);
		iRobotron* newRobo = new cBrain();
		newRobo->setPos(pos);
		((cBrain*) newRobo)->brainWeapon = newWeapon;
		newRobo->setRoboType(Brain);
		m_pTheArena->addRobotron(newRobo, newAnimInfo);
		return;
	}
	if (character == "prog")
	{
		newAnimInfo = m_pMeshFactory->makeMesh(character);
		iRobotron* newRobo = new cProg();
		newRobo->setPos(pos);
		newRobo->setRoboType(Prog);
		newAnimInfo->mesh->drawPosition = glm::vec3(pos, 0);
		m_pTheArena->addRobotron(newRobo, newAnimInfo);
		return;
	}

}
