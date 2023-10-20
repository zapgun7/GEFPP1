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
	glm::vec2 closestCoord = glm::vec2(999, 999);
	if (m_humans.size() == 0)
		return closestCoord; // Returns something outside the arena when no humans, will check for this
	closestCoord = m_humans[0]->getPos();
	for (unsigned int i = 1; i < m_humans.size(); i++)
	{
		//		if()
	}
	return closestCoord;
}

glm::vec2 cArena_Implementation::getPlayer(glm::vec2 whereIam)
{
	return glm::vec2(0, 0);
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

void cArena_Implementation::Initialize()
{
	m_pCharacterMaker = new cCharacterBuilder();
	// Spawns things for the level

	

	//m_thePlayer = new cPlayer();
	//m_thePlayer->setID(nextID++);
	//AnimationInfo* animInfo = m_meshFactory->makeMesh("Player");
	//m_spriteIDMap[m_thePlayer->getID()] = animInfo; // Update ID to animationInfo map
	//m_graphMain->addToDrawMesh(animInfo->mesh);

	m_pCharacterMaker->makeCharacter("player");


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


	// Start by updating player
	m_thePlayer->Update(m_keysPressed, deltaTime);


	
	AnimationInfo* tempInfo = findAnimInfoByID(m_thePlayer->getID()); // Get animation info of player
	float playerOffsetY = tempInfo->spriteOffsetY;
	glm::vec2 playerPos = m_thePlayer->getPos();

	// Keep player within bounds of play area
	if (abs(playerPos.x) > m_XBoundary) // outside x boundry
	{
		playerPos.x = m_XBoundary * (playerPos.x / abs(playerPos.x)); // sets player position to right on the border if over it
	}
	if (abs(playerPos.y  + playerOffsetY) > m_YBoundary)
	{
		playerPos.y = m_YBoundary * (playerPos.y / abs(playerPos.y)) - playerOffsetY;
	}
	m_thePlayer->setPos(playerPos); // Update player position

	// Update player animation //////
	if (glm::vec2(tempInfo->mesh->drawPosition) != playerPos) // If the player hasn't moved since last update, don't worry about animation TODO( In this case, reset back to 0th place in animation trio)
		tempInfo->timeSinceLastAnim -= deltaTime;
	if (tempInfo->timeSinceLastAnim <= 0) // Time to tick animation
	{
		tempInfo->timeSinceLastAnim += tempInfo->animationSpeed;
		tempInfo->animationFrame += 1;
		if (tempInfo->animationFrame > tempInfo->down.size() - 1)
		{
			tempInfo->animationFrame = 0;
		}
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

	// Update projectile animations and perform hit detection
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		// Start by updating its position
		m_projectiles[i]->Update(); // Update position of projectile first
		glm::vec2 projPos = m_projectiles[i]->getPosition(); // Then get its position
		tempInfo = findAnimInfoByID(m_projectiles[i]->getID()); // Get draw info for projectile
		tempInfo->mesh->drawPosition = glm::vec3(projPos, 0);
		if (tempInfo->mesh->friendlyName != "pbullet") // Only do this if not a player bullet (might change to if = if there's less projectiles overall to animate)
		{
			// TODO some enemy projectiles will animate
		}
		else // Player bullet hit detection
		{
			if (abs(projPos.x) > m_XBoundary) // outside x boundary
			{
				m_pGraphMain->removeFromDrawMesh(tempInfo->mesh->uniqueID);
				delete tempInfo; // Delete mesh info
				m_spriteIDMap.erase(m_projectiles[i]->getID()); // Remove from ID_to_Mesh map
				delete m_projectiles[i]; // Delete projectile object itself
				m_projectiles.erase(m_projectiles.begin() + i); // Remove from projectile vector
				i--;
				continue;
			}
			else if (abs(projPos.y) > m_YBoundary) // outside y boundary 
			{
				m_pGraphMain->removeFromDrawMesh(tempInfo->mesh->uniqueID);
				delete tempInfo; // Delete mesh info
				m_spriteIDMap.erase(m_projectiles[i]->getID()); // Remove from ID_to_Mesh map
				delete m_projectiles[i]; // Delete projectile object itself
				m_projectiles.erase(m_projectiles.begin() + i); // Remove from projectile vector
				i--;
				continue;
			}
		}
	}


	//////////////////////////

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
