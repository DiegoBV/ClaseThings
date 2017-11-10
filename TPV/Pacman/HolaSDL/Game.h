#pragma once
#include "SDL.h"
#include "Texture.h"
#include "GameMap.h"
#include "Ghost.h"
#include <fstream>
class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	ifstream archivo;
	int winWidth;
	int winHeight;
	int filasTablero, colsTablero;
	int winX, winY;
	Texture muro; //deberia ser un array, esto es pa probar
	Texture com;
	Texture vitam;
	GameMap map;
	Ghost fantasmas [4]; //array de fantasmas/personajes
	Texture* textGhost[4]; //punteros a la textura general para acceder a ella
	Texture textGeneral; //carga la textura con todas las cositas
public:
	Game();
	~Game();
	void carga_Archivo(string name);//carga el archivo
	void pinta_Mapa();
	void run();
	bool comprueba_Muro(int X, int Y);
	int dame_Altura();
	int dame_Anchura();  //los gets para saber las dimensiones del tablero y pantalla
	int dame_FilasTablero();
	int dame_ColumnasTablero();
	SDL_Renderer* dame_Renderer();
	void destruir();
};

 
