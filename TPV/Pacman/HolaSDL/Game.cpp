#include "Game.h"
#include <sstream>
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
	TTF_Init();
	//Texturas
	//texts[0] = vitaminas, texts[1] = muro, texts[2] = comida, texts[3] = spritesheet, texts[4] = menu, texts[5] = gameOver, texts[6] = mensaje, texts[7] = vidas. texts[8]  = fuente
	leeTexturas();
	color.r = r;
	color.g = g;
	color.b = b;
}


Game::~Game() //destruye el renderer y la ventana
{	
	//Finalization
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	for (int i = 0; i < texts.size(); i++) {
		delete texts[i]; //bora cada una de las texturas creadas
	}
	deleteObjects();
	delete fuente;
	delete pacman;
	TTF_Quit();
}

//------------------------------------MetodosPrincipales-----------------------------
void Game::pinta_Mapa() {
	map->render();
}

void Game::handle_Events() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RIGHT) {
					pacman->siguiente_Dir(1, 0);  //si es derecha le pasa la direccion derecha(1,0) y así con todas las direcciones
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					pacman->siguiente_Dir(0, -1);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					pacman->siguiente_Dir(0, 1);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					pacman->siguiente_Dir(-1, 0);
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					exit = true; //añadido de si le das a escape sales tambien
				}
				else if (event.key.keysym.sym == SDLK_s) { //guardar partida
					saveState = true;
				}
			}
		}
	}
}
void Game::update() {
	delay();
	comprueba_colisiones(pacman->get_PosActX(), pacman->get_PosActY()); //comprueba que los fantasmas y pacman se han o no chocado
	tiempo_Vitamina(); //tiempo que los fantasmas están asustados
	for (GameCharacter* it : objects) { //iterador que recorre toda la lista de GameCharacters y updatea
		it->update();
	}
}

void Game::render() {
	SDL_RenderClear(renderer); //limpia el render
	texts[texts.size() - 1]->loadFromText(renderer, to_string(score), *fuente, color);
	ghost = objects.rbegin(); //empieza el iterador en el final
	for (ghost++; ghost != objects.rend(); ghost++) { //se salta a pacman y hasta que no llegue al principio de la lista, continua
		(*ghost)->render(vitaminas);
	}
	pacman->render();
	animaciones_Extra(); //anima las vitaminas
	pinta_Mapa();   //pinta el tablero
	texts[texts.size() - 1]->RenderFrame(renderer, hudScore);
	plasmaVidas();
	SDL_RenderPresent(renderer); //plasma el renderer en pantalla
}

void Game::run() {
	while (!this->win() && !this->dame_exit()) {
		handle_Events(); //controla los eventos de teclado
		update(); //update de tooodo
		render();  //render de tooodo
		if (saveState) {
			save();
		}
	}
	siguiente_Estado();
}

//------------------------------------Informacion/modificar Mapa-----------------------------

bool Game::siguiente_casilla(int &X, int &Y, int dirX, int dirY) {
	//Primero calculamos la casilla siguiente
	int tempX = X + dirX;
	int tempY = Y + dirY;

	//Comprueba el tipo de casilla que es
	MapCell casilla = map->getCell(tempY, tempX);

	//Miramos si puede mover
	if (casilla != Wall) {
		X += dirX;
		Y += dirY;
		return true;
	}
	else
		return false;
}

MapCell Game::consulta(int x, int y) {
	return map->getCell(x, y);
}

void Game::come(int x, int y) { //modifica la posicion a empty y reduce el numero de comida en 1
	if (map->getCell(x, y) == Vitamins) {
		vitaminas = true;
		vitaminasTiempoAux = vitaminasTiempo;
		sumaScore(ptosVitamina);
	}
	else {
		sumaScore(ptosComida);
	}
	map->modifica_Posicion(x, y, Empty);
	setComida(-1);

}

//------------------------------------Auxiliares-----------------------------

void Game::setComida(int a) {
	numComida += a;
}

bool Game::win() { //comprueba si se ha comido todo e.e
	return (numComida == 0);
}

bool Game::comprueba_colisiones(int x, int y) {
	ghost = objects.rbegin(); //empieza el iterador en el final//se salta a pacman
	for (ghost++; ghost != objects.rend(); ghost++) { //se salta a pacman y hasta que no llegue al principio de la lista, continua
		if ((*ghost)->get_PosActY() == x && (*ghost)->get_PosActX() == y) {
			if (vitaminas) {
				sumaScore(ptosFantasma);
				(*ghost)->muerte();
			}
			else {
				pacman->reduceVidas();
				pacman->muerte();
			}
		}
	}

	if (pacman->he_Muerto()) {
		exit = true;
	}

	return exit;
}

void Game::delay() { //hace lo del Delay más eficiente
	startTime = SDL_GetTicks();
	frameTime = SDL_GetTicks() - startTime;
	if (frameTime < frameRate) {
		SDL_Delay(frameRate - frameTime);
	}
}

void Game::tiempo_Vitamina() { //temporizador vitaminas
	if (vitaminasTiempoAux > 0)
		vitaminasTiempoAux--;
	else
		vitaminas = false;
}

void Game::game_Over() {
	SDL_RenderClear(renderer);
	texts[5]->Render(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}


void Game::sumaScore(int suma) {
	score += suma;
}

void Game::deleteObjects() {
	delete map;
	ghost = objects.rbegin(); //empieza el iterador en el final, se salta a pacman
	for (ghost++; ghost != objects.rend(); ghost++) {
		delete *ghost;
	}
	objects.clear();
}

void Game::plasmaMensaje() {
	SDL_Rect r = { dame_Anchura() / 3 - 50, dame_Anchura() / 4, 400, 200 };
	texts[6]->RenderFrame(renderer, r);
	SDL_RenderPresent(renderer);
}

void Game::plasmaVidas() {
	SDL_Rect re = hudVidas;
	for (int i = 0; i < pacman->dame_Vidas(); i++) {
		re.x = i * 50;
		texts[7]->RenderFrame(renderer, re);
	}
}

//------------------------------------Gets-----------------------------

int Game::dame_Altura() {
	return this->winHeight;
}

int Game::dame_Anchura() {
	return this->winWidth;
}

int Game::dame_FilasTablero() {
	return this->map->fils;
}

int Game::dame_ColumnasTablero() {
	return this->map->cols;
}

bool Game::dame_exit() {
	return this->exit;
}
SDL_Renderer* Game::dame_Renderer() {
	return this->renderer;
}

int Game::obtenerPixelX(int posicion) {
	return (winWidth / this->map->cols) * posicion;
}

void Game::animaciones_Extra() {
	this->texts[0]->Anima(500, 0, 0, 1, 4); //anima las vitaminas fancy
}

int Game::obtenerPixelY(int posicion) {
	return (winHeight / this->map->fils) * posicion;
}

//------------------------------------Archivo-----------------------------

void Game::carga_Archivo(int lvl){
	string name = nombreFichero(pathTxt, lvl, extTxt);
	archivo.open(name);
	if (!archivo.is_open()) {
		string fileName = nombreFichero(pathTxt, 1, extTxt);
		levels_Index = 1;
		archivo.open(fileName);
	}

	map = new GameMap(this);
	map->loadFromFile(archivo);

	int numGhost = 0; //numero de fantasmas, maybe deberia ser un atributo del Game...
	archivo >> numGhost;

	for (int i = 0; i < numGhost; i++) {
		int typeGhost;
		archivo >> typeGhost;
		if (typeGhost == 0) {
			Ghost* fantasmita = new Ghost(0, 0, i + 4, texts[3], this);
			fantasmita->loadFromFile(archivo); //se leen de archivo
			objects.push_front(fantasmita); //pusheamos el fantasma al principio de la lista
		}
	}

	if(pacman == nullptr)
		pacman = new Pacman(0, 0, texts[3], this);
	objects.push_back(pacman); //pusheamos a pacman al final de la lista
	pacman->loadFromFile(archivo); //se lee de archivo

	int aux; //para saber si el archivo acaba o no
	archivo >> aux;
	if (archivo.fail()) {
		archivo.clear();
	}
	else {
		score = aux;
		archivo >> levels_Index;
	}
	numComida = 50;
	archivo.close();
}

void Game::menu() {
	texts[4]->Render(renderer);
	bool finish = false;
	int x, y;
	x = y = 0;
	SDL_Rect rectNew = {200, 400, 400, 75};
	SDL_Rect rectLoad = {200, 500, 400, 75};  //rectángulos de los botones del menú
	SDL_RenderPresent(renderer);
	while (!finish) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				x = event.button.x;
				y = event.button.y;
				if (x > rectNew.x && x < rectNew.x + rectNew.w && y > rectNew.y && y < rectNew.y + rectNew.h) {
					this->carga_Archivo(1);
					finish = true;
				}
				else if (x > rectLoad.x && x < rectLoad.x + rectLoad.w && y > rectLoad.y && y < rectLoad.y + rectLoad.h) {
					saveState = true;
					plasmaMensaje();
					int code = this->escribe_Code();
					this->carga_Archivo(code);
					finish = true;
				}
			}
		}
	}
	this->run();
}

void Game::guarda_Partida(int lvl) {
	bool noEscribir = false; //para no sobreescribir
	string name = nombreFichero(pathTxt, lvl, extTxt);
	partidaGuardada.open(name);
	map->saveToFile(partidaGuardada);
	partidaGuardada << objects.size() - 1 << endl;
	for (GameCharacter* it: objects){
		it->saveToFile(partidaGuardada);
	}
	partidaGuardada << endl << score << endl << levels_Index << endl;
	partidaGuardada.close();
}

void Game::siguiente_Estado() {
	if (this->win()) { //comrpueba que haya comido todo
			levels_Index++;
			deleteObjects();
			this->carga_Archivo(levels_Index); //carga el siguiente archivo
			this->run(); //run!
	}
	else if (pacman->he_Muerto()) {
		game_Over(); 
	}
}

void Game::save() {
	plasmaMensaje();
	int code = escribe_Code();
	this->guarda_Partida(code);
}

int Game::escribe_Code() {
	SDL_Event evento;
	int code = 0;
	while (saveState && !exit) {
		SDL_WaitEvent(&evento);
		if (evento.type == SDL_KEYDOWN) {
			if (evento.key.keysym.sym == SDLK_RETURN) {
				saveState = false;
			}
			else if (evento.key.keysym.sym >= SDLK_0 && evento.key.keysym.sym <= SDLK_9) {
				code = code * 10 + (evento.key.keysym.sym - SDLK_0);
			}
		}
	}
	return code;
}

string Game::nombreFichero(string path, int num, string ext) {
	stringstream ss;
	ss << path << num << ext;
	return ss.str();
}

void Game::leeTexturas() {
	ifstream texturas;
	texturas.open(pathInfoTexturas + extTxt); //archivo de texto donde se encuentra la informacion de las diferentes texturas (ruta, filas, columnas, numero de Texturas, etc)
	int numText = 0;
	texturas >> numText;
	for (int i = 0; i < numText; i++) {
		string fileName;
		int fils, cols;
		texturas >> fileName;
		if (fileName == "Fuente") { //si es la fuente crea una textura vacia y la fuente
			int tamanyo;
			texturas >> fileName >> tamanyo;
			fuente = new Font(fileName, tamanyo);
			texts.push_back(new Texture());
		}
		else {
			texturas >> fils >> cols;
			texts.push_back(new Texture(renderer, fileName, fils, cols));
		}
	}
	texturas.close();
}