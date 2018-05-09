#include "RotationPhysics.h"

RotationPhysics::RotationPhysics(int angle) : angle_(angle) {
}

RotationPhysics::~RotationPhysics() {
}

void RotationPhysics::update(GameObject* o, Uint32 time) {
	Vector2D d = o->getDirection();
	d.rotate(angle_);
	o->setDirection(d);
}
