#include "PaddleMouseInputComponent.h"

PaddleMouseInputComponent::PaddleMouseInputComponent() {
}

PaddleMouseInputComponent::~PaddleMouseInputComponent() {
}

void PaddleMouseInputComponent::handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector2D position = o->getPosition();
		position.setY(y);
		o->setPosition(position);
		o->setVelocity(Vector2D(0, 0));
	}
}
