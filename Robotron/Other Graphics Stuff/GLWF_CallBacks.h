#pragma once

#include "OpenGLCommon.h"
#include "cArena.h"
#include <vector>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Gets the state of all keys relevent to input and passes them to the arena
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
// 	cArena* theArena;
// 	theArena = theArena->getArena();
// 	
// 	std::vector<bool> keysPressed;
// 	int state = glfwGetKey(window, GLFW_KEY_W);
// 	std::cout << state << std::endl;
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_S);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_A);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_D);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 
// 
// 	state = glfwGetKey(window, GLFW_KEY_UP);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_DOWN);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_LEFT);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 	state = glfwGetKey(window, GLFW_KEY_RIGHT);
// 	if (state == GLFW_PRESS)
// 		keysPressed.push_back(true);
// 	else
// 		keysPressed.push_back(false);
// 
// 	theArena->storeKeys(keysPressed);
// }

