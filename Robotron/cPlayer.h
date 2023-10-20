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

	int getID();
	glm::vec2 getPos();
	glm::vec2 getDir();
	iWeapon* playerWeapon;
	//void Animate();
	//void Attack();

private:
	float speed;
	float shootCoolDown;
	float timeSinceLastShot;
	int entityID; // To associate to a model in a map
};

