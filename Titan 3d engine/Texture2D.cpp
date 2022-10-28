#include "Texture2D.h"

#include <SOIL\SOIL.h>

Texture2D::Texture2D() {
	type_ = DIFFUSE;
	id_ = 0;
}


Texture2D::Texture2D(const GLchar* path, const TextureType type)
{
	type_ = type;
	path_ = path;
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	width_ = width;
	height_ = height;
}


Texture2D::~Texture2D()
{
	
}

void Texture2D::setPath(GLchar* path)
{
	path_ = path;
}
void Texture2D::setID(GLuint id) {
	id_ = id;
}
void Texture2D::setType(TextureType type) {
	type_ = type;
}

GLuint Texture2D::getID() {
	return id_;
}
std::string Texture2D::getPath() {
	return path_;
}
TextureType Texture2D::getType() {
	return type_;
}