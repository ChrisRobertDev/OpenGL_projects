#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

class Camera
{
public:
	void Update();
	void UpdateQuat();
	//compute or calculate
	void computeYawVelocity(GLfloat yawInputKey);
	void computePitchVelocity(GLfloat pitchInputKey);
	//setters
	void setVelocityX(GLfloat velocityX);
	void setVelocityZ(GLfloat velocityZ);
	void setYawVelocity(GLfloat yawVelocity);
	void setPitchVelocity(GLfloat pitchVelocity);
	void setSensitivity(GLfloat sensibility);
	void setMovementSpeed(GLfloat movementSpeed);
	//getters
	glm::mat4 getViewMatrix();
	glm::mat4 getViewMatrixQuat();
	glm::vec3 getPosition();

	Camera();
	~Camera();
	
protected:
	GLfloat velocityX_;
	GLfloat velocityZ_;
	GLfloat yaw_;
	GLfloat pitch_;
	GLfloat yawVelocity_;
	GLfloat pitchVelocity_;
	GLfloat movementSpeed_;
	GLfloat cameraSensitivity_;

private:
	glm::vec3 position_;
	glm::vec3 direction_;
	glm::vec3 up_;
	glm::vec3 strafe_;
};

