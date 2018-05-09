#include "FillRectRenderer.h"

FillRectRenderer::FillRectRenderer() :
		color_( { COLOR(0xffffffff) }) {
}

FillRectRenderer::FillRectRenderer(SDL_Color color) :
		color_(color) {
}

FillRectRenderer::~FillRectRenderer() {
}

void FillRectRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
	RECT(o->getPosition().getX(), o->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_SetRenderDrawColor(o->getGame()->getRenderer(), COLOREXP(color_));
	SDL_RenderFillRect(o->getGame()->getRenderer(), &rect);
}

