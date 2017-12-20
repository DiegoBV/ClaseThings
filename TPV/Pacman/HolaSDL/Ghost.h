#pragma once
#include "SDL.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include "GameCharacter.h"
//using namespace std;
static const int auxText = 2;
static const int filsTex = 1;
static const int colsTex = 2;
static const int posAsustado = 12;
class Game;
class Ghost : public GameCharacter
{
friend class Game;
protected:
	//Número Fantasma
	int numFantasma;
	int posibles_Dirs();
	int type;
public:
	Ghost();
	Ghost(int orX, int orY, int numFant, Texture* text, Game* gam, int type);
	~Ghost();
	vector <int> posibles;
	Dirs posiblesDirs[4];

	//Métodos del juego
	void update(); //Actualiza la posición del fantasma en la dirección actual y 
				  //actualiza la direccion aleatoriamente
	void render(bool vitamina); //Pinta el estado actual en pantalla
	void cambiaDir();
	virtual int ghostType();
	virtual void muerte();
	virtual void animar(bool vitamina);
	virtual void saveToFile(ofstream& file);
	virtual bool reproduce();
	virtual bool dead();
};

