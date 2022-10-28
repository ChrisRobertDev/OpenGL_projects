#include "stdafx.h"
#include "Window.h"




Window::Window():
	_window(NULL)
{

}

Window::Window(GLuint width,GLuint height):
_width(width),
_height(height),
_window(NULL)
{
	//std::cout << _width << " " << _height << std::endl;
}


Window::~Window()
{
	_window = NULL;
}

GLuint Window::Get_width() {
	return this->_width;
}
GLuint Window::Get_height() {
	return this->_height;
}

SDL_Window *Window::Get_WindowID() {
	return this->_window;
}
void Window::setWidth(GLuint width) {
	this->_width = width;
}
void Window::setHeight(GLuint height) {
	this->_height = height;
}

void Window::createWindow(const std::string title) {
	Init_Core();
	this->_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_width, this->_height, SDL_WINDOW_OPENGL);
	this->_glContext = SDL_GL_CreateContext(this->_window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cout << "Glew could not be initialized! (line 48 , Window.cpp)" << std::endl;
	}
}
void Window::Init_Core() {
	if (SDL_Init(SDL_INIT_EVERYTHING))
		std::cout << "SDL could not be initialized! (line 44 , Window.cpp)" << std::endl;

	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

}

void Window::closeWindow()
{
	SDL_Quit();
}

void Window::initSettings() {
	glViewport(0, 0, _width, _height);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);
	
	//SDL_ShowCursor(false);

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glDepthFunc(GL_LESS);

	SDL_GL_SetSwapInterval(0);
}