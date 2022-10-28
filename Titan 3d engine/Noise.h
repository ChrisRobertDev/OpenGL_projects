#pragma once
#include <stdlib.h>
#include <vector>
#include <GL\glew.h>
class Noise
{
public:
	Noise(GLuint size, GLint seed);
	~Noise();
	
	GLfloat Octave(GLfloat x, GLfloat y, GLint octaves, GLfloat persistence);
	GLfloat perlinNoise(GLfloat x, GLfloat y);
	
	void computeArray(GLfloat amp1,GLfloat amp2,GLfloat amp3, GLfloat exponent, GLfloat Xincr = 0.1f,GLfloat Yincr = 0.1f);
	void Smooth(GLfloat k);

	//Getters
	GLfloat getArrayIndex(GLuint i, GLuint j);


private:
	std::vector<std::vector<GLfloat>> noiseArray_;
	GLint p[512];
	GLint seed_;
	GLuint size_;
	GLfloat fade(GLfloat t);
	GLfloat lerp(GLfloat t, GLfloat a, GLfloat b);
	GLfloat gradient(GLint hash, GLfloat x, GLfloat y);

};

