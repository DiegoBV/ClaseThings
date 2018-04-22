#pragma once
#include "PhysicsComponent.h"
class CircularMotionPhysics :
	public PhysicsComponent
{
public:
	CircularMotionPhysics();
	virtual ~CircularMotionPhysics();
	virtual void update(GameObject* o, Uint32 time);
};

