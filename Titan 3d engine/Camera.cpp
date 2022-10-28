#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\glm.hpp>
#include "Camera.h"

Camera::Camera() :
	position_(glm::vec3(0.0f, 0.0f, 3.0f)),
	direction_(glm::vec3(0.0f, 0.0f, -1.0f)),
	up_(glm::vec3(0.0f, 1.0f, 0.0f)),
	yaw_(0.0f),
	pitch_(0.0f),
	yawVelocity_(0),
	pitchVelocity_(0),
	cameraSensitivity_(0.25f),
	movementSpeed_(0.25f),
	velocityX_(0.0f),
	velocityZ_(0.0f)
{

}



void Camera::Update()
{
	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;
	if (yaw_ < 0.0f)
		yaw_ = 360.0f;
	if (yaw_ > 360.0f)
		yaw_ = 0.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	direction_ = glm::normalize(front);

	position_ += direction_ * movementSpeed_ * velocityZ_;
	position_ += glm::cross(direction_, up_) * movementSpeed_ * velocityX_;

	// DEBUG
	//std::cout << direction_.x << " " << direction_.y << " " << direction_.z << std::endl;
	//std::cout << position_.x << " " << position_.y << " " << position_.z << std::endl;
	//std::cout << yaw_ << " " << pitch_ << std::endl;
}

void Camera::UpdateQuat() {
	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;
	if (yaw_ < 0.0f)
		yaw_ = 360.0f;
	if (yaw_ > 360.0f)
		yaw_ = 0.0f;
	
	
	position_ += strafe_  * velocityX_* movementSpeed_;
	position_ += direction_  * (-velocityZ_)* movementSpeed_;
}

void Camera::computeYawVelocity(GLfloat yawInputKey)
{
	for (GLuint i = 0; i <= yawVelocity_; i++)
		yaw_ += cameraSensitivity_ * yawInputKey;
}

void Camera::computePitchVelocity(GLfloat pitchInputKey)
{
	for (GLuint i = 0; i <= pitchVelocity_; i++)
		pitch_ += cameraSensitivity_ * pitchInputKey;
}

void Camera::setVelocityX(GLfloat velocityX)
{
	velocityX_ = velocityX;
}

void Camera::setVelocityZ(GLfloat velocityZ)
{
	velocityZ_ = velocityZ;
}

void Camera::setYawVelocity(GLfloat yawVelocity)
{
	yawVelocity_ = yawVelocity;
}

void Camera::setPitchVelocity(GLfloat pitchVelocity)
{
	pitchVelocity_ = pitchVelocity;
}

void Camera::setSensitivity(GLfloat sensitivity)
{
	if (sensitivity != cameraSensitivity_) {
		cameraSensitivity_ = sensitivity;
	}
}

void Camera::setMovementSpeed(GLfloat movementSpeed)
{
	if (movementSpeed != movementSpeed_) {
		movementSpeed_ = movementSpeed;
	}
}
glm::vec3 Camera::getPosition()
{
	return position_;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position_, position_ + direction_, up_);
}

glm::mat4 Camera::getViewMatrixQuat() {
	glm::quat qPitch = glm::angleAxis(glm::radians(-pitch_), glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(glm::radians(yaw_), glm::vec3(0, 1, 0));
	//glm::quat qRoll = glm::angleAxis(roll, glm::vec3(0, 0, 1));

	glm::quat orientation = glm::normalize(qPitch*qYaw);
	glm::mat4 rotate;
	rotate = glm::mat4_cast(orientation);
	direction_.x = rotate[0][2];
	direction_.y = rotate[1][2];
	direction_.z = rotate[2][2];

	strafe_.x = rotate[0][0];
	strafe_.y = rotate[1][0];
	strafe_.z = rotate[2][0];

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -position_);
	return rotate * translate;
}

