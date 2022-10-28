#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
class Texture2D
{
private:
	GLuint ID;
	GLuint Width, Height;
	glm::ivec2 dims;
	GLfloat isMirrored;
	GLuint index;

	GLuint Internal_Format;
	GLuint Image_Format;
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;
public:
	

	Texture2D();
	Texture2D(const GLchar *fileName, glm::ivec2 dims = glm::ivec2(1,1));

	//void Generate(const GLchar *fileName,GLboolean alpha);

	void Bind() const;

	//Getters
	glm::vec4 getUVs();
	GLfloat getMirrorFlag();
	//Setters
	void setIndex(GLuint index);
	void setMirrorFlag(GLfloat flag);
};

