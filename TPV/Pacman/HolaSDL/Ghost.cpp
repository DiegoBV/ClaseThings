#include "Ghost.h"
#include "Game.h"


Ghost::Ghost() {
}
Ghost::Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY, int numFant, Texture* text, Game* gam)
{
	this->numFantasma = numFant;
	posInY = orY;
	posInX = orX;
	juego = gam; //Actualiza el puntero a game
	textura = text;//asigna el puntero de texturas
	rectDes.x = orX * juego->dame_Anchura() / juego->dame_ColumnasTablero(); //pone al fantasma en su posicion
	rectDes.y = orY * juego->dame_Altura() / juego->dame_FilasTablero();
	rectDes.w = juego->dame_Anchura() / juego->dame_FilasTablero();//establece anchura y altura del fantasma
	rectDes.h = juego->dame_Altura() / juego->dame_ColumnasTablero();
	posActX = orX;
	posActY = orY;

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

void Ghost::update(bool muerte) {
	if (muerte){
		this->muerte();
	}
	else {
		posActX += actualDir.dirY;
		posActY += actualDir.dirX;	
	}

	donut();

	cambiaDir();

	rectDes.x = juego->obtenerPixelX(posActY);
	rectDes.y = juego->obtenerPixelY(posActX);

}

void Ghost::render(SDL_Renderer* &render) {
	textura->ModificaRectangulo(0, (this->numFantasma - 4) * 2); //modifica el rectángulo origen para dibujar el sprite adecuado...
	textura->Render(render, rectDes);
}

void Ghost::muerte() {
	//Ponemos la posición en el comienzo
	posActX = posInX;
	posActY = posInY;
}

int Ghost::posibles_Dirs() {
	int tempX;
	int tempY;
	int direccion = 0;
	int backward = 0;
	int prueba = 0;
	bool muro = false;
	bool borrar = false;
	int posibles [4];
	int j = 0; //COntrol del array de posibles

	//Exploramos las posibilidades 
	for (int i = 0; i < 4; i++) {
		tempX = posActY;
		tempY = posActX;

		tempX += posiblesDirs[i].dirX;
		tempY += posiblesDirs[i].dirY;

		muro = juego->comprueba_Muro(tempY, tempX);

		if (actualDir.dirX == 0 && actualDir.dirY == 0){ //Para que se pueda inicia
			posibles[j] = i;
			j++;
		}
		else if ((posiblesDirs[i].dirX == (actualDir.dirX*-1)) && (posiblesDirs[i].dirY == (actualDir.dirY*-1))) { //Primero comprobamos que no es la dir contraria
			backward = i;
		}
		else if (!muro) { //Comprobamos que no hay muro
			posibles[j] = i;
			j++;
		}
	}

	//Elección de direccion
	if (j > 1) { //Hay más de una posición posible: escogemos una random
		prueba = (rand() % j);
		direccion = posibles[rand() % j];
	}
	else if (j == 1) { //Sólo hay una posibilidad, estamos en un pasillo
		direccion = posibles[0];
	}
	else { //No hay posibilidades, callejón sin salida, mueve atrás
		direccion = backward;
	}

	return direccion;
}

void Ghost::cambiaDir() {
	int direction = -1;
	direction = posibles_Dirs();

	if (direction >= 0) { //Si puede cambiar de direccion ponemos la nueva direccion
		actualDir.dirX = posiblesDirs[direction].dirX;
		actualDir.dirY = posiblesDirs[direction].dirY;
	}
}

void Ghost::donut() { //hace las comprobaciones para el movimiento toroidal
	if (posActY < 0) {
		posActY = juego->dame_FilasTablero() - 2;
	}
	if (posActY >= juego->dame_FilasTablero() - 1) {
		posActY = 0;
	}
	if (posActX < 0) {
		posActX = juego->dame_ColumnasTablero() - 1;
	}
	if (posActX > juego->dame_ColumnasTablero()) {
		posActX = 0;
	}
	donutS = true;
}