#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include "iWeapon.h"

class cPlayer
{
public:
	cPlayer();
	~cPlayer();

	glm::vec2 pos;
	glm::vec2 dir;

	void Update(std::vector<bool> keysPressed, double deltaTime);
	void setID(int ID);
	void setPos(glm::vec2 newPosition);

	int getID();
	glm::vec2 getPos();
	glm::vec2 getDir();
	iWeapon* playerWeapon;
	//void Animate();
	//void Attack();

private:
	float m_speed;
	float const m_shootCoolDown = 0.2f;
	double m_timeTillNextShot;
	int m_entityID; // To associate to a model in a map
};

