#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Texture2D.h"

class Quad
{
public:
	Quad(const GLchar* filePath = nullptr);
	~Quad();

	void Render(Shader* shader);
	//Setters
	void setPosition(glm::vec3 position);
	void setProjection(glm::mat4 projection);
	void setView(glm::mat4 view);
	void Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll);
	//Getters
	glm::vec3 getPosition();

protected:
	glm::mat4 projection_;
	glm::mat4 view_;
	

	glm::vec3 position_;
	glm::mat4 rotation_;
	glm::vec3 scale_;

	Texture2D* texture_;
	
private:
	GLuint vbo_;
	GLuint vao_;
	GLuint ebo_;
};

