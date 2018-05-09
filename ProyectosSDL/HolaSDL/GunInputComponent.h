#pragma once

#include "InputComponent.h"
#include "BulletsManager.h"
#include "Observable.h"
#include "Fighter.h"

/*
 *
 */
class GunInputComponent: public InputComponent, public Observable {
public:
	GunInputComponent(SDL_Keycode shootButton, Uint32 timeInterval,
			Uint8 shotsPerInterval);
	virtual ~GunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time,
			const SDL_Event& event);

private:
	void shoot(Fighter* o);

	SDL_Keycode shootButton_;
	Uint32 lastTimeShoot_;
	Uint8 numOfShoots_;
	Uint32 timeInterval_;
	Uint8 shotsPerInterval_;

};

