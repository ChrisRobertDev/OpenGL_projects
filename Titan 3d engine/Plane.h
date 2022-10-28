#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Noise.h"

class Plane
{
public:
	Plane(GLuint amount,GLfloat offset, std::string filePath, bool hasNoise = false);

	void Render(Shader* shader);
	~Plane();


	//Setters
	void setProjection(glm::mat4 projection);
	void setView(glm::mat4 view);
	void setPosition(glm::vec3 position);
	void setLightDirection(glm::vec3 direction);


private:
	GLuint amount_;
	GLfloat offset_;
	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;

	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;

	glm::mat4 projection_;
	glm::mat4 view_;
	glm::vec3 position_;
	glm::vec3 scale_;

	glm::vec3 lightPosition_;
	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	GLfloat shininess_;

	Texture2D diffuseTex_;
	
};

