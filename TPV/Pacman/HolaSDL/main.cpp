//Alejandro Marín Pérez / Diego Baratto Valdivia (2º Videojuegos)
#include "SDLApp.h"
#include "Game.h"
#include "MainMenuState.h"
using namespace std;

int main(int argc, char* argv[]) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Game juego;
	SDLApp app;
	SDL_Event E;
	app.getStateMachine()->pushState(new MainMenuState(&app, app.texts[4]));
	app.run();
	SDL_Quit();
	return 0;
}