#pragma once
#include "ECS/ECS.h"

class PlayerAnimation:public Component
{
private:
	GLfloat deltaCount;
	GLuint frameCount;
	GLuint action;

	GLfloat isMirrored;
	GLfloat inAirMirrored;
public:
	PlayerAnimation();
	~PlayerAnimation();

	void update(GLfloat deltatime) override;
};

