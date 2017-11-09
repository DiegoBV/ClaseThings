#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	Game juego;
	juego.carga_Archivo("..\\level01.dat");
	juego.pinta_Mapa();
	system("pause");
	return 0;
}