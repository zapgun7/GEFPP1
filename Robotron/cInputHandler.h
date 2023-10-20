#pragma once
#include "OpenGLCommon.h"
#include "cArena.h"

class cInputHandler
{
public:
	cInputHandler();
	void queryKeys(GLFWwindow* window);

private:
	cArena* theArena;
};