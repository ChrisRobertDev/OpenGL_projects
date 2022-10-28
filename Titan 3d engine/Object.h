#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Model.h"

class Object
{
public:
	Object(const std::string name,const std::string filePath);
	~Object();

	virtual void Render(Shader* shader);
	//Setters
	void setPosition(glm::vec3 position);
	void setScale(glm::vec3 scale);
	void setProjection(glm::mat4 projection);
	virtual void setView(glm::mat4 view);
	void Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll);
	//Getters
	glm::vec3 getPosition();
	
protected:
	glm::mat4 projection_;
	glm::mat4 view_;

	glm::vec3 position_;
	glm::mat4 rotation_;
	glm::vec3 scale_;

	
	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	GLfloat shininess_;

	std::string name_;

	Model* getModel();
private:
	Model* model_;
};

