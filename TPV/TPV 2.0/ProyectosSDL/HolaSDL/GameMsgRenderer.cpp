#include "GameMsgRenderer.h"
#include "GameManager.h"

GameMsgRenderer::GameMsgRenderer() {
	// TODO Auto-generated constructor stub

}

GameMsgRenderer::~GameMsgRenderer() {
	// TODO Auto-generated destructor stub
}

void GameMsgRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game_ = gm->getGame();

	// press any key message when game is not running
	if (!gm->isRunning()) {
		Texture* hitanykey = game_->getResources()->getTextTexture(
				Resources::PresAnyKey);
		hitanykey->render(game_->getRenderer(),
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (gm->isGameOver()) {
		Texture* gameOver = game_->getResources()->getTextTexture(
				Resources::GameOver);
		gameOver->render(game_->getRenderer(),
				game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}
