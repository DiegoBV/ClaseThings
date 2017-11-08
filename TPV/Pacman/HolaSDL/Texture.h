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
	void CreaTexturaIMG(SDL_Renderer* &renderer, string filename, int fils, int cols, int fila_Inicio, int col_Inicio);
	void CreaTexturaBMP(SDL_Renderer* &renderer, string filename);
	void CreaRectangulo(int alturaIMG, int anchuraIMG, int posX, int posY);
	void Render(SDL_Renderer* rnd);
	void RenderFrame(SDL_Renderer* rnd, SDL_Rect dest);
	void Anima(int veloc, SDL_Renderer* rnd, SDL_Rect dest);
};

