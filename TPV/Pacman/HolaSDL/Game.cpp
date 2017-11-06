#include "Game.h"



Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	const int winWidth = 800;
	const int winHeight = 600;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;

	//Inicialización del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Texturas
	muro.CreaTexturaIMG(renderer, "..\\images\\wall.png", 1, 1);
	com.CreaTexturaIMG(renderer, "..\\images\\comida.png", 1, 1);
	vitam.CreaTexturaIMG(renderer, "..\\images\\vitamina.png", 1, 1);

	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) { //mapa cargado de archivo teoricamente
			tab[i][j] = Empty;
		}
	}
	tab[9][9] = Wall;
	tab[199][199] = Food;
	tab[60][60] = Vitamins;
	map.crea_Mapa(&vitam, &muro, &com, tab);
}


Game::~Game()
{
}

void Game::pinta_Mapa() {
	map.render_Mapa(renderer);
	SDL_RenderPresent(renderer);
}
