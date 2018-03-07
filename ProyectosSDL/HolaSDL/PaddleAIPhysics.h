#ifndef PADDLEAIPHYSICS_H_
#define PADDLEAIPHYSICS_H_

#include "PhysicsComponent.h"
#include "PaddlePhysicsComponent.h"
/*
 *
 */
class PaddleAIPhysics: public PaddlePhysicsComponent /*PhysicsComponent*/ {
public:
	PaddleAIPhysics(GameObject* ball);
	virtual ~PaddleAIPhysics();
	virtual void update(GameObject* o, Uint32 time);
private:
	bool ballComingTowardPaddle(GameObject* o);

	GameObject* ball_;
};

#endif /* PADDLEAIPHYSICS_H_ */
