#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Mesh.h"


class Model3D
{
public:
	Model3D(const GLchar* objPath,const GLchar* mtlPath = nullptr);
	~Model3D();

private:
	std::vector<Mesh> Meshes_;
	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;
};

