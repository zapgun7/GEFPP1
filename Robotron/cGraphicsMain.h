#pragma once

#include "OpenGLCommon.h"
#include <glm/vec3.hpp>
#include "cMesh.h"
#include <vector>
#include <string>
#include <glad/glad.h>

#include "cVAOManager/cVAOManager.h"
#include "cInputHandler.h"
#include "Basic Shader Manager/cShaderManager.h"

class cGraphicsMain
{
public:
	static cGraphicsMain* getGraphicsMain(void);


	bool Update(); // return false when window is triggered to close
	void Destroy();
	void addToDrawMesh(cMesh* newMesh);
	void removeFromDrawMesh(int ID);
	void removeAfterimage(cMesh* mesh);


private:
	cGraphicsMain();
	bool Initialize();

	cMesh* m_pFindMeshByFriendlyName(std::string friendlyNameToFind);
	void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModelParent, GLuint shaderProgramID);
	bool LoadModels(void);


	glm::vec3 m_cameraEye;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_upVector;

	cShaderManager* m_pShaderThing;
	GLuint m_shaderProgramID;


	double m_lastTime;
	GLFWwindow* m_window;
	cVAOManager* m_pMeshManager = NULL;
	std::vector< cMesh* > m_vec_pMeshesToDraw;

	cInputHandler* m_InputHandler;

	static cGraphicsMain* m_pTheOnlyGraphicsMain;
};