#pragma once
#include "Texture.h"
#include "GameCharacter.h"
class Game;
class Pacman: public GameCharacter
{
private:
	Dirs nuevaDir;
	int vidas;
	void modifica_Rectangulo();
	void comer();
	void mueve_Pacman();
public:
	Pacman();
	~Pacman();
	Pacman(int posX, int posY, Texture* text, Game* gam);	
	virtual void render();	
	virtual void update();
	virtual void animar();
	virtual void loadFromFile(ifstream file);
	bool siguiente_Dir(int dX, int dY);
	void reduceVidas();
	bool he_Muerto();
};

