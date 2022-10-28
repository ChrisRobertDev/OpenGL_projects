#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>


#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};
struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	std::vector<Vertex> vertices_;
	std::vector<Texture> textures_;
	std::vector<GLuint> indices_;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<GLuint> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh();
	void Render(Shader* shader);

	
private:
	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;

	void setupMesh();
};

