#pragma once
#include "GameObject.h"
#include "Box.h"
#include "Renderer.h"

class Actor : public GameObject
{

public:
	Actor();
	Actor(Texture2D texture,glm::vec2 position,glm::vec2 scale ,b2BodyType type = b2_dynamicBody);
	~Actor();

	void render(Renderer* renderer);

	void tick(GLfloat deltatime);

	
};

