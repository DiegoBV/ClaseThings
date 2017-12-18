#pragma once
#include "Texture.h"
#include "GameCharacter.h"
const int IniText = 10;
const int TextsFils = 1;
const int ColsText = 2;
class Game;
class Pacman: public GameCharacter
{
private:
	Dirs nuevaDir;
	int vidas;
	void modifica_Rectangulo();
	void comer();
	void mueve_Pacman();

	//---------------------------Metodos--------------------------------
	virtual void animar();
	
	

public:
	Pacman();
	~Pacman();
	Pacman(int posX, int posY, Texture* text, Game* gam);	
	virtual void render();	
	virtual void update();
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
	bool siguiente_Dir(int dX, int dY);
	void reduceVidas();
	bool he_Muerto();
	virtual void render(bool);
	int dame_Vidas();
	
};

