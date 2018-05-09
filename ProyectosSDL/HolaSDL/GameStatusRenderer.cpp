#include "GameStatusRenderer.h"
#include "GameManager.h"

GameStatusRenderer::GameStatusRenderer() {
	// TODO Auto-generated constructor stub

}

GameStatusRenderer::~GameStatusRenderer() {
	// TODO Auto-generated destructor stub
}

void GameStatusRenderer::render(GameObject* o, Uint32 time) {

	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game_ = gm->getGame();

	Texture* msg_ = nullptr;

	// show WAITING or PRESS ENTER messgae
	switch (gm->getState()) {
	case GameManager::WAITING:
		msg_ = game_->getResources()->getTextTexture(Resources::Waiting);
		msg_->render(game_->getRenderer(),
				game_->getWindowWidth() / 2 - msg_->getWidth() / 2,
				game_->getWindowHeight() - msg_->getHeight() - 50);
		break;
	case GameManager::READY:
	case GameManager::OVER:
		msg_ = game_->getResources()->getTextTexture(
				Resources::PressEnterToStart);
		msg_->render(game_->getRenderer(),
				game_->getWindowWidth() / 2 - msg_->getWidth() / 2,
				game_->getWindowHeight() - msg_->getHeight() - 50);
		break;
	default:
		break;
	}

	// show GAME OVER message if needed
	if (gm->getState() == GameManager::OVER) {
		msg_ = game_->getResources()->getTextTexture(Resources::GameOver);
		msg_->render(game_->getRenderer(),
				game_->getWindowWidth() / 2 - msg_->getWidth() / 2,
				game_->getWindowHeight() - msg_->getHeight() - 150);
	}

}
