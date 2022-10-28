#include "Noise.h"

#include <iostream>

#include <glm\glm.hpp>

Noise::Noise(GLuint size, GLint seed):
	size_(size),
	seed_(seed)
{
	std::srand(seed);
	GLint perm[256];
	for (GLuint i = 0; i < 256; i++) {
		GLuint other = rand() % (i + 1);
		if (i > other) {
			perm[i] = perm[other];
		}
		perm[other] = i;
	}

	for (int i = 0; i < 512; i++) {
		p[i] = perm[i % 256];
	}

	//computeArray(1.0f,1.0f,1.0f,2.0f);
}


Noise::~Noise()
{
}

GLfloat Noise::Octave(GLfloat x, GLfloat y, GLint octaves, GLfloat persistence) {
	GLfloat total = 0;
	GLfloat frequency = 1;
	GLfloat amplitude = 1;
	GLfloat maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
	for (GLuint i = 0; i < octaves; i++) {
		total += perlinNoise(x * frequency, y * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}

void Noise::computeArray(GLfloat amp1, GLfloat amp2, GLfloat amp3, GLfloat exponent, GLfloat Xincr, GLfloat Yincr) {

	GLfloat freq1 = 1.0f;
	GLfloat freq2 = 2.0f;
	GLfloat freq3 = 4.0f;
	GLfloat freq4 = 8.0f;
	
	for (GLfloat x = 0; x < size_; x++) {
		std::vector<GLfloat> v;
		for (GLfloat z = 0; z < size_; z++) {
			GLfloat nX = x / (GLfloat)size_ -0.5f;
			GLfloat nZ = z / (GLfloat)size_ -0.5f;
			GLfloat value = 0.3f * perlinNoise(freq1 * nZ, freq1 * nX);
			value += (0.55f) * perlinNoise(freq2 * nZ, freq2 * nX);
			value += (0.8f) * perlinNoise(freq3 * nZ, freq3 * nX);
			value += (0.3f) * perlinNoise(freq4 * nZ, freq4 * nX);
			
			
			value = glm::pow(value, 3.0f);

			v.push_back(value);
			
		}
		noiseArray_.push_back(v);
		
	}
}

void Noise::Smooth(GLfloat k) {
	for (GLuint x = 1; x < size_; x++) {
		for (GLuint z = 0; z < size_; z++) {
			noiseArray_[x][z] = noiseArray_[x - 1][z] * (1 - k) + noiseArray_[x][z] * k;
		}
	}
	for (GLuint x = size_ - 2; x > -1; x--) {
		for (GLuint z = 0; z < size_; z++) {
			noiseArray_[x][z] = noiseArray_[x + 1][z] * (1 - k) + noiseArray_[x][z] * k;
		}
	}
	for (GLuint x = 1; x < size_; x++) {
		for (GLuint z = 1; z < size_; z++) {
			noiseArray_[x][z] = noiseArray_[x][z - 1] * (1 - k) + noiseArray_[x][z] * k;
		}
	}
	for (GLuint x = 1; x < size_; x++) {
		for (GLuint z = size_; z > -1; z--) {
			noiseArray_[x][z] = noiseArray_[x][z + 1] * (1 - k) + noiseArray_[x][z] * k;
		}
	}
}

GLfloat Noise::getArrayIndex(GLuint i, GLuint j) {
	return noiseArray_[i][j];
}

GLfloat Noise::fade(GLfloat t) {
	return 3*t*t - 2*t*t*t;
}

GLfloat Noise::lerp(GLfloat t, GLfloat a, GLfloat b) {
	//return a + t*(b - a);
	return (1.0f - t)*a + t*b;
}

GLfloat Noise::perlinNoise(GLfloat x, GLfloat y) {
	GLint X = (GLint)floorf(x) & 255;
	GLint Y = (GLint)floorf(y) & 255;

	x = x - floorf(x);
	y = y - floorf(y);

	GLfloat u = fade(x);
	GLfloat v = fade(y);

	GLint a = p[X] + Y;
	GLint b = p[X + 1] + Y;
	GLint aa = p[a];
	GLint ab = p[a + 1];
	GLint ba = p[b];
	GLint bb = p[b + 1];

	float itp1 = lerp(u, gradient(aa, x, y), gradient(ba, x - 1, y));
	float itp2 = lerp(u, gradient(ab, x, y - 1), gradient(bb, x - 1, y - 1));

	return lerp(v, itp1, itp2);
}

GLfloat Noise::gradient(GLint hash, GLfloat x, GLfloat y) {
	return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);
}