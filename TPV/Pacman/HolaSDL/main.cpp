#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	Game juego;
	juego.carga_Archivo("..\\level01.dat");
	juego.pinta_Mapa();
	juego.run();//por ahora pinta fanstasmas solo
	juego.destruir();
	return 0;
}