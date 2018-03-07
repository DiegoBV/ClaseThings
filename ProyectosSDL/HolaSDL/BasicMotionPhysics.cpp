#include "BasicMotionPhysics.h"

BasicMotionPhysics::BasicMotionPhysics() {

}

BasicMotionPhysics::~BasicMotionPhysics() {
}

void BasicMotionPhysics::update(GameObject* o, Uint32 time) {
	o->setPosition(o->getPosition() + o->getVelocity());
}
