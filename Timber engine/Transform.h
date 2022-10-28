#pragma once
#include "ECS/ECS.h"
//#include <glm/glm.hpp>
//#include<glm\gtc\matrix_transform.hpp>


class Transform : public Component
{
private:
	glm::vec2 position;
	GLfloat rotation;
	glm::vec2 scale;
public:
	Transform(glm::vec2 position = glm::vec2(0.0f),glm::vec2 scale = glm::vec2(0.0f), GLfloat rotation = 0.0f);

	//void update(GLfloat deltatime) override;
	//void render() override;
	~Transform();

	glm::vec2 getPosition() { return position; }
	glm::vec2 getScale() { return scale; }
	GLfloat getRotation() { return rotation; }
	//GLfloat getY() { return y; }


	void setPosition(glm::vec2 pos) { this->position = pos; }
	void setScale(glm::vec2 scale) { this->scale = scale; }
	void setRotation(GLfloat rotation) { this->rotation = rotation; }
	glm::mat4 getModelMatrix();
};

