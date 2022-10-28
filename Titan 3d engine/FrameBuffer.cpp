#include "FrameBuffer.h"

#include <iostream>

FrameBuffer::FrameBuffer() {

}
FrameBuffer::FrameBuffer(GLenum colorType, int width, int height):
	rbo_(0)
{
	this->initQuad();

	iterator_ = 0;
	width_ = width;
	height_ = height;
	colorType_ = colorType;
	glGenFramebuffers(1, &fbo_);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	//generate color attachment

	glGenTextures(1, &texture_[0]);
	glBindTexture(GL_TEXTURE_2D, texture_[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_[0], 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	attachments_.push_back(GL_COLOR_ATTACHMENT0);
}


FrameBuffer::~FrameBuffer()
{
	//glDeleteFramebuffers(1, &fbo_);
}

void FrameBuffer::generateRenderBuffer() {
	

	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

	glGenRenderbuffers(1, &rbo_);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);//attach rbo
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Render(Shader* shader,GLuint index) {
	//Draw screen
	shader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_[index]);
	

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
}

void FrameBuffer::unBind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addAttachment() {
	iterator_++;
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	//generate color attachment

	glGenTextures(1, &texture_[iterator_]);
	glBindTexture(GL_TEXTURE_2D, texture_[iterator_]);
	glTexImage2D(GL_TEXTURE_2D, 0, colorType_, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + iterator_, GL_TEXTURE_2D, texture_[iterator_], 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	attachments_.push_back(GL_COLOR_ATTACHMENT0 + iterator_);
}

void FrameBuffer::setGLAttachments() {
	//GLuint attachments[2] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 };
	
	if (iterator_ >= 1) {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
		glDrawBuffers(iterator_ + 1, &attachments_[0]);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void FrameBuffer::setTextureID(GLuint texture,GLuint index) {
	texture_[index] = texture;
}

GLuint FrameBuffer::getTextureID(GLuint index) {
	return texture_[index];
}

void FrameBuffer::initQuad() {
	GLfloat vertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
								 // Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}