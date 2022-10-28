#include "WorldPhysics.h"
#include "Box.h"


WorldPhysics::WorldPhysics(glm::vec2 gravity)
{
	b2Vec2 g(gravity.x, gravity.y);
	world = new b2World(g);
}


WorldPhysics::~WorldPhysics()
{
	delete world;
}


void WorldPhysics::initGround() {
	b2BodyDef groundBd;
	groundBd.position.Set(0.0f, 200.0f);
	b2Body* groundB = this->world->CreateBody(&groundBd);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(200.0f, 20.0f);//400 width 40 height
	groundB->CreateFixture(&groundBox, 0.0f);


	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);

	//Box newBox;
	this->box1.init(this->world, glm::vec2(0.0f,0.0f),glm::vec2(40.0f,40.0f));
	this->box2.init(this->world, glm::vec2(100.0f,0.0f), glm::vec2(40.0f, 40.0f));
	this->box3.init(this->world, glm::vec2(100.0f, 80.0f), glm::vec2(40.0f, 40.0f), b2_staticBody);
	//boxes.push_back(newBox);
	
	

}

void WorldPhysics::step(GLfloat deltatime) {
	world->Step(deltatime, 8, 3);
}