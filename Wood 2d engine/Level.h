#pragma once


#include "Tile.h"

class Level
{
private:
	std::vector<std::vector<GLuint>> MAP;
	
	glm::vec2 Scale;
	GLfloat Width, Height;

	void SetUp();
public:
	std::vector<std::vector<Tile>> Tiles;

	Level();
	Level(const std::string filepath, glm::vec2 Scale, GLfloat newWidth, GLfloat newHeight);

	
	void Draw(Renderer *_renderer);

	GLuint Get_LevelLength();
};