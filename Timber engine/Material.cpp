#include "stdafx.h"
#include "Material.h"



Material::Material(Texture2D texture, GLuint layer, glm::vec3 color) :
	texture(texture),
	layer(layer),
	color(color)
{
	
}

Material::~Material()
{
}
