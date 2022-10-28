#pragma once
#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <GL\glew.h>

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
void CheckShaderError(GLuint Shader, GLuint index,std::string filePath)
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

