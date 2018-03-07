#include "RotationComponent.h"


RotationComponent::RotationComponent()
{
}

RotationComponent::RotationComponent(double angle, SDL_Keycode clockwise, SDL_Keycode counter_clockwise): angle(angle), clockwise(clockwise), counter_clockwise(counter_clockwise){

}

RotationComponent::~RotationComponent()
{
}

void RotationComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event){
	if (event.key.keysym.sym == clockwise){
		rotate(o, -1);
	}
	else if (event.key.keysym.sym == counter_clockwise){
		rotate(o, 1);
	}
}

void RotationComponent::rotate(GameObject* o, double aux){
	Vector2D rot = o->getDirection();

	rot.rotate(angle*aux);

	o->setDirection(rot);
}
