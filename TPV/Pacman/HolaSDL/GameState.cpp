#include "GameState.h"



GameState::GameState()
{
}

void GameState::handleEvents(SDL_Event &e) {
	bool handled = false;
	list<GameObject*>::iterator it = stage.begin();
	/*while (it != stage.end() && !handled) {
		if ((*it)->handleEvent(e)) { handled = true; }
		else { it++; }
	}*/
}