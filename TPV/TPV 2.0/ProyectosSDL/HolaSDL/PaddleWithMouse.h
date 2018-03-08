#ifndef PADDLEWITHMOUSE_H_
#define PADDLEWITHMOUSE_H_

#include "Paddle.h"

/*
 *
 */
class PaddleWithMouse: public Paddle {
public:
	PaddleWithMouse(SDLGame* game);
	virtual ~PaddleWithMouse();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
};

#endif /* PADDLEWITHMOUSE_H_ */
