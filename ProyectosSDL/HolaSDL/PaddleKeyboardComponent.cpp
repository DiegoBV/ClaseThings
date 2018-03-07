#include "PaddleKeyboardComponent.h"

PaddleKeyboardComponent::PaddleKeyboardComponent(SDL_Keycode up,
		SDL_Keycode down, SDL_Keycode stop) :
		up_(up), down_(down), stop_(stop) {

}

PaddleKeyboardComponent::~PaddleKeyboardComponent() {
}

void PaddleKeyboardComponent::handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event) {

	Vector2D velocity = o->getVelocity();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == up_) {
			velocity = velocity + Vector2D(0, -2);
		} else if (event.key.keysym.sym == down_) {
			velocity = velocity + Vector2D(0, 2);
		} else if (event.key.keysym.sym == stop_) {
			velocity.set(0, 0);
		}
	}

	o->setVelocity(velocity);
}
