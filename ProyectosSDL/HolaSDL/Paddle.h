#ifndef PADDLE_H_
#define PADDLE_H_

#include "GameObject.h"

/*
 *
 */
class Paddle: public GameObject {
public:
	Paddle(SDLGame* game, SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~Paddle();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode stop_;
};

#endif /* PADDLE_H_ */
