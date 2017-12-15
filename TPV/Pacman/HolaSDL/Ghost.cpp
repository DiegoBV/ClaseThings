#include "Ghost.h"


Ghost::Ghost(): GameCharacter() {} //constructora por defecto

Ghost::Ghost(int orX, int orY, int numFant, Texture* text, Game* gam): GameCharacter(orX, orY, text, gam), numFantasma(numFant)
{	
	//Array con las posibles direcciones que puede tomar el fantasma
	//Rellenado con esas direcciones
	posiblesDirs[0].dirX = 0; //Arriba
	posiblesDirs[0].dirY = -1;
	posiblesDirs[1].dirX = 0; //Abajo
	posiblesDirs[1].dirY = 1;
	posiblesDirs[2].dirX = -1; //Izda
	posiblesDirs[2].dirY = 0;
	posiblesDirs[3].dirX = 1; //Dcha
	posiblesDirs[3].dirY = 0;

	actualDir.dirX = 0;  //Inicializamos de base hacia arriba, para probar cosas
	actualDir.dirY = 0;

	srand(time(nullptr));
}


Ghost::~Ghost()
{
}

void Ghost::update() {
	game->siguiente_casilla(posActY, posActX, actualDir.dirX, actualDir.dirY);

	donut();

	cambiaDir();

	rectDest.x = game->obtenerPixelX(posActY);
	rectDest.y = game->obtenerPixelY(posActX);

}

void Ghost::render(bool vitamina) {
	if (vitamina){
		textura->ModificaRectangulo(0, 13);
	}
	else {
		textura->ModificaRectangulo(0, (this->numFantasma - 4) * 2); //modifica el rectángulo origen para dibujar el sprite adecuado...
	}

	animar(vitamina);
	
	render();
}

int Ghost::posibles_Dirs() {
	int tempX;
	int tempY;
	int backward = 0;
	int posibles [4];
	int j = 0; //Control del array de posibles

	//Exploramos las posibilidades 
	for (int i = 0; i < 4; i++) {
		tempX = posActY;
		tempY = posActX;

		if (actualDir.dirX == 0 && actualDir.dirY == 0){ //Para que se pueda iniciar
			posibles[j] = i;
			j++;
		}
		else if ((posiblesDirs[i].dirX == (actualDir.dirX*-1)) && (posiblesDirs[i].dirY == (actualDir.dirY*-1))) { //Primero comprobamos que no es la dir contraria
			backward = i;
		}
		else if (game->siguiente_casilla(tempX, tempY, posiblesDirs[i].dirX, posiblesDirs[i].dirY)) { //Comprobamos que no hay muro
			posibles[j] = i;
			j++;
		}
	}

	//Elección de direccion
	if (j > 1) { //Hay más de una posición posible: escogemos una random
		return posibles[rand() % j];
	}
	else if (j == 1) { //Sólo hay una posibilidad, estamos en un pasillo
		return posibles[0];
	}
	else { //No hay posibilidades, callejón sin salida, mueve atrás
		return backward;
	}
}

void Ghost::cambiaDir() {
	int direction = -1;
	direction = posibles_Dirs();

	if (direction >= 0) { //Si puede cambiar de direccion ponemos la nueva direccion
		actualDir.dirX = posiblesDirs[direction].dirX;
		actualDir.dirY = posiblesDirs[direction].dirY;
	}
}

void Ghost::animar(bool vitamina){
	if (!vitamina){
		animar(vitamina);
		textura->Anima(100, filaSheet, (this->numFantasma - 4) * 2, 1, 2);
	}
	else
	{
		filaSheet = 0;
		textura->Anima(100, filaSheet, 12, 1, 2);
	}
}

void Ghost::saveToFile(ofstream& file) {
	file << "0" << " "; //guardamos el tipo del fantasma
	saveToFile(file);
	file << endl;
}