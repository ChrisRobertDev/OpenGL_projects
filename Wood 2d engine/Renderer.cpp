#include "Renderer.h"

#include<glm\gtc\matrix_transform.hpp>

Renderer::Renderer(Shader &shader) :
	_shader(shader)
{
	this->InitializeData();
}

void Renderer::Draw(Texture2D texture, glm::vec2 position, glm::vec2 scale, GLfloat angle) {
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position,0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));
	this->_shader.Use();
	this->_shader.SetMatrix4("model", model);
	this->_shader.SetVector4f("texUvoffset", texture.getUVs());
	this->_shader.SetFloat("isMirrored", texture.getMirrorFlag());
	
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->_Vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}

void Renderer::InitializeData()
{
	GLfloat Vdata[] = {
		-0.5f,-0.5, 0.0f,0.0f,
		0.5f,-0.5,	1.0f,0.0f,
		0.5f,0.5,	1.0f,1.0f,

		-0.5f,-0.5,	0.0f,0.0f,
		-0.5f,0.5,	0.0f,1.0f,
		0.5f,0.5,	1.0f,1.0f
	};
	GLuint vbo;

	glGenVertexArrays(1, &this->_Vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vdata), Vdata, GL_STATIC_DRAW);
	

	glBindVertexArray(this->_Vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);

	glBindBuffer(1, 0);
	glBindVertexArray(0);
}