#include "cProjectileFactory.h"

#include "cPlayerBullet.h"
#include "cCruiseMissile.h"
#include "cXShot.h"
#include "cTankShell.h"
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
		
		projectileToMake->setType(PBullet);
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}
	if (proj == "brain")
	{
		projectileToMake = new cCruiseMissile(pos, dir);
		newAnimInfo = m_pMeshFactory->makeMesh("cmissile");
		projectileToMake->setType(CMissile);
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}
	if (proj == "xshot")
	{
		projectileToMake = new cXShot(pos, dir);
		newAnimInfo = m_pMeshFactory->makeMesh("xshot");
		projectileToMake->setType(XShot);
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}
	if (proj == "tankshell")
	{
		projectileToMake = new cTankShell(pos, dir);
		newAnimInfo = m_pMeshFactory->makeMesh("tankshell");
		projectileToMake->setType(TankShell);
		pTheArena->addProjectile(projectileToMake, newAnimInfo);
	}


	return;
}

