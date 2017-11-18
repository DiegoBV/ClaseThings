//Alejandro Marín Pérez / Diego Baratto Valdivia (2º Videojuegos)
#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	Game juego;
	juego.menu();
	juego.run();
	SDL_Quit();
	return 0;
}