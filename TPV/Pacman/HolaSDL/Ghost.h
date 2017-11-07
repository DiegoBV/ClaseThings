#pragma once
#include "Texture.h"
#include "Game.h"
#include "SDL.h"

class Ghost
{
private:
	//Posicion inicial
	int posInX, posInY;

	//Posicion actual
	int posActX, posActY;

	//Dirección actual
	int dirX, dirY;

	//Punteros
	//Textura
	Texture* textura;
	//Game (Para conocer el entorno)
	Game* juego;

	//Rectángulo para dibujarlo
	SDL_Rect rectDes;
	
	
public:
	Ghost();
	~Ghost();


	//Métodos del juego
	void update(); //Actualiza la posición del fantasma en la dirección actual y 
				  //actualiza la direccion aleatoriamente
	void render(SDL_Renderer* &renderer); //Pinta el estado actual en pantalla
	void muerte(); //Muere y vuelve a la posición inicial

};

