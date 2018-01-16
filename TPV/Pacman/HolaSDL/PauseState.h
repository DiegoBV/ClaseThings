#pragma once
#include "GameState.h"
#include "MenuButton.h"
const int numTexturaResume = 10;
const int numTexturaQuit = 11;
class PauseState: public GameState
{
private:
	Texture* bckgrnd;
public:
	PauseState();
	~PauseState();
	PauseState(SDLApp* app, Texture* bckgrnd) : bckgrnd(bckgrnd), GameState(app) {
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura/4, app->winHeight / 2 + altura/2, anchura/2, altura/2, app->texts[numTexturaResume], resume, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura /4, app->winHeight / 2 + altura*2, anchura/2, altura/2, app->texts[numTexturaQuit], quit, app));
	}

	virtual void render() { this->bckgrnd->Render(app->renderer); GameState::render(); }
	virtual void handleEvent(SDL_Event& e) {
		GameState::handleEvent(e);
	}
	static void resume(SDLApp* app){ app->getStateMachine()->popState();} //ni tan mal, funciona y todo
	static void quit(SDLApp* app) { app->setExit(true); }
};

