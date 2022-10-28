#pragma once
#include <Box2D\Box2D.h>
#include <glm\common.hpp>
#include <gl\glew.h>

class Box
{
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
public:
	Box();
	~Box();

	void init(b2World* world,const glm::vec2& position, const glm::vec2& dimension, b2BodyType type = b2_dynamicBody);

	b2Body* getBody() { return body; }
	b2Fixture* getFixture() { return fixture; }

	void destroy();

};

