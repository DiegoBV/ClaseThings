#ifndef PADDLEWITHAI_H_
#define PADDLEWITHAI_H_

#include "Paddle.h"

/*
 *
 */
class PaddleWithAI: public Paddle {
public:
	PaddleWithAI(SDLGame* game, GameObject* ball);
	virtual ~PaddleWithAI();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
private:
	bool ballCommingTowardPaddle();
	GameObject* ball_;
};

#endif /* PADDLEWITHAI_H_ */
