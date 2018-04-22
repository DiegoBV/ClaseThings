#pragma once
#include "InputComponent.h"
#include "GameObject.h"
class RotationComponent :
	public InputComponent
{
private:
	SDL_Keycode clockwise, counter_clockwise;
	double angle;

public:
	RotationComponent();
	virtual ~RotationComponent();
	RotationComponent(double angle, SDL_Keycode clockwise, SDL_Keycode counter_clockwise);
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	void rotate(GameObject* o, double aux);
};

