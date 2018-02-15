#ifndef PADDLEWITHTRANSRECT_H_
#define PADDLEWITHTRANSRECT_H_

#include "Paddle.h"

/*
 *
 */
class PaddleWithTransRect: public Paddle {
public:
	PaddleWithTransRect(SDLGame* game, SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~PaddleWithTransRect();
	virtual void render(Uint32 time);
};

#endif /* PADDLEWITHTRANSRECT_H_ */
