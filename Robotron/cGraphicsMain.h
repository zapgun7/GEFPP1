#pragma once

#include "OpenGLCommon.h"
#include <glm/vec3.hpp>
#include "cVAOManager/cVAOManager.h"
#include "cMesh.h"
#include <vector>
#include <string>
#include <glad/glad.h>

#include "Basic Shader Manager/cShaderManager.h"

class cGraphicsMain
{
public:
	bool Initialize();
	bool Update(); // return false when window is triggered to close
	void Destroy();


private:
	cMesh* m_pFindMeshByFriendlyName(std::string friendlyNameToFind);
	void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModelParent, GLuint shaderProgramID);
	bool LoadModels(void);

	glm::vec3 m_cameraEye = glm::vec3(0.0, 5.0, +90.0f);
	glm::vec3 m_cameraTarget = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::vec3 m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	cShaderManager* m_pShaderThing;
	GLuint m_shaderProgramID;


	double m_lastTime;
	GLFWwindow* m_window;
	cVAOManager* m_pMeshManager = NULL;
	std::vector< cMesh* > m_vec_pMeshesToDraw;
};