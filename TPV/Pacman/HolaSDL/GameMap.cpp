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
	return tablero2[fils][cols];
}

MapCell GameMap::consulta_Posicion(int x, int y) { //esto es lo mismo que lo de arriba, deberia borrarse (?) al ppo devolvia un string pero si no es necesario...
	MapCell pos = Empty; //Devolvemos vacía predeterminadamente para depuración, después calculos de fantasmas.
	//pos = getCell(x, y);

	switch (pos) {
	case Empty:
		pos = Empty;
		break;
	case Wall:
		pos = Wall;
		break;
	case Food:
		pos = Food;
		break;
	case Vitamins:
		pos = Vitamins;
		break;
	default:
		throw invalid_argument("Casilla sin asignar"); //Aquí habría que lanzar una excepción 
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
			des.x = j * game->dame_Anchura() / fils;
			des.y = i * game->dame_Altura() / cols;
			des.w = game->dame_Anchura() / fils;
			des.h = game->dame_Altura() / cols;
			switch (tablero2[i][j]) {  //comprueba lo que hay en la posicion i,j y manda a la textura correspondiente pintarse
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
