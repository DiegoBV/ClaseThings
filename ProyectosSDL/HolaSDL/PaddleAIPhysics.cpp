#include "PaddleAIPhysics.h"

PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
		ball_(ball) {

}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::update(GameObject* o, Uint32 time) {
	Vector2D velocity = o->getVelocity();
	Vector2D position = o->getPosition();

	double height_ = o->getHeight();

	if (ballComingTowardPaddle(o)) {
		double diff = ball_->getPosition().getY()
				- (position.getY() + height_ / 2);
		if (abs(diff) > 10) {
			velocity.setY(
					1.5 * ball_->getVelocity().magnitude()
							* (diff > 0 ? 1 : -1));
		} else {
			velocity.setY(0);
		}
	} else {
		double diff = (o->getGame()->getWindowHeight() / 2)
				- (position.getY() + height_ / 2);
		if (abs(diff) > 10) {
			velocity.setY(5 * (diff > 0 ? 1 : -1));
		} else {
			velocity.setY(0);
		}
	}

	o->setVelocity(velocity);

	PaddlePhysicsComponent::update(o, time);

}

bool PaddleAIPhysics::ballComingTowardPaddle(GameObject* o) {
	Vector2D position = o->getPosition();

	return (position.getX() < ball_->getPosition().getX()
			&& ball_->getVelocity().getX() < 0)
			|| (position.getX() > ball_->getPosition().getX()
					&& ball_->getVelocity().getX() > 0);
}
