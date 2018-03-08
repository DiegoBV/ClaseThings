#include "PaddleWithMouse.h"

PaddleWithMouse::PaddleWithMouse(SDLGame* game) : Paddle(game,SDLK_a,SDLK_b,SDLK_c) {

}

PaddleWithMouse::~PaddleWithMouse() {
	// TODO Auto-generated destructor stub
}

void PaddleWithMouse::handleInput(Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION ) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		position_.setY(y);
	}
}
