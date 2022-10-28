#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension,b2BodyType type) {
	
	if (type == b2_dynamicBody) {
		b2BodyDef bodyDef;
		bodyDef.type = type;
		bodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&bodyDef);



		b2PolygonShape boxShape;
		boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.1f;

		fixture = body->CreateFixture(&fixtureDef);
	}
	else {
		b2BodyDef bodyDef;
		bodyDef.type = type;
		bodyDef.position.Set(position.x, position.y);
		body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;

		fixture = body->CreateFixture(&fixtureDef);
	}

}

void Box::destroy() {
	body->DestroyFixture(fixture);
	body->GetWorld()->DestroyBody(body);
}