#include "Paddle.h"

Paddle::Paddle(SDLGame* game, SDL_Keycode up, SDL_Keycode down,
		SDL_Keycode stop) :
		GameObject(game), up_(up), down_(down), stop_(stop) {
	// TODO Auto-generated constructor stub

}

Paddle::~Paddle() {
}

void Paddle::handleInput(Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == up_) {
			velocity_ = velocity_ + Vector2D(0, -2);
		} else if (event.key.keysym.sym == down_) {
			velocity_ = velocity_ + Vector2D(0, 2);
		} else if (event.key.keysym.sym == stop_) {
			velocity_.set(0, 0);
		}
	}

}

void Paddle::update(Uint32 time) {
	position_ = position_ + velocity_;
	double x = position_.getX();
	double y = position_.getY();

	if (y <= 0) {
		y = 0;
		velocity_.setY(0);
	}

	if (y+height_ >= game_->getWindowHeight()) {
		y = game_->getWindowHeight()-height_;
		velocity_.setY(0);
	}

	position_.setX(x);
	position_.setY(y);

}

void Paddle::render(Uint32 time) {
	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderFillRect(game_->getRenderer(), &rect);

}
