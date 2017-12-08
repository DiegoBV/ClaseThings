#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(): GameCharacter(){}


Pacman::~Pacman()
{
}

Pacman::Pacman(int posY, int posX, Texture* text, Game* gam): GameCharacter(posX, posY, text, gam), vidas(3){
	nuevaDir.dirX = 0;
	nuevaDir.dirY = 0;
} //contructora con parámetros


bool Pacman::siguiente_Dir(int dX, int dY) { //si pulsas una tecla, se guarda la nueva direccion, si no, se mantiene la antigua
	nuevaDir.dirX = dX;
	nuevaDir.dirY = dY;
	int tempX = GameCharacter::posActX;
	int tempY = GameCharacter::posActY;
	return (game->siguiente_casilla(tempX, tempY, nuevaDir.dirX, nuevaDir.dirY));
}

void Pacman::render() {//pinta la textura correcta
	this->animar();
	GameCharacter::render();
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
	if (siguiente_Dir(nuevaDir.dirX, nuevaDir.dirY)) { //si con la nueva direccion que pulsaste puede moverse... (aqui se hace lo de la memoria del movimiento)
		GameCharacter::actualDir.dirX = nuevaDir.dirX;
		GameCharacter::actualDir.dirY = nuevaDir.dirY;
	}

	GameCharacter::game->siguiente_casilla(GameCharacter::posActX, GameCharacter::posActY, GameCharacter::actualDir.dirX, GameCharacter::actualDir.dirY);

	GameCharacter::donut();
	modifica_Rectangulo();
}

void Pacman::update() {
	if (!GameCharacter::game->comprueba_colisiones(GameCharacter::posActX, GameCharacter::posActY)){
		mueve_Pacman();
		comer();
	}
}

void Pacman::reduceVidas() {
	vidas--;
}

bool Pacman::he_Muerto() {
	return (vidas == 0);
}

void Pacman::animar() {
	GameCharacter::animar();
	GameCharacter::textura->Anima(100, filaSheet, 10, 1, 2);
}

void Pacman::loadFromFile(ifstream file) {
	//GameCharacter::loadFromFile(file);
	int aux; //para saber si el archivo acaba o no
	if (file.fail()) {
		file.clear();
	}
	else {
		//remEnergy = aux;
		file >> vidas;
	}
}




