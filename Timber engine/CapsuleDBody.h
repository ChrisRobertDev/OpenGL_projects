#pragma once
#include "ECS/ECS.h"
#include "JumpingListener.h"
class CapsuleDBody : public Component
{
private:
	b2Body * body = nullptr;
	b2Fixture* fixture[10];
	JumpingListener* listener;
	

public:
	CapsuleDBody(const glm::vec2& position, const glm::vec2& dimension);
	~CapsuleDBody();

	void update(GLfloat deltatime) override;


	b2Body* getBody() { return body; }

	void destroy();

	int getNumFootContacts() { return listener->numFootContacts; }
};

