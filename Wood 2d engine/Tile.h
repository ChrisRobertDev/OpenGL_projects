#pragma once

#include "DataManager.h"
#include "Renderer.h"
#include "Box.h"

class Tile
{
private:
	Texture2D texture;
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 boxSize;

	Box box;

public:
	

	Tile();
	Tile(Texture2D texture,glm::vec2 position,glm::vec2 scale,b2BodyType type = b2_dynamicBody);
	
	void Update_Position(glm::vec2 newPosition);
	void Draw(Renderer *renderer);


	glm::vec2 Get_Position();
	glm::vec2 Get_boxSize();

	void setScale(glm::vec2 scale);
	void setPosition(glm::vec2 position);
};

