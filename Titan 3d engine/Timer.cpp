#include "Timer.h"

#include <iostream>

Timer::Timer() :
	clock_(glm::vec3(10.0f,0.0f,0.0f)),
	globalSecond_(1.0f)
{
}


Timer::~Timer()
{
}

void Timer::printTimer()
{
	std::cout << clock_.x << ":" << clock_.y << ":" << clock_.z << std::endl;
}

void Timer::setwaitingTime(const GLfloat hours, const GLfloat minutes, const GLfloat seconds)
{
	waitingTime_ = glm::vec3(hours, minutes, seconds);
}
void Timer::setGlobalSeconds(GLfloat seconds) {
	globalSecond_ = seconds;
}

void Timer::tick(GLfloat deltaSeconds)
{
	static GLfloat accumulator = 0.0f;

	accumulator += deltaSeconds;
	if (accumulator > globalSecond_) {
		accumulator = 0.0f;
		clock_.z += floorf(1.0f / globalSecond_ / 60);
		if (clock_.z >= 60) {
			clock_.y += floorf(clock_.z/60);
			clock_.z = 0.0f;
		}
		if (clock_.y >= 60) {
			clock_.x += floorf(clock_.y / 60);
			clock_.y = 0.0f;
		}
		if (clock_.x >= 24)
			clock_.x = 0.0f;
		
	}
}



void Timer::wait()
{
	if (waitingTime_.x == 0.0f && waitingTime_.y == 0.0f && waitingTime_.z == 0.0f)
		hastoWait_ = GL_FALSE;
	else {
		hastoWait_ = GL_TRUE;
		if (waitingTime_.z == 0.0f && waitingTime_.y == 0.0f) {
			waitingTime_.x -= 1.0f;
			waitingTime_.y = 59.0f;
			waitingTime_.z = 59.0f;

		}
		else
			if (waitingTime_.y == 0) {
				waitingTime_.y -= 1.0f;
				waitingTime_.z = 0.0f;
			}
			else
				waitingTime_.z -= 1.0f;
	}
}

void Timer::reset()
{
	clock_ = glm::vec3(0.0f);
}

GLboolean Timer::waitingTime_isSet()
{
	if(waitingTime_.x > 0.0f || waitingTime_.y > 0.0f || waitingTime_.z > 0.0f)
		return GL_TRUE;
	return GL_FALSE;
}

glm::vec3 Timer::getTimer()
{
	return clock_;
}

GLboolean Timer::getWaitBoolean()
{
	return hastoWait_;
}

GLfloat Timer::getHours()
{
	return clock_.x;
}

GLfloat Timer::getMinutes()
{
	return clock_.y;
}

GLfloat Timer::getSeconds()
{
	return clock_.z;
}

GLfloat Timer::getTotalSeconds() {
	return clock_.z + 60.0f * clock_.y + 3600.0f * clock_.x;
}