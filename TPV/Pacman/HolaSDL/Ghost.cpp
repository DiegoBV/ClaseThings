#include "Ghost.h"
#include "Game.h"


Ghost::Ghost() {
}
Ghost::Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY, int numFant, Texture* text, Game* gam)
{
	/*switch (numFant){
	case 5:
		textura.CreaTexturaIMG(renderer, dirTextura, 0, 0, 0, 0);
		break;
	
	case 6:
		textura.CreaTexturaIMG(renderer, dirTextura, 0, 0, 2, 2);
		break;

	case 7:
		textura.CreaTexturaIMG(renderer, dirTextura, 0, 0, 4, 4);
		break;

	case 8:
		textura.CreaTexturaIMG(renderer, dirTextura, 0, 0, 6, 6);
		break;

	default:
		throw invalid_argument("Este fantasma no existe");
		break;
	}*/
	this->numFantasma = numFant;
	juego = gam; //Actualiza el puntero a game
	textura = text;//asigna el puntero de texturas
	rectDes.x = orY * juego->dame_Anchura() / juego->dame_FilasTablero(); //pone al fantasma en su posicion
	rectDes.y = orX * juego->dame_Altura() / juego->dame_ColumnasTablero();
	rectDes.w = juego->dame_Anchura() / juego->dame_FilasTablero();//establece anchura y altura del fantasma
	rectDes.h = juego->dame_Altura() / juego->dame_ColumnasTablero();
	posActX = orX;
	posActY = orY;

	//Array con las posibles direcciones que puede tomar el fantasma
	posiblesDirs = new Dirs[4];
	//Rellenado con esas direcciones
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

	srand(time(nullptr));
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
	textura->ModificaRectangulo(0, (this->numFantasma - 4) * 2); //modifica el rectángulo origen para dibujar el sprite adecuado...
	textura->RenderFrame(render, rectDes);
}

void Ghost::muerte() {
	//Ponemos la posición en el comienzo
	posActX = posInX;
	posActY = posInY;

	//Actualizamos el estado del fantasma
	update();
}

int Ghost::posibles_Dirs() {
	int tempX;
	int tempY;
	int direccion = 0;
	int backward = 0;
	int prueba = 0;
	bool cambia;
	bool borrar = false;
	int* posibles = new int [4];
	int j = 0; //COntrol del array de posibles

	//Exploramos las posibilidades 
	for (int i = 0; i < 4; i++) {
		tempX = posActX;
		tempY = posActY;

		tempX += posiblesDirs[i].dirX;
		tempY += posiblesDirs[i].dirY;

		if (posiblesDirs[i].dirX != (actualDir.dirX*-1) && posiblesDirs[i].dirY != (actualDir.dirY*-1)) { //Primero comprobamos que no es la dir contraria
			if (!juego->comprueba_Muro(tempX, tempY)) { //Comprobamos que no hay muro
				posibles[j] = i;
				j++;
			}
		}
		else { //Si es la dir contraria, hacemos anoder cing
			backward = i;
		}
	}

	//Elección de direccion
	if (j > 1) { //Hay más de una posición posible: escogemos una random
		prueba = (rand() % j);
		direccion = posibles[rand() % j];
	}
	else if (j = 1) { //Sólo hay una posibilidad, estamos en un pasillo
		direccion = posibles[0];
	}
	else { //No hay posibilidades, callejón sin salida, mueve atrás
		direccion = backward;
	}

	return direccion;
}

void Ghost::cambiaDir() {
	int direction = 0;
	direction = posibles_Dirs();

	if (direction != 0) { //Si puede cambiar de direccion ponemos la nueva direccion
		actualDir.dirX = posiblesDirs[direction].dirX;
		actualDir.dirY = posiblesDirs[direction].dirY;
	}
	else {
		throw invalid_argument("No hay donde mover, ¿es el mapa correcto?");
	}
}
