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
		if (dir.x == 0) // Vertical-oriented bullet
		{
			newAnimInfo->mesh->meshName = "playerbullet2.ply";
		}
		else if (dir.y == 0) // Horizontal-oriented bullet
		{
			newAnimInfo->mesh->meshName = "playerbullet1.ply";
		}
		else if (dir.x == dir.y) // Bottom-left to top-right orientation
		{
			newAnimInfo->mesh->meshName = "playerbullet3.ply";
		}
		else // Top-left to bottom-right orientation
		{
			newAnimInfo->mesh->meshName = "playerbullet4.ply";
		}
		
		
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}


	return;
}

