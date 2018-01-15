#pragma once
#include "GameObject.h"
#include <list>
#include <SDL.h>
class Game;
class GameState
{
protected:
	list <GameObject*> stage;
	Game* game;
public:
	virtual void render() { for (GameObject* it : stage) { it->render(); } };
	virtual void update() { for (GameObject* it : stage) { it->update(); } };
	virtual void handleEvent(SDL_Event &e);
	GameState();
	~GameState() { for (GameObject* it : stage) { delete it; } };
};

