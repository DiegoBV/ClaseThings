#pragma once
#include "Texture.h"
class Game;
class Pacman
{
	Game* game;
	Texture* textura;
	int posX, posY;
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

