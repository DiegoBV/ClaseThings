#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class BasicMotionPhysics: public PhysicsComponent {
public:
	BasicMotionPhysics();
	virtual ~BasicMotionPhysics();
	virtual void update(GameObject* o, Uint32 time);
private:
};

