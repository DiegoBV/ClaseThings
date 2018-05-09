#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class DeActivateOnBorderExit: public PhysicsComponent {
public:
	DeActivateOnBorderExit();
	virtual ~DeActivateOnBorderExit();
	virtual void update(GameObject* o, Uint32 time);
};
