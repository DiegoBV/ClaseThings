#pragma once
#include "GameObject.h"
#include <list>
#include <SDL.h>
class Game;
class GameState
{
private:
	list <GameObject*> stage;
	Game* game;
public:
	void render() { for (GameObject* it : stage) { it->render(); } };
	void update() { for (GameObject* it : stage) { it->update(); } };
	void handleEvents(SDL_Event &e);
	GameState();
	~GameState() { for (GameObject* it : stage) { delete it; } };
};

