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
}

void SmartGhost::changeDir(){

}
