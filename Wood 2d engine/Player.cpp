#include "Player.h"



Player::Player(Texture2D texture, glm::vec2 position, glm::vec2 scale, b2BodyType type):
	GameObject(texture, position, scale, type),
	max_frames(16),
	framecount(0),
	deltacount(0.0f),
	isMirrored(0.0f)
{
}


Player::~Player()
{
}


void Player::render(Renderer* renderer) {
	deltacount++;
	switch (aState)
	{
	case STANDING:
		texture.setIndex(12);
		break;
	case WALKING_LEFT:
		if (framecount == 0)
			framecount = 8;
		isMirrored = 1.0f;
		if (deltacount > 1000.0f / 11.0f && isMirrored == 1.0f) {
			framecount--;
			
			deltacount = 0.0f;
		}
		break;
	case WALKING_RIGHT:
		if (framecount == 8)
			framecount = 0;
		isMirrored = 0.0f;
		if (deltacount > 1000.0f / 11.0f && isMirrored == 0.0f) {
			framecount++;
			
			deltacount = 0.0f;
		}
		break;
	case JUMPING:
		break;
	default:
		break;
	}
	
	
	
	
	

	//change texture accordingly
	texture.setIndex(framecount);
	texture.setMirrorFlag(isMirrored);


	renderer->Draw(texture, position, scale, 0.0f);
}

void Player::tick(GLfloat deltatime) {
	position = glm::vec2(box.getBody()->GetPosition().x, box.getBody()->GetPosition().y);

}

void Player::setMirroring(GLfloat flag) {
	isMirrored = flag;
}

void Player::setFrameCount(GLuint frameCount) {
	framecount = frameCount;
}

void Player::setAnimState(AnimationState state) {
	aState = state;
}