#pragma once

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Shader.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(GLenum colorType,int width , int height);
	~FrameBuffer();

	void generateRenderBuffer();
	void Render(Shader* shader, GLuint index = 0);
	void Bind();
	void unBind();
	void addAttachment();
	//Setters
	void setGLAttachments();
	void setTextureID(GLuint texture, GLuint index = 0);
	//Getters
	GLuint getTextureID(GLuint index = 0);

private:
	int width_;
	int height_;
	GLenum colorType_;
	GLuint fbo_;
	GLuint rbo_;
	GLuint texture_[8];
	GLuint vao_;
	GLuint vbo_;
	GLuint iterator_;
	std::vector<GLuint> attachments_;

	void initQuad();
};

