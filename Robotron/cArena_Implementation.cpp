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

	// Initialize the scoreboard
	glm::vec2 scorePos = glm::vec2(-100, 55);
	for (unsigned int i = 0; i < 9; i++)
	{
		cMesh* newNumber = new cMesh();
		newNumber->meshName = "smallfont0.ply";
		newNumber->scale = 0.05f;
		newNumber->drawPosition = glm::vec3(scorePos, 0);
		newNumber->bDoNotLight = true;
		newNumber->uniqueID = -1; // Set to -1, as nothing else should be this (default 0 gets in the way)
		m_pGraphMain->addToDrawMesh(newNumber);
		mScoreboard.push_back(newNumber);
		scorePos.x += 4;
	}

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
	//deltaTime = 0.001f;

	if (m_TimeTillGameContinues > 0) // TODO On game start, have player size big and gradually decrease size to correct amount leading up to game start
	{
		m_TimeTillGameContinues -= deltaTime;
		// Scale down player
		if (!m_bResetStage)
		{
			AnimationInfo* playerInfo = findAnimInfoByID(m_thePlayer->getID());
			playerInfo->mesh->scale = 0.05f + m_TimeTillGameContinues;
			playerInfo->mesh->yOffset = 2.75f + (m_TimeTillGameContinues * 30);
		}

		return;
	}
	else if(!m_bResetStage)
	{
		AnimationInfo* playerInfo = findAnimInfoByID(m_thePlayer->getID());
		playerInfo->mesh->scale = 0.05f;
		playerInfo->mesh->yOffset = 2.75f;
	}

	if (m_bResetStage)
	{
		InitializeLevel(m_bResetFresh);
		return;
	}


	// Check if stage has been completed
	bool isAllHulks = true;
	for (iRobotron* robo : m_robotrons)
	{
		if (robo->getRoboType() != Hulk)
		{
			isAllHulks = false;
			break;
		}
	}
	if (isAllHulks)
	{
		if (m_humans.size() == 0)
		{
			m_bResetFresh = true;
			m_bResetStage = true;
			m_TimeTillGameContinues = m_GameContinueInterval;
		}
	}

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
		currRobo->Update(deltaTime); // Update robotron first
		//currRobo->Update(0.02f);
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


		// Here check if the robot is colliding with the player
		if (glm::distance(currRobo->getPos(), m_thePlayer->getPos()) < 3)
		{
			//std::cout << "player dies holy moly" << std::endl;
			tempInfo = findAnimInfoByID(m_thePlayer->getID());
			tempInfo->mesh->friendlyName = "destructing";
			deletePlayer(tempInfo);
			m_TimeTillGameContinues = m_GameContinueInterval; // 4s of pause after player death
			m_bResetStage = true;
			return;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	///////////////////////////// HUMAN UPDATE //////////////////////////// This will be very similar to the player update above
	////////////////////////////////////////////////////////////////////

	for (unsigned int i = 0; i < m_humans.size(); i++) // Update all humans
	{
		m_humans[i]->Update(deltaTime);
		AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID()); // Get animation info of human
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
		// Check if human is touching the player and is rescued
		if (glm::distance(humanPos, m_thePlayer->getPos()) < 4.5)
		{
			AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID());
			deleteHuman(m_humans[i]->getID(), humanInfo);
			i--;
			m_score += m_NextHumanPoints;
			createScoreNumber(m_NextHumanPoints, humanPos);
			
			m_NextHumanPoints += 1000;
			m_NextHumanPoints = m_NextHumanPoints > 5000 ? 5000 : m_NextHumanPoints;
			
			continue;
		}

		// Check if human is touching any relevant robotron
		for (unsigned int e = 0; e < m_robotrons.size(); e++)
		{
			if (m_robotrons[e]->getRoboType() == Hulk)
			{
				if (glm::distance(m_robotrons[e]->getPos(), humanPos) < 3)
				{
					// TODO: Destroy human, put skull over this position (which disappears soon after or smthn, whatever it does in the real robotron)
					AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID());
					deleteHuman(m_humans[i]->getID(), humanInfo);
				    i--;
					break;
				}
			}
			else if (m_robotrons[e]->getRoboType() == Brain)
			{
				if (glm::distance(m_robotrons[e]->getPos(), humanPos) < 3)
				{
					// TODO: Turn human into prog (destroy human an replace with prog in the same position)
					AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID());
					deleteHuman(m_humans[i]->getID(), humanInfo);
					m_pCharacterMaker->makeCharacter("prog", glm::vec2(humanPos));
					i--;
					break;
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
		if (i < 0) continue;
		
		// Start by updating its position
		m_projectiles[i]->Update(deltaTime); // Update position of projectile first

		glm::vec2 projPos = m_projectiles[i]->getPosition(); // Then get its position
		tempInfo = findAnimInfoByID(m_projectiles[i]->getID()); // Get draw info for projectile
		tempInfo->mesh->drawPosition = glm::vec3(projPos, 0);

		// Quickly check if projectile flagged itself for deletion
		if (m_projectiles[i]->ShouldBeDestroyed())
		{
			deleteProjectile(m_projectiles[i]->getID(), tempInfo);
			i--;
			continue;
		}


		if (tempInfo->mesh->friendlyName != "pbullet") // Non-player bullets
		{
			// Animate robotron projectiles
			tempInfo->timeTillNextAnim -= deltaTime;

			if (tempInfo->timeTillNextAnim <= 0) // Time to tick next fram of animation
			{
				tempInfo->timeTillNextAnim += tempInfo->animationSpeed;
				tempInfo->animationFrame = ((tempInfo->animationFrame + 1) % tempInfo->down.size());
				tempInfo->mesh->meshName = tempInfo->down[tempInfo->animationFrame];
			}
			// Detect hit on player
			if (glm::distance(projPos, m_thePlayer->getPos()) < 2.5)
			{
				std::cout << "Player hit with projectile (dies)" << std::endl;
				tempInfo = findAnimInfoByID(m_thePlayer->getID());
				tempInfo->mesh->friendlyName = "destructing";
				deletePlayer(tempInfo);
				m_TimeTillGameContinues = m_GameContinueInterval; // 4s of pause after player death
				m_bResetStage = true;
				return;
			}
		}
		else // Player bullet hit detection
		{
			if (abs(projPos.x) > m_XBoundary) // outside x boundary
			{
				deleteProjectile(m_projectiles[i]->getID(), tempInfo);
				i--;
				continue;
			}
			else if (abs(projPos.y) > m_YBoundary) // outside y boundary 
			{
				deleteProjectile(m_projectiles[i]->getID(), tempInfo);
				i--;
				continue;
			}
			bool doesProjDie = false;
			for (int e = 0; e < m_robotrons.size(); e++) // Check if bullet hits any robotrons
			{
				glm::vec2 roboPos = m_robotrons[e]->getPos();
				if (glm::distance(roboPos, projPos) < 5) 
				{											// ROBOHIT!!!
					AnimationInfo* roboInfo = findAnimInfoByID(m_robotrons[e]->getID());
					deleteProjectile(m_projectiles[i]->getID(), tempInfo);
					i--;
					doesProjDie = true;
					if(m_robotrons[e]->getRoboType() == Hulk)
					{
						m_robotrons[e]->isShot();
						break;
					}
					else
					{
						int scoreToAdd = getScoreAmount(m_robotrons[e]->getRoboType());
						m_score += scoreToAdd;
						if (scoreToAdd == 1000)
						{
							createScoreNumber(1000, roboPos);
						}
						roboInfo->mesh->friendlyName = "destructing";
						deleteRobotron(e, roboInfo);
						break;
					}
				}
			}
			if (doesProjDie) // Detect if projectile was deleted above
			{
				continue;
			}
			for (int e = 0; e < m_projectiles.size(); e++) // Check if player bullet hits cruise missile or XShots
			{
				if ((m_projectiles[e]->getType() != CMissile) && (m_projectiles[e]->getType() != XShot) && (m_projectiles[e]->getType() != TankShell))
					continue;

				// Assuming e is a cruise missile or XShot or tank shell
				glm::vec2 otherProjPos = m_projectiles[e]->getPosition();
				if (glm::distance(otherProjPos, projPos) < 2.5) // Distance of 2.5 for proj on proj collision
				{	
					if (m_projectiles[e]->getType() == CMissile)
					{
						m_score += 25;
					}
					AnimationInfo* otherProjInfo = findAnimInfoByID(m_projectiles[e]->getID());
					deleteProjectile(m_projectiles[i]->getID(), tempInfo);
					i--;
					deleteProjectile(m_projectiles[e]->getID(), otherProjInfo);
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


	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////SCOREBOARD//////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	std::string scorestr = std::to_string(m_score);
	int scoreBoardIdx = 0;
	for (int i = scorestr.size() -1; i > -1; i--)
	{
		std::string filename = "smallfont";
		filename += scorestr[i];
		filename += ".ply";

		mScoreboard[8 - scoreBoardIdx++]->meshName = filename;
	}




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

void cArena_Implementation::deleteProjectile(int projID, AnimationInfo* anim)
{
	m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID);
	delete anim; // Delete mesh info
	m_spriteIDMap.erase(projID); // Remove from ID_to_Mesh map
	int projIdx = 0;
	for (unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i]->getID() == projID)
		{
			projIdx = i;
			break;
		}
	}
	delete m_projectiles[projIdx]; // Delete projectile object itself
	m_projectiles.erase(m_projectiles.begin() + projIdx); // Remove from projectile vector
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

void cArena_Implementation::deleteHuman(int humanID, AnimationInfo* anim)
{
	m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID); // Remove robo mesh from graphics class
	delete anim; // Delete mesh info
	m_spriteIDMap.erase(humanID); // Remove from ID_to_Mesh map
	int humanIdx = 0;
	for (unsigned int i = 0; i < m_humans.size(); i++)
	{
		if (m_humans[i]->getID() == humanID)
		{
			humanIdx = i;
			break;
		}
	}
	delete m_humans[humanIdx]; // Delete robotron object itself
	m_humans.erase(m_humans.begin() + humanIdx); // Remove from projectile vector
}

void cArena_Implementation::deletePlayer(AnimationInfo* anim)
{
	if (anim->mesh->friendlyName != "destructing") // Let graphics main take care of destructing "animation" and deleting the mesh
	{
		m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID); // Remove robo mesh from graphics class
		delete anim->mesh;
	}

	delete anim; // Delete mesh info
	m_spriteIDMap.erase(m_thePlayer->getID()); // Remove from ID_to_Mesh map
	delete m_thePlayer; // Delete robotron object itself
}

// Re(loads) the level, whether after player death or stage completion
void cArena_Implementation::InitializeLevel(bool isFresh) // 162 max entities can be spawned
{
	AnimationInfo* tempInfo;
	// Only projectiles all get deleted on either condition of this function
	while (m_projectiles.size() > 0)
	{
		tempInfo = findAnimInfoByID(m_projectiles[0]->getID());
		deleteProjectile(m_projectiles[0]->getID(), tempInfo);
	}

	ResetPlacementArray();

	if (isFresh)// Brand new level
	{
		m_wave++; // Increment current wave
		//Start by clearing all existing info if any
		while (m_robotrons.size() > 0)
		{
			AnimationInfo* tempInfo = findAnimInfoByID(m_robotrons[0]->getID());
			deleteRobotron(0, tempInfo);
		}
		
		while (m_humans.size() > 0)
		{
			AnimationInfo* tempInfo = findAnimInfoByID(m_humans[0]->getID());
			deleteHuman(0, tempInfo);
		}
		if (m_thePlayer)
		{
			AnimationInfo* tempInfo = findAnimInfoByID(m_thePlayer->getID());
			deletePlayer(tempInfo);
		}

		// Randomize enemy counts
// 		int hulks = rand() % 10 + 20;
// 		int grunts = rand() % 10 + 25;
// 		int humans = rand() % 10 + 5;
// 		int brains = rand() % 10 + 5;
// 		int sphereoids = rand() % 5;
// 		int quarks = rand() % 5;
		int hulks = 0;
		int grunts = 0;
		int humans = 10;
		int brains = 0;
		int sphereoids = 1;
		int quarks = 1;

		///////////////////////////////////////////////////////////////    1 Grunts + humans                                         +Diff-> Hulks
		///////////LEVEL RANDOMIZATION (With difficulty scaling!///////    2 Many Grunts + few Hulks + sphereoids + humans           +Diff-> +1 quark, maybe increase amounts of quark and sphereoids
		//////////////////////MAX 180 ENEMIES//////////////////////////    3 Grunts = Brains + many humans + 1 sphereoid             +Diff-> Some hulks, more sphereoids, mayhaps a quark
		///////////////////////////////////////////////////////////////    4 Hulks + many quarks + humans                            +Diff-> Equal amounts of quarks and sphereoids (summing to old quark total)
		int levelType = rand() % m_wave;
		if (levelType < m_wave * 0.2)
		{
			humans = rand() % (2 + (m_wave/10)) + 5;
			grunts = rand() % (10 + m_wave/2) + (40 + (m_wave / 4));
			hulks = rand() % (1 + (m_wave/2)) + (m_wave / 5);
			// Cap possible numbers
			if (hulks > 30) hulks = 30;
			if (grunts > 100) grunts = 100;
			if (humans > 20) humans = 20;
		}
		else if (levelType < m_wave * 0.5)
		{
			humans = rand() % (2 + (m_wave / 10)) + 5;
			grunts = rand() % (int)(20 + (m_wave / 1.5)) + (60 + (m_wave / 2));
			hulks = rand() % (1 + (m_wave / 8)) + (3 + (m_wave / 10));
			sphereoids = rand() % (1 + (m_wave / 5)) + (3);
			quarks = rand() % (1 + (m_wave / 10));
			// Number caps
			if (hulks > 15) hulks = 15;
			if (grunts > 100) grunts = 110;
			if (humans > 20) humans = 20;
			if (sphereoids > 20) sphereoids = 20;
			if (quarks > 10) quarks = 10;
		}
		else if (levelType <= m_wave * 0.8)
		{
			humans = rand() % (2 + (m_wave / 10)) + 15;
			grunts = rand() % (1 + (m_wave / 10)) + (20 + (m_wave / 5));
			brains = rand() % (1 + (m_wave / 10)) + (20 + (m_wave / 5));
			sphereoids = rand() % (1 + (m_wave/10)) + (m_wave / 20);
			quarks = rand() % (1 + (m_wave / 15)) + (m_wave / 30);
			hulks = rand() % (1 + (m_wave/10)) + (m_wave / 15);
			// Number caps
			if (humans > 35) humans = 35;
			if (grunts > 50) grunts = 50;
			if (brains > 50) brains = 50;
			if (sphereoids > 7) sphereoids = 7;
			if (quarks > 7) quarks = 7;
			if (hulks > 15) hulks = 15;
		}
		else if (levelType < m_wave * 1.0)
		{
			humans = rand() % (1 + (m_wave/7)) + 5;
			hulks = rand() % (1 + (m_wave/7)) + (15 + (m_wave / 10));
			quarks = rand() % (1 + (m_wave/10)) + (10 + (m_wave / 15));
			int randSph = rand() % m_wave;
			if (randSph > (10 + m_wave / 5))
			{
				sphereoids = quarks / 2;
				quarks /= 2;
			}
			// Number caps
			if (humans > 20) humans == 20;
			if (hulks > 50) hulks = 50;
			if (quarks > 35) quarks = 35;
			if (sphereoids > 35) sphereoids = 35;
		}


		///////////////////////////////////////////////////////////////
		////////////////////END OF LEVEL RANDO/////////////////////////

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
		while (humans != 0)
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

			m_pCharacterMaker->makeCharacter("human", placePos);
			humans--;
			isValid = false;
		}
		while (sphereoids != 0)
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

			m_pCharacterMaker->makeCharacter("sphereoid", placePos);
			sphereoids--;
			isValid = false;
		}
		while (quarks != 0)
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

			m_pCharacterMaker->makeCharacter("quark", placePos);
			quarks--;
			isValid = false;
		}
		while (brains != 0)
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

			m_pCharacterMaker->makeCharacter("brain", placePos);
			brains--;
			isValid = false;
		}
		while (grunts != 0)
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

			m_pCharacterMaker->makeCharacter("grunt", placePos);
			grunts--;
			isValid = false;
		}
		// Now set all their draw positions
		for (iRobotron* robo: m_robotrons)
		{
			tempInfo = findAnimInfoByID(robo->getID());
			tempInfo->mesh->drawPosition = glm::vec3(robo->getPos(), 0);
		}
		for (cHuman* human : m_humans)
		{
			tempInfo = findAnimInfoByID(human->getID());
			tempInfo->mesh->drawPosition = glm::vec3(human->getPos(), 0);
		}

	}
	else if (!isFresh)
	{
		bool isValid = false;
		glm::vec2 placePos = glm::vec2(0);
		int xPlace = 0;
		int yPlace = 0;


		for(unsigned int i = 0; i < m_robotrons.size(); i++)
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

			m_robotrons[i]->setPos(placePos);
			tempInfo = findAnimInfoByID(m_robotrons[i]->getID());
			tempInfo->mesh->drawPosition = glm::vec3(placePos, 0);
			isValid = false;
		}
		for (unsigned int i = 0; i < m_humans.size(); i++)
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

			m_humans[i]->setPos(placePos);
			tempInfo = findAnimInfoByID(m_humans[i]->getID());
			tempInfo->mesh->drawPosition = glm::vec3(placePos, 0);
			isValid = false;
		}
	}

	// Both conditions will have the player remade
	m_pCharacterMaker->makeCharacter("player", glm::vec2(0, 0));

	m_TimeTillGameContinues = m_GameContinueInterval; // Pause the game for a moment upon starting the arena
	m_bResetFresh = false;
	m_bResetStage = false;
	m_NextHumanPoints = 1000;
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

int cArena_Implementation::getScoreAmount(RoboType type)
{
	switch (type)
	{
	case Grunt:
		return 100;
	case Brain:
		return 500;
	case Prog:
		return 100;
	case Sphereoid:
		return 1000;
	case Enforcer:
		return 150;
	case Quark:
		return 1000;
	case Tank:
		return 200;
	default:
		return 0;

	}
}

// Creates a score mesh
void cArena_Implementation::createScoreNumber(int score, glm::vec2 pos)
{
	if (score % 1000 != 0) // A little safety so we don't call the wrong score
		return;

	cMesh* newNumberMesh = new cMesh();
	newNumberMesh->drawPosition = glm::vec3(pos, 0);
	newNumberMesh->scale = 0.05f;
	newNumberMesh->bDoNotLight = true;
	newNumberMesh->uniqueID = -1;
	newNumberMesh->friendlyName = "score";

	std::string filename = std::to_string(score);
	filename += ".ply";

	newNumberMesh->meshName = filename;

	m_pGraphMain->addToDrawMesh(newNumberMesh);
}
