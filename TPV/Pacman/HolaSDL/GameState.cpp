#include "GameState.h"
#include "Game.h"


GameState::GameState()
{
}

void GameState::handleEvent(SDL_Event &e) { //manda a los objetos del juego que detecten eventos
	bool handled = false;
	list<GameObject*>::iterator it = stage.begin();
	while (!handled && it != stage.end()) {
		if ((*it)->handleEvent(e)) { handled = true; } //para la ejecucion, para evitar posibles fallos
		else { it++; }
	}
}