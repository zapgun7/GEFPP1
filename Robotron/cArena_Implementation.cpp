#include "cArena_Implementation.h"

#include<glm/vec3.hpp>
#include "cGraphicsMain.h"

#include <iostream>

cArena_Implementation::cArena_Implementation()
{
	std::cout << "cArena_Implementation created." << std::endl;
	//m_meshFactory = new cMeshFactory();
	m_keysPressed.assign(8, false);
	m_pGraphMain = cGraphicsMain::getGraphicsMain();
	//this->pTheWeaponFactory = new cWeaponMaker();
	//this->m_arenaSizeInMeters = 0.0f;
}

cArena_Implementation::~cArena_Implementation()
{
	//delete this->pTheWeaponFactory;
}

glm::vec2 cArena_Implementation::getClosestHuman(glm::vec2 whereIAm)
{
	glm::vec2 closestCoord = glm::vec2(999, 999); // If this 999 999 returns, no humans left
	if (m_humans.size() == 0)
		return closestCoord; // Returns something outside the arena when no humans, will check for this
	closestCoord = m_humans[0]->getPos();
	for (unsigned int i = 1; i < m_humans.size(); i++)
	{
		if ((glm::distance(whereIAm, m_humans[i]->getPos())) < (glm::distance(whereIAm, closestCoord)))
			closestCoord = m_humans[i]->getPos();
	}
	return closestCoord;
}

glm::vec2 cArena_Implementation::getPlayerPosition() // Returns unit vector to player
{
	//glm::vec2 returnDir = m_thePlayer->getPos() - whereIam;
	//returnDir = glm::normalize(returnDir);
	//return returnDir;
	glm::vec2 playerPos = m_thePlayer->getPos();
	return playerPos;
}

void cArena_Implementation::setPlayer(cPlayer* player, AnimationInfo* newInfo)
{
	m_thePlayer = player;
	player->setID(nextID++);
	newInfo->mesh->uniqueID = nextID - 1;
	m_spriteIDMap[player->getID()] = newInfo;
	m_pGraphMain->addToDrawMesh(newInfo->mesh);
}

void cArena_Implementation::addRobotron(iRobotron* newRobo, AnimationInfo* newInfo)
{
	m_robotrons.push_back(newRobo);
	newRobo->setID(nextID++);
	newInfo->mesh->uniqueID = nextID - 1;
	m_spriteIDMap[newRobo->getID()] = newInfo;
	m_pGraphMain->addToDrawMesh(newInfo->mesh);
}

void cArena_Implementation::addProjectile(iProjectile* newProjectile, AnimationInfo* newInfo)
{
	m_projectiles.push_back(newProjectile);
	newProjectile->setID(nextID++);
	newInfo->mesh->uniqueID = nextID - 1;
	m_spriteIDMap[newProjectile->getID()] = newInfo;
	m_pGraphMain->addToDrawMesh(newInfo->mesh);
}

void cArena_Implementation::addHuman(cHuman* newHuman, AnimationInfo* newInfo)
{
	m_humans.push_back(newHuman);
	newHuman->setID(nextID++);
	newInfo->mesh->uniqueID = nextID - 1;
	m_spriteIDMap[newHuman->getID()] = newInfo;
	m_pGraphMain->addToDrawMesh(newInfo->mesh);
}

void cArena_Implementation::addAfterimage(cMesh* aImg)
{
	// Graphics main will handle adjustment and death of afterimages
	m_pGraphMain->addToDrawMesh(aImg);
}

void cArena_Implementation::Initialize()
{
	m_pCharacterMaker = new cCharacterBuilder();
	// Spawns things for the level



	m_pCharacterMaker->makeCharacter("player", glm::vec2(0, 0));


// 	m_pCharacterMaker->makeCharacter("grunt", glm::vec2(20, 40));
// 	
// 	m_pCharacterMaker->makeCharacter("grunt", glm::vec2(30, 50));
// 	
// 	m_pCharacterMaker->makeCharacter("grunt", glm::vec2(30, 10));
	

// 	m_pCharacterMaker->makeCharacter("hulk", glm::vec2(20, 20));
// 	m_pCharacterMaker->makeCharacter("hulk", glm::vec2(45, 10));
// 	m_pCharacterMaker->makeCharacter("hulk", glm::vec2(-10, -10));
// 	m_pCharacterMaker->makeCharacter("hulk", glm::vec2(-35, -30));
	//m_robotrons[m_robotrons.size() - 1]->setPos(glm::vec2(45, 10));

//	m_pCharacterMaker->makeCharacter("human", glm::vec2(-10, 10));
// 	m_pCharacterMaker->makeCharacter("human", glm::vec2(-30, 10));
// 	m_pCharacterMaker->makeCharacter("human", glm::vec2(-60, 10));
// 
//	m_pCharacterMaker->makeCharacter("brain", glm::vec2(40, 50));

	//m_pCharacterMaker->makeCharacter("prog", glm::vec2(40, -40));

	//m_pCharacterMaker->makeCharacter("enforcer", glm::vec2(30, 40));

	//m_pCharacterMaker->makeCharacter("sphereoid", glm::vec2(30, 30));

	//m_pCharacterMaker->makeCharacter("tank", glm::vec2(35, 40));

	//m_pCharacterMaker->makeCharacter("quark", glm::vec2(35, 40));

	InitializeLevel(true);

	lastTime = glfwGetTime();

}

void cArena_Implementation::storeKeys(std::vector<bool> keys)
{
	m_keysPressed = keys;
	return;
}

// This function updates animations, calls update functions for all entities that require it, will scan for hit detection, and keep things in the boundaries
void cArena_Implementation::Update()
{
	// Update animations
	// Apply logged input to player

	double currTime = glfwGetTime();
	double deltaTime = currTime - lastTime;
	lastTime = currTime;


	//////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////// PLAYER /////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////


	// Start by updating player
	m_thePlayer->Update(m_keysPressed, deltaTime);


	
	AnimationInfo* tempInfo = findAnimInfoByID(m_thePlayer->getID()); // Get animation info of player
	glm::vec2 playerPos = m_thePlayer->getPos();

	// Keep player within bounds of play area
	if (abs(playerPos.x) > m_XBoundary) // outside x boundry
	{
		playerPos.x = m_XBoundary * (playerPos.x / abs(playerPos.x)); // sets player position to right on the border if over it
	}
	if (abs(playerPos.y) > m_YBoundary)
	{
		playerPos.y = m_YBoundary * (playerPos.y / abs(playerPos.y));
	}
	m_thePlayer->setPos(playerPos); // Update player position

	// Update player animation //////
	if (glm::vec2(tempInfo->mesh->drawPosition) != playerPos) // If the player hasn't moved since last update, don't worry about animation TODO( In this case, reset back to 0th place in animation trio)
		tempInfo->timeTillNextAnim -= deltaTime;
	if (tempInfo->timeTillNextAnim <= 0) // Time to tick animation
	{
		tempInfo->timeTillNextAnim += tempInfo->animationSpeed;
		tempInfo->animationFrame = (tempInfo->animationFrame + 1) % tempInfo->down.size();


		glm::vec2 playerDir = m_thePlayer->getDir();
		if (playerDir.x != 0) // Any direction left or right
		{
			if (playerDir.x < 0) // Left
			{
				tempInfo->mesh->meshName = tempInfo->left[tempInfo->animationFrame];
			}
			else // Right
			{
				tempInfo->mesh->meshName = tempInfo->right[tempInfo->animationFrame];
			}
		}
		else
		{
			if (playerDir.y < 0) // Down
			{
				tempInfo->mesh->meshName = tempInfo->down[tempInfo->animationFrame];
			}
			else // Right
			{
				tempInfo->mesh->meshName = tempInfo->up[tempInfo->animationFrame];
			}
		}
	}
	tempInfo->mesh->drawPosition = glm::vec3(playerPos, 0);

	
	 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////////// ROBOTRONS ////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	// Update robotrons and their animations

	for (int i = 0; i < m_robotrons.size(); i++) // Increment through all robotrons
	{
		iRobotron* currRobo = m_robotrons[i];
		//currRobo->Update(deltaTime); // Update robotron first
		//currRobo->Update(0.2f);
		tempInfo = findAnimInfoByID(currRobo->getID());
		//std::cout << tempInfo->mesh->meshName << std::endl;
		
		// Spawning animation
		if (currRobo->isSpawning())
		{
			tempInfo->timeTillNextAnim -= deltaTime;
			if (tempInfo->timeTillNextAnim <= 0)
			{
				tempInfo->timeTillNextAnim += tempInfo->animationSpeed;
				tempInfo->animationFrame = (tempInfo->animationFrame + 1) % tempInfo->spawning.size();
			}
			tempInfo->mesh->meshName = tempInfo->spawning[tempInfo->animationFrame];
			tempInfo->mesh->drawPosition = glm::vec3(currRobo->getPos(), 0);

		}

		if (currRobo->ShouldBeDestroyed()) // This is for Sphereoids and Quarks when they've exhausted their spawn limit
		{
			deleteRobotron(i, tempInfo);
			i--;
			continue;
		}

		// Animation
		if (glm::vec2(tempInfo->mesh->drawPosition) != currRobo->getPos()) // If last tick position is different then current position
		{
			tempInfo->timeTillNextAnim -= deltaTime;
		}
		if (tempInfo->timeTillNextAnim <= 0) // Increment animation frame
		{
			if (tempInfo->mesh->friendlyName == "grunt") // Those who only animate when they move (regardless of time passed)
			{
				tempInfo->timeTillNextAnim = 0.001f;
			}
			else // Those based on time
			{
				tempInfo->timeTillNextAnim += tempInfo->animationSpeed;
			}
			tempInfo->animationFrame = (tempInfo->animationFrame + 1) % tempInfo->down.size(); // Mod frame number by length of frames available


			// Do direction here
			glm::vec2 roboDir = currRobo->getDir();
			if (roboDir.x != 0) // Any direction left or right
			{
				if (roboDir.x < 0) // Left
				{
					tempInfo->mesh->meshName = tempInfo->left[tempInfo->animationFrame];
				}
				else // Right
				{
					tempInfo->mesh->meshName = tempInfo->right[tempInfo->animationFrame];
				}
			}
			else
			{
				if (roboDir.y < 0) // Down
				{
					tempInfo->mesh->meshName = tempInfo->down[tempInfo->animationFrame];
				}
				else // Right
				{
					tempInfo->mesh->meshName = tempInfo->up[tempInfo->animationFrame];
				}
			}
		}


		tempInfo->mesh->drawPosition = glm::vec3(currRobo->getPos(), 0); // Update position last
	}

	/////////////////////////////////////////////////////////////////////////////
	///////////////////////////// HUMAN UPDATE //////////////////////////// This will be very similar to the player update above
	////////////////////////////////////////////////////////////////////

	for (unsigned int i = 0; i < m_humans.size(); i++) // Update all humans
	{
		m_humans[i]->Update(deltaTime);
		AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID()); // Get animation info of player
		glm::vec2 humanPos = m_humans[i]->getPos();

		// Update human animation //////
		if (glm::vec2(humanInfo->mesh->drawPosition) != humanPos) // If the human hasn't moved since last update, don't worry about animation TODO( In this case, reset back to 0th place in animation trio)
			humanInfo->timeTillNextAnim -= deltaTime;
		if (humanInfo->timeTillNextAnim <= 0) // Time to tick animation
		{
			humanInfo->timeTillNextAnim += humanInfo->animationSpeed;
			humanInfo->animationFrame = (humanInfo->animationFrame + 1) % humanInfo->down.size();


			glm::vec2 humanDir = m_humans[i]->getDir();
			if (humanDir.x != 0) // Any direction left or right
			{
				if (humanDir.x < 0) // Left
				{
					humanInfo->mesh->meshName = humanInfo->left[humanInfo->animationFrame];
				}
				else // Right
				{
					humanInfo->mesh->meshName = humanInfo->right[humanInfo->animationFrame];
				}
			}
			else
			{
				if (humanDir.y < 0) // Down
				{
					humanInfo->mesh->meshName = humanInfo->down[humanInfo->animationFrame];
				}
				else // Right
				{
					humanInfo->mesh->meshName = humanInfo->up[humanInfo->animationFrame];
				}
			}
		}
		humanInfo->mesh->drawPosition = glm::vec3(humanPos, 0);

		//for (iRobotron* robo : m_robotrons)
		for (unsigned int e = 0; e < m_robotrons.size(); e++)
		{
			if (m_robotrons[e]->getRoboType() == Hulk)
			{
				if (glm::distance(m_robotrons[e]->getPos(), humanPos) < 5)
				{
					// TODO: Destroy human, put skull over this position (which disappears soon after or smthn, whatever it does in the real robotron)
				}
			}
			else if (m_robotrons[e]->getRoboType() == Brain)
			{
				if (glm::distance(m_robotrons[e]->getPos(), humanPos) < 3)
				{
					// TODO: Turn human into prog (destroy human an replace with prog in the same position)
					AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID());
					deleteHuman(i, humanInfo);
					m_pCharacterMaker->makeCharacter("prog", glm::vec2(humanPos));
				}
			}
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// PROJECTILES //////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Update projectile animations and perform hit detection
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		// Start by updating its position
		m_projectiles[i]->Update(deltaTime); // Update position of projectile first

		glm::vec2 projPos = m_projectiles[i]->getPosition(); // Then get its position
		tempInfo = findAnimInfoByID(m_projectiles[i]->getID()); // Get draw info for projectile
		tempInfo->mesh->drawPosition = glm::vec3(projPos, 0);

		// Quickly check if projectile flagged itself for deletion
		if (m_projectiles[i]->ShouldBeDestroyed())
		{
			deleteProjectile(i, tempInfo);
			i--;
			continue;
		}


		if (tempInfo->mesh->friendlyName != "pbullet") // Only do this if not a player bullet (might change to if = if there's less projectiles overall to animate)
		{
			// TODO some enemy projectiles will animate
			tempInfo->timeTillNextAnim -= deltaTime;

			if (tempInfo->timeTillNextAnim <= 0) // Time to tick next fram of animation
			{
				tempInfo->timeTillNextAnim += tempInfo->animationSpeed;
				tempInfo->animationFrame = ((tempInfo->animationFrame + 1) % tempInfo->down.size());
				tempInfo->mesh->meshName = tempInfo->down[tempInfo->animationFrame];
			}
			// TODO detect hits on player
		}
		else // Player bullet hit detection
		{
			if (abs(projPos.x) > m_XBoundary) // outside x boundary
			{
				deleteProjectile(i, tempInfo);
				i--;
				continue;
			}
			else if (abs(projPos.y) > m_YBoundary) // outside y boundary 
			{
				deleteProjectile(i, tempInfo);
				i--;
				continue;
			}

			for (int e = 0; e < m_robotrons.size(); e++) // Check if bullet hits any robotrons
			{
				glm::vec2 roboPos = m_robotrons[e]->getPos();
				if (glm::distance(roboPos, projPos) < 5) 
				{											// ROBOHIT!!!
					AnimationInfo* roboInfo = findAnimInfoByID(m_robotrons[e]->getID());                                     // TODO: Spawn an explosion here (some object that loops through an animation and terminates after)
					deleteProjectile(i, tempInfo);
					i--;
					if(m_robotrons[e]->getRoboType() == Hulk)
					{
						m_robotrons[e]->isShot();
						break;
					}
					else
					{
						roboInfo->mesh->friendlyName = "destructing";
						deleteRobotron(e, roboInfo);
						break;
					}
				}
			}
			for (int e = 0; e < m_projectiles.size(); e++) // Check if player bullet hits cruise missile or XShots
			{
				if ((m_projectiles[e]->getType() != CMissile) && (m_projectiles[e]->getType() != XShot) && (m_projectiles[e]->getType() != TankShell))
					continue;

				// Assuming e is a cruise missile or XShot
				glm::vec2 otherProjPos = m_projectiles[e]->getPosition();
				if (glm::distance(otherProjPos, projPos) < 2) // Distance of 2 for proj on proj collision
				{											
					AnimationInfo* otherProjInfo = findAnimInfoByID(m_projectiles[e]->getID());                                     // TODO: Spawn an explosion here (some object that goes through an animation and terminates after)
					deleteProjectile(i, tempInfo);
					i--;
					deleteProjectile(e, otherProjInfo);
					break;
				}
			}
		}
	}

	//////////////////////////

	/////////////////////////////////////////////////////////////////////////
	///////////////////////////////// AFTERIMAGES ///////////////////////////
	/////////////////////////////////////////////////////////////////////////

	for (iRobotron* robo : m_robotrons)
	{
		if (robo->getRoboType() == Prog)
		{
			cMesh* newAi = new cMesh();
			cMesh* robomesh = findAnimInfoByID(robo->getID())->mesh;
			memcpy(newAi, robomesh, sizeof(cMesh));
			
			newAi->friendlyName = "progAi";
			newAi->wholeObjectDebugColourRGBA = glm::vec4(glm::vec3(0.5), 1);
			addAfterimage(newAi);
		}
	}
	for (iProjectile* proj : m_projectiles)
	{
		if (proj->getType() == CMissile)
		{
			//cMesh* newAi = findAnimInfoByID(proj->getID())->mesh;
			cMesh* newAi = new cMesh();
			cMesh* projmesh = findAnimInfoByID(proj->getID())->mesh;
			memcpy(newAi, projmesh, sizeof(cMesh));

			newAi->friendlyName = "missileAi";
			addAfterimage(newAi);
		}
	}



	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////


	m_keysPressed.assign(8, false); // Clear the "buffer"
	
}

AnimationInfo* cArena_Implementation::findAnimInfoByID(int ID)
{
	std::map<int, AnimationInfo*>::iterator itAnim = m_spriteIDMap.find(ID);

	if (itAnim == this->m_spriteIDMap.end()) // If we didn't find it
	{
	 // TODO cleanup if this issue arises
		return NULL;
	}
	return itAnim->second;
}

void cArena_Implementation::deleteProjectile(int projNum, AnimationInfo* anim)
{
	m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID);
	delete anim; // Delete mesh info
	m_spriteIDMap.erase(m_projectiles[projNum]->getID()); // Remove from ID_to_Mesh map
	delete m_projectiles[projNum]; // Delete projectile object itself
	m_projectiles.erase(m_projectiles.begin() + projNum); // Remove from projectile vector
}

void cArena_Implementation::deleteRobotron(int roboNum, AnimationInfo* anim)
{
	if (anim->mesh->friendlyName != "destructing") // Let graphics main take care of destructing "animation" and deleting the mesh
	{
		m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID); // Remove robo mesh from graphics class
		delete anim->mesh;
	}

	delete anim; // Delete mesh info
	m_spriteIDMap.erase(m_robotrons[roboNum]->getID()); // Remove from ID_to_Mesh map
	delete m_robotrons[roboNum]; // Delete robotron object itself
	m_robotrons.erase(m_robotrons.begin() + roboNum); // Remove from projectile vector
}

void cArena_Implementation::deleteHuman(int humanNum, AnimationInfo* anim)
{
	m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID); // Remove robo mesh from graphics class
	delete anim; // Delete mesh info
	m_spriteIDMap.erase(m_humans[humanNum]->getID()); // Remove from ID_to_Mesh map
	delete m_humans[humanNum]; // Delete robotron object itself
	m_humans.erase(m_humans.begin() + humanNum); // Remove from projectile vector
}

// Re(loads) the level, whether after player death or stage completion
void cArena_Implementation::InitializeLevel(bool isFresh) // 162 max entities can be spawned
{
	ResetPlacementArray();
	if (isFresh)// Brand new level
	{
		//int hulks = rand() % 10 + 20;
		int hulks = 160;
		int grunts = rand() % 10 + 25;
		int humans = rand() % 10 + 5;
		int brains = rand() % 10 + 5;
		int sphereoids = rand() % 5;
		int quarks = rand() % 5;
		bool isValid = false;
		glm::vec2 placePos = glm::vec2(0);
		int xPlace = 0;
		int yPlace = 0;

		while (hulks != 0)
		{
			while (!isValid) // Find a valid place for the entity
			{
				// Randomize array placement first, will convert into real vector position after validity check
				xPlace = rand() % 21;
				yPlace = rand() % 9;

				if (!m_SpawnSpots[xPlace][yPlace])
					isValid = true;
			}

			m_SpawnSpots[xPlace][yPlace] = true;
			// Now to translate into real positions
			placePos.x = (xPlace - 10) * 10;
			placePos.y = (yPlace - 4) * 10;

			m_pCharacterMaker->makeCharacter("hulk", placePos);
			hulks--;
			isValid = false;
		}
	}
}

void cArena_Implementation::ResetPlacementArray()
{
	for (unsigned int i = 0; i < 21; i++)
	{
		for (unsigned int e = 0; e < 9; e++)
		{
			m_SpawnSpots[i][e] = false;
		}
	}
	// Now make space around player equal true i.e. taken and not available

	for (unsigned int i = 9; i < 12; i++) // 3x3 with player in middle
	{
		for (unsigned int e = 3; e < 6; e++)
		{
			m_SpawnSpots[i][e] = true;
		}
	}
}
