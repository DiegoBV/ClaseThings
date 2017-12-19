#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "Font.h"
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
	//int auxAncho, auxAlto;
public:
	Texture(): textura(nullptr), filas(1), columnas(1){}; //contructora por defecto
	Texture(SDL_Renderer* &renderer, string filename, int fils, int cols);//crea la textura a partir del archivo
	~Texture();
	void ModificaRectangulo(int fil, int col); //modifica el rectangulo origen
	void Render(SDL_Renderer* rnd); //render fondo
	void RenderFrame(SDL_Renderer* rnd, SDL_Rect dest); //render un frame espécifico
	void Anima(int veloc, int posInicialX, int posInicialY,int fil, int col);//anima la textura, hay q modificarlo
	bool loadFromText(SDL_Renderer* renderer, string text, const Font& font, SDL_Color color);
	void prueba(int alto, int ancho);
};

