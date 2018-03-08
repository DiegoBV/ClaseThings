#include "DemoActor.h"
#include "SDLGame.h"

DemoActor::DemoActor(SDLGame* game) :
		GameObject(game) {
}

DemoActor::~DemoActor() {
}

void DemoActor::handleInput(Uint32 time, const SDL_Event& event) {
	if ( event.type == SDL_KEYDOWN ) {
		switch ( event.key.keysym.sym ) {
		case SDLK_UP:
			velocity_ = velocity_+Vector2D(0,-1);
			break;
		case SDLK_DOWN:
			velocity_ = velocity_+Vector2D(0,1);
			break;
		case SDLK_RIGHT:
			velocity_ = velocity_+Vector2D(1,0);
			break;
		case SDLK_LEFT:
			velocity_ = velocity_+Vector2D(-1,0);
			break;
		case SDLK_SPACE:
			velocity_ = Vector2D(0,0);
			break;
		}
	}
}

void DemoActor::update(Uint32 time) {
	position_ = position_+velocity_;
	double x = position_.getX();
	double y = position_.getY();

	if ( x >= game_->getWindowWidth() ) {
		x = 0;
	} else if (x+width_ <= 0 ) {
		x =  game_->getWindowWidth()-width_;
	}

	if ( y >= game_->getWindowHeight() ) {
		y = 0;
	} else if (y+height_ <= 0 ) {
		y =  game_->getWindowHeight()-height_;
	}

	position_.setX(x);
	position_.setY(y);
}

void DemoActor::render(Uint32 time) {

	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderFillRect(game_->getRenderer(), &rect);

	/*
	game_->getResources()->getTextTexture(SDLGame::HelloWorld)->render(
			game_->getRenderer(), dest);
			*/
}
