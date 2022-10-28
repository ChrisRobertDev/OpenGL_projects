#include "stdafx.h"
#include "DataManager.h"


std::map<std::string, Shader> DataManager::Shaders;
std::map<std::string, Texture2D> DataManager::Textures;
//std::vector<GameObject> DataManager::Objects;
b2World* DataManager::world;

//Rendering related functions

void DataManager::LoadShader(const GLchar *Vfile, const GLchar *Ffile , const std::string name) {
	Shader *shader;
	shader = new Shader(Vfile, Ffile);
	Shaders[name]= *shader;
	delete shader;
}
void DataManager::LoadTexture(const GLchar *filename, const std::string name, glm::ivec2 dims) {
	Texture2D *texture;
	texture = new Texture2D(filename,dims);
	Textures[name] = *texture;
	delete texture;
}

Shader DataManager::GetShader(const std::string name) {
	return Shaders[name];
}
Texture2D DataManager::GetTexture(const std::string name) {
	return Textures[name];
}

//Game object related functions

void DataManager::addObject(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type, GLuint texIndex) {
	//GameObject* a;
	//a = new GameObject(texture, position, scale);
	//Objects[0] = a;
	//delete a;
	//Objects.push_back(GameObject(texture, position, scale,type, texIndex));

}
void DataManager::destroyObject(GLuint index) {
	/*Objects[index].getBox().destroy();
	Objects.erase(Objects.begin() + index);*/
}

// if an object is found it returns the index of it else returns -1
GLuint DataManager::findObject(glm::vec2 position) {
	/*for (GLuint i = 0; i < Objects.size(); i++) {
		if (Objects[i].getPosition().x == position.x && Objects[i].getPosition().y == position.y)
			return i;
	}*/
	return 0;
}

// Determines if an object exists in the collection
GLboolean DataManager::Exists(glm::vec2 position) {
	/*for (GLuint i = 0; i < Objects.size(); i++) {
		if (Objects[i].getPosition().x == position.x && Objects[i].getPosition().y == position.y)
			return true;
	}*/
	return false;
}

//Physics related functions

void DataManager::initWorld(glm::vec2 gravity) {
	b2Vec2 g(gravity.x, gravity.y);
	world = new b2World(g);
	world->SetAllowSleeping(true);
}

void DataManager::initGround() {
	b2BodyDef groundBd;
	groundBd.position.Set(0.0f, -10.0f);
	b2Body* groundB = world->CreateBody(&groundBd);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(2.5f, 0.25f);//400 width 40 height
	groundB->CreateFixture(&groundBox, 0.0f);
}