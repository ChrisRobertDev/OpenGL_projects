#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Model.h"
#include "Object.h"
class Sun: public Object
{
public:
	Sun(const std::string filePath);
	~Sun();

	void Render(Shader* shader);
	//Setters
	void setView(glm::mat4 view);
	void setAngle(GLfloat angle);
	void setColor(glm::vec3 color);

	//Getters
	glm::vec3 getDirectionalLight();
	GLfloat getAngle();

	void rotateSun();
private:
	glm::vec3 sunColor_;
	GLfloat angle_;



};

