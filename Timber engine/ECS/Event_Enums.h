#pragma once

enum class InputEvent {
	UP_PRESSED,
	DOWN_PRESSED,
	LEFT_PRESSED,
	RIGHT_PRESSED,
	SPACE_PRESSED,
	CLOSE_PRESSED,
	UP_RELEASED,
	DOWN_RELEASED,
	LEFT_RELEASED,
	RIGHT_RELEASED,
	SPACE_RELEASED
};

enum class EAnimation {
	LEFT,
	RIGHT,
	JUMP,
	STAND,
	HURT
};