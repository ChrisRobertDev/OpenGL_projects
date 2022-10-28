#include "Camera2D.h"

#include <iostream>

Camera2D::Camera2D()
{
}


Camera2D::Camera2D(glm::vec2 CameraPosition,GLfloat Scale,GLfloat Width,GLfloat Height):
	ifNeedsUpdate(false),
	_width(Width),
	_height(Height),
	CameraScaling(Scale)
{
	this->CameraPos = glm::vec2(CameraPosition.x - this->_width / 2.0f, CameraPosition.y - this->_height / 2.0f);
	
	this->OrthoProjection  = glm::ortho(0.0f, _width,  _height, 0.0f, -1.0f, 1.0f);
	this->CameraMatrix = glm::translate(this->OrthoProjection, glm::vec3(-CameraPos, 0.0f));
	this->CameraMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(Scale, Scale, 1.0f))*this->CameraMatrix;
}

void Camera2D::Update() {
	
	if (this->ifNeedsUpdate) {
		this->CameraMatrix = glm::translate(this->OrthoProjection, glm::vec3(-CameraPos,1.0f));
		this->CameraMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->CameraScaling, this->CameraScaling, 1.0f)) * this->CameraMatrix;
		this->ifNeedsUpdate = false;
	}
	
}

glm::mat4 Camera2D::Get_cameraMatrix() {
	return this->CameraMatrix;
}

glm::mat4 Camera2D::Get_OrthoMatrix() {
	return this->OrthoProjection;
}

glm::vec2 Camera2D::Get_CameraPos() {
	return this->CameraPos;
}
glm::vec2 Camera2D::Get_NCameraPos() {
	return glm::vec2(this->CameraPos.x + this->_width / 2, this->CameraPos.y + this->_height / 2);
}
GLfloat Camera2D::Get_Scale() {
	return this->CameraScaling;
}

void Camera2D::Set_CameraPos(glm::vec2 Pos) {
	this->CameraPos = Pos;
	this->ifNeedsUpdate = true;
}
void Camera2D::Set_Scale(GLfloat scale) {
	this->CameraScaling = scale;
	this->ifNeedsUpdate = true;
}
void Camera2D::Set_PlayerCamPos(glm::vec2 Pos) {
	this->CameraPos.x = Pos.x - this->_width / 2.0f;
	this->CameraPos.y = Pos.y - this->_height / 2.0f;
	this->ifNeedsUpdate = true;
}