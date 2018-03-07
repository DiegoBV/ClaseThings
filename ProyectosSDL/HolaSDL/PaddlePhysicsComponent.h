#ifndef PADDLEPHYSICSCOMPONENT_H_
#define PADDLEPHYSICSCOMPONENT_H_

#include "PhysicsComponent.h"

/*
 *
 */
class PaddlePhysicsComponent: public PhysicsComponent {
public:
	PaddlePhysicsComponent();
	virtual ~PaddlePhysicsComponent();
	virtual void update(GameObject* o, Uint32 time);
};

#endif /* PADDLEPHYSICSCOMPONENT_H_ */
