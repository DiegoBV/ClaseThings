#include "GameState.h"
#include "Game.h"


GameState::GameState()
{
}

void GameState::handleEvent(SDL_Event &e) {
	bool handled = false;
	list<GameObject*>::iterator it = stage.begin();
	while (!handled && it != stage.end()) {
		if ((*it)->handleEvent(e)) { handled = true; }
		else { it++; }
	}
}