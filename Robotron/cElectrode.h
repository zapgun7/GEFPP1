#pragma once

#include <glm/vec2.hpp>
#include <iRobotron.h>

class cElectrode : public iRobotron
{
public:
	// iRobotron functions
	virtual void Action(); // Does nothing
	virtual void Update(double deltaTime); // Effectively just calls animate
	virtual void Animate(); // Cycles through models

	glm::vec2 pos;

};

