#include "ConnectedPlayersRenderer.h"

#include "GameManager.h"

ConnectedPlayersRenderer::ConnectedPlayersRenderer() {
}

ConnectedPlayersRenderer::~ConnectedPlayersRenderer() {
}

void ConnectedPlayersRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	if (gm->getState() == GameManager::WAITING) {
		// draw score
		Texture score(o->getGame()->getRenderer(),
				"Connected Players: "
						+ std::to_string(gm->getNumOfConnectedPlayers()),
				*(game->getResources()->getFont(Resources::ARIAL24)),
				{ COLOR(0xffffffff) });
		score.render(game->getRenderer(), 10, 10);
	}

}
