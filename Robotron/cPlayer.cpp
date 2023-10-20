#include "cPlayer.h"
#include <glm/detail/func_geometric.inl>

cPlayer::cPlayer()
{
	this->pos = glm::vec2(0, 0);
	this->dir = glm::vec2(0, -1); // Looking down to start (not sad)
	this->speed = 0.5f;
}

void cPlayer::Update(std::vector<bool> keysPressed)
{
	glm::vec2 movementToAdd;
	movementToAdd = glm::vec2(0.0f, 0.0f);
	// MOVEMENT
	if (keysPressed[0]) // Up
	{
		movementToAdd.y += 1;
	}
	if (keysPressed[1]) // Down
	{
		movementToAdd.y -= 1;
	}
	if (keysPressed[2]) // Left
	{
		movementToAdd.x -= 1;
	}
	if (keysPressed[3]) // Right
	{
		movementToAdd.x += 1;
	}
	if(glm::length(movementToAdd) != 0)
		movementToAdd = glm::normalize(movementToAdd);
	movementToAdd *= speed;
	this->pos += movementToAdd;

	if (keysPressed[4]) // Up button
	{
		return;
	}
	dir = movementToAdd;
	// SHOOTING
}

void cPlayer::setID(int ID)
{
	entityID = ID;
	return;
}

int cPlayer::getID()
{
	return entityID;
}

glm::vec2 cPlayer::getPos()
{
	return this->pos;
}

glm::vec2 cPlayer::getDir()
{
	return this->dir;
}
