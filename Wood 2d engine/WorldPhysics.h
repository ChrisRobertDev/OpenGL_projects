#pragma once

#include <Box2D\Box2D.h>
#include <glm\common.hpp>
#include <gl\glew.h>
#include <vector>

#include "Box.h"

class WorldPhysics
{
private:
	b2World* world;
	
public:
	WorldPhysics(glm::vec2 gravity);
	~WorldPhysics();

	void initGround();	

	void step(GLfloat deltatime);

	b2World* getWorld() { return this->world; }

	//std::vector<Box> boxes;
	Box box1;
	Box box2;
	Box box3;
};

