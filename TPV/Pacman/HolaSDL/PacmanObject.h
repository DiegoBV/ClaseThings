#pragma once
#include "GameObject.h"

class Game;
class PacmanObject: public GameObject //clase intermedia que define los metodos load y save
{
protected:
	Game* game;
public:
	PacmanObject();
	PacmanObject(Game* game, SDLApp* app) : game(game), GameObject(app) {};
	~PacmanObject();
	virtual void loadFromFile(ifstream& file) = 0;
	virtual void saveToFile(ofstream& file) = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handleEvent(SDL_Event& e) = 0;
};

