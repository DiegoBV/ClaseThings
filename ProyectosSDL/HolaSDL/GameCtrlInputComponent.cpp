#include "GameCtrlInputComponent.h"
#include "GameManager.h"

GameCtrlInputComponent::GameCtrlInputComponent() {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_RETURN) {
			if (!gm->isRunning()) {
				gm->setRunning(true);
				gm->send(&(Message(ROUND_START)));
				if (gm->isGameOver()) {
				}
			}
		}
	}
}
