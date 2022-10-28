#include "Tile.h"
#include "DataManager.h"


Tile::Tile()
{
	
}


Tile::Tile(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type):
	texture(texture),
	position(position),
	scale(scale)
{
	box.init(DataManager::world, position, scale, type);
}

void Tile::Draw(Renderer *renderer) {
	renderer->Draw(texture, position, scale);
}

void Tile::Update_Position(glm::vec2 newPosition) {
	this->position = newPosition;
	
}

glm::vec2 Tile::Get_Position() {
	return this->position;
}

void Tile::setScale(glm::vec2 scale) {
	this->scale = scale;
}
void Tile::setPosition(glm::vec2 position) {
	this->position = position;
}