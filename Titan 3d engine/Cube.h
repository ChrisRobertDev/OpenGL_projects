#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <SOIL\SOIL.h>

#include "Shader.h"
class Cube
{
public:
	Cube(const GLchar* diffusePath = nullptr, const GLchar* specularPath = nullptr);
	~Cube();
	void Render(Shader* shader);
	//setters
	void setProjection(glm::mat4 projection);
	void setView(glm::mat4 view);

	void setPosition(glm::vec3 position = glm::vec3(0.0f));
	void setRotation(GLfloat yaw = 0.0f, GLfloat pitch = 0.0f, GLfloat roll = 0.0f);
	void setScale(glm::vec3 scale = glm::vec3(1.0f));
	void setViewPosition(const glm::vec3 position = glm::vec3(0.0f));
	void setLightPosition(const glm::vec3 position = glm::vec3(0.0f));
	void setCubeColor(const glm::vec3 color = glm::vec3(1.0f));
	void setLightColor(const glm::vec3 color = glm::vec3(1.0f));

	//Getters
	glm::vec3 getPosition();


	glm::vec3 RotateV3(GLfloat theta, glm::vec3 Axis);
	glm::mat4 Rotate(GLfloat theta, glm::vec3 Axis);
protected:
	glm::mat4 projection_;
	glm::mat4 view_;
	glm::mat4 rotation_;
	glm::vec3 position_;
	glm::vec3 scale_;
	glm::vec3 viewPosition_;

	//textures;
	GLuint textureDiffuse_;
	GLuint textureSpecular_;
	
	// Lighting variables
	glm::vec3 lightPosition_;
	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	GLfloat shininess_;

	glm::vec3 lightAmbient_;
	glm::vec3 lightDiffuse_;
	glm::vec3 lightSpecular_;

	glm::vec3 cubeColor_;
	glm::vec3 lightColor_;

	void loadTexture(const GLchar* diffusePath = nullptr, const GLchar* specularPath = nullptr);
private:
	GLuint vao_;
};

