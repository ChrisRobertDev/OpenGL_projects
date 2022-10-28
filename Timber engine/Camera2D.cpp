#include "stdafx.h"
#include "Camera2D.h"


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
	
	this->OrthoProjection = glm::ortho<GLfloat>(0.0f, _width / 100.0f, 0.0f, _height / 100.0f, -1.0f, 1.0f);
	this->CameraMatrix = glm::translate(this->OrthoProjection, glm::vec3(-CameraPos, 0.0f));
	this->CameraMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(Scale, Scale, 1.0f))*this->CameraMatrix;
}

void Camera2D::update() {
	
	if (this->ifNeedsUpdate) {
		this->CameraMatrix = glm::translate(this->OrthoProjection, glm::vec3(-CameraPos,1.0f));
		this->CameraMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->CameraScaling, this->CameraScaling, 1.0f)) * this->CameraMatrix;
		this->ifNeedsUpdate = false;
	}
	
}

glm::mat4 Camera2D::getCameraMatrix() {
	return this->CameraMatrix;
}

glm::mat4 Camera2D::getOrthoMatrix() {
	return this->OrthoProjection;
}

glm::vec2 Camera2D::getCameraPos() {
	return this->CameraPos;
}
glm::vec2 Camera2D::getNormalCameraPos() {
	return glm::vec2(this->CameraPos.x + this->_width / 2, this->CameraPos.y + this->_height / 2);
}
GLfloat Camera2D::getScale() {
	return this->CameraScaling;
}

void Camera2D::setCameraPos(glm::vec2 Pos) {
	this->CameraPos = Pos;
	this->ifNeedsUpdate = true;
}
void Camera2D::setScale(GLfloat scale) {
	this->CameraScaling = scale;
	this->ifNeedsUpdate = true;
}
void Camera2D::setPlayerCamPos(glm::vec2 Pos) {
	this->CameraPos.x = Pos.x - this->_width / 200.0f;
	this->CameraPos.y = Pos.y - this->_height / 200.0f;
	this->ifNeedsUpdate = true;
}