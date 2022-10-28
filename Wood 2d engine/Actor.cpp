#include "Actor.h"
#include "DataManager.h"

#include <iostream>

Actor::Actor():
	GameObject()
{

}

Actor::Actor(Texture2D texture, glm::vec2 position , glm::vec2 scale , b2BodyType type):
	GameObject(texture, position, scale, type)
{
	
}


Actor::~Actor()
{
}


void Actor::render(Renderer* renderer) {
	//std::cout << "Actor::render() Called!" << std::endl;
	renderer->Draw(texture, position, scale);
}

void Actor::tick(GLfloat deltatime) {
	//update position
	//std::cout << "Tick: Asdsasd" << std::endl;
	position = glm::vec2(box.getBody()->GetPosition().x, box.getBody()->GetPosition().y);
}