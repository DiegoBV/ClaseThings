#pragma once
#include "Game.h"
#include "MenuButton.h"
#include "GameState.h"

using namespace std;
const SDL_Rect hudTime = { 400, 0, 50, 40 };

//Este estado es igual que Game, solo que hay tiempo límite
class TimeLimitState : public Game
{
private:
	int timeLim;
	int counter;

public:
	~TimeLimitState();
	TimeLimitState(SDLApp* app, int lvl, int time) : Game(app, lvl){ //Constructora del estado
		timeLim = time;
		counter = 0;
	}

	virtual void update(){
		counter++;
		comprueba_colisiones(pacman->get_PosActX(), pacman->get_PosActY());
		tiempo_Vitamina();
		GameState::update();
		this->delay();
		this->siguiente_Estado();
	}
	virtual void render(){
		Game::render();
		texts[texts.size() - 1]->RenderFrame(app->renderer, hudTime);
	}
	virtual void siguiente_Estado();
};

