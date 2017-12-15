#pragma once
#include "Texture.h"
#include "GameObject.h"

class Game;
class GameCharacter: public GameObject
{
protected:
	struct Dirs {
		int dirX;
		int dirY;
	};
	Dirs actualDir; //direccion actual
	//Game* game; //puntero a Game
	Texture* textura; //textura
	int iniX, iniY; //pos inicial
	SDL_Rect rectDest; //rectangulo para dibujarlo 			   
	int posActX, posActY; //Posicion actual
	void donut();
	int filaSheet; //animar el frame correcto...
	
public:
	GameCharacter();
	~GameCharacter();
	GameCharacter(int posX, int posY, Texture* text, Game* gam); //fantasma y pacman tienen el mismo constructor, salvo el numFantasma
	virtual void muerte(); //Muere y vuelve a la posición inicial
	int dame_IniX();
	int dame_IniY();
	int get_PosActX();
	int get_PosActY();
	virtual void animar();
	virtual void animar(bool);
	virtual void render();
	virtual void render(bool);
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};

