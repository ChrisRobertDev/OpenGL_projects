#pragma once

#include "Shader.h"

//#include <glm\gtc\matrix_transform.hpp>
class Camera2D
{

private:
	glm::vec2 CameraPos;
	GLfloat CameraScaling;
	glm::mat4 CameraMatrix;
	glm::mat4 OrthoProjection;
	GLfloat _width, _height;
	bool ifNeedsUpdate;

public:
	Camera2D();
	Camera2D(glm::vec2 CameraPosition, GLfloat Scale, GLfloat Width, GLfloat Height);

	void update();

	// Getters
	glm::mat4 getCameraMatrix();
	glm::mat4 getOrthoMatrix();
	glm::vec2 getCameraPos();
	glm::vec2 getNormalCameraPos();
	GLfloat getScale();
	//Setters
	void setCameraPos(glm::vec2 Pos);
	void setScale(GLfloat scale);
	void setPlayerCamPos(glm::vec2 Pos);
};

