#include "FreeMoveInputComponent.h"

FreeMoveInputComponent::FreeMoveInputComponent(SDL_Keycode left,
		SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, Uint8 maxSpeed,
		Uint8 degree) :
		left_(left), right_(right), up_(up), down_(down), maxSpeed_(maxSpeed), degree_(
				degree) {
}

FreeMoveInputComponent::~FreeMoveInputComponent() {
	// TODO Auto-generated destructor stub
}

void FreeMoveInputComponent::handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		Vector2D v = o->getVelocity();
		Vector2D d = o->getDirection();

		if (event.key.keysym.sym == left_) {
			d.rotate(-degree_);
			v.rotate(-degree_);
		} else if (event.key.keysym.sym == right_) {
			d.rotate(degree_);
			v.rotate(degree_);
		} else if (event.key.keysym.sym == up_) {
			if (v.magnitude() == 0)
				v = d;
			else
				v = v * 1.1;
			if (v.magnitude() > maxSpeed_) {
				v.normalize();
				v = v * maxSpeed_;
			}

		} else if (event.key.keysym.sym == down_) {
			v = v * 0.9;
			if (v.magnitude() < 0.1)
				v = Vector2D(0, 0);
		}
		o->setVelocity(v);
		o->setDirection(d);
		sendPlayerState(static_cast<Fighter*>(o));
	}
}

void FreeMoveInputComponent::sendPlayerState(Fighter* f) {
	FighterStateMsg msg = { f->getId(), f->getPosition(), f->getDirection(),
			f->getVelocity(), f->getWidth(), f->getHeight() };
	send(&msg);
}

