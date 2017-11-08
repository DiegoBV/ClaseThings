#include "Ghost.h"



Ghost::Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY)
{
	textura->CreaTexturaIMG(renderer, dirTextura);

	posActX = orX;
	posActY = orY;

	dirX = 0;
	dirY = 0;

	rectDes = textura->CreaRectangulo(
}


Ghost::~Ghost()
{
}

void Ghost::update() {

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
