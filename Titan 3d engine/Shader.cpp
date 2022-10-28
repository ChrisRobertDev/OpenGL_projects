#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>

std::string ReadFile(const std::string& filePath);
void CheckShaderError(GLuint Shader, GLuint index, std::string filePath);
void CheckProgramError(GLuint Program);

Shader::Shader()
{
	this->ID = 0;
}

Shader::Shader(const GLchar *vertexFile,const GLchar *fragmentFile)
{
	// Initialize the shaders and the program

	GLuint _vertShader;
	GLuint _fragShader;
	//GLuint _geomShader;		// not good enough!

	ID = glCreateProgram();
	_vertShader = glCreateShader(GL_VERTEX_SHADER);
	_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//_geomShader = glCreateShader(GL_GEOMETRY_SHADER);		// not good enough!

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
void Shader::SetFloat3(const GLchar * name, glm::vec3 values, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform3f(glGetUniformLocation(ID, name), values.x, values.y, values.z);
}
void Shader::SetFloat4(const GLchar * name, GLfloat valueX, GLfloat valueY, GLfloat valueZ, GLfloat valueW, GLboolean useShader)
{
	if (useShader)
	{
		this->Use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), valueX, valueY, valueZ, valueW);
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

void Shader::SetMatrix3(const GLchar *name, const glm::mat3 &matrix, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	
}



std::string ReadFile(const std::string& filePath)
{
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		std::cout << "Failed to open the file from " << filePath << std::endl;
	}
	std::string fileContents;
	std::string line;
	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}
	vertexFile.close();
	return fileContents;
}
void CheckShaderError(GLuint Shader, GLuint index, std::string filePath)
{
	GLint result;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		if (index == 0)	std::cout << "Vertex shader compilation failed ! Path : " << filePath << std::endl;
		if (index == 1) std::cout << "Fragment shader compilation failed ! Path : " << filePath << std::endl;
		if (index == 2) std::cout << "Geometry shader compilation failed ! Path : " << filePath << std::endl;

		GLint logLength;
		glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logLength);

		char * log = (char *)malloc(logLength);
		GLsizei written;
		glGetShaderInfoLog(Shader, logLength, &written, log);
		std::cout << "Shader log : " << std::endl << log << std::endl;
		free(log);

	}
}

void CheckProgramError(GLuint Program)
{
	GLint result;
	glGetProgramiv(Program, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << "Program compilation failed !" << std::endl;
		GLint logLength;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &logLength);

		char * log = (char *)malloc(logLength);
		GLsizei written;
		glGetProgramInfoLog(Program, logLength, &written, log);
		std::cout << "Shader log : " << std::endl << log << std::endl;
		free(log);

	}


}