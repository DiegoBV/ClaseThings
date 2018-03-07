#include "FillRectRenderer.h"

FillRectRenderer::FillRectRenderer() {
}

FillRectRenderer::~FillRectRenderer() {
}

void FillRectRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());

	SDL_SetRenderDrawColor(o->getGame()->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderFillRect(o->getGame()->getRenderer(), &rect);
}
