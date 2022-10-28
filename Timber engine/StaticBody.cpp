#include "stdafx.h"
#include "StaticBody.h"
#include "DataManager.h"
#include "Transform.h"

StaticBody::StaticBody(const glm::vec2& position, const glm::vec2& dimension)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	body = DataManager::world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;

	fixture[0] = body->CreateFixture(&fixtureDef);
	fixtureCount++;
}

StaticBody::StaticBody(const glm::vec2 & position, const std::vector<b2Vec2>& lines)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	body = DataManager::world->CreateBody(&bodyDef);
	fixtureCount = 0;
	for (GLuint i = 0; i < lines.size(); i+=2) {
		b2EdgeShape e;
		e.Set(lines[i], lines[i + 1]);

		b2FixtureDef fixDef;
		fixDef.shape = &e;

		fixture[fixtureCount++] = body->CreateFixture(&fixDef);
	}
}


StaticBody::~StaticBody()
{
}

void StaticBody::update(GLfloat deltatime)
{
	if (entity->hasComponent<Transform>()) {
		glm::vec2 v(body->GetPosition().x, body->GetPosition().y);
		entity->getComponent<Transform>().setPosition(v);
	}
}

void StaticBody::destroy()
{
	for(GLuint i = 0; i<fixtureCount;i++)
		body->DestroyFixture(fixture[i]);
	body->GetWorld()->DestroyBody(body);
}
