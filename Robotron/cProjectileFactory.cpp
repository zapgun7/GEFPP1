#include "cProjectileFactory.h"

#include "cPlayerBullet.h"
#include "cArena.h"


cProjectileFactory::cProjectileFactory()
{
	//m_TheArena = cArena::getArena();
	m_pMeshFactory = new cMeshFactory();
}

void cProjectileFactory::makeProjectile(std::string proj, glm::vec2 pos, glm::vec2 dir)
{
	//if (m_TheArena == NULL) // Initialize arena if not already
	//	m_TheArena = cArena::getArena();
	cArena* pTheArena = cArena::getArena();

	iProjectile* projectileToMake;
	AnimationInfo* newAnimInfo;
	if (proj == "player")
	{
		projectileToMake = new cPlayerBullet(pos, dir);
		newAnimInfo = m_pMeshFactory->makeMesh("pbullet");
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}


	return;
}

