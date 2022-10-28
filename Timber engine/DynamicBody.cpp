#include "stdafx.h"
#include "DynamicBody.h"
#include "Transform.h"
#include "DataManager.h"

DynamicBody::DynamicBody(const glm::vec2& position, const glm::vec2& dimension)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = DataManager:: world->CreateBody(&bodyDef);



	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
}


DynamicBody::~DynamicBody()
{
}

void DynamicBody::update(GLfloat deltatime)
{
	if (entity->hasComponent<Transform>()) {
		glm::vec2 v(body->GetPosition().x, body->GetPosition().y);
		entity->getComponent<Transform>().setPosition(v);
	}
}

void DynamicBody::destroy()
{
	body->DestroyFixture(fixture);
	body->GetWorld()->DestroyBody(body);
}
