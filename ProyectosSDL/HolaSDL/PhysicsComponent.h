#pragma once

#include "GameObject.h"

/*
 *
 */
class PhysicsComponent {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update(GameObject* o, Uint32 time) = 0;
};

