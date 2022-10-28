
#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <SDL\SDL.h>
#include <glm\gtc\matrix_transform.hpp>
#include <AntTweakBar\AntTweakBar.h>

#include <bullet\btBulletDynamicsCommon.h>
#include <bullet\btBulletCollisionCommon.h>

#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Window.h"
#include "Timer.h"
#include "Model.h"
#include "Object.h"
#include "Quad.h"
#include "CubeMap.h"
#include "Sun.h"
#include "FrameBuffer.h"
#include "PostProcessing.h"
#include "Plane.h"
#include "Noise.h"

int main(int argc, char** argv)
{
	GLuint width = 800;
	GLuint height = 600;
	std::string s("Titan 1.00");

	Window window(s, width, height);
	//Post-Processing init func
	PostProcessing::Initialize(width, height);
	
	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	// ATB second run
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(width, height);

	TwBar* bar;
	bar = TwNewBar("Titan Tester");

	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with SDL and OpenGL.\nPress [Space] to toggle fullscreen.' ");

	//end of Tweak bar

	std::cout << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << std::endl;
	std::cout << SDL_MAJOR_VERSION << SDL_MINOR_VERSION<<std::endl;

	
	glm::vec3 lightPosition(3.0f, 5.0f, 4.0f);
	
	//Light shader
	Shader* lightShader;
	lightShader = new Shader("Shaders/simpleLight.vsd", "Shaders/simpleLight.fsd");
	//textured Cube shader
	Shader* shader;
	shader = new Shader("Shaders/Cube2.vsd", "Shaders/Cube2.fsd");
	Shader* modelShader;
	modelShader = new Shader("Shaders/model.vsd", "Shaders/model.fsd");
	Shader* grassShader;
	grassShader = new Shader("Shaders/grass.vsd", "Shaders/grass.fsd");
	Shader* glassShader;
	glassShader = new Shader("Shaders/glass.vsd", "Shaders/glass.fsd");
	Shader* skyboxShader;
	skyboxShader = new Shader("Shaders/skybox.vsd", "Shaders/skybox.fsd");
	Shader* sunShader;
	sunShader = new Shader("Shaders/sun.vsd", "Shaders/sun.fsd");
	Shader* planeShader;
	planeShader = new Shader("Shaders/Plane.vsd", "Shaders/Plane.fsd");

	Camera* camera;
	camera = new Camera();
	
	CubeMap* skybox;
	skybox = new CubeMap("Textures/skybox_test/skybox.sx");
	
	Sun* sun;
	sun = new Sun("Models/Sphere/untitled.obj");

	Cube* cube;
	cube = new Cube("Textures/container2.png", "Textures/container2_specular.png");
	Cube* spCube;
	spCube = new Cube("Textures/container2.png", "Textures/container2_specular.png");

	Cube* light;
	light = new Cube();

	Quad* quad;
	quad = new Quad("Textures/grass.png");

	Quad* quad2;
	quad2 = new Quad("Textures/blending_transparent_window.png");

	Plane* plane;
	plane = new Plane(128, 1.0f, "Textures/Dirt2.jpg", true);
	Plane* water;
	water = new Plane(128, 1.0f, "Textures/water.jpg");
	//
	//Model
	//Model* nanosuit;
	//nanosuit = new Model("Models/nanosuit/nanosuit.obj");
	Object* nanosuit;
	nanosuit = new Object("nanosuit","Models/nanosuit/nanosuit.obj");


	Timer* clock;
	clock = new Timer();

	SDL_Event e;
	int handled;
	static int s_KeyMod = 0;

	bool isOpen = true;
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	
	glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 model(1.0f);
	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;
	GLfloat roll = 0.0f;
	GLfloat yawVel = 0.0f;
	GLfloat pitchVel = 0.0f;
	GLfloat rollVel = 0.0f;
	GLfloat distance = 0.0f;
	
	GLfloat currentFrame, deltaTime, lastFrame = 0.0f;
	GLfloat timeFrames = 0.0f;
	GLfloat frameRate = 60.0f;
	bool myBool = true;
	
	camera->setMovementSpeed(16.0f / frameRate);
	GLboolean pause = GL_FALSE;
	
	//Light variables
	glm::vec3 lightColor = glm::vec3(1.0f);
	glm::vec3 cubeColor = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 lightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);


	GLfloat myAngle = 0.0f;
	glm::vec3 cubePos(1.0f);
	glm::vec3 vectDir(1.0f,0.0f,0.0f);

	GLfloat exposure = 3.0f;
	GLfloat GBSun = 255.0f;
	GLfloat gamma = 0.2f;
	GLfloat screenExp = 5.0f;

	//T bar add vars

	TwAddVarRW(bar, "light X Pos", TW_TYPE_FLOAT, &(float)lightPosition.x,
		" label='light Pos X' min=-100 max=100  step=0.01 ");
	TwAddVarRW(bar, "light Y Pos", TW_TYPE_FLOAT, &(float)lightPosition.y,
		" label='light Pos Y' min=-100 max=100  step=0.01 ");
	TwAddVarRW(bar, "light Z Pos", TW_TYPE_FLOAT, &(float)lightPosition.z,
		" label='light Pos Z' min=-100 max=100  step=0.01 ");
	TwAddSeparator(bar, "Lights", "");

	TwAddVarRW(bar, "global Light", TW_TYPE_COLOR3F, &lightColor,
		" label='light Color' min=0 max=1  step=0.001 ");
	
	TwAddSeparator(bar, "Quatern", "");

	TwAddVarRW(bar, "cub X Pos", TW_TYPE_FLOAT, &(float)cubePos.x,
		" label='cub Pos X' min=-100 max=100  step=0.01 ");
	TwAddVarRW(bar, "cub Y Pos", TW_TYPE_FLOAT, &(float)cubePos.y,
		" label='cub Pos Y' min=-100 max=100  step=0.01 ");
	TwAddVarRW(bar, "cub Z Pos", TW_TYPE_FLOAT, &(float)cubePos.z,
		" label='cub Pos Z' min=-100 max=100  step=0.01 ");

	TwAddSeparator(bar, "asd", "");
	TwAddVarRW(bar, "direct quat", TW_TYPE_DIR3F, &vectDir,
		" label='Directional quat ' min=-1 max=1  step=0.001 ");
	TwAddSeparator(bar, "dfs", "");
	TwAddVarRW(bar, "exposure", TW_TYPE_FLOAT, &(float)exposure,
		" label='exposure' min=-10 max=10  step=0.1 ");
	TwAddVarRW(bar, "Sun GB", TW_TYPE_FLOAT, &(float)GBSun,
		" label='Sun GB' min=60 max=250  step=1.0 ");
	TwAddSeparator(bar, "terrain", "");
	
	TwAddVarRW(bar, "gamma", TW_TYPE_FLOAT, &(float)gamma,
		" label='gamma' min=0.2 max=5.0  step=0.01 ");
	TwAddVarRW(bar, "Screen Expos", TW_TYPE_FLOAT, &(float)screenExp,
		" label='Screen Expos' min=1.0 max=5.0  step=0.01 ");
	//end of T bar
	//Framebuffer Try 1
	Shader* screenShader;
	screenShader = new Shader("Shaders/framebuffer.vsd", "Shaders/framebuffer.fsd");
	Shader* hdrShader;
	hdrShader = new Shader("Shaders/hdr.vsd", "Shaders/hdr.fsd");
	Shader* blurShader;
	blurShader = new Shader("Shaders/Gblur.vsd", "Shaders/Gblur.fsd");
	//fbo class
	FrameBuffer* frame;
	frame = new FrameBuffer(GL_RGBA16F, width, height);//GL_RGBA16F
	frame->addAttachment();
	frame->generateRenderBuffer();
	frame->setGLAttachments();
	FrameBuffer* blurFrame1;
	FrameBuffer* blurFrame2;
	blurFrame1 = new FrameBuffer(GL_RGBA16F, width, height);
	blurFrame2 = new FrameBuffer(GL_RGBA16F, width, height);

	FrameBuffer* frame2;
	frame2 = new FrameBuffer(GL_RGBA16F, width, height);//GL_RGBA16F
	frame2->addAttachment();
	frame2->generateRenderBuffer();
	frame2->setGLAttachments();
	
	GLfloat XPosition = 0.0f;

	// Finally PHYSICS
/*
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);

	world->setGravity(btVector3(0.0f, -9.8f, 0.0f));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	world->addRigidBody(groundRigidBody);

*/
	//End of Physics

	GLfloat globalSeconds = 0.001f;
	clock->setGlobalSeconds(globalSeconds);
	while (isOpen) {
		//Fps counter >>DELTA<<
		currentFrame = (GLfloat)SDL_GetTicks() / 1000.0f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		timeFrames += deltaTime;


		clock->tick(deltaTime);

		if (timeFrames > globalSeconds) {
			//std::cout << deltaTime << std::endl;
			//frameRate = (timeFrames - deltaTime) / deltaTime;
			//std::cout << frameRate<<" fps" << std::endl;
			//clock->printTimer();
			sun->setAngle((clock->getTotalSeconds() - 7.0f * 3600.0f)  * 0.004166667);
			timeFrames = 0.0f;
		}
		
		 
		// Event stuff *still needs code amount reduction!!!
		if (pause == GL_TRUE) {	// Menu STATE
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					isOpen = false;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					isOpen = false;
				}
				// AntTweakBar event handler
				switch (e.type)
				{
				case SDL_TEXTINPUT:
					if (e.text.text[0] != 0 && e.text.text[1] == 0)
					{
						if (s_KeyMod & TW_KMOD_CTRL && e.text.text[0]<32)
							handled = TwKeyPressed(e.text.text[0] + 'a' - 1, s_KeyMod);
						else
						{
							if (s_KeyMod & KMOD_RALT)
								s_KeyMod &= ~KMOD_CTRL;
							handled = TwKeyPressed(e.text.text[0], s_KeyMod);
						}
					}
					s_KeyMod = 0;
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym & SDLK_SCANCODE_MASK)
					{
						int key = 0;
						switch (e.key.keysym.sym)
						{
						case SDLK_p:
						{
							pause = GL_FALSE;
							SDL_WarpMouseInWindow(window.getWindow(), halfWidth, halfHeight);

						}break;
						case SDLK_UP:
							key = TW_KEY_UP;
							break;
						case SDLK_DOWN:
							key = TW_KEY_DOWN;
							break;
						case SDLK_RIGHT:
							key = TW_KEY_RIGHT;
							break;
						case SDLK_LEFT:
							key = TW_KEY_LEFT;
							break;
						case SDLK_INSERT:
							key = TW_KEY_INSERT;
							break;
						case SDLK_HOME:
							key = TW_KEY_HOME;
							break;
						case SDLK_END:
							key = TW_KEY_END;
							break;
						case SDLK_PAGEUP:
							key = TW_KEY_PAGE_UP;
							break;
						case SDLK_PAGEDOWN:
							key = TW_KEY_PAGE_DOWN;
							break;
						default:
							if (e.key.keysym.sym >= SDLK_F1 && e.key.keysym.sym <= SDLK_F12)
								key = e.key.keysym.sym + TW_KEY_F1 - SDLK_F1;
						}
						if (key != 0)
							handled = TwKeyPressed(key, e.key.keysym.mod);
					}
					else if (e.key.keysym.mod & TW_KMOD_ALT)
						handled = TwKeyPressed(e.key.keysym.sym & 0xFF, e.key.keysym.mod);
					else
						s_KeyMod = e.key.keysym.mod;
					break;
				case SDL_KEYUP:
					s_KeyMod = 0;
					break;
				case SDL_MOUSEMOTION:
					handled = TwMouseMotion(e.motion.x, e.motion.y);
					break;
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
					if (e.type == SDL_MOUSEBUTTONDOWN && (e.button.button == 4 || e.button.button == 5))  // mouse wheel
					{
						static int s_WheelPos = 0;
						if (e.button.button == 4)
							++s_WheelPos;
						else
							--s_WheelPos;
						handled = TwMouseWheel(s_WheelPos);
					}
					else
						handled = TwMouseButton((e.type == SDL_MOUSEBUTTONUP) ? TW_MOUSE_RELEASED : TW_MOUSE_PRESSED, (TwMouseButtonID)e.button.button);
					break;
				}
				//return to camera
				switch (e.type)
				{
				case SDL_KEYDOWN:
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_p:
					{
						pause = GL_FALSE; 
						SDL_WarpMouseInWindow(window.getWindow(), halfWidth, halfHeight);
						
					}break;
					default:
						break;
					}
					break;
				}
				default:break;
				}
			}

		}
		else
		{// Playing state
			//processInput needs a class
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					isOpen = false;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					isOpen = false;
				}

				switch (e.type)
				{
				case SDL_KEYDOWN:
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_p:pause = GL_TRUE; break;
					case SDLK_a:camera->setVelocityX(-1.0f); break;
					case SDLK_d:camera->setVelocityX(1.0f); break;
					case SDLK_w:camera->setVelocityZ(1.0f); break;
					case SDLK_s:camera->setVelocityZ(-1.0f); break;

					case SDLK_UP:pitchVel = -1.0f; break;
					case SDLK_DOWN:pitchVel = 1.0f; break;
					case SDLK_LEFT:yawVel = -1.0f; break;
					case SDLK_RIGHT:yawVel = 1.0f; break;
					case SDLK_m:rollVel = 1.0f; break;
					case SDLK_n:rollVel = -1.0f; break;
					default:
						break;
					}
					break;
				}
				case SDL_KEYUP:
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_a:camera->setVelocityX(0.0f); break;
					case SDLK_d:camera->setVelocityX(0.0f); break;
					case SDLK_w:camera->setVelocityZ(0.0f); break;
					case SDLK_s:camera->setVelocityZ(0.0f); break;

					case SDLK_UP:pitchVel = 0.0f; break;
					case SDLK_DOWN:pitchVel = 0.0f; break;
					case SDLK_LEFT:yawVel = 0.0f; break;
					case SDLK_RIGHT:yawVel = 0.0f; break;
					case SDLK_m:rollVel = 0.0f; break;
					case SDLK_n:rollVel = 0.0f; break;

					default:
						break;
					}
					break;
				}

				case SDL_MOUSEMOTION:
				{
					// Parameters for Mouse Sensitivity
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (x <= halfWidth)
						camera->setYawVelocity((GLfloat)(halfWidth - x));
					else
						camera->setYawVelocity((GLfloat)(x - halfWidth));

					if (y <= halfHeight)
						camera->setPitchVelocity((GLfloat)(halfHeight - y));
					else
						camera->setPitchVelocity((GLfloat)(y - halfHeight));

					//Actual mouse movements
					if (e.motion.x > halfWidth)
						camera->computeYawVelocity(1.0f);
					else
						if (e.motion.x < halfWidth)
							camera->computeYawVelocity(-1.0f);

					if (e.motion.y > halfHeight)
						camera->computePitchVelocity(-1.0f);
					else
						if (e.motion.y < halfHeight)
							camera->computePitchVelocity(1.0f);

					//Check for the mouse movements DEBUG
					//std::cout << x << " " << y <<std::endl;

					SDL_WarpMouseInWindow(window.getWindow(), halfWidth, halfHeight);

				}break;


				default:break;

				}

			}

		}
		// end of events


		sun->rotateSun();
		//update Camera
		camera->UpdateQuat();

		//Update view and projection
		skybox->setProjection(projection);
		skybox->setView(camera->getViewMatrixQuat());
		sun->setProjection(projection);
		sun->setView(camera->getViewMatrixQuat());
		cube->setProjection(projection);
		cube->setView(camera->getViewMatrixQuat());
		plane->setProjection(projection);
		plane->setView(camera->getViewMatrixQuat());
		water->setProjection(projection);
		water->setView(camera->getViewMatrixQuat());
		spCube->setProjection(projection);
		spCube->setView(camera->getViewMatrixQuat());
		light->setProjection(projection);
		light->setView(camera->getViewMatrixQuat());
		quad->setProjection(projection);
		quad->setView(camera->getViewMatrixQuat());
		quad2->setProjection(projection);
		quad2->setView(camera->getViewMatrixQuat());
		nanosuit->setProjection(projection);
		nanosuit->setView(camera->getViewMatrixQuat());

		//Collision
		
		//world->stepSimulation(1.0f / 60.0f, 10);
		
		/// Kinda empty
		distance += 0.001f;
		myAngle += 2.0f;
		if (myAngle == 360.0f)
			myAngle = 0.0f;
		yaw += yawVel;
		pitch += pitchVel;
		roll += rollVel;

		XPosition += 0.001f;


		//Render	still too much
		
		frame->Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		skybox->Render(skyboxShader);
		sunShader->SetFloat("exposure", exposure, true);
		sun->setColor(glm::vec3(1.0f, GBSun / 255.0f, GBSun / 255.0f));
		sun->Render(sunShader);

		cube->setViewPosition(camera->getPosition());
		cube->setLightPosition(sun->getDirectionalLight());
		cube->setCubeColor(cubeColor);
		cube->setLightColor(lightColor);
		for (GLfloat i = 0.0f; i < 16.0f; i += 1.0f) {
			for (GLfloat j = 0.0f; j < 16.0f; j += 1.0f) {
				glEnable(GL_CULL_FACE);
				//shader->SetInteger("tester", var1, true);
				cube->setPosition(glm::vec3(i, -2.0f, j));
				//cube->setLightPosition(-lightDirection);
				cube->Render(shader);
				glDisable(GL_CULL_FACE);
				grassShader->Use();
				quad->setPosition(glm::vec3(i, -1.0f, j - 0.5f));
				quad->Render(grassShader);
			}
		}
		glEnable(GL_CULL_FACE);

		shader->Use();
		cube->setPosition(glm::vec3(XPosition, 2.0f, 2.0f));
		cube->Render(shader);
		cube->setPosition(glm::vec3(3.0f, 4.0f, 5.0f));
		cube->Render(shader);
		cube->setPosition(glm::vec3(5.0f, 2.0f, 4.0f));
		cube->Render(shader);
		cube->setPosition(glm::vec3(3.0f, 3.0f, 7.0f));
		cube->Render(shader);
		
		

		spCube->setPosition( glm::vec3(3.0f, 0.0f, 0.0f));
		spCube->setRotation(yaw, pitch, roll);
		spCube->Render(shader);
		
		lightShader->Use();
		light->setPosition(glm::vec3(2.0f));
		light->Render(lightShader);

		lightShader->Use();
		light->setPosition(glm::vec3(1.0f, 2.0f, 2.0f));
		light->Render(lightShader);

		//modelShader->Use();
		nanosuit->setPosition(glm::vec3(2.0f,0.0f,2.0f));
		nanosuit->setScale(glm::vec3(0.1f));
		nanosuit->Render(modelShader);

		
		glDisable(GL_CULL_FACE);

		
		plane->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		plane->setLightDirection(sun->getDirectionalLight());
		plane->Render(planeShader);

		water->setPosition(glm::vec3(0.0f,-3.0f,0.0f));
		water->setLightDirection(sun->getDirectionalLight());
		water->Render(planeShader);
		//Done Drawing to frame
		//Blur it 
		frame->unBind();
		
		GLuint bloomTex;
		bloomTex = PostProcessing::Bloom(frame, blurShader, 16);

		/*
		GLboolean firstIteration = true;
		GLboolean horizontal = true;
		blurShader->Use();
		for (GLuint i = 0; i < 32; i++) {
			if (horizontal) {
				blurFrame1->Bind();
				blurShader->SetInteger("horizontal", horizontal);
				if (firstIteration) {
					frame->Render(blurShader, 1);
					firstIteration = false;
					horizontal = !horizontal;
					blurFrame1->unBind();
				}
				else
				{
					blurFrame2->Render(blurShader);
					horizontal = !horizontal;
					blurFrame1->unBind();
				}
			}
			else
			{
				blurFrame2->Bind();
				blurShader->SetInteger("horizontal", horizontal);
				blurFrame1->Render(blurShader);
				horizontal = !horizontal;
				blurFrame2->unBind();
			}
		}
		//Render our frame
		blurFrame1->unBind();
		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDisable(GL_DEPTH_TEST);
		hdrShader->SetFloat("exposure", screenExp,true);
		hdrShader->SetFloat("gamma", gamma);
		hdrShader->SetFloat3("lightDir", sun->getDirectionalLight());
		hdrShader->SetInteger("screenTexture", 0);
		hdrShader->SetInteger("bloomTexture", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, bloomTex);
		

		
		frame->Render(hdrShader);
		
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glDisable(GL_DEPTH_TEST);
		//frame->Render(hdrShader);



		//glEnable(GL_CULL_FACE);
		//done with writing to the framebuffer
		
		//Draw TweakBar
		TwDraw();

		SDL_GL_SwapWindow(window.getWindow());
		/// End of Render
		
	}
	

	//delete dispatcher;
	//delete broadphase;
	//delete solver;
	//delete collisionConfig;

	TwTerminate();
	return 0;
}

