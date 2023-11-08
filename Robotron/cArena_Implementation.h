#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <map>

#include "cHuman.h"
#include "iRobotron.h"
#include "cPlayer.h"
#include "cMeshFactory.h"
#include "cGraphicsMain.h"
#include "iProjectile.h"
#include "cCharacterBuilder.h"


class cArena_Implementation
{
public:
	cArena_Implementation();		// Can't be called by anything but "me" (i.e. the cArena class)
	~cArena_Implementation();

	glm::vec2 getClosestHuman(glm::vec2 whereIAm); // For the brains
	glm::vec2 getPlayerPosition(); // For most robotrons; will return a unit vector

	// Factories/builders call these
	void setPlayer(cPlayer* player, AnimationInfo* newInfo);
	void addRobotron(iRobotron* newRobo, AnimationInfo* newInfo);
	void addProjectile(iProjectile* newProjectile, AnimationInfo* newInfo);
	void addHuman(cHuman* newHuman, AnimationInfo* newInfo);
	void addAfterimage(cMesh* aImg);

	void Initialize();
	void storeKeys(std::vector<bool> keys); // GLFW call back calls this to store key inputs for later parsing
	void Update();

private:
	AnimationInfo* findAnimInfoByID(int ID);
	void deleteProjectile(int projID, AnimationInfo* anim);
	void deleteRobotron(int roboNum, AnimationInfo* anim);
	void deleteHuman(int humanID, AnimationInfo* anim);
	void deletePlayer(AnimationInfo* anim);

	void InitializeLevel(bool isFresh); // isFresh specifies if it's a brand new level requiring new enemy generation, player died and reloading otherwise
	void ResetPlacementArray(); //Sets all values in m_SpawnSpots to false

	int getScoreAmount(RoboType type);
	void createScoreNumber(int score, glm::vec2 pos); // Creates a mesh of the desired score(1000-5000) at the location provided

	std::vector<bool> m_keysPressed; // Last recorded user input
	std::vector<iRobotron*> m_robotrons; // Vector of all enemies
	std::vector<cHuman*> m_humans; // Vector of all existing humans
	std::vector<iProjectile*> m_projectiles; // Vector of all existing projectiles
	cPlayer* m_thePlayer;

	std::vector<cMesh*> mScoreboard;
	std::vector<cMesh*> mWaveCounter;
	std::vector<cMesh*> mLives;

	int m_XBoundary = 113;
	int m_YBoundary = 55;

	int m_lives = 3; // Default start with 3 lives
	int m_score = 0; // Internal representation of score, used to update visual score
	int m_lifeScore = 0; // Internal number to keep track of when to add a life (every time difference between this and score is >= 150,000 add a life and add 150,000 to it)
	int m_wave = 0; // Current wave (helps scale difficulty)
	int m_NextHumanPoints = 1000;

	float const m_GameContinueInterval = 2.0f; // Pause time after player death, and upon stage regeneration
	double m_TimeTillGameContinues = m_GameContinueInterval; // Variable that delays game object updates. Allows a delay at the start of the game, and when the player dies before continuing

	bool m_bResetStage = false; // Triggers from completing a level or a player death
	bool m_bResetFresh = false; // Bool indicating if a stage should start fresh, player dies - false       player completes stage - true


	bool m_SpawnSpots[21][9]; // 10 horizontal slots to left and right of 0,0 (player)| 4 vertical slots above and below 0,0 (player)

	double lastTime; // Time at last update; used for delta time
	int nextID = 0; // Unique ID assigned to each entity
	std::map<int, AnimationInfo*> m_spriteIDMap; // Map matching unique ID to sprite information
	//cMeshFactory* m_meshFactory;
	cGraphicsMain* m_pGraphMain;
	cCharacterBuilder* m_pCharacterMaker;
};