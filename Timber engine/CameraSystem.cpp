#include "stdafx.h"
#include "CameraSystem.h"
#include "Transform.h"
#include "ECS/EventHandler.h"

CameraSystem::CameraSystem(Entity& pawn, glm::vec2 cameraPosition, GLfloat scale, GLfloat width, GLfloat height)
	
{
	camera = new Camera2D(cameraPosition, scale, width, height);
	follower = &pawn;
}

CameraSystem::~CameraSystem()
{
	delete camera;
}

void CameraSystem::preUpdate(GLfloat deltatime)
{
	if (follower->isActive() && follower->hasComponent<Transform>()) {
		glm::vec2 v = follower->getComponent<Transform>().getPosition();
		v.y = 0.0f;
		camera->setPlayerCamPos(v);
	}
}

void CameraSystem::update(GLfloat deltatime)
{
	camera->update();
}

void CameraSystem::setFollower(Entity& e)
{
	follower = &e;
}

glm::mat4 CameraSystem::getProjectionMatrix()
{
	return camera->getCameraMatrix();
}
