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
	actualDir.dirX = actualDir.dirY = 0;
	filaSheet = 0;
}

void GameCharacter::donut() { //hace las comprobaciones para el movimiento toroidal
	if (posActY < 0) {
		posActY = game->dame_FilasTablero() - 2;
	}
	if (posActY >= game->dame_FilasTablero() - 1) {
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

void GameCharacter::animar() {
	if (this->actualDir.dirX == 1) {
		filaSheet = 0;
	}
	else if (this->actualDir.dirX == -1) {
		filaSheet = 2;
	}
	else if (this->actualDir.dirY == 1) {
		filaSheet = 1;
	}
	else {
		filaSheet = 3;
	}
}

void GameCharacter::loadFromFile(ifstream& file) {
	file >> posActY >> posActX >> iniY >> iniX >> actualDir.dirX >> actualDir.dirY;
	rectDest.x = posActY * this->game->dame_Anchura() / game->dame_ColumnasTablero(); //esto hay que quitarlo wey
	rectDest.y = posActX * this->game->dame_Altura() / game->dame_FilasTablero();
}

void GameCharacter::saveToFile(ofstream& file) {
	file << this->posActY << " " << this->posActX << " " << this->iniY << " " << this->iniX << " " << this->actualDir.dirX << " " << this->actualDir.dirY << " ";
}
void GameCharacter::render() {
	this->textura->RenderFrame(game->dame_Renderer(), rectDest);
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



