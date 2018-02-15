#include "PaddleWithAI.h"

PaddleWithAI::PaddleWithAI(SDLGame* game, GameObject* ball) : Paddle(game, SDLK_a, SDLK_b, SDLK_c), ball_(ball) {

}

PaddleWithAI::~PaddleWithAI() {
}

void PaddleWithAI::handleInput(Uint32 time, const SDL_Event& event) {
}

void PaddleWithAI::update(Uint32 time) {

	if (ballCommingTowardPaddle()) {
		double diff = ball_->getPosition().getY() -( position_.getY() + height_ / 2);
		if ( abs(diff) > 10 ) {
			velocity_.setY(1.5*ball_->getVelocity().magnitude() * (diff>0 ? 1 : -1) );
		} else  {
			velocity_.setY(0);
		}
	} else {
		double diff = (game_->getWindowHeight() / 2)
				- (position_.getY() + height_ / 2);
		if (abs(diff) > 10) {
			velocity_.setY(5 * (diff>0 ? 1 : -1));
		} else {
			velocity_.setY(0);
		}
	}

	Paddle::update(time);
}

bool PaddleWithAI::ballCommingTowardPaddle() {
	return (position_.getX() < ball_->getPosition().getX() && ball_->getVelocity().getX() < 0) ||
			(position_.getX() > ball_->getPosition().getX() && ball_->getVelocity().getX() > 0);
}
