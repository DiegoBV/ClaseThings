#include "BounceOnBordersPhysics.h"

BounceOnBordersPhysics::BounceOnBordersPhysics(bool left, bool right, bool up,
		bool down) :
		left_(left), right_(right), up_(up), down_(down) {

}

BounceOnBordersPhysics::~BounceOnBordersPhysics() {
}

void BounceOnBordersPhysics::update(GameObject* o, Uint32 time) {
	Vector2D velocity_ = o->getVelocity();
	Vector2D position_ = o->getPosition()+velocity_;

	double height = o->getHeight();
	double width = o->getWidth();

	double y = position_.getY();
	double x = position_.getX();


	if ( down_ && y+height >= o->getGame()->getWindowHeight() ) {
		velocity_.setY( -velocity_.getY() );
		o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}

	if (up_ && y <= 0 ) {
		velocity_.setY( -velocity_.getY() );
		o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}

	if ( right_ && x+width >= o->getGame()->getWindowWidth() ) {
		velocity_.setX( -velocity_.getX() );
		o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}

	if (left_ && x <= 0 ) {
		velocity_.setX( -velocity_.getX() );
		o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}

	o->setPosition(position_);
	o->setVelocity(velocity_);

}
