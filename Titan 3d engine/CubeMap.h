#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Texture2D.h"

class CubeMap
{
public:
	CubeMap(std::string filePath = nullptr);
	~CubeMap();

	void Render(Shader* shader);

	//Setters
	void setProjection(glm::mat4 projection);
	void setView(glm::mat4 view);

protected:
	glm::mat4 projection_;
	glm::mat4 view_;

private:
	GLuint texture_;

	GLuint vao_;
	GLuint vbo_;
};

