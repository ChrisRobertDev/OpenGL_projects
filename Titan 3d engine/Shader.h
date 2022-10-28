#pragma once

#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>


class Shader
{
private:
	GLuint ID;
public:

	Shader();
	Shader(const GLchar *vertexFile, const GLchar *fragmentFile);

	//Getter
	GLuint Get_ID() { return this->ID; }

	Shader &Use();

	// Utility functions
	void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void    SetFloat3(const GLchar *name, glm::vec3 values, GLboolean useShader = false);
	void    SetFloat4(const GLchar *name, GLfloat valueX = 0.0f, GLfloat valueY = 0.0f, GLfloat valueZ = 0.0f, GLfloat valueW = 0.0f, GLboolean useShader = false);
	void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix3(const GLchar *name, const glm::mat3 &matrix, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	
	
};

