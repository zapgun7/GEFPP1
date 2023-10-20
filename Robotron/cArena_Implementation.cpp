#include "cArena_Implementation.h"

#include<glm/vec3.hpp>
#include "cGraphicsMain.h"

#include <iostream>

cArena_Implementation::cArena_Implementation()
{
	std::cout << "cArena_Implementation created." << std::endl;
	m_meshFactory = new cMeshFactory();
	m_keysPressed.assign(8, false);
	m_graphMain = cGraphicsMain::getGraphicsMain();
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

void cArena_Implementation::Initialize()
{
	// Spawns things for the level

	

	m_thePlayer = new cPlayer();
	m_thePlayer->setID(nextID++);
	AnimationInfo* animInfo = m_meshFactory->makeMesh("Player");
	m_spriteIDMap[m_thePlayer->getID()] = animInfo; // Update ID to animationInfo map
	m_graphMain->addToDrawMesh(animInfo->mesh);
	lastTime = glfwGetTime();

}

void cArena_Implementation::storeKeys(std::vector<bool> keys)
{
	m_keysPressed = keys;
	return;
}

void cArena_Implementation::Update()
{
	// Update animations
	// Apply logged input to player

	double currTime = glfwGetTime();
	double deltaTime = currTime - lastTime;
	lastTime = currTime;


	// Start by updating player
	m_thePlayer->Update(m_keysPressed);


	// Update animation //////
	AnimationInfo* tempInfo = findAnimInfoByID(m_thePlayer->getID()); // Get animation info of player
	if( glm::vec2(tempInfo->mesh->drawPosition) != m_thePlayer->getPos()) // If the player hasn't moved since last update, don't worry about animation TODO( In this case, reset back to 0th place in animation trio)
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

	//////////////////////////

	m_keysPressed.assign(8, false); // Clear the "buffer"
	
	tempInfo->mesh->drawPosition = glm::vec3(m_thePlayer->getPos(), 0);
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
