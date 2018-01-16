#pragma once
#include "GameState.h"
#include "MenuButton.h"
class PauseState: public GameState
{
public:
	PauseState();
	~PauseState();
	PauseState(SDLApp* app/*puntero a game probablemente*/) : GameState(app) {
		stage.push_back(new MenuButton(app->winWidth / 2, app->winHeight / 2, 50, 50, app->texts[6], app));
	}

	virtual void render() {GameState::render(); }
	virtual void handleEvent(SDL_Event& e) {
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			this->app->getStateMachine()->popState(); //ni tan mal, funciona y todo, quedan los botones que espero que explique hoy en clasee
		}
	}
};

