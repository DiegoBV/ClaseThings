#ifndef BALL_H_
#define BALL_H_

#include "GameObject.h"

/*
 *
 */
class Ball: public GameObject {
public:
	Ball(SDLGame* game);
	virtual ~Ball();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
};

#endif /* BALL_H_ */
