#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <GL\glew.h>

#include "Texture2D.h"

class Material
{
public:
	Material();
	~Material();
	//Communicate with the given shader
	void Bind(Shader* shader);

	//Adders
	void addTexture(const GLchar* path,TextureType type);
	//Setters
	void setMaterialAmbient(glm::vec3 ambient);
	void setMaterialDiffuse(glm::vec3 diffuse);
	void setMaterialSpecular(glm::vec3 specular);
	void setMaterialShininess(GLfloat shininess);
	void setMaterialDissolve(GLfloat dissolve);
	void setMaterialIllumination(GLuint illumination);
	void setMaterialName(const GLchar* name);
	//Getters
	glm::vec3 getMaterialAmbient();
	glm::vec3 getMaterialDiffuse();
	glm::vec3 getMaterialSpecular();
	GLfloat getMaterialShininess();
	GLfloat getMaterialDissolve();
	GLuint getMaterialIllumination();
	std::string getMaterialName();

private:
	std::vector<Texture2D> textures_;
	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	GLfloat shininess_;
	
	GLfloat dissolve_;
	GLuint illumination_;
	std::string name_;

};

