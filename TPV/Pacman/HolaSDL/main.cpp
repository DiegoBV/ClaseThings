#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	Game juego;
	juego.carga_Archivo("..\\level01.dat");
	while (!juego.win() && !juego.dame_exit()) {
		juego.run();//por ahora pinta fanstasmas solo
	}
	juego.destruir();
	SDL_Quit();
	return 0;
}