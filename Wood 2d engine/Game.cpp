#include "Game.h"


#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <algorithm>




Game::Game():
	playerShouldJump(false),
	VelocityX(0.0f),
	VelocityY(0.0f),
	State(GAME_ACTIVE),
	Width(800),
	Height(600),
	Running(true),
	PlayerPos(glm::vec2(0.0f, 100.0f)),//387.0f, 287.0f
	CameraScale(1.0f),
	GlobalScale(40.0f),
	Screen()
{
	Screen.Set_width(Width);
	Screen.Set_height(Height);

	time = glm::vec3(0.0f,0.0f,0.0f);
	time_frames = 0.0f;
}




//Start function
void Game::Start()
{
	//Create the window with afferent parameters
	Screen.Create_Window("My game");
	Screen.Set_Settings();
	

	//Delta 
	GLfloat t = 0.0f;
	GLfloat dt = 1.0f/60.0f;
	GLfloat previousTime = SDL_GetTicks();

	//Init Game Data
	this->Initialize();

	//const GLubyte* ren = glGetString(GL_RENDERER);
	//std::cout << ren<<std::endl;
	//Start dem Loops
	while (Running) {
		//Delta 
		GLfloat currentTime = SDL_GetTicks();
		GLfloat frameTime = currentTime - previousTime;
		previousTime = currentTime;

		//Delta Ben
		//currentTick = SDL_GetTicks();
		//GLfloat frameTime = currentTick - prevTick;
		//prevTick = currentTick;

		//GLfloat totalDeltaTtime = frameTime / desiredFrameTime;

		//Process input
		this->ProcessInput();

		//Update 
		GLuint i = 0;

		//while (frameTime > 0.0f && i < 5) {
		//	GLfloat deltaTime = std::min(frameTime, 5.0f);
		//	this->Update(deltaTime);
		//	frameTime -= deltaTime;
		//	i++;
			//std::cout << deltaTime << std::endl;
		//}
		//std::cout << frameTime << std::endl;
		GLfloat deltaTime = std::min(frameTime, 1.0f);
		for (GLuint i = 0; i<frameTime; i++)
			this->Update(1.0f/60.0f);

		//Render
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		this->Render();
		SDL_GL_SwapWindow(this->Screen.Get_WindowID());
	}

	SDL_Quit();
}

//Init function
void Game::Initialize() {



	//Load Shaders
	DataManager::LoadShader("Data/Shaders/SpriteShader.vert", "Data/Shaders/SpriteShader.frag", "SpriteShader");

	//Load textures
	//DataManager::LoadTexture("Data/Textures/BG/BG.png", "background");
	
	DataManager::LoadTexture("Data/Textures/P1_Tilesheet.png", "player",glm::ivec2(7,3));

	DataManager::LoadTexture("Data/Textures/Brick.png", "brick");
	DataManager::LoadTexture("Data/Textures/Brick2.png", "brick2");
	DataManager::LoadTexture("Data/Textures/Ground.png", "ground");


	///Initialise GameObjects
	//for (GLuint i = 0; i < DataManager::Objects.size();i++) {
	//	DataManager::Objects[i].init();
	//}



	//Initialization of Pointers
		///Init Camera
	this->Camera = new Camera2D(PlayerPos, CameraScale, (GLfloat)this->Width, (GLfloat)this->Height);
	///Init Renderer
	this->SpriteRenderer = new Renderer(DataManager::GetShader("SpriteShader"));
	///Init Level
// EMPTY SPACE
	
	//this->Player = new Tile(DataManager::GetTexture("player"), PlayerPos, GlobalScale,glm::vec2(19.75f));//19.75
	/// Init Physics
	//this->physics = new WorldPhysics(glm::vec2(0.0f, 9.81f));//9.81f
	//this->physics->initGround();
	DataManager::initWorld(glm::vec2(0.0f, 9.81f));
	DataManager::initGround();

	///Init Player
	player = new Player(DataManager::GetTexture("player"), glm::vec2(0.0f, 0.0f), glm::vec2(72.0f,97.0f));

	/// a few blocks
	Block1 = new Actor(DataManager::GetTexture("brick"), glm::vec2(0.0f, 0.0f), GlobalScale);
	Block1->getBox().getBody()->SetFixedRotation(true);

	Block11 = new Actor(DataManager::GetTexture("brick2"), glm::vec2(100.0f, 40.0f), GlobalScale,b2_staticBody);
	Block2 = new Actor(DataManager::GetTexture("brick"), glm::vec2(200, 0.0f), GlobalScale);

	Block3 = new Tile(DataManager::GetTexture("brick2"), glm::vec2(-200.0f, 200.0f), GlobalScale);

	/// a level maybe
	//level = new Level("Data/Levels/Level_1.lvl", GlobalScale, Width, Height);
}

//Destructor -> Deletes every pointer used
Game::~Game()
{
	delete SpriteRenderer;
	delete Camera;
	//delete Player;
	 
}


// Loop
void Game::ProcessInput() {

	int Halfwidth = (int)(this->Width / 2);
	int Halfheight = (int)(this->Height / 2);

	SDL_Event Evnt;
	while (SDL_PollEvent(&Evnt))
	{

		if (Evnt.key.keysym.sym == SDLK_ESCAPE) {
			this->Running = false;
			SDL_ShowCursor(true);
			break;
		}


		switch (Evnt.type) {
		
		case SDL_KEYDOWN:
			switch (Evnt.key.keysym.sym) {
			case SDLK_LEFT:this->VelocityX = -1.0f; player->setAnimState(WALKING_LEFT);  break;
			case SDLK_RIGHT:this->VelocityX = 1.0f; player->setAnimState(WALKING_RIGHT);  break;
			case SDLK_UP:this->VelocityY = -1.0f; break;
			case SDLK_DOWN:this->VelocityY = 1.0f; break;
			case SDLK_SPACE: {
				//b2Vec2 vel = Block1->getBox().getBody()->GetLinearVelocity();
				//vel.y = -75.0f;
				//Block1->getBox().getBody()->SetLinearVelocity(vel);
				///impulse
				if (playerShouldJump) {
					GLfloat impulse = player->getBox().getBody()->GetMass()*(75.0f);
					player->getBox().getBody()->ApplyLinearImpulse(b2Vec2(0.0f, -impulse), player->getBox().getBody()->GetWorldCenter(), true);
					playerShouldJump = false;

				}
				//VelocityJ = 6.0f;
				break; }
			case SDLK_a: DataManager::addObject(DataManager::GetTexture("brick2"), glm::vec2(0.0f,-80.0f), GlobalScale); break;
			case SDLK_r: {this->PlayerPos = glm::vec2(387.0f, 287.0f); break; }
			default: break;
			}
			break;
		case SDL_KEYUP:
			switch (Evnt.key.keysym.sym) {
			case SDLK_LEFT:this->VelocityX = 0.0f; player->setFrameCount(8); player->setAnimState(STANDING); break;
			case SDLK_RIGHT:this->VelocityX = 0.0f; player->setFrameCount(0); player->setAnimState(STANDING); break;
			case SDLK_UP:this->VelocityY = 0.0f; break;
			case SDLK_DOWN:this->VelocityY = 0.0f; break;
			case SDLK_SPACE:this->playerShouldJump = true; break;
			default: break;
			}
			break;
			//case SDL_MOUSEMOTION:
			//	SDL_WarpMouseInWindow(this->Screen.Get_WindowID(), Halfwidth, Halfheight);break;
		default: break;
		}
	}
}

void Game::Render() {

	//Render layers
		///Render background
	//this->SpriteRenderer->Draw(DataManager::GetTexture("background"), glm::vec2(this->Width / 2.0f, this->Height / 2.0f), glm::vec2(this->Width, this->Height));
	/// Render Level

	///GameObjects
	for (GLuint i = 0; i < DataManager::Objects.size(); i++) {
		DataManager::Objects[i].render(SpriteRenderer);
	}

	for (GLuint i = 0; i < 10; i++) {
		Block3->setPosition(glm::vec2(180.0f - i * 40, 200.0f));
		Block3->Draw(SpriteRenderer);
	}
	//Block3->Draw(SpriteRenderer);
	Block11->render(SpriteRenderer);
	//level->Draw(SpriteRenderer);
	Block1->render(SpriteRenderer);
	Block2->render(SpriteRenderer);
	///Render the Player
	player->render(SpriteRenderer);

	//this->Player->Draw(this->SpriteRenderer);


}

void Game::Update(GLfloat deltatime) {

	///World step
	//this->physics->step(deltatime);
	DataManager::world->Step(deltatime, 8, 3);

	numEntities = DataManager::Objects.size();
	//std::cout << numEntities << std::endl;
	///GameObjects
	for (GLuint i = 0; i < DataManager::Objects.size(); i++) {
		if (DataManager::Objects[i].shouldTick())
			DataManager::Objects[i].tick(deltatime);
		if (DataManager::Objects[i].shouldBeDestroyed()) {
			DataManager::destroyObject(i);
			i--;
		}
		
	}

	// Player update
	player->tick(deltatime);
	

	GLfloat X = VelocityX*deltatime*200;
	GLfloat Y = VelocityY*deltatime*200;

	b2Vec2 pos = player->getBox().getBody()->GetPosition();
	b2Vec2 vel = player->getBox().getBody()->GetLinearVelocity();
	//Block1->getBox().getBody()->SetLinearVelocity(b2Vec2(VelocityX*10.0f, vel.y));

	float velChange = VelocityX*10.0f - vel.x;
	float impulse = player->getBox().getBody()->GetMass()*velChange;
	player->getBox().getBody()->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), player->getBox().getBody()->GetWorldCenter(), true);

	//if (VelocityJ > 0.0f) {
	//	this->physics->box1.getBody()->ApplyForce(b2Vec2(0.0f, -75.0f), physics->box1.getBody()->GetWorldCenter(), true);
	//	VelocityJ--;
	//}

	//Block1->setPosition(glm::vec2(pos.x,pos.y));
	Block1->tick(deltatime);

	//pos = this->physics->box2.getBody()->GetPosition();
	//Block2->setPosition(glm::vec2(pos.x, pos.y));
	Block2->tick(deltatime);
	
	
	
	//Collision ends here

	//Move the player
	PlayerPos.y += Y;
	PlayerPos.x += X;

	pos = player->getBox().getBody()->GetPosition();
	Camera->Set_PlayerCamPos(glm::vec2(pos.x,100.0f));//pos.y

	//Player->Update_Position(glm::vec2(pos.x,pos.y));
	
	Camera->Update();
	DataManager::GetShader("SpriteShader").SetMatrix4("projection", Camera->Get_cameraMatrix(), true);
}
