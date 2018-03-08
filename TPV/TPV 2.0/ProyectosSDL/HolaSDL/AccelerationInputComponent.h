#pragma once
#include "InputComponent.h"
class AccelerationInputComponent :
	public InputComponent
{
private:
	SDL_Keycode accelerate;
	SDL_Keycode decelerate;
	double thrust;
	double reductionFactor;
	double limit;
public:
	AccelerationInputComponent();
	virtual ~AccelerationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);

	AccelerationInputComponent(SDL_Keycode accelerate, SDL_Keycode decelerate, double thrust, double reductionFactor, double limit) : InputComponent(), accelerate(accelerate), 
		decelerate(decelerate), thrust(thrust), reductionFactor(reductionFactor), limit(limit) {}; //constructora que recibe las teclas

	void acelerar(GameObject* o);
	void frenar(GameObject* o);
};

