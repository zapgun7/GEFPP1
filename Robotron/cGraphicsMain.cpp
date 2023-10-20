#include "cGraphicsMain.h"

#include<iostream>


#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "GLWF_CallBacks.h"


cGraphicsMain* cGraphicsMain::m_pTheOnlyGraphicsMain = NULL;



static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


cGraphicsMain* cGraphicsMain::getGraphicsMain(void) // Making graphics main a singleton
{
	if (cGraphicsMain::m_pTheOnlyGraphicsMain == NULL)
	{
		cGraphicsMain::m_pTheOnlyGraphicsMain = new cGraphicsMain();
		if (!cGraphicsMain::m_pTheOnlyGraphicsMain->Initialize())
		{
			cGraphicsMain::m_pTheOnlyGraphicsMain->Destroy();
		}
	}
	return cGraphicsMain::m_pTheOnlyGraphicsMain;
}

cGraphicsMain::cGraphicsMain()
{
	m_cameraEye = glm::vec3(0.0, 0.0, 200.0f);
	m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

bool cGraphicsMain::Initialize()
{
	m_InputHandler = new cInputHandler();


	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//glfwSetKeyCallback(m_window, key_callback);

	glfwMakeContextCurrent(m_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);


	m_pShaderThing = new cShaderManager();
	m_pShaderThing->setBasePath("assets/shaders");

	cShaderManager::cShader vertexShader;
	vertexShader.fileName = "vertexShader01.glsl";

	cShaderManager::cShader fragmentShader;
	fragmentShader.fileName = "fragmentShader01.glsl";

	if (!m_pShaderThing->createProgramFromFile("shader01", vertexShader, fragmentShader))
	{
		std::cout << "Error: Couldn't compile or link:" << std::endl;
		std::cout << m_pShaderThing->getLastError();
		return -1;
	}


	//
	m_shaderProgramID = m_pShaderThing->getIDFromFriendlyName("shader01");

	m_pMeshManager = new cVAOManager();

	m_pMeshManager->setBasePath("assets/models");


	// Do this for all models   TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	sModelDrawInfo playerDrawingInfo;
	m_pMeshManager->LoadModelIntoVAO("player1.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player2.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player3.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player4.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player5.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player6.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player7.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player8.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player9.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player10.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player11.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	m_pMeshManager->LoadModelIntoVAO("player12.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;


	m_pMeshManager->LoadModelIntoVAO("playerbullet1.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;
	m_pMeshManager->LoadModelIntoVAO("playerbullet2.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;
	m_pMeshManager->LoadModelIntoVAO("playerbullet3.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;
	m_pMeshManager->LoadModelIntoVAO("playerbullet4.ply",
		playerDrawingInfo, m_shaderProgramID);
	std::cout << "Loaded: " << playerDrawingInfo.numberOfVertices << " vertices" << std::endl;

	//LoadModels();


	// Initialize lights here if ya want em
	m_lastTime = glfwGetTime();

	return 1;
}






bool cGraphicsMain::Update() // Main "loop" of the window. Not really a loop, just gets called every tick
{
	// Start by checking input
	m_InputHandler->queryKeys(m_window);



	float ratio;
	int width, height;

	glUseProgram(m_shaderProgramID);

	glfwGetFramebufferSize(m_window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// While drawing a pixel, see if the pixel that's already there is closer or not?
	glEnable(GL_DEPTH_TEST);
	// (Usually) the default - does NOT draw "back facing" triangles
	glCullFace(GL_BACK);


	// *****************************************************************
	// if ya want lights
	//m_pTheLights->UpdateUniformValues(shaderProgramID);


	// *****************************************************************
			//uniform vec4 eyeLocation;
	GLint eyeLocation_UL = glGetUniformLocation(m_shaderProgramID, "eyeLocation");
	glUniform4f(eyeLocation_UL,
		m_cameraEye.x, m_cameraEye.y, m_cameraEye.z, 1.0f);



	//       //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glm::mat4 matProjection = glm::perspective(0.6f,
		ratio,
		0.1f,
		1000.0f);

	glm::mat4 matView = glm::lookAt(m_cameraEye,
		m_cameraTarget,
		m_upVector);

	GLint matProjection_UL = glGetUniformLocation(m_shaderProgramID, "matProjection");
	glUniformMatrix4fv(matProjection_UL, 1, GL_FALSE, glm::value_ptr(matProjection));

	GLint matView_UL = glGetUniformLocation(m_shaderProgramID, "matView");
	glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(matView));

	// *********************************************************************
	// Draw all the objects
	for (unsigned int index = 0; index != m_vec_pMeshesToDraw.size(); index++) // Prob black or smthn
	{
		cMesh* pCurrentMesh = m_vec_pMeshesToDraw[index];

		if (pCurrentMesh->bIsVisible)
		{

			glm::mat4 matModel = glm::mat4(1.0f);   // Identity matrix

			DrawObject(pCurrentMesh, matModel, m_shaderProgramID);
		}//if (pCurrentMesh->bIsVisible)

	}//for ( unsigned int index

	// Time per frame (more or less)
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - m_lastTime;
	//        std::cout << deltaTime << std::endl;
	m_lastTime = currentTime;


	glfwSwapBuffers(m_window);
	glfwPollEvents();

	if (glfwWindowShouldClose(m_window))
		return -1;
	else
		return 0;
}



void cGraphicsMain::Destroy()
{

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

// Creates a new mesh to bind to an object; returns a pointer which the arena can associate to specific objects to animate them


void cGraphicsMain::addToDrawMesh(cMesh* newMesh)
{
	m_vec_pMeshesToDraw.push_back(newMesh);
	return;
}

void cGraphicsMain::removeFromDrawMesh(int ID)
{
	for (unsigned int i = 0; i < m_vec_pMeshesToDraw.size(); i++)
	{
		if (m_vec_pMeshesToDraw[i]->uniqueID == ID)
		{
			m_vec_pMeshesToDraw.erase(m_vec_pMeshesToDraw.begin() + i);
			return;
		}
	}
}

cMesh* cGraphicsMain::m_pFindMeshByFriendlyName(std::string friendlyNameToFind)
{
	for (unsigned int index = 0; index != m_vec_pMeshesToDraw.size(); index++)
	{
		if (m_vec_pMeshesToDraw[index]->friendlyName == friendlyNameToFind)
		{
			// Found it
			return m_vec_pMeshesToDraw[index];
		}
	}
	// Didn't find it
	return NULL;
}

void cGraphicsMain::DrawObject(cMesh* pCurrentMesh, glm::mat4 matModelParent, GLuint shaderProgramID)
{

	//         mat4x4_identity(m);
	glm::mat4 matModel = matModelParent;



	// Translation
	glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
		glm::vec3(pCurrentMesh->drawPosition.x,
			pCurrentMesh->drawPosition.y,
			pCurrentMesh->drawPosition.z));


	// Rotation matrix generation
	glm::mat4 matRotateX = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->orientation.x, // (float)glfwGetTime(),
		glm::vec3(1.0f, 0.0, 0.0f));


	glm::mat4 matRotateY = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->orientation.y, // (float)glfwGetTime(),
		glm::vec3(0.0f, 1.0, 0.0f));

	glm::mat4 matRotateZ = glm::rotate(glm::mat4(1.0f),
		pCurrentMesh->orientation.z, // (float)glfwGetTime(),
		glm::vec3(0.0f, 0.0, 1.0f));

	// Scaling matrix
	glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
		glm::vec3(pCurrentMesh->scale,
			pCurrentMesh->scale,
			pCurrentMesh->scale));
	//--------------------------------------------------------------

	// Combine all these transformation
	matModel = matModel * matTranslate;

	matModel = matModel * matRotateX;
	matModel = matModel * matRotateY;
	matModel = matModel * matRotateZ;

	matModel = matModel * matScale;

	//        m = m * rotateZ;
	//        m = m * rotateY;
	//        m = m * rotateZ;



	   //mat4x4_mul(mvp, p, m);
	//    glm::mat4 mvp = matProjection * matView * matModel;

	//    GLint mvp_location = glGetUniformLocation(shaderProgramID, "MVP");
	//    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
	//    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

	GLint matModel_UL = glGetUniformLocation(shaderProgramID, "matModel");
	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matModel));


	// Also calculate and pass the "inverse transpose" for the model matrix
	glm::mat4 matModel_InverseTranspose = glm::inverse(glm::transpose(matModel));

	// uniform mat4 matModel_IT;
	GLint matModel_IT_UL = glGetUniformLocation(shaderProgramID, "matModel_IT");
	glUniformMatrix4fv(matModel_IT_UL, 1, GL_FALSE, glm::value_ptr(matModel_InverseTranspose));


	if (pCurrentMesh->bIsWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//        glPointSize(10.0f);


			// uniform bool bDoNotLight;
	GLint bDoNotLight_UL = glGetUniformLocation(shaderProgramID, "bDoNotLight");

	if (pCurrentMesh->bDoNotLight)
	{
		// Set uniform to true
		glUniform1f(bDoNotLight_UL, (GLfloat)GL_TRUE);
	}
	else
	{
		// Set uniform to false;
		glUniform1f(bDoNotLight_UL, (GLfloat)GL_FALSE);
	}

	//uniform bool bUseDebugColour;	
	GLint bUseDebugColour_UL = glGetUniformLocation(shaderProgramID, "bUseDebugColour");
	if (pCurrentMesh->bUseDebugColours)
	{
		glUniform1f(bUseDebugColour_UL, (GLfloat)GL_TRUE);
		//uniform vec4 debugColourRGBA;
		GLint debugColourRGBA_UL = glGetUniformLocation(shaderProgramID, "debugColourRGBA");
		glUniform4f(debugColourRGBA_UL,
			pCurrentMesh->wholeObjectDebugColourRGBA.r,
			pCurrentMesh->wholeObjectDebugColourRGBA.g,
			pCurrentMesh->wholeObjectDebugColourRGBA.b,
			pCurrentMesh->wholeObjectDebugColourRGBA.a);
	}
	else
	{
		glUniform1f(bUseDebugColour_UL, (GLfloat)GL_FALSE);
	}



	sModelDrawInfo modelInfo;
	if (m_pMeshManager->FindDrawInfoByModelName(pCurrentMesh->meshName, modelInfo))
	{
		// Found it!!!

		glBindVertexArray(modelInfo.VAO_ID); 		//  enable VAO (and everything else)
		glDrawElements(GL_TRIANGLES,
			modelInfo.numberOfIndices,
			GL_UNSIGNED_INT,
			0);
		glBindVertexArray(0); 			            // disable VAO (and everything else)

	}

	return;
}

bool cGraphicsMain::LoadModels(void)
{

	// bun_zipper_res2_xyz_n_rgba.ply
// bathtub_xyz_n_rgba.ply

//    // Add some models to the "scene"
//    cMesh bunny1;   
//    bunny1.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny1.position = glm::vec3(-1.0f, 0.0f, 0.0f);
//    bunny1.scale = 10.0f;
//    bunny1.orientation.x = glm::radians(45.0f);
//
//    cMesh bunny2;
//    bunny2.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bunny2.scale = 7.5f;
//    bunny2.orientation.y = glm::radians(135.0f);
//
//    cMesh bathtub;
//    bathtub.meshName = "bathtub_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bathtub.scale = 0.25f;
//
////    // Smart array of cMesh object
////    std::vector<cMesh> vecMeshesToDraw;
//    g_vecMeshesToDraw.push_back(bunny1);
//    g_vecMeshesToDraw.push_back(bunny2);
//    g_vecMeshesToDraw.push_back(bathtub);
//    g_vecMeshesToDraw.push_back(terrain);

//    cMesh* pTerrain = new cMesh();
//    pTerrain->meshName = "Terrain_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    pTerrain->scale = 1.0f;
//    pTerrain->drawPosition.y = -25.0f;
//    ::g_vec_pMeshesToDraw.push_back(pTerrain);


//    cMesh* pGridGroundMesh = new cMesh();
//    pGridGroundMesh->meshName = "Flat_Grid_100x100.ply";
//pGridGroundMesh->bIsWireframe = true;
//pGridGroundMesh->bDoNotLight = true;
// note this does NOT have a physProps, so is ignored by the physics update loop
//    pGridGroundMesh->drawPosition.y = 0.0f;   //  0,-10,0
//    pGridGroundMesh->friendlyName = "Ground";
//    ::g_vec_pMeshesToDraw.push_back(pGridGroundMesh);

	cMesh* player = new cMesh();
	player->meshName = "player7.ply";
	//pFlat_1x1_planeMesh->bIsWireframe = true;
	//pFlat_1x1_planeMesh->bDoNotLight = true;
	// note this does NOT have a physProps, so is ignored by the physics update loop
	player->drawPosition.y = -0.0f;   //  0,-10,0
	player->scale = 100;
	player->friendlyName = "player";
	m_vec_pMeshesToDraw.push_back(player);

// 	cMesh* pFlat_1x1_planeMesh_DEBUG = new cMesh();
// 	pFlat_1x1_planeMesh_DEBUG->meshName = "Flat_1x1_plane.ply";
// 	pFlat_1x1_planeMesh->bIsWireframe = true;
// 	pFlat_1x1_planeMesh->bDoNotLight = true;
// 	pFlat_1x1_planeMesh->bUseDebugColours = true;
// 	pFlat_1x1_planeMesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
// 	// note this does NOT have a physProps, so is ignored by the physics update loop
// 	pFlat_1x1_planeMesh_DEBUG->drawPosition.y = pFlat_1x1_planeMesh->drawPosition.y - 0.01f;   //  0,-10,0
// 	m_vec_pMeshesToDraw.push_back(pFlat_1x1_planeMesh_DEBUG);


	return true;
}
