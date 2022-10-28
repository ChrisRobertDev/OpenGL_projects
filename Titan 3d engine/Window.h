#pragma once
#include <string>

#include <SDL\SDL.h>
#include <GL\glew.h>

class Window
{
public:
	Window(std::string name,const GLuint width,GLuint height);
	~Window();
	//setters
	void setResolution(GLuint width, GLuint height);
	//getters
	SDL_Window* getWindow();

private:
	GLuint width_;
	GLuint height_;

	SDL_Window* window_;
	SDL_GLContext context_;
};

