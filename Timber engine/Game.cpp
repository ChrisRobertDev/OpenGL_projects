#include "stdafx.h"
#include "Game.h"


Game::Game():
	playerShouldJump(false),
	VelocityX(0.0f),
	VelocityY(0.0f),
	indexTex(0),
	camVelX(0.0f), 
	camVelY(0.0f),
	State(GAME_ACTIVE),
	Width(800),
	Height(600),
	quit(false),
	PlayerPos(glm::vec2(0.0f, 0.0f)),//387.0f, 287.0f
	CameraScale(0.5f),
	GlobalScale(70.0f/100.0f),
	Screen()
{
	Screen.setWidth(Width);
	Screen.setHeight(Height);

	time = glm::vec3(0.0f,0.0f,0.0f);
	time_frames = 0.0f;
	
}




//Start function
void Game::Start()
{
	//Create the window with afferent parameters
	Screen.createWindow("My game");
	Screen.initSettings();
	

	//Delta 
	GLfloat dt = 320.0f;
	GLfloat previousTime = SDL_GetTicks();

	//Init Game Data
	this->Initialize();

	//Start dem Loops
	while (!quit) {
		//Delta 
		GLfloat currentTime = SDL_GetTicks();
		GLfloat frameTime = currentTime - previousTime;
		previousTime = currentTime;

		//Update 
		GLuint i = 0;
		//std::cout << frameTime << std::endl;
		while (frameTime > 0.0f && i < 5) {
			GLfloat deltaTime = std::min(frameTime, 5.0f);
			GLfloat totalDeltaTtime = deltaTime / dt;
			this->Update(totalDeltaTtime);
			frameTime -= deltaTime;
			i++;
			//std::cout << deltaTime << std::endl;
		}

		//Render
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		this->Render();

		//refresh ECS
		ecs.refresh();

		SDL_GL_SwapWindow(this->Screen.Get_WindowID());
	}

	ecs.flush();
	Screen.closeWindow();
}

//Init function
void Game::Initialize() {
	// Quit event handling
	EventHandler<InputEvent>::registerObserver(InputEvent::CLOSE_PRESSED, [this] {this->quit = true; });


	//Load Shaders
	DataManager::LoadShader("Data/Shaders/SpriteShader.vert", "Data/Shaders/SpriteShader.frag", "SpriteShader");
	DataManager::LoadShader("Data/Shaders/DebugShader.vert", "Data/Shaders/DebugShader.frag", "DebugShader");
	//Load textures
	//DataManager::LoadTexture("Data/Textures/BG/BG.png", "background");
	
	DataManager::LoadTexture("Data/Textures/P1_Tilesheet.png", "player",glm::ivec2(7,3));
	DataManager::LoadTexture("Data/Textures/Level_Tileset.png", "tiles", glm::ivec2(12, 13));
	DataManager::LoadTexture("Data/Textures/Brick.png", "brick");
	DataManager::LoadTexture("Data/Textures/Brick2.png", "brick2");
	DataManager::LoadTexture("Data/Textures/Ground.png", "ground");
	DataManager::LoadTexture("Data/Textures/bg.png", "bg");
	//Init Physics
	DataManager::initWorld(glm::vec2(0.0f, -6.81f));
	DataManager::initGround();

	std::vector<b2Vec2> lines;
	lines.emplace_back(b2Vec2(0.0f, 0.0f));
	lines.emplace_back(b2Vec2(4.2f, 0.0f));
	lines.emplace_back(b2Vec2(4.2f, 0.0f));
	lines.emplace_back(b2Vec2(4.2f, -2.1f));
	lines.emplace_back(b2Vec2(4.2f, -2.1f));
	lines.emplace_back(b2Vec2(0.0f, -2.1f));
	lines.emplace_back(b2Vec2(0.0f, -2.1f));
	lines.emplace_back(b2Vec2(0.0f, 0.0f));
	std::vector<b2Vec2> platformLines;
	platformLines.emplace_back(b2Vec2(0.0f, 0.0f));
	platformLines.emplace_back(b2Vec2(2.1f, 0.0f));
	platformLines.emplace_back(b2Vec2(2.1f, 0.0f));
	platformLines.emplace_back(b2Vec2(1.575f, -0.575f));
	platformLines.emplace_back(b2Vec2(1.575f, -0.575f));
	platformLines.emplace_back(b2Vec2(0.875f, -0.575f));
	platformLines.emplace_back(b2Vec2(0.875f, -0.575f));
	platformLines.emplace_back(b2Vec2(0.0f, 0.0f));

	std::vector<b2Vec2> platformLines2;
	platformLines2.emplace_back(b2Vec2(0.0f, 0.0f));
	platformLines2.emplace_back(b2Vec2(2.1f, 0.0f));
	platformLines2.emplace_back(b2Vec2(2.1f, 0.0f));
	platformLines2.emplace_back(b2Vec2(2.1f, -0.35f));
	platformLines2.emplace_back(b2Vec2(2.1f, -0.35f));
	platformLines2.emplace_back(b2Vec2(0.0f, -0.35f));
	platformLines2.emplace_back(b2Vec2(0.0f, -0.35f));
	platformLines2.emplace_back(b2Vec2(0.0f, 0.0f));

	std::vector<b2Vec2> groundLines3;
	groundLines3.emplace_back(b2Vec2(0.0f, -2.1f));
	groundLines3.emplace_back(b2Vec2(2.1f, 0.0f));
	groundLines3.emplace_back(b2Vec2(2.1f, 0.0f));
	groundLines3.emplace_back(b2Vec2(2.1f, -4.2f));
	groundLines3.emplace_back(b2Vec2(2.1f, -4.2f));
	groundLines3.emplace_back(b2Vec2(0.0f, -4.2f));
	groundLines3.emplace_back(b2Vec2(0.0f, -4.2f));
	groundLines3.emplace_back(b2Vec2(0.0f, -2.1f));

	// ECS
	
	Entity& Background = ecs.eManager.addEntity();
	Entity& Brick = ecs.eManager.addEntity();
	Entity& Brick2 = ecs.eManager.addEntity();
	Entity& groundShape1 = ecs.eManager.addEntity();
	Entity& groundShape2 = ecs.eManager.addEntity();
	Entity& groundShape3 = ecs.eManager.addEntity();
	Entity& platform = ecs.eManager.addEntity();
	Entity& platform2 = ecs.eManager.addEntity();
	Entity& pawn = ecs.eManager.addEntity();

	Brick.addComponent<Transform>(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f));
	Brick.addComponent<Material>(DataManager::GetTexture("brick2"), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	Brick.setRenderable(true);
	//Brick2.addComponent<Transform>(glm::vec2(0.5f, -1.0f), glm::vec2(0.5f));
	//Brick2.addComponent<Material>(DataManager::GetTexture("brick2"), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	//Brick2.addComponent<StaticBody>(glm::vec2(1.0f, -1.5f), glm::vec2(0.5f));

	terrain = new Terrain(ecs,"tiles",glm::vec2(-8.4f,-4.0f),glm::vec2(0.7f),"Data/Shapes/newGround.tr");

	groundShape1.addComponent<Transform>(glm::vec2(0.0f, 0.0f), glm::vec2(0.7f));
	groundShape1.addComponent<Material>(DataManager::GetTexture("tiles"));
	groundShape1.addComponent<Shape>("Data/Shapes/Ground.shape");
	groundShape1.addComponent<StaticBody>(glm::vec2(-4.2f, -4.0f), lines);
	groundShape1.setRenderable(true);

	groundShape2.addComponent<Transform>(glm::vec2(3.0f, -2.0f), glm::vec2(0.7f));
	groundShape2.addComponent<Material>(DataManager::GetTexture("tiles"));
	groundShape2.addComponent<Shape>("Data/Shapes/Ground.shape");
	groundShape2.addComponent<StaticBody>(glm::vec2(0.0f, -4.0f), lines);
	groundShape2.setRenderable(true);

	groundShape3.addComponent<Transform>(glm::vec2(3.0f, -2.0f), glm::vec2(0.7f));
	groundShape3.addComponent<Material>(DataManager::GetTexture("tiles"));
	groundShape3.addComponent<Shape>("Data/Shapes/Ground2.shape");
	groundShape3.addComponent<StaticBody>(glm::vec2(4.2f, -1.9f), groundLines3);
	groundShape3.setRenderable(true);

	platform.addComponent<Transform>(glm::vec2(0.0f, 0.0f), glm::vec2(0.7f));
	platform.addComponent<Material>(DataManager::GetTexture("tiles"));
	platform.addComponent<Shape>("Data/Shapes/platform.shape");
	platform.addComponent<StaticBody>(glm::vec2(1.0f, 0.0f), platformLines);
	platform.setRenderable(true);

	platform2.addComponent<Transform>(glm::vec2(0.0f, 0.0f), glm::vec2(0.7f));
	platform2.addComponent<Material>(DataManager::GetTexture("tiles"));
	platform2.addComponent<Shape>("Data/Shapes/platform2.shape");
	platform2.addComponent<StaticBody>(glm::vec2(-3.0f, 0.35f), platformLines2);
	platform2.setRenderable(true);

	Background.addComponent<Transform>(glm::vec2(0.0f), glm::vec2(40.0f));
	Background.addComponent<Material>(DataManager::GetTexture("bg"), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	Background.setRenderable(true);

	pawn.addComponent<Transform>(glm::vec2(0.0f),glm::vec2(0.72f,0.97f));
	pawn.addComponent<Input>();
	pawn.addComponent<CapsuleDBody>(glm::vec2(0.0f), glm::vec2(0.72f, 0.97f));
	pawn.addComponent<Material>(DataManager::GetTexture("player"),2,glm::vec3(0.0f));
	pawn.addComponent<PlayerAnimation>();
	pawn.setRenderable(true);

	ecs.sManager.addSystem<InputSystem>();
	ecs.sManager.addSystem<RendererSystem>(DataManager::GetShader("SpriteShader"), DataManager::GetShader("DebugShader"));
	ecs.sManager.addSystem<CameraSystem>(pawn,glm::vec2(0.0f),0.5f,Width,Height);

}

//Destructor -> Deletes every pointer used
Game::~Game()
{
	
}


// Loop


void Game::Render() {
	//
	ecs.render();
	
}

void Game::Update(GLfloat deltatime) {

	DataManager::world->Step(deltatime, 8, 3);

	//Update ECS
	ecs.update(deltatime);
}
