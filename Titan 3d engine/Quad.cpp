#include "Quad.h"

#include <glm\gtc\matrix_transform.hpp>

Quad::Quad(const GLchar* filePath):
	rotation_(glm::mat4(1.0f)),
	position_(0.0f),
	scale_(1.0f)
{
	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,  0.0f,0.0f,-1.0f,  0.0f,0.0f,
		 0.5f,-0.5f,0.0f,  0.0f,0.0f,-1.0f,  1.0f,0.0f, 

		 0.5f, 0.5f,0.0f,  0.0f,0.0f, 1.0f,  1.0f,1.0f,
		-0.5f, 0.5f,0.0f,  0.0f,0.0f, 1.0f,  0.0f,1.0f
	};
	GLuint indices[] = {
		0,1,2,
		2,3,0
	};

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 32.0f, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	glBindVertexArray(0);

	
	texture_ = new Texture2D(filePath);;
	
	
}


Quad::~Quad()
{
}

void Quad::Render(Shader* shader) {
	shader->Use();

	glm::mat4 model(1.0f);
	model = glm::translate(model, position_);
	//model = model * rotation_;
	model = glm::scale(model, scale_);

	shader->SetMatrix4("projection", projection_);
	shader->SetMatrix4("view", view_);
	shader->SetMatrix4("model", model);

	glActiveTexture(GL_TEXTURE0);
	shader->SetInteger("quadTex",0);
	glBindTexture(GL_TEXTURE_2D, texture_->getID());
	//draw the figure
	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}
//Setters
void Quad::setPosition(glm::vec3 position) {
	position_ = position;
}
void Quad::setProjection(glm::mat4 projection) {
	projection_ = projection;
}
void Quad::setView(glm::mat4 view) {
	view_ = view;
}
void Quad::Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll) {
	glm::quat qPitch = glm::angleAxis(glm::radians(-pitch), glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(glm::radians(roll), glm::vec3(0, 0, 1));

	rotation_ = glm::mat4_cast(glm::normalize(qPitch *qYaw * qRoll));
}
//Getters
glm::vec3 Quad::getPosition() {
	return position_;
}