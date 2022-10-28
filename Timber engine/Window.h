#pragma once
//#include "stdafx.h"

class Window
{
private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	GLuint _width, _height;

	void Init_Core();
public:
	Window();
	Window(GLuint width, GLuint height);
	~Window();

	GLuint Get_width();
	GLuint Get_height();
	SDL_Window *Get_WindowID();

	void setWidth(GLuint width);
	void setHeight(GLuint height);

	//void Create_Window(const std::string title,const GLuint width,const GLuint height);
	void createWindow(const std::string title);
	void closeWindow();
	void initSettings();
};

