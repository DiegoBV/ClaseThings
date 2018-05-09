#include "GunInputComponent.h"
#include <algorithm>
#include <math.h>

GunInputComponent::GunInputComponent(SDL_Keycode shootButton,
		Uint32 timeInterval, Uint8 shotsPerInterval) :
		InputComponent(), shootButton_(shootButton), timeInterval_(
				timeInterval), shotsPerInterval_(shotsPerInterval) {
	lastTimeShoot_ = 0;
	numOfShoots_ = 0;
}

GunInputComponent::~GunInputComponent() {
}

void GunInputComponent::handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == shootButton_) {
		if (time - lastTimeShoot_ > timeInterval_) {
			lastTimeShoot_ = time;
			numOfShoots_ = 0;
		}
		if (numOfShoots_ < shotsPerInterval_) {
			numOfShoots_++;
			shoot(static_cast<Fighter*>(o));
		}
	}
}

void GunInputComponent::shoot(Fighter* o) {
	Vector2D bulletPoition = o->getPosition()
			+ Vector2D(o->getWidth() / 2, o->getHeight() / 2)
			+ (o->getDirection() * ((o->getHeight() / 2) + 2));
	Vector2D bulletVelocity = o->getDirection()
			* std::max(o->getVelocity().magnitude() * 2, 2.0);
	FighterIsShootingMsg msg = { o->getId(), bulletPoition, bulletVelocity };
	send(&msg);
}
