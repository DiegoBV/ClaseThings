#pragma once
#include "Texture.h"
#include "SDL.h"

using namespace std;
enum MapCell { Empty, Wall, Food, Vitamins };
class Game;
class GameMap
{
friend class Game;
private:
	int fils;
	int cols;
	MapCell** tablero2; //Matriz dinámica para el tablero
	Texture* vitamina;
	Texture* muro;
	Texture* comida;
	Game* game;

public:
	GameMap();
	~GameMap();
	GameMap(int fils, int cols, Texture* vit, Texture* m, Texture* com, Game* gam);//constructora con parámetros
	MapCell getCell(int fils, int cols); //devuelve una celda
	MapCell consulta_Posicion(int x, int y);//devuelve el contenido de la posicion indicada
	void modifica_Posicion(int x, int y, MapCell nuevoObjeto);
	void render_Mapa(SDL_Renderer* &rnd);
	void destruir_Mapa();
	
};

