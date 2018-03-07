#include "PaddleWithAIWithTransRect.h"

PaddleWithAIWithTransRect::PaddleWithAIWithTransRect(SDLGame* game, GameObject* ball)  : PaddleWithAI(game, ball) {

}

PaddleWithAIWithTransRect::~PaddleWithAIWithTransRect() {
}

void PaddleWithAIWithTransRect::render(Uint32 time) {
	SDL_Rect rect RECT(position_.getX(),position_.getY(),width_,height_);

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderDrawRect(game_->getRenderer(), &rect);
}
