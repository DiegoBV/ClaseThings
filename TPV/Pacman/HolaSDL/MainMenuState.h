#pragma once
#include "GameState.h"
#include "Texture.h"
#include "SDLApp.h"
#include "MenuButton.h"
#include "Game.h"
#include "TimeLimitState.h"

const int startLvl = 1;
const int numTexturaPlay = 8;
const int numTexturaLoad = 9;
class MainMenuState: public GameState
{
private:
	Texture* txt;
public:
	MainMenuState();
	~MainMenuState();
	MainMenuState(SDLApp* app, Texture* txt) : txt(txt), GameState(app) {
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura/2, anchura/2, altura/2, app->texts[numTexturaPlay], start,app)); //colocacion de los botones
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura*1.25, anchura / 2, altura / 2, app->texts[numTexturaPlay], startTime, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura*1.75, anchura / 2, altura / 2, app->texts[numTexturaLoad], cargaPartida, app));
		stage.push_back(new MenuButton(app->winWidth / 2 - anchura / 4, app->winHeight / 2 + altura*2.25, anchura / 2, altura / 2, app->texts[numTexturaQuit], quit, app));
	}
	virtual void render() { this->txt->Render(app->renderer); GameState::render(); }
	virtual void handleEvent(SDL_Event& e);
	static void start(SDLApp* app) { 
		app->getStateMachine()->pushState(new Game(app, startLvl));
	}
	static void startTime(SDLApp* app){
		app->getStateMachine()->pushState(new TimeLimitState(app, startLvl, 10000));
	}
	static void cargaPartida(SDLApp* app) { app->plasmaMensaje(); int code = app->escribe_Code(); app->getStateMachine()->pushState(new Game(app, code)); } //declaracion de los metodos static (callbacks)
	static void quit(SDLApp* app) { app->setExit(true); } 
};

