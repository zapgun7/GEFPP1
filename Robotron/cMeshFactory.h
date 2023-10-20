#pragma once

#include "cMesh.h"
#include <string>
#include <vector>

// Will create structures to handle animating 

struct AnimationInfo
{
	~AnimationInfo() 
	{ 
		delete mesh; 
	};
	std::vector <std::string> up;    //
	std::vector <std::string> down;  // Names of sprites for their respective directions
	std::vector <std::string> left;  //
	std::vector <std::string> right; //
	cMesh* mesh;
	float animationSpeed; // Every animationSpeed seconds the animation ticks
	double timeSinceLastAnim;
	int animationFrame; // Keeps track of current animation frame
	float spriteOffsetY; // Offset for having the logic origin in the center of the sprite
};
class cMeshFactory
{
public:
	AnimationInfo* makeMesh(std::string entity);
};