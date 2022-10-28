#include "stdafx.h"
#include "Input.h"
#include "ECS/EventHandler.h"
#include "CapsuleDBody.h"





Input::~Input()
{
}

void Input::update(GLfloat deltatime)
{
	//if (timer > 0)
		//timer--;
	//std::cout << timer << std::endl;
	// std::cout << "Updating Input component!" << std::endl;
	if (upPressed) {
		
		if (this->entity->hasComponent<Transform>()) {
			glm::vec2 pos = entity->getComponent<Transform>().getPosition();
			//pos.x += deltatime;
			pos.y -= deltatime;
			entity->getComponent<Transform>().setPosition(pos);
		}
		upPressed = false;
	}
	if (downPressed) {
		if (this->entity->hasComponent<Transform>()) {
			glm::vec2 pos = entity->getComponent<Transform>().getPosition();
			//pos.x += deltatime;
			pos.y += deltatime;
			entity->getComponent<Transform>().setPosition(pos);
		}
		downPressed = false;
	}
	if (leftPressed) {
		if (this->entity->hasComponent<CapsuleDBody>()) {
			b2Vec2 pos = entity->getComponent<CapsuleDBody>().getBody()->GetPosition();
			b2Vec2 vel = entity->getComponent<CapsuleDBody>().getBody()->GetLinearVelocity();
			float velChange = (-1.0f)*std::min(iVelocity, 2.0f) - vel.x;
			float impulse = entity->getComponent<CapsuleDBody>().getBody()->GetMass()*velChange;
			entity->getComponent<CapsuleDBody>().getBody()->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), entity->getComponent<CapsuleDBody>().getBody()->GetWorldCenter(), true);

			//glm::vec2 pos = entity->getComponent<Transform>().getPosition();
			//pos.x -= deltatime;
			////pos.y -= deltatime;
			//entity->getComponent<Transform>().setPosition(pos);
		}
		leftPressed = false;
	}
	if (rightPressed) {
		if (this->entity->hasComponent<CapsuleDBody>()) {
			b2Vec2 pos = entity->getComponent<CapsuleDBody>().getBody()->GetPosition();
			b2Vec2 vel = entity->getComponent<CapsuleDBody>().getBody()->GetLinearVelocity();
			float velChange = std::min(iVelocity,2.0f) - vel.x;
			float impulse = entity->getComponent<CapsuleDBody>().getBody()->GetMass()*velChange;
			entity->getComponent<CapsuleDBody>().getBody()->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), entity->getComponent<CapsuleDBody>().getBody()->GetWorldCenter(), true);

			//glm::vec2 pos = entity->getComponent<Transform>().getPosition();
			//pos.x += deltatime;
			////pos.y -= deltatime;
			//entity->getComponent<Transform>().setPosition(pos);
		}
		rightPressed = false;
	}
	if (Jump) {
		
		if (entity->hasComponent<CapsuleDBody>()) {
			//std::cout << entity->getComponent<CapsuleDBody>().getNumFootContacts()  <<std::endl;
			if (entity->getComponent<CapsuleDBody>().getNumFootContacts() > 0) {
				GLfloat impulse = entity->getComponent<CapsuleDBody>().getBody()->GetMass()*(std::min(iVelocity+0.4f,0.8f));
				entity->getComponent<CapsuleDBody>().getBody()->ApplyLinearImpulse(b2Vec2(0.0f, impulse), entity->getComponent<CapsuleDBody>().getBody()->GetWorldCenter(), true);
				Jump = false;
				timer = 60;
			}
		}
	}
}

//void Input::render()
//{
//}


Input::Input()
{
	timer = 0;
	upPressed = false;
	downPressed = false;
	leftPressed = false;
	rightPressed = false;
	Jump = false;

	iVelocity = 0.0f;

	//EventHandler<InputEvent>::registerObserver(InputEvent::DOWN_PRESSED, goDown);
	//EventHandler<InputEvent>::registerObserver(InputEvent::DOWN_PRESSED, [this]() {this->downPressed = true; });
	//EventHandler<InputEvent>::registerObserver(InputEvent::UP_PRESSED, [this]() {this->upPressed = true; });
	EventHandler<InputEvent>::registerObserver(InputEvent::LEFT_PRESSED, [this]() {this->leftPressed = true; this->iVelocity += 0.0048f; });
	EventHandler<InputEvent>::registerObserver(InputEvent::RIGHT_PRESSED, [this]() {this->rightPressed = true; this->iVelocity += 0.0048f; });
	EventHandler<InputEvent>::registerObserver(InputEvent::SPACE_PRESSED, [this]() {this->Jump = true; });
	EventHandler<InputEvent>::registerObserver(InputEvent::LEFT_RELEASED, [this]() {this->leftPressed = false; this->iVelocity = 0.0f; });
	EventHandler<InputEvent>::registerObserver(InputEvent::RIGHT_RELEASED, [this]() {this->rightPressed = false; this->iVelocity = 0.0f; });
	EventHandler<InputEvent>::registerObserver(InputEvent::SPACE_RELEASED, [this]() {this->Jump = false; });
}