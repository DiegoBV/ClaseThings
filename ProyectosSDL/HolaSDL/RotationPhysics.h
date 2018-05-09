#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class RotationPhysics: public PhysicsComponent {
public:
	RotationPhysics(int angle);
	virtual ~RotationPhysics();
	virtual void update(GameObject* o, Uint32 time);
private:
	int angle_;
};

