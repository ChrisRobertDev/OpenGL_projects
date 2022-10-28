#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>


#include"Material.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};



class Mesh
{
public:
	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;
	Material material_;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,Material material);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh();

	void Render(Shader* shader);

	
private:
	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;
	std::string name_;
	std::string directory_;

	void setupMesh();
};

