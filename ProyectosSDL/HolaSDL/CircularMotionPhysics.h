#pragma once

#include "PhysicsComponent.h"

class CircularMotionPhysics: public PhysicsComponent {
public:
	CircularMotionPhysics();
	virtual ~CircularMotionPhysics();
	void init(GameObject *o);
	void update(GameObject *o, Uint32 time);
};

