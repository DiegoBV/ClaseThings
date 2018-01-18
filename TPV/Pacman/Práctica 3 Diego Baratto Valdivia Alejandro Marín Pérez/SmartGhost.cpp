#include "SmartGhost.h"



SmartGhost::SmartGhost()
{
}


SmartGhost::~SmartGhost()
{
}

SmartGhost::SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad, int type): Ghost(orX, orY, numFant, text, gam, type){
	age = edad;
	adult = false;
	deadState = false;
	ancho = rectDest.w;
	alto = rectDest.h;
	fertilidad = 0;
}

void SmartGhost::update(){
	int tempX = posActX;
	int tempY = posActY;

	if (!deadState) {
		if ((fertilidad == 0) && game->colision_Fantasma(tempX + actualDir.dirY, posActY + actualDir.dirX) && !deadState && adult){
			game->nace_Fantasma(posActX - actualDir.dirY, posActY - actualDir.dirX);
			fertilidad = 20;
		}

		Ghost::update();
		crece();
		donut();
		if (adult) {
			changeDir();
		}


		age++;

		if (age > edadAdulta) { //El pequeñajo crece
			adult = true;
		}

		if (age >= edadMuerte) {
			olddie();
			cout << "SEMOS AGÜELOS" << endl;
		}

		if (fertilidad > 0){
			fertilidad--;
		}

	}
}

void SmartGhost::changeDir(){//Persigue al jugador usando un vector físico
	int posPacX, posPacY;

	game->give_posPacman(posPacX, posPacY);
	bool found = false;
	int i = 0;
	while(i < posibles.size() && !found) {
		int pos = posibles[i];
		int vX, vY;
		vX = abs(posActY + posiblesDirs[pos].dirX -  posPacX);
		vY = abs(posActX + posiblesDirs[pos].dirY - posPacY);
		if (vX < abs(posActY - posPacX) || vY < abs(posActX - posPacY)) {
			actualDir.dirX = posiblesDirs[pos].dirX;
			actualDir.dirY = posiblesDirs[pos].dirY;
			found = true;
		}
		i++;
	}
	posibles.clear();
}

bool SmartGhost::backward(int dirX, int dirY) { //Devolverá false si la dirección no es la contraria o si está en un callejon sin salida
	if (dirX == (actualDir.dirX*-1) && dirY == (actualDir.dirY*-1)) { //Si es la drirección contraria no la pillamos a menos que no haya salida
		return true;
	}
	else {
		return false;
	}
}

bool SmartGhost::reproduce() {
	return adult;
}

void SmartGhost::crece() {
	if (age < edadAdulta) {
		rectDest.w = ancho - tamanyoBaby;
		rectDest.h = alto - tamanyoBaby;
	}
	else {
		rectDest.w = ancho;
		rectDest.h = alto;
	}
}

void SmartGhost::olddie() { //El pequeñajo crece
	deadState = true;
}

bool SmartGhost::dead(){
	return this->deadState;
}