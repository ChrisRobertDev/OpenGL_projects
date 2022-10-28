#pragma once
#include <GL\glew.h>
#include "Renderer.h"
#include "Box.h"


class GameObject
{
protected:
	GLboolean shouldTickFlag;
	GLboolean shouldBeDestroyedFlag;

	std::string nameId;

	Texture2D texture;

	glm::vec2 position;
	glm::vec2 scale;

	b2BodyType type;
	Box box;

	//void integrateClassInLoop(); impossible
public:
	GameObject();
	GameObject(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type = b2_dynamicBody);
	~GameObject();


	virtual void render(Renderer* renderer);

	virtual void tick(GLfloat deltatime);

	GLboolean shouldTick() { return shouldTickFlag; }
	GLboolean shouldBeDestroyed() { return shouldBeDestroyedFlag; }
	
	//setters
	void setNameId(std::string name);
	void setDestroyFlag(GLboolean flag);
	void setTickFlag(GLboolean flag);

	//getters
	std::string getNameId();
	Box getBox() { return box; }
};

