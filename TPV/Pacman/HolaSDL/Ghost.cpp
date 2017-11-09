#include "Ghost.h"



/Ghost::Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY)
{
	textura->CreaTexturaIMG(renderer, dirTextura);

	posActX = orX;
	posActY = orY;

	posiblesDirs = new Dirs[4];


	posiblesDirs[0].dirX = 0; //Arriba
	posiblesDirs[0].dirY = -1;
	posiblesDirs[1].dirX = 0; //Abajo
	posiblesDirs[1].dirY = 1;
	posiblesDirs[2].dirX = -1; //Izda
	posiblesDirs[2].dirY = 0;
	posiblesDirs[3].dirX = 1; //Dcha
	posiblesDirs[3].dirY = 0;

	actualDir.dirX = 0;
	actualDir.dirY = 0;
	rectDes = textura->CreaRectangulo(
}


Ghost::~Ghost()
{
}

void Ghost::update() {
	posActX += actualDir.dirX;
	posActY += actualDir.dirY;

	cambiaDir();
}

void Ghost::render(SDL_Renderer* &render) {
	textura->RenderFrame(render, rectDes);
}

void Ghost::muerte() {
	//Ponemos la posición en el comienzo
	posActX = posInX;
	posActY = posInY;

	//Actualizamos el estado del fantasma
	update();
}

bool Ghost::posibles_Dirs(int &direction) {
	int tempX;
	int tempY;
	bool cambia;
	int* posibles = new int [];

	for (int i = 0; i < 4; i++) {
		tempX = posActX;
		tempY = posActY;

		if (juego->comprueba_Celda(tempX, tempY)) {
			posibles
		}
	}

}

void Ghost::cambiaDir() {
	int direction = 0;
	bool puedeCambiar = posibles_Dirs(direction);

	if (puedeCambiar) {

	}
}
