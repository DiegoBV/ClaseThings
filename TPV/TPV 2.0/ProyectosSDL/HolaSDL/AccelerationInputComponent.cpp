#include "AccelerationInputComponent.h"



AccelerationInputComponent::AccelerationInputComponent()
{
}


AccelerationInputComponent::~AccelerationInputComponent()
{
}

void AccelerationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == accelerate) {
			acelerar(o);
		}
		else if (event.key.keysym.sym == decelerate) {
			frenar(o);
		}
	}
}

void AccelerationInputComponent::acelerar(GameObject* o) {
	Vector2D dir = o->getDirection();
	dir.setX(-dir.getX());
	Vector2D newVel = o->getVelocity() + dir * thrust;

	if (newVel.magnitude() > limit) {
		newVel.normalize(); //limite de velocidad sobrepasado, se reduce su magnitud a 1
		newVel = newVel * limit;
	}

	o->setVelocity(newVel);
}

void AccelerationInputComponent::frenar(GameObject* o) {
	Vector2D newVel = o->getVelocity() * reductionFactor;

	if (newVel.magnitude() < 0.1) {
		newVel.setX(0);
		newVel.setY(0);
	}

	o->setVelocity(newVel);
}
