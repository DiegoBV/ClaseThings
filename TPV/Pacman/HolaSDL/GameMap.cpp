#include "GameMap.h"
#include "Game.h"

/* Esto es una cosa opcional, luego vemos si lo metemos o no xD
class GameMap(){
	friend class Game; La clase Game puede acceder a los atributos privados de GameMap
}
*/

GameMap::GameMap() //Crea un tablero con un array dinámico
{	
}
GameMap::GameMap(int fils, int cols, Texture* vit, Texture* m, Texture* com, Game* gam) { //Constructora con parámetros
	vitamina = vit;
	muro = m;
	comida = com;
	game = gam;
	if (fils != 0 && cols != 0) {
		this->fils = fils;
		this->cols = cols;

		//Creación de la matriz
		tablero2 = new MapCell*[fils]; //Es una matriz de punteros, para referenciar las casillas
		for (int r = 0; r < fils; r++) {
			tablero2[r] = new MapCell[cols]; //Ahora sí son arrays dinámicos completos
		}
	}
	else {
		tablero2 = nullptr;
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

GameMap::~GameMap() 
{
}

void GameMap::destruir_Mapa() { //Destructora del tablero de juego con un array dinámico, la destructora por defecto se llama al hacer un nuevo map
	if (tablero2 != nullptr) {
	for (int r = 0; r < fils; r++) {
	delete[] tablero2[r];
	}
	delete[] tablero2;
	}
}

MapCell GameMap::getCell(int fils, int cols) {
	if (fils < game->dame_FilasTablero() && fils >= 0 && cols < game->dame_ColumnasTablero() && cols >= 0) {
		return tablero2[fils][cols];
	}
}

void GameMap::modifica_Posicion(int x, int y, MapCell nuevoObjeto) {
	tablero2[x][y] = nuevoObjeto;
}

void GameMap::render_Mapa() {
	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			SDL_Rect des;
			des.x = j * game->dame_Anchura() / cols;
			des.y = i * game->dame_Altura() / fils;
			des.w = game->dame_Anchura() / cols;
			des.h = game->dame_Altura() / cols;
			switch (tablero2[i][j]) {  //comprueba lo que hay en la posicion i,j y manda a la textura correspondiente pintarse
			case Wall:
				muro->RenderFrame(game->dame_Renderer(), des);
				break;
			case Food:
				comida->RenderFrame(game->dame_Renderer(), des);
				break;
			case Vitamins:
				vitamina->RenderFrame(game->dame_Renderer(), des);
				break;
			}
		}
	}
}
