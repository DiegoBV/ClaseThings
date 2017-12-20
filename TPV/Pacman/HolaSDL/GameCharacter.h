#pragma once
#include "Texture.h"
#include "GameObject.h"
const int velAnimacion = 100;
class Game;
class GameCharacter: public GameObject
{
protected:
	struct Dirs {
		int dirX;
		int dirY;
	};
	Dirs actualDir; //direccion actual
	Texture* textura; //textura
	int iniX, iniY; //pos inicial
	SDL_Rect rectDest; //rectangulo para dibujarlo 			   
	int posActX, posActY; //Posicion actual
	void donut();
	int filaSheet; //animar el frame correcto...

	//-----------------------------------Metodos----------------------------------

	virtual void animar(int posIn, int fils, int cols);
	int dame_IniX();
	int dame_IniY();
	
public:
	GameCharacter();
	~GameCharacter();
	GameCharacter(int posX, int posY, Texture* text, Game* gam); //fantasma y pacman tienen el mismo constructor, salvo el numFantasma
	virtual void muerte(); //Muere y vuelve a la posición inicial
	int get_PosActX();
	int get_PosActY();
	virtual void update() = 0;
	virtual bool dead() = 0; //comprueba que el el gamecharacter está muerto
	virtual void render();
	virtual void render(bool)=0;
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
	virtual int ghostType() = 0;
	virtual bool reproduce() = 0;
};

