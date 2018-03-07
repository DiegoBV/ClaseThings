#include "PaddlePhysicsComponent.h"

PaddlePhysicsComponent::PaddlePhysicsComponent() {
}

PaddlePhysicsComponent::~PaddlePhysicsComponent() {
}

void PaddlePhysicsComponent::update(GameObject* o, Uint32 time) {

	Vector2D position = o->getPosition();
	Vector2D velocity = o->getVelocity();

	position = position + velocity;
	double x = position.getX();
	double y = position.getY();

	if (y <= 0) {
		y = 0;
		velocity.setY(0);
	}

	if (y+o->getHeight() >= o->getGame()->getWindowHeight()) {
		y = o->getGame()->getWindowHeight()-o->getHeight();
		velocity.setY(0);
	}

	position.setX(x);
	position.setY(y);

	o->setVelocity(velocity);
	o->setPosition(position);
}
