#pragma once
#include "Texture.h"
class Game;
class Pacman
{
private:
	Game* game;
	Texture* textura;
	SDL_Rect rectDest;
	int dirX, dirY, nX, nY;
	int iniX, iniY;
	
public:
	int posX, posY;
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
	int dame_IniX();
	int dame_IniY();
};

