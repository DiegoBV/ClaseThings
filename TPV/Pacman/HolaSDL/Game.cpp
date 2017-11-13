#include "Game.h"



Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	winWidth = 870;
	winHeight = 644;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;

	//Inicialización del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Texturas
	muro.CreaTexturaIMG(renderer, "..\\images\\wall.png", 1, 1, 0 , 0);
	com.CreaTexturaIMG(renderer, "..\\images\\comida.png", 1, 1, 0 , 0);
	vitam.CreaTexturaIMG(renderer, "..\\images\\vitamina.png", 1, 1, 0 , 0);
	textGeneral.CreaTexturaIMG(renderer, "..\\images\\characters1.png", 4, 14, 0, 0); //carga las texturas de todos los personajes
	
		textGhost = &textGeneral; //Dirección de la textGeneral cargada
	
}


Game::~Game()
{
}

void Game::carga_Archivo(string name){
	int fils, cols;

	archivo.open(name);

	if (archivo.is_open()){
		archivo >> fils >> cols;
		this->filasTablero = fils;
		this->colsTablero = cols;
		map = GameMap(fils, cols, &vitam, &muro, &com, this);
		for (int i = 0; i < fils; i++){
			for (int j = 0; j < cols; j++){
				int pos;
				archivo >> pos;
				switch (pos) {
				case 0:
					map.modifica_Posicion(i, j, Empty);
					break;
				case 1:
					map.modifica_Posicion(i, j, Wall);
					break;
				case 2:
					map.modifica_Posicion(i, j, Food);
					break;
				case 3:
					map.modifica_Posicion(i, j, Vitamins);
					break;
				case 4: //Pacman

					break;
				case 5:
					fantasmas[0] = Ghost(renderer, "..\\images\\characters1.png", i, j, pos, textGhost, this); //todo lo del new no es necesario, trabajariamos con mem dinamica																									
					break;
				case 6:
					fantasmas[1] = Ghost(renderer, "..\\images\\characters1.png", i, j, pos, textGhost, this); //basta con tener un array estatico de fantasmas o , como mucho, un array dinamico
					break;
				case 7:
					fantasmas[2] = Ghost(renderer, "..\\images\\characters1.png", i, j, pos, textGhost, this); //el this se refiere a "Game"
					break;
				case 8:
					fantasmas[3] = Ghost(renderer, "..\\images\\characters1.png", i, j, pos, textGhost, this);
					break;
					//faltan pcman
				default:
					break;
				}
			}
		}
		archivo.close();
	}
}

void Game::pinta_Mapa() {
	map.render_Mapa(renderer);
	SDL_RenderPresent(renderer);
}

bool Game::comprueba_Muro(int X, int Y) {
	MapCell casilla = map.consulta_Posicion(X, Y);
	if (casilla == Wall) {
		return true;
	}
	else
		return false;
}

void Game::run() {

	while (SDL_PollEvent(&termina) && !end){
		if (termina.type == SDL_QUIT)
			end = true;

		SDL_RenderClear(renderer);
		map.render_Mapa(renderer);

		for (int i = 0; i < 4; i++) {
			fantasmas[i].update();
			fantasmas[i].render(renderer);
		}
		SDL_RenderPresent(renderer);
		system("pause");
	}
	//prueba.update();
}

//los gets de altura, anchura, renderer...
int Game::dame_Altura() {
	return this->winHeight;
}

int Game::dame_Anchura() {
	return this->winWidth;
}

int Game::dame_FilasTablero() {
	return this->filasTablero;
}

int Game::dame_ColumnasTablero() {
	return this->colsTablero;
}

SDL_Renderer* Game::dame_Renderer() {
	return this->renderer;
}

void Game::destruir() { //llamaría a todos los destructores, por ahora solo hay uno
	map.destruir_Mapa();
}

int Game::obtenerPixelX(int posicion){
	return (winWidth / filasTablero) * posicion;
}

int Game::obtenerPixelY(int posicion){
	return (winHeight / colsTablero) * posicion;
}
