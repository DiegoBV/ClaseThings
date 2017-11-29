#pragma once
#include "Texture.h"

class Game;
class GameCharacter
{
protected:
	Game* game; //puntero a Game
	Texture* textura; //textura
	int iniX, iniY; //pos inicial
	SDL_Rect rectDest; //rectangulo para dibujarlo 			   
	int posActX, posActY; //Posicion actual
	void donut();
	void muerte(); //Muere y vuelve a la posición inicial
	void animar(); //se podrá implementar cuando tengamos las direcciones en esta clase...
	virtual void update() = 0;
	virtual void render() = 0;
public:
	GameCharacter();
	~GameCharacter();
	GameCharacter(int posX, int posY, Texture* text, Game* gam); //fantasma y pacman tienen el mismo constructor, salvo el numFantasma
	int dame_IniX();
	int dame_IniY();
	int get_PosActX();
	int get_PosActY();
};

