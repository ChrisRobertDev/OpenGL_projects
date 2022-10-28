#include "GameObject.h"
#include "DataManager.h"

#include <iostream>
#include <sstream>

GameObject::GameObject() :
	shouldTickFlag(true),
	shouldBeDestroyedFlag(false),
	texture(NULL),
	position(glm::vec2(0.0f, 0.0f)),
	scale(glm::vec2(1.0f, 1.0f)),
	type(b2_staticBody)
{
	
	box.init(DataManager::world, position, scale, type);
}

GameObject::GameObject(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type):
	shouldTickFlag(true),
	shouldBeDestroyedFlag(false),
	texture(texture),
	position(position),
	scale(scale),
	type(type)
{
	//std::stringstream ss;
	//ss << "Object_" << index;
	//nameId = ss.str();
	box.init(DataManager::world, position, scale, type);
}


GameObject::~GameObject()
{
}



void GameObject::render(Renderer* renderer) {
	//Render stuffie
	//std::cout << "GameObject::render() Called!" << std::endl;
	renderer->Draw(texture, position, scale);
 }

void GameObject::tick(GLfloat deltatime) {
	//Tick stuffie
	position = glm::vec2(box.getBody()->GetPosition().x, box.getBody()->GetPosition().y);

	if (position.y > 400.0f)
		shouldBeDestroyedFlag = true;
 }

//setters
void GameObject::setNameId(std::string name) {
	
	nameId = name;
}
void GameObject::setDestroyFlag(GLboolean flag) {
	shouldBeDestroyedFlag = flag;
}
void GameObject::setTickFlag(GLboolean flag) {
	shouldTickFlag = flag;
}

//getters
std::string GameObject::getNameId() {
	return nameId;
}
