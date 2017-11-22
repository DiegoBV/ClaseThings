#pragma once
#include "Texture.h"
#include "GO.h"
class Game;
class Pacman: public GO
{
private:
	int dirX, dirY, nX, nY;
	int vidas;
	void modifica_Rectangulo();
public:
	Pacman();
	~Pacman();
	Pacman(int posX, int posY, Texture* text, Game* gam);
	bool siguiente_Dir(int dX, int dY);
	void render();
	void comer();
	void mueve_Pacman();
	void animar();
	void update();
	void reduceVidas();
	bool he_Muerto();
};

