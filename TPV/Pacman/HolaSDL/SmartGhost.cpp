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
	dead = false;
	ancho = rectDest.w;
	alto = rectDest.h;
}

void SmartGhost::update(){
	if (!dead) {
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

		else if (age >= edadMuerte) {
			muerte();
		}
	}
}
/*Primero vamos a buscar la dirección que más nos acerca a Pacman, es decir:
comparamos las X y la Y de ambos personajes, en función de cual de las posiciones de Pacman sea más grande después de ver el
resultado anterior.
Comprobamos si podemos ir en esa dirección, si no, exploramos todas las demás, y si está en un pasillo (que no un callejón sin salida)
seguimos el mismo camino. Obviamente si estamos en un callejón, volvemos atrás duh
*/
void SmartGhost::changeDir(){
	int posPacX, posPacY;
	//int tempX = posActX;
	//int tempY = posActY;
	//bool y, x; //La y indica que la pos de pacman en y es mayor que la del fantasma
	//La x indica si la posición de pacman en x es mayor que la del fantasma

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

	/*y = posPacY >= posActY;
	x = posPacX >= posActX;

	if (x && y){ //Primero comprueba si se puede acercar a Pacman con la dirección calculada, si no coge una aleatoria
				 //Si la x y la y son mayores (haciendo un eje de coordenadas sobre el fantasma, estando este en la (0, 0) virtual
				 //Cuadrante abajo a la derecha
		if (game->siguiente_casilla(tempY, tempX, 0, 1)){
			if (!backward(0, 1)) {
				actualDir.dirX = 0;
				actualDir.dirY = 1;
			}
			else if (game->siguiente_casilla(tempY, tempX, 1, 0)) {
				if (!backward(1, 0)) {
					actualDir.dirX = 1;
					actualDir.dirY = 0;
				}
				else {
					//cambiaDir();
				}
			}
			else {
				//cambiaDir();
			}
		}
		else if (game->siguiente_casilla(tempY, tempX, 1, 0)) {
			if (!backward(1, 0)) {
				actualDir.dirX = 1;
				actualDir.dirY = 0;
			}
			else {
				//cambiaDir();
			}
		}
		else {
			//cambiaDir();
		}
	}

	else if (y && !x){ //Cuadrante abajo a la izquierda (x menor que la X del fantasma
		if (game->siguiente_casilla(tempY, tempX, 0, 1)){
			if (!backward(0, 1)) {
				actualDir.dirX = 0;
				actualDir.dirY = 1;
			}
			else if (game->siguiente_casilla(tempY, tempX, -1, 0)) {
				if (!backward(-1, 0)) {
					actualDir.dirX = -1;
					actualDir.dirY = 0;
				}
				else {
					//cambiaDir();
				}
			}
			else {
				//cambiaDir();
			}
		}
		else if (game->siguiente_casilla(tempY, tempX, -1, 0)) {
			if (!backward(-1, 0)) {
				actualDir.dirX = -1;
				actualDir.dirY = 0;
			}
			else {
				//cambiaDir();
			}
		}
		else {
			//cambiaDir();
		}
	}

	else if (!y && x){ //Cuadrante arriba a la derecha
		if (game->siguiente_casilla(tempY, tempX, 1, 0)){
			if (!backward(1, 0)) {
				actualDir.dirX = 1;
				actualDir.dirY = 0;
			}
			else if (game->siguiente_casilla(tempY, tempX, 0, -1)) {
				if (!backward(0, -1)) {
					actualDir.dirX = 0;
					actualDir.dirY = -1;
				}
				else {
					//cambiaDir();
				}
			}
			else {
				//cambiaDir();
			}
		}
		else if (game->siguiente_casilla(tempY, tempX, 0, -1)) {
			if (!backward(0, -1)) {
				actualDir.dirX = 0;
				actualDir.dirY = -1;
			}
			else {
				//cambiaDir();
			}
		}
		else {
			//cambiaDir();
		}
	}
	else{  //Cuadrante arriba izquierda
		if (game->siguiente_casilla(tempY, tempX, -1, 0)){
			if (!backward(-1, 0)) {
				actualDir.dirX = -1;
				actualDir.dirY = 0;
			}
			else if (game->siguiente_casilla(tempY, tempX, 0, -1)) {
				if (!backward(0, -1)) {
					actualDir.dirX = 0;
					actualDir.dirY = -1;
				}
				else {
					//cambiaDir();
				}
			}
			else {
				//cambiaDir();
			}
		}
		else if (game->siguiente_casilla(tempY, tempX, 0, -1)) {
			if (!backward(0, -1)) {
				actualDir.dirX = 0;
				actualDir.dirY = -1;
			}
			else {
				//cambiaDir();
			}
		}
		else {
			//cambiaDir();
		}
	}*/
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

void SmartGhost::muerte() {
	dead = true;
}