#pragma once

#include "Window.h"
#include "DataManager.h"
#include "Renderer.h"
#include "Camera2D.h"
#include "Tile.h"
#include "Level.h"
#include "WorldPhysics.h"
#include "GameObject.h"
#include "Actor.h"
#include "Player.h"

//#include <Box2D\Box2D.h>

enum GameState {
	GAME_ACTIVE,
	GAME_QUIT,
	GAME_MENU
};

class Game
{
private:
	GameState State;
	Window Screen;
	bool Running;
	GLboolean playerShouldJump;
	glm::vec3 time;
	GLfloat time_frames;

	WorldPhysics* physics;

	//Velocity Scale Player pos
	GLfloat VelocityX,VelocityY,VelocityJ;
	GLfloat LastVelX, LstVelY;
	GLfloat CameraScale;
	glm::vec2 GlobalScale;
	glm::vec2 PlayerPos;
	GLuint numEntities;

	//Declaration of Pointers
	Player* player;
	Renderer *SpriteRenderer;
	Camera2D *Camera;
	//Level *level;
	Tile *Block3;
	Actor *Block1,*Block2,*Block11;
	Level *level;

public:
	GLuint Width, Height;

	Game();
	~Game();

	// Start function
	void Start();
	//Init function
	void Initialize();

	// Loop
	void ProcessInput();
	void Render();
	void Update(GLfloat deltatime);
};

