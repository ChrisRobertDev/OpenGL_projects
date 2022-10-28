#include "stdafx.h"
#include "InputSystem.h"
#include "ECS/EventHandler.h"
#include "ECS/Event_Enums.h"
//#include <iostream>

void InputSystem::resetKeys()
{
	/*keyMap["up"] = 0.0f;
	keyMap["down"] = 0.0f;
	keyMap["left"] = 0.0f;
	keyMap["right"] = 0.0f;
	keyMap["space"] = 0.0f;
	keyMap["q"] = 0.0f;
	keyMap["w"] = 0.0f;
	keyMap["e"] = 0.0f;
	keyMap["r"] = 0.0f;
	keyMap["t"] = 0.0f;
	keyMap["i"] = 0.0f;
	keyMap["p"] = 0.0f;
	keyMap["a"] = 0.0f;
	keyMap["s"] = 0.0f;
	keyMap["d"] = 0.0f;
	keyMap["f"] = 0.0f;
	keyMap["j"] = 0.0f;
	keyMap["k"] = 0.0f;
	keyMap["l"] = 0.0f;
	keyMap["c"] = 0.0f;
	keyMap["v"] = 0.0f;
	keyMap["b"] = 0.0f;
	keyMap["n"] = 0.0f;
	keyMap["m"] = 0.0f;*/

	keyMap["up"] = -1.0f;
	keyMap["down"] = -1.0f;
	keyMap["left"] = -1.0f;
	keyMap["right"] = -1.0f;
	keyMap["space"] = -1.0f;
	keyMap["q"] = -1.0f;
	keyMap["w"] = -1.0f;
	keyMap["e"] = -1.0f;
	keyMap["r"] = -1.0f;
	keyMap["t"] = -1.0f;
	keyMap["i"] = -1.0f;
	keyMap["p"] = -1.0f;
	keyMap["a"] = -1.0f;
	keyMap["s"] = -1.0f;
	keyMap["d"] = -1.0f;
	keyMap["f"] = -1.0f;
	keyMap["j"] = -1.0f;
	keyMap["k"] = -1.0f;
	keyMap["l"] = -1.0f;
	keyMap["c"] = -1.0f;
	keyMap["v"] = -1.0f;
	keyMap["b"] = -1.0f;
	keyMap["n"] = -1.0f;
	keyMap["m"] = -1.0f;

	
}

InputSystem::InputSystem()
{
	//keyState = SDL_GetKeyboardState(NULL);
	quit = false;
	
	resetKeys();
}


InputSystem::~InputSystem()
{
}

void InputSystem::update(GLfloat deltatime)
{
	

	handleInput();
}

void InputSystem::preUpdate(GLfloat deltatime)
{
	SDL_Event Evnt;

	while (SDL_PollEvent(&Evnt))
	{

		if (Evnt.type == SDL_QUIT) {
			//if(Evnt.key.keysym.sym == SDLK_ESCAPE) {
			//quit = true;
			EventHandler<InputEvent>::notify(InputEvent::CLOSE_PRESSED);
			SDL_ShowCursor(true);
			break;
		}


		switch (Evnt.type) {
		case SDL_KEYDOWN:
			switch (Evnt.key.keysym.sym) {
			case SDLK_LEFT: keyMap["left"] = 1.0f; break;
			case SDLK_RIGHT: keyMap["right"] = 1.0f; break;
			case SDLK_UP: keyMap["up"] = 1.0f;  break;
			case SDLK_DOWN: keyMap["down"] = 1.0f; break;
			case SDLK_SPACE:keyMap["space"] = 1.0f; break;
			case SDLK_q:keyMap["q"] = 1.0f; break;
			case SDLK_w:keyMap["w"] = 1.0f; break;
			case SDLK_e:keyMap["e"] = 1.0f; break;
			case SDLK_r:keyMap["r"] = 1.0f; break;
			case SDLK_t:keyMap["t"] = 1.0f; break;
			case SDLK_i:keyMap["i"] = 1.0f; break;
			case SDLK_p:keyMap["p"] = 1.0f; break;
			case SDLK_a:keyMap["a"] = 1.0f; break;
			case SDLK_s:keyMap["s"] = 1.0f; break;
			case SDLK_d:keyMap["d"] = 1.0f; break;
			case SDLK_f:keyMap["f"] = 1.0f; break;
			case SDLK_j:keyMap["j"] = 1.0f; break;
			case SDLK_k:keyMap["k"] = 1.0f; break;
			case SDLK_l:keyMap["l"] = 1.0f; break;
			case SDLK_c:keyMap["c"] = 1.0f; break;
			case SDLK_v:keyMap["v"] = 1.0f; break;
			case SDLK_b:keyMap["b"] = 1.0f; break;
			case SDLK_n:keyMap["n"] = 1.0f; break;
			case SDLK_m:keyMap["m"] = 1.0f; break;
			default: resetKeys(); break;
			}
			break;
		case SDL_KEYUP:
			switch (Evnt.key.keysym.sym) {
			case SDLK_LEFT: keyMap["left"] = 0.0f; break;
			case SDLK_RIGHT: keyMap["right"] = 0.0f; break;
			case SDLK_UP: keyMap["up"] = 0.0f;  break;
			case SDLK_DOWN: keyMap["down"] = 0.0f; break;
			case SDLK_SPACE:keyMap["space"] = 0.0f; break;
			case SDLK_q:keyMap["q"] = 0.0f; break;
			case SDLK_w:keyMap["w"] = 0.0f; break;
			case SDLK_e:keyMap["e"] = 0.0f; break;
			case SDLK_r:keyMap["r"] = 0.0f; break;
			case SDLK_t:keyMap["t"] = 0.0f; break;
			case SDLK_i:keyMap["i"] = 0.0f; break;
			case SDLK_p:keyMap["p"] = 0.0f; break;
			case SDLK_a:keyMap["a"] = 0.0f; break;
			case SDLK_s:keyMap["s"] = 0.0f; break;
			case SDLK_d:keyMap["d"] = 0.0f; break;
			case SDLK_f:keyMap["f"] = 0.0f; break;
			case SDLK_j:keyMap["j"] = 0.0f; break;
			case SDLK_k:keyMap["k"] = 0.0f; break;
			case SDLK_l:keyMap["l"] = 0.0f; break;
			case SDLK_c:keyMap["c"] = 0.0f; break;
			case SDLK_v:keyMap["v"] = 0.0f; break;
			case SDLK_b:keyMap["b"] = 0.0f; break;
			case SDLK_n:keyMap["n"] = 0.0f; break;
			case SDLK_m:keyMap["m"] = 0.0f; break;
			default: resetKeys(); break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (Evnt.button.button)
			{
			case SDL_BUTTON_LEFT: {
				break;
			}
			case SDL_BUTTON_RIGHT: {
				break;
			}
			default:break;
			}
		case SDL_MOUSEMOTION: {
			break;
		}
		default: break;
		}
	}
	//SDL_PumpEvents();
	//keyState = SDL_GetKeyboardState(NULL);
}

void InputSystem::handleInput()
{
	if (keyMap["up"] == 1.0f)	EventHandler<InputEvent>::notify(InputEvent::UP_PRESSED);
	else
		EventHandler<InputEvent>::notify(InputEvent::UP_RELEASED);

	if (keyMap["down"] == 1.0f) EventHandler<InputEvent>::notify(InputEvent::DOWN_PRESSED);
	else
		EventHandler<InputEvent>::notify(InputEvent::DOWN_RELEASED);
	if (keyMap["left"] == 1.0f) EventHandler<InputEvent>::notify(InputEvent::LEFT_PRESSED);
	else
		if (keyMap["right"] == 1.0f) EventHandler<InputEvent>::notify(InputEvent::RIGHT_PRESSED);
		else
			EventHandler<InputEvent>::notify(InputEvent::RIGHT_RELEASED);
	if (keyMap["space"] == 1.0f) EventHandler<InputEvent>::notify(InputEvent::SPACE_PRESSED);
	else
		EventHandler<InputEvent>::notify(InputEvent::SPACE_RELEASED);
}

bool InputSystem::hasQuit()
{
	return quit;
}
