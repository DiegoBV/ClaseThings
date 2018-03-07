#include "PaddleWithMouseWithTransRect.h"

PaddleWithMouseWithTransRect::PaddleWithMouseWithTransRect(SDLGame* game) : PaddleWithMouse(game) {

}

PaddleWithMouseWithTransRect::~PaddleWithMouseWithTransRect() {
	// TODO Auto-generated destructor stub
}

void PaddleWithMouseWithTransRect::render(Uint32 time) {
	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderDrawRect(game_->getRenderer(), &rect);
}
