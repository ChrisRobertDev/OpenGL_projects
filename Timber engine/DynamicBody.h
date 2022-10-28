#pragma once
#include "ECS/ECS.h"
class DynamicBody : public Component
{
private:
	b2Body * body = nullptr;
	b2Fixture* fixture = nullptr;
public:
	DynamicBody(const glm::vec2& position, const glm::vec2& dimension);
	~DynamicBody();

	void update(GLfloat deltatime) override;


	b2Body* getBody() { return body; }
	b2Fixture* getFixture() { return fixture; }

	void destroy();
};

