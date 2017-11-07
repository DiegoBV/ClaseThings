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

	//Direcci�n actual
	int dirX, dirY;

	//Punteros
	//Textura
	Texture* textura;
	//Game (Para conocer el entorno)
	Game* juego;

	//Rect�ngulo para dibujarlo
	SDL_Rect rectDes;
	
	
public:
	Ghost();
	~Ghost();


	//M�todos del juego
	void update(); //Actualiza la posici�n del fantasma en la direcci�n actual y 
				  //actualiza la direccion aleatoriamente
	void render(SDL_Renderer* &renderer); //Pinta el estado actual en pantalla
	void muerte(); //Muere y vuelve a la posici�n inicial

};

