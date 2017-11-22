#include "GO.h"
#include "Game.h"


GO::GO()
{
}


GO::~GO()
{
}

GO::GO(int posX, int posY, Texture* text, Game* gam) {

	this->game = gam; //asignacion de punteros a juego y textura
	this->textura = text;
	this->posActX = posX;
	this->posActY = posY;  //establece coordenadas y crea el rectangulo destino inicial
	iniX = posX;
	iniY = posY; //posiciones iniciales del pacman para el guardado
	rectDest.x = posX * game->dame_Anchura() / game->dame_ColumnasTablero();
	rectDest.y = posY * game->dame_Altura() / game->dame_FilasTablero();
	rectDest.w = game->dame_Anchura() / game->dame_FilasTablero(); //establece anchura y altura del fantasma
	rectDest.h = game->dame_Altura() / game->dame_ColumnasTablero();
	//dirX = dirY = nX = nY = 0;
	this->textura->ModificaRectangulo(0, 10);
}

void GO::donut() { //hace las comprobaciones para el movimiento toroidal
	if (posActY < 0) {
		posActY = game->dame_FilasTablero() - 1;
	}
	if (posActY >= game->dame_FilasTablero()) {
		posActY = 0;
	}
	if (posActX < 0) {
		posActX = game->dame_ColumnasTablero() - 1;
	}
	if (posActX >= game->dame_ColumnasTablero()) {
		posActX = 0;
	}
}

void GO::muerte() {
	//Ponemos la posición en el comienzo
	posActX = iniX;
	posActY = iniY;
}

int GO::dame_IniX() {
	return this->iniX;
}

int GO::dame_IniY() {
	return this->iniY;
}

int GO::get_PosActX() {
	return this->posActX;
}

int GO::get_PosActY() {
	return this->posActY;
}


