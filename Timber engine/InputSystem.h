#pragma once
#include <SDL/SDL.h>
#include <iostream>
#include <map>
#include <string>
#include <GL/glew.h>
#include "ECS/ECS.h"

class InputSystem : public System
{
private:
	//std::map<Command*, std::string> commands;
	//ForwardCommand * fC;

	std::map<std::string, GLfloat> keyMap;
	//const uint8_t * keyState;

	bool quit;
	void resetKeys();
public:
	InputSystem();
	~InputSystem();

	void update(GLfloat deltatime) override;
	void preUpdate(GLfloat deltatime) override;
	void render() override {}
	void handleInput();
	bool hasQuit();

};

