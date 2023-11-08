#include "cPlayer.h"
#include <OpenGLCommon.h>
#include <iostream>


cPlayer::cPlayer()
{
	this->pos = glm::vec2(0, 0);
	this->dir = glm::vec2(0, -1); // Looking down to start (not sad)
	this->m_speed = 50.0f;
	m_timeTillNextShot = 0.0f;
}

cPlayer::~cPlayer()
{
	delete playerWeapon;
}

void cPlayer::Update(std::vector<bool> keysPressed, double deltaTime)
{
	//std::cout << pos.y << std::endl;
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
	movementToAdd *= m_speed * (float)deltaTime;
	this->pos += movementToAdd;

	bool isShooting = false;
	glm::vec2 shootDir = glm::vec2(0);
	if (keysPressed[4]) // Up
	{
		shootDir.y = 1;
		isShooting = true;
	}
	if (keysPressed[5]) // Down
	{
		shootDir.y = -1;
		isShooting = true;
	}
	if (keysPressed[6]) // Left
	{
		shootDir.x = -1;
		isShooting = true;
	}
	if (keysPressed[7]) // Right
	{
		shootDir.x = 1;
		isShooting = true;
	}
	shootDir = glm::normalize(shootDir);




	if (m_timeTillNextShot > 0)
		m_timeTillNextShot -= deltaTime;
	if (isShooting) // Up button
	{
		// Currently shooting
		if (m_timeTillNextShot <= 0)
		{
			playerWeapon->Shoot(pos, shootDir);
			m_timeTillNextShot += m_shootCoolDown;
		}
		return;
	}
	if (m_timeTillNextShot < 0)
		m_timeTillNextShot = 0;
	if (glm::length(movementToAdd) != 0) // Only update new directions, don't wanna set dir to 0
		dir = movementToAdd;
	// SHOOTING
}

void cPlayer::setID(int ID)
{
	m_entityID = ID;
	return;
}

void cPlayer::setPos(glm::vec2 newPosition)
{
	pos = newPosition;
}

int cPlayer::getID()
{
	return m_entityID;
}

glm::vec2 cPlayer::getPos()
{
	return this->pos;
}

glm::vec2 cPlayer::getDir()
{
	return this->dir;
}
