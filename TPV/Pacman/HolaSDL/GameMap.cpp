#include "GameMap.h"
#include "Game.h"

/* Esto es una cosa opcional, luego vemos si lo metemos o no xD
class GameMap(){
	friend class Game; La clase Game puede acceder a los atributos privados de GameMap
}
*/

GameMap::GameMap() //Crea un tablero con un array dinámico
{
	this->fils = 29;
	this->cols = 28;

	//Creación de la matriz
	tablero2 = new MapCell*[fils]; //Es una matriz de punteros, para referenciar las casillas
	for (int r = 0; r < fils; r++) {
		tablero2[r] = new MapCell[cols]; //Ahora sí son arrays dinámicos completos
	}
}
/*
//////////
Alternativa
//////////

En vez de hacer un array de punteros a arrays dinámicos, se hace todo en un mismo array dinámico
MapCell* celdas; //Esto en el .h

Contructora:
GameMap(int fils, int cols){
	celdas = new MapCell[fils*cols];
}

Destructora:
~GameMap(){
	delete[] celdas;
}

Acceso:
MapCell getCell(int fila, int columna){
	return celdas [fils*cols + columna]; //Esto no lo entiendo muy bien xD Habría que revisarlo
}

*/

GameMap::~GameMap()  //Destructora del tablero de juego con un array dinámico
{
	if (tablero2 != nullptr) {
		for (int r = 0; r < fils; r++) {
			delete[] tablero2[r];
		}
		delete[] tablero2;
	}
}

MapCell GameMap::getCell(int fils, int cols) {
	return tablero[fils][cols];
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
	tablero2[x][y] = nuevoObjeto;
}

void GameMap::render_Mapa(SDL_Renderer* &rnd) {
	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			SDL_Rect des;
			des.x = j * 870 / fils;
			des.y = i * 644 / cols;
			des.w = 870 / fils; //pruebas, deberia coger la anchura del game
			des.h = 644 / cols;
			switch (tablero2[i][j]) {
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
