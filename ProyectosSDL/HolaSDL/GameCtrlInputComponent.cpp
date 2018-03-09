#include "GameCtrlInputComponent.h"
#include "GameManager.h"

GameCtrlInputComponent::GameCtrlInputComponent() {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {

		// if any key pressed while not running, we choose a random velocity of the ball
		if (!gm->isRunning()) {
			gm->setRunning(true);
			gm->send(&(Message(ROUND_START)));
			// rest the score if the game is over
			if (gm->isGameOver()) {
				gm->setLeftScore(0);
				gm->setRightScore(0);
			}
		}
	}

}
