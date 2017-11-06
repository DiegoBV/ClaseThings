#include "GameMap.h"
#include "Game.h"


GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::crea_Mapa(Texture* vit, Texture* m, Texture* com, MapCell tab[200][200]) {
	vitamina = vit;
	muro = m;
	comida = com;
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			tablero[i][j] = tab[i][j];
		}
	}
}
string GameMap::consulta_Posicion(int x, int y) {
	string pos;
	switch (tablero[x][y]) {
	case Empty:
		pos = "Empty";
		break;
	case Wall:
		pos = "Wall";
		break;
	case Food:
		pos = "Food";
		break;
	case Vitamins:
		pos = "Vitamins";
		break;
	default:
		pos = "Error";
		break;	
	}

	return pos;
}

void GameMap::modifica_Posicion(int x, int y, MapCell nuevoObjeto) {
	tablero[x][y] = nuevoObjeto;
}

void GameMap::render_Mapa(SDL_Renderer* &rnd) {
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			SDL_Rect des;
			des.x = i;
			des.y = j;
			des.w = 30; //pruebas, deberia coger la anchura del game
			des.h = 30;
			switch (tablero[i][j]) {
			case Empty:
				//algo
				break;
			case Wall:
				muro->RenderFrame(rnd, des);
				break;
			case Food:
				comida->RenderFrame(rnd, des);
				break;
			case Vitamins:
				vitamina->RenderFrame(rnd, des);
				break;
			}
		}
	}
}
