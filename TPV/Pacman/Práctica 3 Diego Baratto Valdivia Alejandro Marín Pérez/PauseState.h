#pragma once
#include "GameState.h"
#include "MenuButton.h"
class PauseState: public GameState
{
private:
	Texture* bckgrnd;
public:
	PauseState();
	~PauseState();
	PauseState(SDLApp* app, Texture* bckgrnd) : bckgrnd(bckgrnd), GameState(app) {
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura/4, app->winHeight / 2 + altura/2, anchura/2, altura/2, app->texts[numTexturaResume], resume, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura*1.2, anchura / 2, altura / 2, app->texts[numTexturaSave], save, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura /4, app->winHeight / 2 + altura*2, anchura/2, altura/2, app->texts[numTexturaQuit], quit, app));
	}

	virtual void render() { this->bckgrnd->Render(app->renderer); GameState::render(); }
	static void resume(SDLApp* app){ app->getStateMachine()->popState();} //ni tan mal, funciona y todo
	static void quit(SDLApp* app) { app->setExit(true);}
	static void save(SDLApp * app);
};

