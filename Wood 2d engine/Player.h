#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	GLfloat deltacount;
	GLuint framecount;
	GLuint max_frames;
	GLfloat isMirrored;

	AnimationState aState;

public:
	Player(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type = b2_dynamicBody);
	~Player();

	void render(Renderer* renderer);

	void tick(GLfloat deltatime);

	//Setters
	void setMirroring(GLfloat flag);
	void setFrameCount(GLuint frameCount);
	void setAnimState(AnimationState state);
};

