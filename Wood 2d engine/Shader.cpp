#include "Shader.h"
#include "ShaderFunctions.h"
#include <iostream>

Shader::Shader()
{
	this->ID = 0;
}

Shader::Shader(const GLchar *vertexFile,const GLchar *fragmentFile)
{
	// Initialize the shaders and the program

	GLuint _vertShader;
	GLuint _fragShader;
	GLuint _geomShader;

	ID = glCreateProgram();
	_vertShader = glCreateShader(GL_VERTEX_SHADER);
	_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	_geomShader = glCreateShader(GL_GEOMETRY_SHADER);

	std::string fileContents = ReadFile(vertexFile);
	const char * contentsPtr = fileContents.c_str();
	glShaderSource(_vertShader, 1, &contentsPtr, NULL);
	glCompileShader(_vertShader);
	CheckShaderError(_vertShader, 0,vertexFile);

	fileContents.empty();
	fileContents = ReadFile(fragmentFile);
	contentsPtr = fileContents.c_str();
	glShaderSource(_fragShader, 1, &contentsPtr, NULL);
	glCompileShader(_fragShader);
	CheckShaderError(_fragShader, 1, fragmentFile);

	glAttachShader(ID, _vertShader);
	glAttachShader(ID, _fragShader);

	glLinkProgram(ID);
	CheckProgramError(ID);

	glDeleteShader(_fragShader);
	glDeleteShader(_vertShader);

}


Shader &Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}