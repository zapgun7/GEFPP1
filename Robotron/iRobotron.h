#pragma once

//#include "cArena.h"
#include <glm/vec2.hpp>
enum RoboType
{
	Grunt,
	Hulk,
	Brain,
	Electrode,
	Enforcer,
	Prog,
	Quark,
	Spheroid,
	Tank
};

class iRobotron
{
public:
	virtual ~iRobotron() {};

	virtual void Update(double deltaTime) = 0;
	virtual void Attack() = 0;
	virtual void setID(int ID) = 0;
	virtual void setPos(glm::vec2 newPos) = 0;
	virtual void setRoboType(RoboType type) = 0;
	//virtual void setArena(cArena* arena) = 0; // All robotrons will have to communicate with the arena
	virtual int getID() = 0;
	virtual glm::vec2 getPos() = 0;
	virtual glm::vec2 getDir() = 0;
	virtual RoboType getRoboType() = 0;
	virtual void isShot() = 0;
	virtual bool isSpawning() = 0;
};