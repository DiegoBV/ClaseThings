#ifndef PADDLEWITHAIWITHTRANSRECT_H_
#define PADDLEWITHAIWITHTRANSRECT_H_

#include "PaddleWithAI.h"

/*
 *
 */
class PaddleWithAIWithTransRect: public PaddleWithAI {
public:
	PaddleWithAIWithTransRect(SDLGame* game, GameObject* ball);
	virtual ~PaddleWithAIWithTransRect();
	virtual void render(Uint32 time);
};

#endif /* PADDLEWITHAIWITHTRANSRECT_H_ */
