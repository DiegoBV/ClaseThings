#pragma once
#include "Texture.h"
#include "GameCharacter.h"
class Game;
class Pacman: public GameCharacter
{
private:
	int dirX, dirY, nX, nY;
	int vidas;
	void modifica_Rectangulo();
	int filaSheet; //animar el frame correcto...
	void comer();
	void mueve_Pacman();
	void animar();
public:
	Pacman();
	~Pacman();
	Pacman(int posX, int posY, Texture* text, Game* gam);	
	virtual void render();	
	virtual void update();
	bool siguiente_Dir(int dX, int dY);
	void reduceVidas();
	bool he_Muerto();
};

