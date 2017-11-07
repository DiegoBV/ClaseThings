#include "Ghost.h"



Ghost::Ghost()
{
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
