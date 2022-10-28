#include "stdafx.h"
#include "Transform.h"

Transform::Transform(glm::vec2 position, glm::vec2 scale, GLfloat rotation) :
	position(position),
	scale(scale),
	rotation(rotation)
{

}

//void Transform::update(GLfloat deltatime)
//{
//	//std::cout << "Updating Transform component" << std::endl;
//	//x++;
//	//y++;
//
//}
//
//void Transform::render()
//{
//}

Transform::~Transform()
{
}

glm::mat4 Transform::getModelMatrix()
{
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));

	return model;
}

