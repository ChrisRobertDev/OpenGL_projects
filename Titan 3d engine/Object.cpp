#include "Object.h"

#include <glm\gtc\matrix_transform.hpp>

Object::Object(const std::string name, const std::string filePath) :
	ambient_(glm::vec3(0.2f)),
	diffuse_(glm::vec3(0.5f)),
	specular_(glm::vec3(1.0f)),
	shininess_(128.0f)
{
	model_ = new Model(filePath);
	name_ = name;

}


Object::~Object()
{
	delete model_;
}


void Object::Render(Shader* shader) {

	glm::mat4 model;
	model = glm::translate(model, position_);
	model = model * rotation_;
	model = glm::scale(model, scale_);

	shader->Use();
	shader->SetMatrix4("projection", projection_);
	shader->SetMatrix4("view", view_);
	shader->SetMatrix4("model", model);
	shader->SetMatrix3("TImodel", glm::mat3(glm::transpose(glm::inverse(model))));

	model_->Render(shader);
}
//Setters
void Object::setPosition(glm::vec3 position) {
	position_ = position;
}
void Object::setScale(glm::vec3 scale) {
	scale_ = scale;
}

void Object::setProjection(glm::mat4 projection) {
	projection_ = projection;
}
void Object::setView(glm::mat4 view) {
	view_ = view;
}
void Object::Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll) {

}
//Getters
glm::vec3 Object::getPosition() {
	return position_;
}
Model* Object::getModel() {
	return model_;
}