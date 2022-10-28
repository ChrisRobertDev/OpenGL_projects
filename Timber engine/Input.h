#pragma once
#include "ECS/ECS.h"
#include "Transform.h"
#include "DynamicBody.h"
 
class Input:public Component
{
protected:
	GLint timer;
public:
	bool upPressed, downPressed, leftPressed, rightPressed,Jump;
	GLfloat iVelocity;
	Input();
	~Input();

	void update(GLfloat deltatime) override;
	//void render() override;


};

