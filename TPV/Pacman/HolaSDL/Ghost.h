#pragma once
#include "SDL.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include "GameCharacter.h"
//using namespace std;
class Game;
class Ghost : public GameCharacter
{
friend class Game;
private:
	//N�mero Fantasma
	int numFantasma;
	Dirs posiblesDirs [4];
	int posibles_Dirs();
	
	
public:
	Ghost();
	Ghost(int orX, int orY, int numFant, Texture* text, Game* gam);
	~Ghost();


	//M�todos del juego
	void update(); //Actualiza la posici�n del fantasma en la direcci�n actual y 
				  //actualiza la direccion aleatoriamente
	void render(bool vitamina); //Pinta el estado actual en pantalla
	void cambiaDir();
	virtual void animar(bool vitamina);
};

