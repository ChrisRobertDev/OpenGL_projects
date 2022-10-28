#pragma once

#include "stdafx.h"

#include "Window.h"
#include "DataManager.h"
#include "Tile.h"
#include "ECS/ECS.h"
#include "Transform.h"
#include "InputSystem.h"
#include "ECS/EventHandler.h"
#include "RendererSystem.h"
#include "CameraSystem.h"
#include "Input.h"
#include "DynamicBody.h"
#include "StaticBody.h"
#include "CapsuleDBody.h"
#include "PlayerAnimation.h"
#include "Shape.h"
#include "Terrain.h"

enum GameState {
	GAME_ACTIVE,
	GAME_QUIT,
	GAME_MENU
};

class Game
{
private:
	ECS ecs;
	//Entity& pawn;
	//Entity& Background;
	GameState State;
	Window Screen;
	
	GLboolean playerShouldJump;
	glm::vec3 time;
	GLfloat time_frames;
	Terrain* terrain;

	//Velocity Scale Player pos
	GLfloat VelocityX,VelocityY,VelocityJ,camVelX,camVelY,mouseX,mouseY;
	GLfloat LastVelX, LstVelY;
	GLfloat CameraScale;
	glm::vec2 GlobalScale;
	glm::vec2 PlayerPos;
	GLuint numEntities;
	GLuint indexTex;


public:
	GLuint Width, Height;
	bool quit;
	Game();
	~Game();

	// Start function
	void Start();
	//Init function
	void Initialize();

	// Loop
	//void ProcessInput();
	void Render();
	void Update(GLfloat deltatime);
};

