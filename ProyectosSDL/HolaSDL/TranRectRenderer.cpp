#include "TranRectRenderer.h"

TranRectRenderer::TranRectRenderer() {
	// TODO Auto-generated constructor stub

}

TranRectRenderer::~TranRectRenderer() {
	// TODO Auto-generated destructor stub
}

void TranRectRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());

	SDL_SetRenderDrawColor(o->getGame()->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderDrawRect(o->getGame()->getRenderer(), &rect);
}
