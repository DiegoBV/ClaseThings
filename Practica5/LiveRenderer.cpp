#include "LiveRenderer.h"
#include "GameManager.h"


LiveRenderer::LiveRenderer()
{
}


LiveRenderer::~LiveRenderer()
{
}

void LiveRenderer::render(GameObject* o, Uint32 time) {
	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	if (gm->getLives() > 0) {
		for (unsigned int i = 0; i < gm->getLives(); i++) {
			Texture* aux = game->getResources()->getImageTexture(Resources::Vida);
			aux->render(game->getRenderer(), (i+1)*aux->getWidth() , 10);
		}
	}
}
