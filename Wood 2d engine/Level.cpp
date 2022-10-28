#include "Level.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
Level::Level()
{
	this->MAP.clear();
}

Level::Level(const std::string filepath, glm::vec2 Scale,GLfloat newWidth, GLfloat newHeight) :
	Width(newWidth),
	Height(newHeight),
	Scale(Scale)
{
	this->MAP.clear();

	std::string line;
	std::ifstream input(filepath);

	while (std::getline(input, line)) {
		GLuint x;
		std::vector<GLuint> row;
		std::stringstream ss(line);
		while (ss >> x) {
			row.push_back(x);
			
		}
		this->MAP.push_back(row);
	}
	
	this->SetUp();
}

void Level::SetUp() {
	
	glm::vec2 Position(
		this->Width / 2.0f - (Scale.x * MAP[0].size()) / 2.0f + Scale.x / 2.0f, 
		this->Height/2.0f - (Scale.y * MAP.size()) / 2.0f + Scale.y / 2.0f
		);
	std::cout << this->Width / 2.0f - (Scale.x * MAP[0].size()) / 2.0f + Scale.x / 2.0f << std::endl;
	for (GLuint i = 0; i < this->MAP.size(); i++) {
		std::vector<Tile> row;
		Position.x = this->Width / 2.0f - Scale.x * MAP[0].size() / 2.0f + Scale.x / 2.0f;
		for (GLuint j = 0; j < this->MAP[0].size(); j++)
		{
			Tile tile;
			switch (this->MAP[i][j]) {
			case 0:tile = Tile(DataManager::GetTexture("ground"), Position, this->Scale); Position.x += this->Scale.x; break;
			case 1:tile = Tile(DataManager::GetTexture("brick"), Position, this->Scale); Position.x += this->Scale.x; break;
			default: break;
			}
			row.push_back(tile);
		}
		Tiles.push_back(row);
		Position.y += this->Scale.y;
	}
}

void Level::Draw(Renderer *renderer) {
	for (GLuint i = 0; i < Tiles.size(); i++) {
		for (GLuint j = 0; j < Tiles[0].size(); j++)
			Tiles[i][j].Draw(renderer);
	}
}

GLuint Level::Get_LevelLength() {
	return this->MAP[0].size();
}
