#pragma once
#include "Shader.h"
#include "Texture2D.h"

//Animation states

enum AnimationState {
	STANDING,
	WALKING_LEFT,
	WALKING_RIGHT,
	JUMPING
};

class Renderer
{
private:
	GLuint _Vao;
	Shader _shader;

	void InitializeData();
public:
	Renderer(Shader &shader);
	
	void Draw(
		Texture2D texture, 
		glm::vec2 Position = glm::vec2(0.0f,0.0f),
		glm::vec2 Scale=glm::vec2(1.0f,1.0f),
		GLfloat angle = 0.0f
	);
};

