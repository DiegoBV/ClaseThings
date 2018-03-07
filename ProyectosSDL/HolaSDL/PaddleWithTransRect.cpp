#include "PaddleWithTransRect.h"

PaddleWithTransRect::PaddleWithTransRect(SDLGame* game, SDL_Keycode up,
		SDL_Keycode down, SDL_Keycode stop) :
		Paddle(game, up, down, stop) {
	// TODO Auto-generated constructor stub

}

PaddleWithTransRect::~PaddleWithTransRect() {
	// TODO Auto-generated destructor stub
}

void PaddleWithTransRect::render(Uint32 time) {
	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderDrawRect(game_->getRenderer(), &rect);
}
