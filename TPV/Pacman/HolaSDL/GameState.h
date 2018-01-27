#pragma once
#include "GameObject.h"
#include <list>
#include <SDL.h>
class Game;
class GameState
{
protected:
	list <GameObject*> stage; //lista de objetos del estado
	SDLApp* app; //puntero a SDLApp
public:
	virtual void render() { for (GameObject* it : stage) { it->render(); } }; //manda a los objetos del estado render
	virtual void update() { for (GameObject* it : stage) { it->update(); } }; //manda a los objetos del estado update
	virtual void handleEvent(SDL_Event &e);
	GameState();
	~GameState() { for (GameObject* it : stage) { delete it; } }; //delete de los objetos
	GameState(SDLApp* app) : app(app) {}
};

