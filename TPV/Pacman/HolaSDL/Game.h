#pragma once
#include "SDL.h"
#include "Texture.h"
#include "GameMap.h"
#include "Ghost.h"
#include <fstream>
class Game
{
friend class GameMap;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	ifstream archivo;
	int winWidth;
	int winHeight;
	int winX, winY;
	Texture muro; //deberia ser un array, esto es pa probar
	Texture com;
	Texture vitam;
	MapCell tab[200][200];
	GameMap map;
	Ghost* fantasmas [4]; 
public:
	Game();
	~Game();
	void carga_Archivo(string name);
	void pinta_Mapa();
	bool comprueba_Muro(int X, int Y);
};

 
