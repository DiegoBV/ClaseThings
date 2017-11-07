#pragma once
#include "Texture.h"
#include "SDL.h"
using namespace std;
enum MapCell { Empty, Wall, Food, Vitamins };

class GameMap
{
private:
	int fils;
	int cols;
	MapCell tablero[200][200];
	MapCell** tablero2; //Matriz dinámica para el tablero
	Texture* vitamina;
	Texture* muro;
	Texture* comida;
	Game* game;
public:
	GameMap(int fils, int cols);
	~GameMap();

	MapCell getCell(int fils, int cols); //devuelve una celda
	void crea_Mapa(Texture* vit, Texture* m, Texture* com, MapCell tab[200][200]);
	string consulta_Posicion(int x, int y);
	void modifica_Posicion(int x, int y, MapCell nuevoObjeto);
	void render_Mapa(SDL_Renderer* &rnd);
	void destruir_Mapa();

};

