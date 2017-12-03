#pragma once
#include "Texture.h"

class Game;
class GameCharacter
{
protected:
	struct Dirs {
		int dirX;
		int dirY;
	};
	Dirs actualDir; //direccion actual
	Game* game; //puntero a Game
	Texture* textura; //textura
	int iniX, iniY; //pos inicial
	SDL_Rect rectDest; //rectangulo para dibujarlo 			   
	int posActX, posActY; //Posicion actual
	void donut();
	int filaSheet; //animar el frame correcto...
	virtual void animar(); //se podrá implementar cuando tengamos las direcciones en esta clase...
	virtual void update() = 0;
	virtual void render();
public:
	GameCharacter();
	~GameCharacter();
	GameCharacter(int posX, int posY, Texture* text, Game* gam); //fantasma y pacman tienen el mismo constructor, salvo el numFantasma
	void muerte(); //Muere y vuelve a la posición inicial
	int dame_IniX();
	int dame_IniY();
	int get_PosActX();
	int get_PosActY();
};

