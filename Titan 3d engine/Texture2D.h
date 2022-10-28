#pragma once

#include <GL\glew.h>
#include <string>

#include "Shader.h"

enum TextureType{
	DIFFUSE = 0,
	SPECULAR = 1,
	BUMP = 2,
	NORMAL = 3,
};

class Texture2D
{
public:
	Texture2D();
	Texture2D(const GLchar* path,const TextureType type = DIFFUSE);
	~Texture2D();

	
	//Setter
	void setID(GLuint id);
	void setPath(GLchar* path);
	void setType(TextureType type);
	//Getters
	GLuint getID();
	std::string getPath();
	TextureType getType();

private:
	GLint width_, height_;
	GLuint id_;
	std::string path_;
	TextureType type_;
};

