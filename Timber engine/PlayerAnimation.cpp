#include "stdafx.h"
#include "PlayerAnimation.h"
#include "ECS/EventHandler.h"
#include "ECS/Event_Enums.h"
#include "Material.h"

PlayerAnimation::PlayerAnimation()
{
	frameCount = 0;
	deltaCount = 0.0f;
	isMirrored = 0.0f;
	inAirMirrored = 0.0f;
	EventHandler<InputEvent>::registerObserver(InputEvent::LEFT_PRESSED, [this]() {this->action = 1; this->inAirMirrored = 1.0f; });
	EventHandler<InputEvent>::registerObserver(InputEvent::RIGHT_PRESSED, [this]() {this->action = 2; this->inAirMirrored = 0.0f; });
	EventHandler<EAnimation>::registerObserver(EAnimation::JUMP, [this]() {this->action = 3; });
	EventHandler<EAnimation>::registerObserver(EAnimation::STAND, [this]() {this->action = 4; });
	EventHandler<InputEvent>::registerObserver(InputEvent::LEFT_RELEASED, [this]() {this->action = 4; });
	EventHandler<InputEvent>::registerObserver(InputEvent::RIGHT_RELEASED, [this]() {this->action = 4; });
}


PlayerAnimation::~PlayerAnimation()
{
}

void PlayerAnimation::update(GLfloat deltatime)
{
	deltaCount += deltatime;
	if (entity->hasComponent<Material>()) {
		Material& mat = entity->getComponent<Material>();
		
		// std::cout << frameCount << std::endl;
		switch (action)
		{
		case 1: {
			if (frameCount <= 0)
				frameCount = 8;
			isMirrored = 1.0f;
			if (deltaCount > 1.0f / 3.75f) {
				frameCount--;
				deltaCount = 0.0f;
			}
			mat.setMirrorFlag(isMirrored);
			mat.setTextureIndex(frameCount);
			break;
		}
		case 2: {
			//std::cout << frameCount << std::endl;
			if (frameCount >= 8)
				frameCount = 0;
			isMirrored = 0.0f;
			if (deltaCount > 1.0f / 3.75f) {
				frameCount++;
				deltaCount = 0.0f;
			}
			mat.setMirrorFlag(isMirrored);
			mat.setTextureIndex(frameCount);
			break;
		}
		case 3: {
			mat.setTextureIndex(13);
			mat.setMirrorFlag(inAirMirrored);
			break;
		}
		case 4:
			mat.setTextureIndex(12);
			
			break;
		default:
			
			break;
		}

		
		

	}
}

