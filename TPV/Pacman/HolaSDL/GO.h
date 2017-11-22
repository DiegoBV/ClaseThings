#pragma once
#include "Texture.h"

class Game;
class GO
{
protected:
	Game* game; //puntero a Game
	Texture* textura; //textura
	int iniX, iniY; //pos inicial
	SDL_Rect rectDest; //rectangulo para dibujarlo 			   
	int posActX, posActY; //Posicion actual
public:
	GO();
	~GO();
	GO(int posX, int posY, Texture* text, Game* gam); //fantasma y pacman tienen el mismo constructor, salvo el numFantasma
	void donut();
	void muerte(); //Muere y vuelve a la posición inicial
	int dame_IniX();
	int dame_IniY();
	int get_PosActX();
	int get_PosActY();
};

