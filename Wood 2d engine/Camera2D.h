#pragma once

#include "Shader.h"

#include <glm\gtc\matrix_transform.hpp>
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

	void Update();

	// Getters
	glm::mat4 Get_cameraMatrix();
	glm::mat4 Get_OrthoMatrix();
	glm::vec2 Get_CameraPos();
	glm::vec2 Get_NCameraPos();
	GLfloat Get_Scale();
	//Setters
	void Set_CameraPos(glm::vec2 Pos);
	void Set_Scale(GLfloat scale);
	void Set_PlayerCamPos(glm::vec2 Pos);
};

