#pragma once
#include "Texture.h"
#include "SDL.h"
enum MapCell { Empty, Wall, Food, Vitamins };

class GameMap
{
private:
	MapCell tablero[200][200];
	Texture* vitamina;
	Texture* muro;
	Texture* comida;
	//Game* game;
public:
	GameMap();
	~GameMap();
	void crea_Mapa(Texture* vit, Texture* m, Texture* com, MapCell tab[200][200]);
	string consulta_Posicion(int x, int y);
	void modifica_Posicion(int x, int y, MapCell nuevoObjeto);
	void render_Mapa(SDL_Renderer* &rnd);
	void destruir_Mapa();

};

