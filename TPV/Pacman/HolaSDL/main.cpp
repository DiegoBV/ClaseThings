//Alejandro Marín Pérez / Diego Baratto Valdivia (2º Videojuegos)
#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game juego;
	juego.menu();
	SDL_Quit();
	return 0;
}