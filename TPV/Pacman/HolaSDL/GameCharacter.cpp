#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter()
{
}


GameCharacter::~GameCharacter()
{
}

GameCharacter::GameCharacter(int posX, int posY, Texture* text, Game* gam) {

	this->game = gam; //asignacion de punteros a jueGameCharacter y textura
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

void GameCharacter::donut() { //hace las comprobaciones para el movimiento toroidal
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

void GameCharacter::muerte() {
	//Ponemos la posición en el comienzo
	posActX = iniX;
	posActY = iniY;
}

int GameCharacter::dame_IniX() {
	return this->iniX;
}

int GameCharacter::dame_IniY() {
	return this->iniY;
}

int GameCharacter::get_PosActX() {
	return this->posActX;
}

int GameCharacter::get_PosActY() {
	return this->posActY;
}


