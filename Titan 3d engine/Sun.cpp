#include "Sun.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
Sun::Sun(const std::string filePath):
	Object("sun",filePath)
{
	angle_ = 0.0f;
	scale_ = glm::vec3(0.05f);
	sunColor_ = glm::vec3(1.0f, 1.0f, 220.0f / 255.0f);
	position_ = glm::vec3(1.0f, 0.0f, 0.0f);
	
}


Sun::~Sun()
{
}

void Sun::Render(Shader* shader)
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	//model = model * rotation_;
	model = glm::scale(model, scale_);
	shader->Use();
	
	shader->SetMatrix4("projection", projection_);
	shader->SetMatrix4("view", view_);
	shader->SetMatrix4("model", model);
	//shader->SetMatrix3("TImodel", glm::mat3(glm::transpose(glm::inverse(model))));

	shader->SetFloat3("sunColor", sunColor_);

	glDepthMask(GL_FALSE);
	getModel()->Render(shader);
	glDepthMask(GL_TRUE);
}

void Sun::setView(glm::mat4 view) {
	view_ = glm::mat4(glm::mat3(view));
	//view_ = view;
}

void Sun::setAngle(GLfloat angle) {
	if (angle == 360.0f)
		angle == 0.0f;
	angle_ = angle;
}

void Sun::setColor(glm::vec3 color) {
	sunColor_ = color;
}

void Sun::rotateSun() {
	
	position_.x = glm::cos(glm::radians(angle_));
	position_.y = glm::sin(glm::radians(angle_));
	position_.z = 0.0f;
	
}

glm::vec3 Sun::getDirectionalLight() {
	return position_;
}

GLfloat Sun::getAngle() {
	return angle_;
}