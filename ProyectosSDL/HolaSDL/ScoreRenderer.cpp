#include "ScoreRenderer.h"
#include "GameManager.h"

ScoreRenderer::ScoreRenderer() {
}

ScoreRenderer::~ScoreRenderer() {
}

void ScoreRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	// draw score
	Texture score(o->getGame()->getRenderer(),
			std::to_string(gm->getScore()),
			*(game->getResources()->getFont(Resources::ARIAL24)),
			{ COLOR(0x111122ff) });
	score.render(game->getRenderer(),
			game->getWindowWidth() / 2 - score.getWidth() / 2, 10);

}
