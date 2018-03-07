#include "Ball.h"

Ball::Ball(SDLGame* game) : GameObject(game) {

}

Ball::~Ball() {
}

void Ball::handleInput(Uint32 time, const SDL_Event& event) {
}

void Ball::update(Uint32 time) {
	position_ = position_+velocity_;
	double y = position_.getY();


	if ( y+height_ >= game_->getWindowHeight() ) {
		velocity_.setY( -velocity_.getY() );
		game_->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	} else if (y <= 0 ) {
		velocity_.setY( -velocity_.getY() );
		game_->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}
}

void Ball::render(Uint32 time) {
	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x1111ffff));
	SDL_RenderFillRect(game_->getRenderer(), &rect);
}
