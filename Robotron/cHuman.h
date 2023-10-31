#pragma once

#include <glm/vec2.hpp>
#include "cArena.h"

class cHuman
{
public:
	cHuman();
	~cHuman();

	virtual glm::vec2 getPos();
	virtual glm::vec2 getDir();
	virtual int getID();



	virtual void Update(double deltaTime); // Moves randomly
	virtual void setID(int ID);
	virtual void setPos(glm::vec2 newPos);
	//virtual void setArena(cArena* arena);

private:
	int m_EntityID;
	glm::vec2 m_pos;
	glm::vec2 m_dir;


	float const m_Speed = 1.0f;
	float const m_MoveInterval = 0.1f; // Time between moving
	float m_TimeToNextMove = m_MoveInterval;

	//cArena* m_pTheArena;


};

// Next for implementing this: Update human in the arena update loop. Add movement for it. Detect that certain (not sure if all) robotrons touch it (killing it) or player touches it (disappear + points)