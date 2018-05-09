#include "CircularMotionPhysics.h"

CircularMotionPhysics::CircularMotionPhysics() {
}

CircularMotionPhysics::~CircularMotionPhysics() {
}

void CircularMotionPhysics::init(GameObject* o) {
}

void CircularMotionPhysics::update(GameObject* o, Uint32 time) {
	if (o->isActive()) {
		Vector2D p = o->getPosition()+o->getVelocity();

		if (p.getX() >= o->getGame()->getWindowWidth()) {
			p.setX(-o->getWidth()*0.1);
		} else if (p.getX() + o->getWidth() <= 0) {
			p.setX(o->getGame()->getWindowWidth()-o->getWidth()*0.1);
		}

		if (p.getY() >= o->getGame()->getWindowHeight()) {
			p.setY(-o->getHeight()*0.1);
		} else if (p.getY() + o->getHeight() <= 0) {
			p.setY(o->getGame()->getWindowHeight()-o->getWidth()*0.1);
		}

		o->setPosition(p);
	}
}

