#pragma once
#include "Texture.h"
#include "Game.h"
#include "SDL.h"
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <random>
using namespace std;

class Ghost
{
private:
	//Posicion inicial
	int posInX, posInY;

	//Posicion actual
	int posActX, posActY;

	//Dirección actual
	struct Dirs {
		int dirX;
		int dirY;
	};
	Dirs* posiblesDirs;
	Dirs actualDir;

	//Punteros
	//Textura
	Texture* textura;
	//Game (Para conocer el entorno)
	Game* juego;

	//Rectángulo para dibujarlo
	SDL_Rect rectDes;
	int posibles_Dirs();
	
	
public:
	Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY, int numFant);
	~Ghost();


	//Métodos del juego
	void update(); //Actualiza la posición del fantasma en la dirección actual y 
				  //actualiza la direccion aleatoriamente
	void render(SDL_Renderer* &renderer); //Pinta el estado actual en pantalla
	void muerte(); //Muere y vuelve a la posición inicial
	void cambiaDir();
};

