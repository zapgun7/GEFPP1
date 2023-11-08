
#include "cMeshFactory.h"
#include <random>


// Creates animation info for every entity, setting up direction meshes, animation speed, and some parameters for spawning animations!
AnimationInfo* cMeshFactory::makeMesh(std::string entity)
{
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
		entityMesh->mesh->scale = .5f;
		entityMesh->animationSpeed = 0.05f; // every 50ms
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
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
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
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
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "hulk")
	{
		entityMesh->down.push_back("hulk4.ply");
		entityMesh->down.push_back("hulk5.ply");
		entityMesh->down.push_back("hulk6.ply");
		entityMesh->up.push_back("hulk4.ply");
		entityMesh->up.push_back("hulk5.ply");
		entityMesh->up.push_back("hulk6.ply");
		entityMesh->left.push_back("hulk1.ply");
		entityMesh->left.push_back("hulk2.ply");
		entityMesh->left.push_back("hulk3.ply");
		entityMesh->right.push_back("hulk7.ply");
		entityMesh->right.push_back("hulk8.ply");
		entityMesh->right.push_back("hulk9.ply");

		entityMesh->mesh->meshName = "hulk4.ply";
		entityMesh->mesh->friendlyName = "hulk";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "brain")
	{
		entityMesh->down.push_back("brain7.ply");
		entityMesh->down.push_back("brain8.ply");
		entityMesh->down.push_back("brain9.ply");
		entityMesh->up.push_back("brain10.ply");
		entityMesh->up.push_back("brain11.ply");
		entityMesh->up.push_back("brain12.ply");
		entityMesh->left.push_back("brain1.ply");
		entityMesh->left.push_back("brain2.ply");
		entityMesh->left.push_back("brain3.ply");
		entityMesh->right.push_back("brain4.ply");
		entityMesh->right.push_back("brain5.ply");
		entityMesh->right.push_back("brain6.ply");

		entityMesh->mesh->meshName = "brain7.ply";
		entityMesh->mesh->friendlyName = "brain";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f; 
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "cmissile")// Cruise missile
	{
		entityMesh->down.push_back("cruise_missile.ply");
		entityMesh->up.push_back("cruise_missile.ply");
		entityMesh->left.push_back("cruise_missile.ply");
		entityMesh->right.push_back("cruise_missile.ply");

		entityMesh->mesh->meshName = "cruise_missile.ply";
		entityMesh->mesh->friendlyName = "cmissile";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 0.0f;
		return entityMesh;
	}
	if (entity == "prog") // For now will just use daddy sprite
	{
		entityMesh->left.push_back("daddy1.ply");
		entityMesh->right.push_back("daddy4.ply");
		entityMesh->down.push_back("daddy7.ply");
		entityMesh->up.push_back("daddy10.ply");

		entityMesh->spawning.push_back("prog_create.ply");

		entityMesh->mesh->meshName = "prog_create.ply";
		entityMesh->mesh->friendlyName = "prog";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;

		entityMesh->mesh->bUseDebugColours = true;
		entityMesh->mesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f); // Make it white
		return entityMesh;
	}
	if (entity == "enforcer")
	{
		entityMesh->left.push_back("enforcer1.ply");
		entityMesh->right.push_back("enforcer1.ply");
		entityMesh->down.push_back("enforcer1.ply");
		entityMesh->up.push_back("enforcer1.ply");

		entityMesh->spawning.push_back("enforcer2.ply");
		entityMesh->spawning.push_back("enforcer3.ply");
		entityMesh->spawning.push_back("enforcer4.ply");
		entityMesh->spawning.push_back("enforcer5.ply");
		entityMesh->spawning.push_back("enforcer6.ply");


		entityMesh->mesh->meshName = "enforcer2.ply"; // Ideally have this flick through 6 when spawning, then stick to 1 afterwards
		entityMesh->mesh->friendlyName = "enforcer";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.2f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;

		return entityMesh;
	}
	if (entity == "xshot")
	{
		entityMesh->left.push_back("enforcerbullet1.ply");
		entityMesh->left.push_back("enforcerbullet2.ply");
		entityMesh->right.push_back("enforcerbullet1.ply");
		entityMesh->right.push_back("enforcerbullet2.ply");
		entityMesh->up.push_back("enforcerbullet1.ply");
		entityMesh->up.push_back("enforcerbullet2.ply");
		entityMesh->down.push_back("enforcerbullet1.ply");
		entityMesh->down.push_back("enforcerbullet2.ply");

		entityMesh->mesh->meshName = "enforcerbullet1.ply"; // Ideally have this flick through 6 when spawning, then stick to 1 afterwards
		entityMesh->mesh->friendlyName = "xshot";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.1f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;

		return entityMesh;
	}
	if (entity == "sphereoid")
	{
		entityMesh->down.push_back("sphereoid1.ply");
		entityMesh->down.push_back("sphereoid2.ply");
		entityMesh->down.push_back("sphereoid3.ply");
		entityMesh->down.push_back("sphereoid4.ply");
		entityMesh->down.push_back("sphereoid5.ply");
		entityMesh->down.push_back("sphereoid6.ply");
		entityMesh->down.push_back("sphereoid7.ply");
		entityMesh->down.push_back("sphereoid8.ply");

		entityMesh->up.push_back("sphereoid1.ply");
		entityMesh->up.push_back("sphereoid2.ply");
		entityMesh->up.push_back("sphereoid3.ply");
		entityMesh->up.push_back("sphereoid4.ply");
		entityMesh->up.push_back("sphereoid5.ply");
		entityMesh->up.push_back("sphereoid6.ply");
		entityMesh->up.push_back("sphereoid7.ply");
		entityMesh->up.push_back("sphereoid8.ply");

		entityMesh->left.push_back("sphereoid1.ply");
		entityMesh->left.push_back("sphereoid2.ply");
		entityMesh->left.push_back("sphereoid3.ply");
		entityMesh->left.push_back("sphereoid4.ply");
		entityMesh->left.push_back("sphereoid5.ply");
		entityMesh->left.push_back("sphereoid6.ply");
		entityMesh->left.push_back("sphereoid7.ply");
		entityMesh->left.push_back("sphereoid8.ply");

		entityMesh->right.push_back("sphereoid1.ply");
		entityMesh->right.push_back("sphereoid2.ply");
		entityMesh->right.push_back("sphereoid3.ply");
		entityMesh->right.push_back("sphereoid4.ply");
		entityMesh->right.push_back("sphereoid5.ply");
		entityMesh->right.push_back("sphereoid6.ply");
		entityMesh->right.push_back("sphereoid7.ply");
		entityMesh->right.push_back("sphereoid8.ply");


		entityMesh->mesh->meshName = "sphereoid1.ply";
		entityMesh->mesh->friendlyName = "sphereoid";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.05f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "tank")
	{
		entityMesh->down.push_back("tank3.ply");
		entityMesh->down.push_back("tank2.ply");
		entityMesh->down.push_back("tank1.ply");
		entityMesh->up.push_back("tank1.ply");
		entityMesh->up.push_back("tank2.ply");
		entityMesh->up.push_back("tank3.ply");

		entityMesh->left.push_back("tank3.ply");
		entityMesh->left.push_back("tank2.ply");
		entityMesh->left.push_back("tank1.ply");

		entityMesh->right.push_back("tank1.ply");
		entityMesh->right.push_back("tank2.ply");
		entityMesh->right.push_back("tank3.ply");


		entityMesh->spawning.push_back("tank5.ply");
		entityMesh->spawning.push_back("tank5.ply");
		entityMesh->spawning.push_back("tank6.ply");
		entityMesh->spawning.push_back("tank6.ply");
		entityMesh->spawning.push_back("tank7.ply");
		entityMesh->spawning.push_back("tank7.ply");
		entityMesh->spawning.push_back("tank8.ply");
		entityMesh->spawning.push_back("tank8.ply");

		entityMesh->mesh->meshName = "brain5.ply";
		entityMesh->mesh->friendlyName = "tank";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.05f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}
	if (entity == "tankshell")
	{
		entityMesh->left.push_back("tank_shell1.ply");
		entityMesh->left.push_back("tank_shell2.ply");
		entityMesh->right.push_back("tank_shell1.ply");
		entityMesh->right.push_back("tank_shell2.ply");
		entityMesh->up.push_back("tank_shell1.ply");
		entityMesh->up.push_back("tank_shell2.ply");
		entityMesh->down.push_back("tank_shell1.ply");
		entityMesh->down.push_back("tank_shell2.ply");

		entityMesh->mesh->meshName = "tank_shell1.ply"; // Ideally have this flick through 6 when spawning, then stick to 1 afterwards
		entityMesh->mesh->friendlyName = "tankshell";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.1f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 1.3f;

		return entityMesh;
	}
	if (entity == "quark")
	{
		entityMesh->down.push_back("quark1.ply");
		entityMesh->down.push_back("quark2.ply");
		entityMesh->down.push_back("quark3.ply");
		entityMesh->down.push_back("quark4.ply");
		entityMesh->down.push_back("quark5.ply");
		entityMesh->down.push_back("quark6.ply");
		entityMesh->down.push_back("quark7.ply");
		entityMesh->down.push_back("quark8.ply");

		entityMesh->up.push_back("quark1.ply");
		entityMesh->up.push_back("quark2.ply");
		entityMesh->up.push_back("quark3.ply");
		entityMesh->up.push_back("quark4.ply");
		entityMesh->up.push_back("quark5.ply");
		entityMesh->up.push_back("quark6.ply");
		entityMesh->up.push_back("quark7.ply");
		entityMesh->up.push_back("quark8.ply");

		entityMesh->left.push_back("quark1.ply");
		entityMesh->left.push_back("quark2.ply");
		entityMesh->left.push_back("quark3.ply");
		entityMesh->left.push_back("quark4.ply");
		entityMesh->left.push_back("quark5.ply");
		entityMesh->left.push_back("quark6.ply");
		entityMesh->left.push_back("quark7.ply");
		entityMesh->left.push_back("quark8.ply");

		entityMesh->right.push_back("quark1.ply");
		entityMesh->right.push_back("quark2.ply");
		entityMesh->right.push_back("quark3.ply");
		entityMesh->right.push_back("quark4.ply");
		entityMesh->right.push_back("quark5.ply");
		entityMesh->right.push_back("quark6.ply");
		entityMesh->right.push_back("quark7.ply");
		entityMesh->right.push_back("quark8.ply");


		entityMesh->mesh->meshName = "quark1.ply";
		entityMesh->mesh->friendlyName = "quark";
		entityMesh->mesh->scale = .05f;
		entityMesh->animationSpeed = 0.05f;
		entityMesh->animationFrame = 0;
		entityMesh->timeTillNextAnim = entityMesh->animationSpeed;
		entityMesh->mesh->yOffset = 2.75f;
		return entityMesh;
	}

	return NULL;

}
