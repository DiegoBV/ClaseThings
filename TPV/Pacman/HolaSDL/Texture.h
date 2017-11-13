#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Texture
{
private:
	SDL_Texture* textura;
	SDL_Rect rect; //Rectángulo de la textura
	int textH;   //Altura de la textura
	int textW;   //Anchura de la textura
	int filas;
	int columnas;
public:
	Texture();
	~Texture();
	void CreaTexturaIMG(SDL_Renderer* &renderer, string filename, int fils, int cols, int fila_Inicio, int col_Inicio);//crea la textura a partir del archivo
	void CreaTexturaBMP(SDL_Renderer* &renderer, string filename);
	void ModificaRectangulo(int fil, int col); //modifica el rectangulo origen
	void Render(SDL_Renderer* rnd, SDL_Rect dest); //render fondo
	void RenderFrame(SDL_Renderer* rnd, SDL_Rect dest); //render un frame espécifico
	void Anima(int veloc, SDL_Renderer* rnd, SDL_Rect dest);//anima la textura, hay q modificarlo
};

