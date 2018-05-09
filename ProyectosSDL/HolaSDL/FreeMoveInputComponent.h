#pragma once

#include "InputComponent.h"
#include "Fighter.h"
#include "Observable.h"

/*
 *
 */
class FreeMoveInputComponent : public InputComponent, public Observable {
public:
	FreeMoveInputComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, Uint8 maxSpeed, Uint8 degree);
	virtual ~FreeMoveInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	void sendPlayerState(Fighter* f);
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode up_;
	SDL_Keycode down_;
	Uint8 maxSpeed_;
	Uint8 degree_;
};

