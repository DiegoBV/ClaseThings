#ifndef BOUNCEONBORDERSPHYSICS_H_
#define BOUNCEONBORDERSPHYSICS_H_

#include "PhysicsComponent.h"

/*
 *
 */
class BounceOnBordersPhysics: public PhysicsComponent {
public:
	BounceOnBordersPhysics(bool left, bool right, bool up, bool down);
	virtual ~BounceOnBordersPhysics();
	virtual void update(GameObject* o, Uint32 time);
private:
	bool left_;
	bool right_;
	bool up_;
	bool down_;
};

#endif /* BOUNCEONBORDERSPHYSICS_H_ */
