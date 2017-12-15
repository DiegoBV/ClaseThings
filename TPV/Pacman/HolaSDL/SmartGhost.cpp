#include "SmartGhost.h"



SmartGhost::SmartGhost()
{
}


SmartGhost::~SmartGhost()
{
}

SmartGhost::SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad){
	age = edad;
	adult = false;
	Ghost(orX, orY, numFant, text, gam);
}

void SmartGhost::update(){
	game->siguiente_casilla(posActY, posActX, actualDir.dirX, actualDir.dirY);

	donut();

	changeDir();

	rectDest.x = game->obtenerPixelX(posActY);
	rectDest.y = game->obtenerPixelY(posActX);

	age++;
}
/*Primero vamos a buscar la dirección que más nos acerca a Pacman, es decir: 
	comparamos las X y la Y de ambos personajes, en función de cual de las posiciones de Pacman sea más grande después de ver el 
	resultado anterior. 
	Comprobamos si podemos ir en esa dirección, si no, exploramos todas las demás, y si está en un pasillo (que no un callejón sin salida)
	seguimos el mismo camino. Obviamente si estamos en un callejón, volvemos atrás duh
	*/
void SmartGhost::changeDir(){
	int posPacX, posPacY;
	int tempX = posActX;
	int tempY = posActY;
	bool y, x; //La y indica que la pos de pacman en y es mayor que la del fantasma
			   //La x indica si la posición de pacman en x es mayor que la del fantasma

	game->give_posPacman(posPacX, posPacY);

	y = posPacY > posActY;
	x = posPacX > posActX;

	if (x && y){
		if (posPacY > posPacX){
			if (game->siguiente_casilla(tempX, tempY, 0, 1)){
				actualDir.dirX = 0;
				actualDir.dirY = 1;
			}
			else {
				cambiaDir();
			}
		}
		else {
			if (game->siguiente_casilla(tempX, tempY, 1, 0)){
				actualDir.dirX = 1;
				actualDir.dirY = 0;
			}
			else {
				cambiaDir();
			}
		}
	}

	else if (y && !x){
		if (game->siguiente_casilla(tempX, tempY, 0, 1)){
			actualDir.dirX = 0;
			actualDir.dirY = 1;
		}
		else if (game->siguiente_casilla(tempX, tempY, -1, 0)){
			actualDir.dirX = -1;
			actualDir.dirY = 0;
		}
		else {
			cambiaDir();
		}
	}

	else if (!y && x){
		if (x && game->siguiente_casilla(tempX, tempY, 1, 0)){
			actualDir.dirX = 1;
			actualDir.dirY = 0;
		}
		else if (game->siguiente_casilla(tempX, tempY, 0, -1)){
			actualDir.dirX = 0;
			actualDir.dirY = -1;
		}
		else {
			cambiaDir();
		}
	}
	else{
		cambiaDir();
	}
}
