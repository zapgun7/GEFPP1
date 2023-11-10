#include "cArena_Implementation.h"

#include<glm/vec3.hpp>
#include "cGraphicsMain.h"

#include <iostream>

cArena_Implementation::cArena_Implementation()
{
	std::cout << "cArena_Implementation created." << std::endl;
	m_keysPressed.assign(8, false);
	m_pGraphMain = cGraphicsMain::getGraphicsMain();
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

// This initializes the game as a whole, only run once per app startup
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

	// Initialize the wave counter
	glm::vec2 wavePos = glm::vec2(-20, -60);
	std::string wavestr = "WAVE";
	for (unsigned int i = 0; i < 4; i++) // Build the 'wave' word first
	{
		cMesh* newNumber = new cMesh();
		newNumber->meshName = "largefont";
		newNumber->meshName += wavestr[i];
		newNumber->meshName += ".ply";
		newNumber->scale = 0.05f;
		newNumber->drawPosition = glm::vec3(wavePos, 0);
		newNumber->bDoNotLight = true;
		newNumber->uniqueID = -1; // Set to -1, as nothing else should be this (default 0 gets in the way)
		m_pGraphMain->addToDrawMesh(newNumber);
		wavePos.x += 4;
	}
	wavePos.x += 2;
	for (unsigned int i = 0; i < 3; i++)
	{
		cMesh* newNumber = new cMesh();
		newNumber->meshName = "largefont0.ply";
		newNumber->scale = 0.05f;
		newNumber->drawPosition = glm::vec3(wavePos, 0);
		newNumber->bDoNotLight = true;
		newNumber->uniqueID = -1; // Set to -1, as nothing else should be this (default 0 gets in the way)
		m_pGraphMain->addToDrawMesh(newNumber);
		mWaveCounter.push_back(newNumber);
		wavePos.x += 4;
	}

	// Initialize life sprites
	scorePos.x += 70;
	for (unsigned int i = 0; i < 6; i++) // Six max lives
	{
		cMesh* newLife = new cMesh();
		newLife->meshName = "player7.ply";
		newLife->scale = 0.03f;
		newLife->drawPosition = glm::vec3(scorePos, 0);
		newLife->bDoNotLight = true;
		newLife->uniqueID = -1; // Set to -1, as nothing else should be this (default 0 gets in the way)
		m_pGraphMain->addToDrawMesh(newLife);
		mLives.push_back(newLife);
		scorePos.x += 3;
	}

	// Initialize the pause screen letters (big "PAUSED" letters)

	glm::vec2 pausePos = glm::vec2(-25, 0); // Try dead center for now (y-wise)
	std::string pausestr = "PAUSED";
	for (unsigned int i = 0; i < 6; i++)
	{
		cMesh* newLetter = new cMesh();
		newLetter->meshName = "smallfont";
		newLetter->meshName += pausestr[i];
		newLetter->meshName += ".ply";
		newLetter->scale = 0.2f;
		newLetter->drawPosition = glm::vec3(pausePos, 20);
		newLetter->bDoNotLight = true;
		newLetter->bIsVisible = false;
		newLetter->uniqueID = -1; // Set to -1, as nothing else should be this (default 0 gets in the way)
		m_pGraphMain->addToDrawMesh(newLetter);
		mPause.push_back(newLetter);
		pausePos.x += 10;
	}

	InitializeLevel(true);

	lastTime = glfwGetTime();

}

// This is called from the cInputHandler to update the state of relevant keys
void cArena_Implementation::storeKeys(std::vector<bool> keys)
{
	m_keysPressed = keys;
	return;
}

// This function does a lot, perhaps too much but it works!
// Updates all entities, including animation
// Performs hit detection between entities and responds accordingly
// Updates score, wave counter, lives on-screen
// Initiates special visual effects for progs, cruiser missiles, and dead robotrons, with the cGraphicsMain taking care of the rest
void cArena_Implementation::Update()
{
	double currTime = glfwGetTime();
	double deltaTime = currTime - lastTime;
	lastTime = currTime;


	////////// PAUSE AREA //////////////////////
	static bool isESCPressed = false;
	static bool isPaused;
	if ((!isESCPressed) && (m_keysPressed[8])) // If escape button
	{
		isESCPressed = true;
		if (isPaused)
			isPaused = false;
		else
			isPaused = true;
		for (unsigned int i = 0; i < mPause.size(); i++)
		{
			mPause[i]->bIsVisible = isPaused;
		}
	}
	else if (!m_keysPressed[8])
		isESCPressed = false;

	if (isPaused)
	{

		m_keysPressed.assign(9, false); // Clear the input buffer
		return;
	}


	///////////////////////////////////////////


	if (m_TimeTillGameContinues > 0) // This is what puts delay after a stage load, or after player death
	{
		m_TimeTillGameContinues -= deltaTime;

		if (!m_bResetStage) // If it is a new stage, have the player size decrease in line with the start of the level
		{
			AnimationInfo* playerInfo = findAnimInfoByID(m_thePlayer->getID());
			playerInfo->mesh->scale = 0.05f + m_TimeTillGameContinues;
			playerInfo->mesh->yOffset = 2.75f + (m_TimeTillGameContinues * 30);
		}

		return;
	}
	else if(!m_bResetStage) // Make sure player draw info is correct
	{
		AnimationInfo* playerInfo = findAnimInfoByID(m_thePlayer->getID());
		playerInfo->mesh->scale = 0.05f;
		playerInfo->mesh->yOffset = 2.75f;
	}

	if (m_bResetStage) // If a stage re-initialization was called
	{
		InitializeLevel(m_bResetFresh);
		return;
	}


	// Check if stage has been completed, i.e. if only robotrons left (if any) are hulks and if there's no more humans left to save
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

	/////////////////////////////////////////////////////////////////////////////////////////     Updates the player
	////////////////////////////////////// PLAYER ///////////////////////////////////////////
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

	
	 ///////////////////////////////////////////////////////////////////////////////////////////////    Updates all currently active robotrons
	 ////////////////////////////////////////////////// ROBOTRONS //////////////////////////////////    Checks if it is colliding with the player and updates accordingly
	 ///////////////////////////////////////////////////////////////////////////////////////////////
	 
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

	////////////////////////////////////////////////////////////////////   Updates all humans currently active
	///////////////////////////// HUMAN UPDATE /////////////////////////   Detects if it is touching a hulk or brain and acts accordingly
	////////////////////////////////////////////////////////////////////   Detects if it is touching the player and acts accordingly

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
			createScoreNumber(m_NextHumanPoints, humanPos); // Spawns score mesh
			
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
					createScoreNumber(-1, humanPos); // Spawns a skull
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
					AnimationInfo* humanInfo = findAnimInfoByID(m_humans[i]->getID());
					deleteHuman(m_humans[i]->getID(), humanInfo); // Deletes human
					m_pCharacterMaker->makeCharacter("prog", glm::vec2(humanPos)); // Then spawns a prog in its place
					i--;
					break;
				}
			}
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////     Updates every projectile currently active
	////////////////////////////////////////// PROJECTILES ////////////////////////////////////////////////////     This checks player bullet collision with walls and enemies
	///////////////////////////////////////////////////////////////////////////////////////////////////////////     Also checks enemy projectiles with player

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
				tempInfo = findAnimInfoByID(m_thePlayer->getID());
				tempInfo->mesh->friendlyName = "destructing"; // This name tells the cGraphicsMain to set it to red, increase scale and decrease red over an amount of time before deleting
				deletePlayer(tempInfo); 
				m_TimeTillGameContinues = m_GameContinueInterval; // 2s of pause after player death
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


// Just duplicate the current sprite of the thing, give it a distinguishable friendlyname and the graphics main takes care of the rest
	for (iRobotron* robo : m_robotrons)
	{
		continue;// DEBUG
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
		continue; // DEBUG
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

	updateOnScreenInfo();
	m_keysPressed.assign(9, false); // Clear the input buffer
	
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
		// No death animation, so delete mesh info
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
	if (!anim)
		return;
	if (anim->mesh->friendlyName != "destructing") // Let graphics main take care of destructing "animation" and deleting the mesh
	{
		m_pGraphMain->removeFromDrawMesh(anim->mesh->uniqueID); // Remove robo mesh from graphics class
		delete anim->mesh;
	}

	delete anim; // Delete mesh info
	m_spriteIDMap.erase(m_thePlayer->getID()); // Remove from ID_to_Mesh map
	delete m_thePlayer; // Delete robotron object itself
}

// (Re)loads the level, whether after player death or stage completion
void cArena_Implementation::InitializeLevel(bool isFresh) // 180 max entities can be spawned
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

		int hulks = 0;
		int grunts = 0;
		int humans = 0;
		int brains = 0;
		int sphereoids = 0;
		int quarks = 0;

		static int lastLevel = 0;
		bool hasGenerated = false;

		///////////////////////////////////////////////////////////////    1 Grunts + humans                                         +Diff-> Hulks
		///////////LEVEL RANDOMIZATION (With difficulty scaling!///////    2 Many Grunts + few Hulks + sphereoids + humans           +Diff-> +1 quark, maybe increase amounts of quark and sphereoids
		//////////////////////MAX 180 ENEMIES//////////////////////////    3 Grunts = Brains + many humans + 1 sphereoid             +Diff-> Some hulks, more sphereoids, mayhaps a quark
		///////////////////////////////////////////////////////////////    4 Hulks + many quarks + humans                            +Diff-> Equal amounts of quarks and sphereoids (summing to old quark total)
		while (!hasGenerated)
		{
			int levelType = rand() % m_wave;
			levelType = 4;// DEBUG
			lastLevel = 0; // DEBUG
			m_wave = 10;// DEBUG

			if (levelType < m_wave * 0.2)
			{
				if (lastLevel == 1) continue; // Prevent same subsequent level types

				humans = rand() % (2 + (m_wave / 10)) + 5;
				grunts = rand() % (10 + m_wave / 2) + (40 + (m_wave / 4));
				hulks = rand() % (1 + (m_wave / 2)) + (m_wave / 5);
				// Cap possible numbers
				if (hulks > 30) hulks = 30;
				if (grunts > 100) grunts = 100;
				if (humans > 20) humans = 20;
				lastLevel = 1;
				hasGenerated = true;
			}
			else if (levelType < m_wave * 0.5)
			{
				if (lastLevel == 2) continue;

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
				lastLevel = 2;
				hasGenerated = true;
			}
			else if (levelType <= m_wave * 0.8)
			{
				if (lastLevel == 3) continue;

				humans = rand() % (2 + (m_wave / 10)) + 15;
				grunts = rand() % (1 + (m_wave / 10)) + (20 + (m_wave / 5));
				brains = rand() % (1 + (m_wave / 10)) + (20 + (m_wave / 5));
				sphereoids = rand() % (1 + (m_wave / 10)) + (m_wave / 20);
				quarks = rand() % (1 + (m_wave / 15)) + (m_wave / 30);
				hulks = rand() % (1 + (m_wave / 10)) + (m_wave / 15);
				// Number caps
				if (humans > 35) humans = 35;
				if (grunts > 50) grunts = 50;
				if (brains > 50) brains = 50;
				if (sphereoids > 7) sphereoids = 7;
				if (quarks > 7) quarks = 7;
				if (hulks > 15) hulks = 15;
				lastLevel = 3;
				hasGenerated = true;
			}
			else if (levelType < m_wave * 1.0)
			{
				if (lastLevel == 4) continue;

				humans = rand() % (1 + (m_wave / 7)) + 5;
				hulks = rand() % (1 + (m_wave / 7)) + (15 + (m_wave / 10));
				quarks = rand() % (1 + (m_wave / 10)) + (10 + (m_wave / 15));
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
				lastLevel = 4;
				hasGenerated = true;
			}
		}


		///////////////////////////////////////////////////////////////
		////////////////////END OF LEVEL RANDO/////////////////////////

		bool isValid = false;
		glm::vec2 placePos = glm::vec2(0);
		int xPlace = 0;
		int yPlace = 0;


		///////////////// NOW SPAWN ALL RANDOMIZED ENTITIES //////////////////

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
	else if (!isFresh) // Reload the level, i.e. replace all currently active robotrons and humans;     Player must've died to get here
	{
		m_lives--;

		if (m_lives < 0)
		{
			// Game Over
			// Returns to Update(), returns, then upon Update() getting called again from main, calls this InitializeLevel() again with the following parameters
			m_score = 0;
			m_lifeScore = 0;
			m_wave = 0;
			m_lives = 3;
			m_bResetFresh = true;
			m_bResetStage = true;
			updateOnScreenInfo();
			return;
		}


		// Here assuming the player used up another valid life and gets to keep on goin

		bool isValid = false;
		glm::vec2 placePos = glm::vec2(0);
		int xPlace = 0;
		int yPlace = 0;


		for(unsigned int i = 0; i < m_robotrons.size(); i++) // Find new spots for all robotrons
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
		for (unsigned int i = 0; i < m_humans.size(); i++) // Find new spots for all humans
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
	updateOnScreenInfo();
}


// Resest placement array to default values: all false except for a 3x3 encompassing the center position (player position)
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

// Returns the amount of score for the type of passed enemy; used in adding to the internal m_score
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

// Creates a score mesh (the little 1000, 2000, ..., 5000 that appears when saving a human or killing the releveant robotron)
void cArena_Implementation::createScoreNumber(int score, glm::vec2 pos)
{
	if (score == -1) // Human death
	{
		cMesh* familyDeath = new cMesh();
		familyDeath->drawPosition = glm::vec3(pos, 0);
		familyDeath->scale = 0.05f;
		familyDeath->bDoNotLight = true;
		familyDeath->uniqueID = -1;
		familyDeath->friendlyName = "score";
		familyDeath->meshName = "familydeath.ply";
		m_pGraphMain->addToDrawMesh(familyDeath);
		return;
	}
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

// Updates all on-screen info: wave counter, score, lives
void cArena_Implementation::updateOnScreenInfo()
{
	//////////////////////// SCOREBOARD /////////////////////////////////
	std::string scorestr = std::to_string(m_score);
	int scoreBoardIdx = 0;
	for (unsigned int i = 0; i < mScoreboard.size(); i++) mScoreboard[i]->meshName = "smallfont0.ply"; // Reset scoreboard before writing the updated one
	for (int i = scorestr.size() - 1; i > -1; i--)
	{
		std::string filename = "smallfont";
		filename += scorestr[i];
		filename += ".ply";

		mScoreboard[8 - scoreBoardIdx++]->meshName = filename;
	}


	//////////////////////// WAVE COUNTER ////////////////////
	std::string wavestr = std::to_string(m_wave);
	int waveIdx = 0;
	for (unsigned int i = 0; i < 3; i++) mWaveCounter[i]->meshName = "largefont0.ply";
	for (int i = wavestr.size() - 1; i > -1; i--)
	{
		std::string filename = "largefont";
		filename += wavestr[i];
		filename += ".ply";

		mWaveCounter[2 - waveIdx++]->meshName = filename;
	}

	///////////////////////// LIVES /////////////////////
	// Quickly check if a new life has been earned
	if (m_score - m_lifeScore >= 150'000)
	{
		m_lives++;
		m_lifeScore += 150'000;
	}

	for (unsigned int i = 0; i < 6; i++) mLives[i]->bIsVisible = false;
	for (unsigned int i = 0; i < m_lives; i++)
	{
		mLives[i]->bIsVisible = true;
	}
}
// Wowee 1186 lines, surely this is too much responsibility for one class?