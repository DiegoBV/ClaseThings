#pragma once
#include "GameState.h"
#include "SDLApp.h"
#include "MenuButton.h"
class GameOverState: public GameState
{
private:
	Texture* bckgrnd;
public:
	GameOverState();
	~GameOverState();
	GameOverState(SDLApp* app, Texture* bckgrnd) : bckgrnd(bckgrnd), GameState(app) {
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura / 2, anchura / 2, altura / 2, app->texts[numTexturaResume], returnMenu, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura * 2, anchura / 2, altura / 2, app->texts[numTexturaQuit], quit, app));
	}

	virtual void render() { this->bckgrnd->Render(app->renderer); GameState::render(); } //render de la imagen de fondo y de los demas objetos

	static void returnMenu(SDLApp* app) { app->getStateMachine()->popState(); app->getStateMachine()->popState();} //pop del estado muerte y del estado play
	static void quit(SDLApp* app) { app->setExit(true); }
};

