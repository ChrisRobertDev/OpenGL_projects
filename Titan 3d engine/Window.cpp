
#include <iostream>

#include "Window.h"

Window::Window(std::string name, const GLuint width, GLuint height)
{
	width_ = width;
	height_ = height;
	GLuint check;
	check = SDL_Init(SDL_INIT_EVERYTHING);
	if (check < 0) {
		std::cout << "Could not initialize SDL!" << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	window_ = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL);

	SDL_GLContext context;
	context_ = SDL_GL_CreateContext(window_);


	GLboolean status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Glew could not be initialised . . . " << std::endl;
	}
	glViewport(0, 0, width_, height_);
	glEnable(GL_DEPTH_TEST);

}


Window::~Window()
{
	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Window::setResolution(GLuint width, GLuint height)
{
	width_ = width;
	height_ = height;
}

SDL_Window* Window::getWindow()
{
	return window_;
}
