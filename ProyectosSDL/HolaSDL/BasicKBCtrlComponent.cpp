#include "BasicKBCtrlComponent.h"

BasicKBCtrlComponent::BasicKBCtrlComponent(SDL_Keycode left,
		SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop) :
		left_(left), right_(right), up_(up), down_(down), stop_(stop) {
}

BasicKBCtrlComponent::~BasicKBCtrlComponent() {
}

void BasicKBCtrlComponent::handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event) {

	Vector2D velocity = o->getVelocity();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == left_) {
			velocity.set(-1,0);
		} else if (event.key.keysym.sym == right_) {
			velocity.set(1,0);
		} else if (event.key.keysym.sym == up_) {
			velocity.set(0,-1);
		} else if (event.key.keysym.sym == down_) {
			velocity.set(0,1);
		} else if (event.key.keysym.sym == stop_) {
			velocity.set(0, 0);
		}
	}

	o->setVelocity(velocity);
}
