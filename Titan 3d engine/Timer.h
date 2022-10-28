#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
class Timer
{
public:
	Timer();
	~Timer();

	void tick(GLfloat deltaSeconds);
	void wait();
	void reset();
	GLboolean waitingTime_isSet();
	//getters
	glm::vec3 getTimer();
	GLboolean getWaitBoolean();
	GLfloat getHours();
	GLfloat getMinutes();
	GLfloat getSeconds();
	GLfloat getTotalSeconds();
	//printers
	void printTimer();

	//setters and recorder
	void setClock(const GLfloat hour, const GLfloat minutes, const GLfloat seconds);
	void setwaitingTime(const GLfloat hours, const GLfloat minutes, const GLfloat seconds);
	void setGlobalSeconds(GLfloat seconds);
	
protected:
	glm::vec3 waitingTime_;
	glm::vec3 lastTime_;
	GLboolean hastoWait_;

private:
	glm::vec3 clock_;
	GLfloat globalSecond_;
};

