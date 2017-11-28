#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(): GameCharacter(), dirX(0), dirY(0), nX(0), nY(0) {}


Pacman::~Pacman()
{
}

Pacman::Pacman(int posY, int posX, Texture* text, Game* gam): GameCharacter(posX, posY, text, gam), dirX(0), dirY(0), nX(0), nY(0) {} //contructora con parámetros


bool Pacman::siguiente_Dir(int dX, int dY) { //si pulsas una tecla, se guarda la nueva direccion, si no, se mantiene la antigua
	nX = dX;
	nY = dY;
	int tempX = GameCharacter::posActX;
	int tempY = GameCharacter::posActY;
	return (game->siguiente_casilla(tempX, tempY, nX, nY));
}

void Pacman::render() {//pinta la textura correcta
	this->textura->RenderFrame(game->dame_Renderer(), rectDest);
}

void Pacman::comer() { //comrpueba si la casilla en la que estas es comida o vitamina, si lo es, la cambia por casilla vacia
	if (GameCharacter::game->consulta(GameCharacter::posActY, GameCharacter::posActX) == Food || GameCharacter::game->consulta(GameCharacter::posActY, GameCharacter::posActX) == Vitamins) {
		GameCharacter::game->come(GameCharacter::posActY, GameCharacter::posActX);
	}
}

void Pacman::modifica_Rectangulo() { //modifica el rectangulo destino, asignandole la x y la y multiplicandolo por las medidas del tablero
	GameCharacter::rectDest.y = GameCharacter::posActY * GameCharacter::game->dame_Altura() / GameCharacter::game->dame_FilasTablero();
	GameCharacter::rectDest.x = GameCharacter::posActX * GameCharacter::game->dame_Anchura() / GameCharacter::game->dame_ColumnasTablero();
}

void Pacman::mueve_Pacman() {
	if (siguiente_Dir(nX, nY)) { //si con la nueva direccion que pulsaste puede moverse... (aqui se hace lo de la memoria del movimiento)
		dirX = nX;
		dirY = nY; 
	}

	GameCharacter::game->siguiente_casilla(GameCharacter::posActX, GameCharacter::posActY, dirX, dirY);

	GameCharacter::donut();
	modifica_Rectangulo();
	animar();
}

//esto se parece mucho al ghost...hmmmm
void Pacman::animar() {
	int filaSheet; //indica la fila donde animar (0, 1, 2, 3)
	if (this->dirX == 1) {
		filaSheet = 0;
	}
	else if (this->dirX == -1) {
		filaSheet = 2;
	}
	else if (this->dirY == 1) {
		filaSheet = 1;
	}
	else {
		filaSheet = 3;
	}
	this->textura->Anima(100, filaSheet, 10, 1, 2);
}

void Pacman::update() {
	//if (!GameCharacter::game->comprueba_colisiones(GameCharacter::posActX, GameCharacter::posActY)){
		mueve_Pacman();
		comer();
		this->render();
	//}
}

/*int Pacman::dame_IniX() {
	return this->iniX;
}

int Pacman::dame_IniY() {
	return this->iniY;
}*/

void Pacman::reduceVidas() {
	vidas--;
}

bool Pacman::he_Muerto() {
	return (vidas == 0);
}

/*void Pacman::vuelta_Origen() {
	this->posX = this->iniX;
	this->posY = this->iniY;
}*/




