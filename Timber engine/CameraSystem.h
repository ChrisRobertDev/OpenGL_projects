#pragma once
#include "ECS/ECS.h"
#include "Camera2D.h"

class CameraSystem : public System
{
private:
	Camera2D* camera;
	Entity* follower;

public:
	CameraSystem(Entity& pawn,glm::vec2 CameraPosition = glm::vec2(0.0f) , GLfloat Scale = 1.0f, GLfloat Width = 800.0f, GLfloat Height = 600.0f);
	~CameraSystem();

	void preUpdate(GLfloat deltatime) override;
	void update(GLfloat deltatime) override;

	void setFollower(Entity& e);

	glm::mat4 getProjectionMatrix();
};

