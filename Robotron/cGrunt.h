#pragma once

#include<glm/vec2.hpp>

#include <iRobotron.h>

class cGrunt : public iRobotron
{
public:
	cGrunt();
	~cGrunt();

	bool isDestroyed;
	bool canAction; // Check to see if the robotron can perform their specific action

	glm::vec2 pos;
	

	bool isDead();
	glm::vec2 getLocation();

	void Action();
	void Update();

private:

};