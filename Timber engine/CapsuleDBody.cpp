#include "stdafx.h"
#include "CapsuleDBody.h"
#include "DataManager.h"
#include "Transform.h"
#include "ECS/EventHandler.h"

CapsuleDBody::CapsuleDBody(const glm::vec2& position, const glm::vec2& dimension)
{

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = DataManager::world->CreateBody(&bodyDef);
	
	//body->SetGravityScale(0.0f);


	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, (dimension.y - dimension.x) / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.1f;

	fixture[0] = body->CreateFixture(&fixtureDef);

	b2CircleShape circleShape;
	circleShape.m_radius = dimension.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = 1.0f;
	circleDef.friction = 0.2f;
	circleDef.restitution = 0.1f;
	

	//Bottom circle
	circleShape.m_p.Set(0.0f, (-dimension.y + dimension.x) / 2.0f);
	fixture[1] = body->CreateFixture(&circleDef);
	//Top circle
	circleShape.m_p.Set(0.0f, (dimension.y - dimension.x) / 2.0f);
	fixture[1] = body->CreateFixture(&circleDef);

	boxShape.SetAsBox(0.1f, 0.1f, b2Vec2(0.0f, (-1.0f)*dimension.y / 2.0f), 0.0f);
	fixtureDef.isSensor = true;
	fixture[2] = body->CreateFixture(&fixtureDef);
	fixture[2]->SetUserData((void*)3);

	listener = new JumpingListener();
	DataManager::world->SetContactListener(listener);

}


CapsuleDBody::~CapsuleDBody()
{
}

void CapsuleDBody::update(GLfloat deltatime)
{
	if (entity->hasComponent<Transform>()) {
		glm::vec2 v(body->GetPosition().x, body->GetPosition().y);
		entity->getComponent<Transform>().setPosition(v);
	}

	if(listener->numFootContacts == 0)
		EventHandler<EAnimation>::notify(EAnimation::JUMP);
	//else
		//EventHandler<EAnimation>::notify(EAnimation::STAND);
}

void CapsuleDBody::destroy()
{
	body->DestroyFixture(fixture[0]);
	body->DestroyFixture(fixture[1]);
	body->GetWorld()->DestroyBody(body);
}
