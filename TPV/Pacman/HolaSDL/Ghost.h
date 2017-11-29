/*#pragma once
#include "SDL.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
//using namespace std;
class Game;
class Ghost : public GameCharacter
{
friend class Game;
private:

	int filaSheet;
	//Dirección actual
	struct Dirs {
		int dirX;
		int dirY;
	};

	//Número Fantasma
	int numFantasma;
	Dirs posiblesDirs [4];
	Dirs actualDir;
	int posibles_Dirs();
	
	
public:
	Ghost();
	Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY, int numFant, Texture* text, Game* gam);
	~Ghost();


	//Métodos del juego
	virtual void update(); //Actualiza la posición del fantasma en la dirección actual y 
				  //actualiza la direccion aleatoriamente
	virtual void render(bool vitamina); //Pinta el estado actual en pantalla
	void cambiaDir();
	void animar(bool vitamina);
};*/

