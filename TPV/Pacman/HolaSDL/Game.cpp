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
	muro.CreaTexturaIMG(renderer, "..\\images\\wall2.png", 1, 1);
	com.CreaTexturaIMG(renderer, "..\\images\\comida4.png", 1, 1);
	vitam.CreaTexturaIMG(renderer, "..\\images\\vitaminas.png", 1, 4);
	textGeneral.CreaTexturaIMG(renderer, "..\\images\\characters1.png", 4, 14); //carga las texturas de todos los personajes
	textGhost = &textGeneral; //Dirección de la textGeneral cargada

	//FrameRate
	this->frameRate = 100; //a + alto, + lento
	
}


Game::~Game() //destruye el renderer y la ventana
{	
	//Finalization
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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
					setComida(1);
					break;
				case 3:
					map.modifica_Posicion(i, j, Vitamins);
					setComida(1);
					break;
				case 4:
					//pacman = Pacman(i, j, textGhost, this);
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
				case 9: {
					map.modifica_Posicion(i, j, Empty);
					pacman = Pacman(i, j, textGhost, this);
					break;
				}
				default:
					break;
				}
			}
		}
		archivo.close();
	}
}

void Game::pinta_Mapa() {
	map.render_Mapa();
}

bool Game::comprueba_Muro(int X, int Y) {
	MapCell casilla = map.getCell(X, Y);
	if (casilla == Wall) {
		return true;
	}
	else
		return false;
}
void Game::setComida(int a) {
	numComida += a;
}
void Game::come(int x, int y) {
	map.modifica_Posicion(x, y, Empty);
	setComida(-1);
}

MapCell Game::consulta(int x, int y) {
	return map.getCell(x, y);
}

bool Game::win() { //comprueba si se ha comido todo e.e
	return (numComida == 0);
}

void Game::handle_Events() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		exit = true;
	}
	else {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_RIGHT) {
				pacman.siguiente_Dir(1, 0);  //si es derecha le pasa la direccion derecha(1,0) y así con todas las direcciones
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				pacman.siguiente_Dir(0, -1);
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				pacman.siguiente_Dir(0, 1);
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				pacman.siguiente_Dir(-1, 0);
			}
		}
	}
}

void Game::run() {
	SDL_RenderClear(renderer); //limpia el render
	startTime = SDL_GetTicks();
	frameTime = SDL_GetTicks() - startTime; //hace lo del Delay más eficiente
	for (int i = 0; i < 4; i++) {
		fantasmas[i].render(renderer);
		//fantasmas[i].update();
	}
	this->vitam.Anima(500, 0, 0, 1, 4); //anima las vitaminas fancy
	handle_Events(); //controla los eventos de teclado
	pacman.update(); //update del pacman
	pinta_Mapa();   //pinta el tablero
	SDL_RenderPresent(renderer); //plasma el renderer en pantalla
	if (frameTime < frameRate) {
		SDL_Delay(frameRate - frameTime); //delay
	}
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

bool Game::dame_exit() {
	return this->exit;
}
SDL_Renderer* Game::dame_Renderer() {
	return this->renderer;
}

void Game::destruir() { //llamaría a todos los destructores, por ahora solo hay uno
	map.destruir_Mapa();
}
