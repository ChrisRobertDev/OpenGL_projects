#include "Texture2D.h"
#include <SOIL\SOIL.h>
#include <iostream>

Texture2D::Texture2D() :
	Width(0),
	Height(0),
	isMirrored(0.0f),
	index(0),
	Internal_Format(GL_RGB), 
	Image_Format(GL_RGB), 
	Wrap_S(GL_REPEAT), 
	Wrap_T(GL_REPEAT), 
	Filter_Min(GL_LINEAR), 
	Filter_Max(GL_LINEAR)
{
	
}
Texture2D::Texture2D(const GLchar *fileName, glm::ivec2 dims):
	dims(dims),
	isMirrored(0.0f),
	index(0)
{
	unsigned char * _image;
	int width, height;
	/*Create the image then use it to create the texture*/
	_image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
	
	if(_image == nullptr)
		std::cout << "Soil image failed to load ( Relative path might be wrong!) !!" << std::endl;
	this->Width = width;
	this->Height = height;
	//Generate the texture
	glGenTextures(1, &this->ID);
	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, ID);

	//Create the texture + MipMapping
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->Width, this->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(_image);
}
/*
void Texture2D::Generate(const GLchar *fileName,GLboolean alpha)
{
	unsigned char * _image;
	int width, height;
	//Create the image then use it to create the texture
	_image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

	this->Width = width;
	this->Height = height;
	//Generate the texture
	glGenTextures(1, &this->ID);
	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, ID);

	//Create the texture + MipMapping
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->Width, this->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(_image);
}
*/

void Texture2D::Bind()	const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

glm::vec4 Texture2D::getUVs() {
	int xTile = index % dims.x;		 // xTile = 0
	int yTile = index / dims.x;		 // yTile = 0
	
	glm::vec4 uvs;
	uvs.x = xTile / (GLfloat)dims.x; //	uv.x = 0 / 7 = 0
	uvs.y = yTile / (GLfloat)dims.y; // uv.y = 0 / 3 = 0
	uvs.z = 1.0f / (GLfloat)dims.x;	 // uv.z = 1 / 7 = 0.1428 ~ 72 pixels
	uvs.w = 1.0f / (GLfloat)dims.y;	 // uv.w = 1 / 3 = 0.33 ~ 96 pixels

	//index = 1
	//xTile = 1
	//yTile = 0
	//uv.x = 1 / 7 = 0.1428 ~ 71 pixels
	//uv.y = 0 / 3 = 0
	//uv.z = 1 / 7 = 0.1428 ~ 71 pixels
	//uv.w = 1 / 3 = 0.33 ~ 96 pixels

	///V Tex data
	//0.0f, 0.0f,		TexCoord.x+uv.x , TexCoord.y+uv.y
	//1.0f, 0.0f,		uv.x + uv.z		, TexCoord.y+uv.y
	//1.0f, 1.0f,		uv.x + uv.z		, uv.y + uv.w
	
	//0.0f, 0.0f,		TexCoord.x+uv.x , TexCoord.y+uv.y
	//0.0f, 1.0f,		TexCoord.x+uv.x , uv.y + uv.w
	//1.0f, 1.0f		uv.x + uv.z		, uv.y + uv.w

	return uvs;
}

GLfloat Texture2D::getMirrorFlag() {
	return isMirrored;
}

void Texture2D::setIndex(GLuint index) {
	this->index = index;
}
void Texture2D::setMirrorFlag(GLfloat flag) {
	isMirrored = flag;
}