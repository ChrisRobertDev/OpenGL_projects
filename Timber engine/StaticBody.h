#pragma once
#include "ECS/ECS.h"

class StaticBody : public Component
{
private:
	b2Body * body = nullptr;
	b2Fixture* fixture[10];
	GLuint fixtureCount;
public:
	StaticBody(const glm::vec2& position, const glm::vec2& dimension);
	StaticBody(const glm::vec2& position, const std::vector<b2Vec2>& lines);
	~StaticBody();

	void update(GLfloat deltatime) override;

	b2Body* getBody() { return body; }
	b2Fixture* getFixture(GLuint index = 0) { return fixture[index]; }

	void destroy();
};

