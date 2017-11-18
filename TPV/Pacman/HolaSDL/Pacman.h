#pragma once
#include "Texture.h"
class Game;
class Pacman
{
private:
	Game* game;
	Texture* textura;
public:
	int posX, posY;
private:
	SDL_Rect rectDest;
	int dirX, dirY, nX, nY;
	
public:
	Pacman();
	~Pacman();
	Pacman(int posX, int posY, Texture* text, Game* gam);
	bool siguiente_Dir(int dX, int dY);
	void render();
	void comer();
	void donut();
	void mueve_Pacman();
	void modifica_Rectangulo();
	void animar();
	void update();

};

