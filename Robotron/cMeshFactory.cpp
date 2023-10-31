
#include "cMeshFactory.h"
#include <random>

AnimationInfo* cMeshFactory::makeMesh(std::string entity)
{
	//srand(time(NULL));
	AnimationInfo* entityMesh = new AnimationInfo();
	entityMesh->mesh = new cMesh();
	entityMesh->mesh->bDoNotLight = true;

	if (entity == "player")
	{
		entityMesh->left.push_back("player1.ply");
		entityMesh->left.push_back("player2.ply");
		entityMesh->left.push_back("player3.ply");
		entityMesh->right.push_back("player4.ply");
		entityMesh->right.push_back("player5.ply");
		entityMesh->right.push_back("player6.ply");
		entityMesh->down.push_back("player7.ply");
		entityMesh->down.push_back("player8.ply");
		entityMesh->down.push_back("player9.ply");
		entityMesh->up.push_back("player10.ply");
		entityMesh->up.push_back("player11.ply");
		entityMesh->up.push_back("player12.ply");

		entityMesh->mesh->meshName = "player7.ply";
		//entityMesh->mesh->drawPosition.y = -40.0f;
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.05f; // every 50ms
		entityMesh->animationFrame = 0;
		entityMesh->timeSinceLastAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "pbullet") // player bullet   
	{
		entityMesh->left.push_back("playerbullet1.ply");
		entityMesh->right.push_back("playerbullet4.ply");
		entityMesh->up.push_back("playerbullet2.ply");
		entityMesh->down.push_back("playerbullet3.ply");

		entityMesh->mesh->meshName = "playerbullet1.ply";
		entityMesh->mesh->friendlyName = "pbullet";
		//entityMesh->mesh->drawPosition.y = -40.0f;
		entityMesh->mesh->scale = .05f;
		entityMesh->mesh->yOffset = 0.0f;
		//entityMesh->animationSpeed = 0.05f;                              //
		//entityMesh->animationFrame = 0;								   // These 3 shouldn't matter, player bullet doesn't animate
		//entityMesh->timeSinceLastAnim = entityMesh->animationSpeed;      //
		return entityMesh;
	}
	if (entity == "grunt")
	{
		entityMesh->down.push_back("grunt1.ply");
		entityMesh->down.push_back("grunt2.ply");
		entityMesh->down.push_back("grunt3.ply");
		entityMesh->up.push_back("grunt1.ply");
		entityMesh->up.push_back("grunt2.ply");
		entityMesh->up.push_back("grunt3.ply");
		entityMesh->left.push_back("grunt1.ply");
		entityMesh->left.push_back("grunt2.ply");
		entityMesh->left.push_back("grunt3.ply");
		entityMesh->right.push_back("grunt1.ply");
		entityMesh->right.push_back("grunt2.ply");
		entityMesh->right.push_back("grunt3.ply");

		entityMesh->mesh->meshName = "grunt1.ply";
		entityMesh->mesh->friendlyName = "grunt";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.0f; // every time it moves
		entityMesh->animationFrame = 0;
		entityMesh->timeSinceLastAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "human")
	{
		int randHuman = rand() % 3;
		if (randHuman == 0)
		{
			entityMesh->left.push_back("daddy1.ply");
			entityMesh->left.push_back("daddy2.ply");
			entityMesh->left.push_back("daddy3.ply");
			entityMesh->right.push_back("daddy4.ply");
			entityMesh->right.push_back("daddy5.ply");
			entityMesh->right.push_back("daddy6.ply");
			entityMesh->down.push_back("daddy7.ply");
			entityMesh->down.push_back("daddy8.ply");
			entityMesh->down.push_back("daddy9.ply");
			entityMesh->up.push_back("daddy10.ply");
			entityMesh->up.push_back("daddy11.ply");
			entityMesh->up.push_back("daddy12.ply");

			entityMesh->mesh->meshName = "daddy7.ply";
		}
		else if (randHuman == 1)
		{
			entityMesh->left.push_back("mommy1.ply");
			entityMesh->left.push_back("mommy2.ply");
			entityMesh->left.push_back("mommy3.ply");
			entityMesh->right.push_back("mommy4.ply");
			entityMesh->right.push_back("mommy5.ply");
			entityMesh->right.push_back("mommy6.ply");
			entityMesh->down.push_back("mommy7.ply");
			entityMesh->down.push_back("mommy8.ply");
			entityMesh->down.push_back("mommy9.ply");
			entityMesh->up.push_back("mommy10.ply");
			entityMesh->up.push_back("mommy11.ply");
			entityMesh->up.push_back("mommy12.ply");

			entityMesh->mesh->meshName = "mommy7.ply";
		}
		else
		{
			entityMesh->left.push_back("mikey1.ply");
			entityMesh->left.push_back("mikey2.ply");
			entityMesh->left.push_back("mikey3.ply");
			entityMesh->right.push_back("mikey4.ply");
			entityMesh->right.push_back("mikey5.ply");
			entityMesh->right.push_back("mikey6.ply");
			entityMesh->down.push_back("mikey7.ply");
			entityMesh->down.push_back("mikey8.ply");
			entityMesh->down.push_back("mikey9.ply");
			entityMesh->up.push_back("mikey10.ply");
			entityMesh->up.push_back("mikey11.ply");
			entityMesh->up.push_back("mikey12.ply");

			entityMesh->mesh->meshName = "mikey7.ply";
		}
		//entityMesh->mesh->drawPosition.y = -40.0f;
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f; // every 50ms
		entityMesh->animationFrame = 0;
		entityMesh->timeSinceLastAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}

	return NULL;

}
