#include "RotationPhysics.h"



RotationPhysics::RotationPhysics(): angle(rand()% 3 + 1)
{
}


RotationPhysics::~RotationPhysics()
{
}

void RotationPhysics::update(GameObject* o, Uint32 time) {
	rotate(o);
}

void RotationPhysics::rotate(GameObject* o) {
	Vector2D rot = o->getDirection();

	rot.rotate(angle);

	o->setDirection(rot);
}
