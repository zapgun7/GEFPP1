#pragma once

#include <glm/vec2.hpp>

class cPlayer
{
public:
	cPlayer();
	~cPlayer();

	glm::vec2 pos;
	glm::vec2 dir;

	void Update();
	void Animate();
	void Attack();
};

