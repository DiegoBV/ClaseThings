#ifndef BASICMOTIONPHYSICS_H_
#define BASICMOTIONPHYSICS_H_

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

#endif /* BASICMOTIONPHYSICS_H_ */
