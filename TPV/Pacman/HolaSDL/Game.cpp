#include "Game.h"


Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	winWidth = 870;
	winHeight = 644;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	this->path = "..\\images\\textura";
	//Inicialización del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Texturas
	//texts[0] = vitaminas, texts[1] = muro, texts[2] = comida, texts[3] = spritesheet, texts[4] = menu, texts[5] = gameOver
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 1, 4); //vitamina animada
		}
		else if (i == 3) {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 4, 14); //carga las texturas de todos los personajes
		}
		else {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 1, 1);
		}
	}

	//FrameRate
	this->frameRate = 120; //a + alto, + lento
	
	this->levels[0] = "..\\partidaGuardada.txt";  //guarda los niveles en un array
	for (int i = 1; i < 6; i++) {
		this->levels[i] = "..\\level0" + to_string(i) + ".pac";
	}

	personajes.resize(6);
}


Game::~Game() //destruye el renderer y la ventana
{	
	//Finalization
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	for (int i = 0; i < 6; i++) {
		delete texts[i]; //bora cada una de las texturas creadas
	}
	for (int i = 0; i < personajes.size(); i++) {
		delete personajes[i];
	}
}

void Game::carga_Archivo(string name){
	archivo.open(name);
	int fils, cols;
	archivo >> fils >> cols;
	map = new GameMap(fils, cols, texts[0], texts[1], texts[2], this);
	map->loadFromFile(archivo);
	int numGhost = 0; //numero de fantasmas, maybe deberia ser un atributo del Game...
	archivo >> numGhost;
	for (int i = 0; i < numGhost; i++) {
		int typeGhost;
		archivo >> typeGhost;
		if (typeGhost == 0) {
			personajes[i] = new Ghost(0, 0, i + 4, texts[3], this);
			personajes[i]->loadFromFile(archivo);
		}
		else {
			personajes[i] = new Ghost(0, 0, i + 4, texts[3], this); //añade un fantasma al final del vector
			personajes[i]->loadFromFile(archivo); //esto es pa q lea al 4 fantasma pero meh, hay que quitarlo, se supone que es un smartGhost
			int kk;        //Esto hay  que definirlo de alguna manera, igual redefiniendo el 
						   //constructor en el SmartGhost para ponerle la Edad a 1, a menos que ya vengan
						   //con la edad
			archivo >> kk; //la edad y tal, q mierda molesta
		}
	}
	personajes[4] = map;
	personajes[5] = new Pacman(0, 0, texts[3], this); //esto de aqui hay que quitarlo, tener un array de cosas y tal, pero por ahora
	personajes[5]->loadFromFile(archivo);

	archivo.close();
}

void Game::pinta_Mapa() {
	personajes[4]->render();;
}

bool Game::siguiente_casilla (int &X, int &Y, int dirX, int dirY) {
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

void Game::setComida(int a) {
	numComida += a;
}

void Game::come(int x, int y) { //modifica la posicion a empty y reduce el numero de comida en 1
	if (map->getCell(x, y) == Vitamins){
		vitaminas = true;
		vitaminasTiempoAux = vitaminasTiempo;
	}
	map->modifica_Posicion(x, y, Empty);
	setComida(-1);
}

MapCell Game::consulta(int x, int y) {
	return map->getCell(x, y);
}

bool Game::win() { //comprueba si se ha comido todo e.e
	return (numComida == 0);
}

void Game::handle_Events() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RIGHT) {
					static_cast<Pacman*>(personajes[5])->siguiente_Dir(1, 0);  //si es derecha le pasa la direccion derecha(1,0) y así con todas las direcciones
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					static_cast<Pacman*>(personajes[5])->siguiente_Dir(0, -1);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					static_cast<Pacman*>(personajes[5])->siguiente_Dir(0, 1);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					static_cast<Pacman*>(personajes[5])->siguiente_Dir(-1, 0);
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					exit = true; //añadido de si le das a escape sales tambien
				}
				else if (event.key.keysym.sym == SDLK_g) { //guardar partida
					saveState = true;
				}
			}
		}
	}
}

void Game::update() {
	delay();
	comprueba_colisiones(static_cast<Pacman*>(personajes[5])->get_PosActX(), static_cast<Pacman*>(personajes[5])->get_PosActY()); //comprueba que los fantasmas y pacman se han o no chocado
	tiempo_Vitamina(); //tiempo que los fantasmas están asustados
	for (int i = 0; i < 3; i++) {
		personajes[i]->update();
	}
	personajes[5]->update(); //update del pacman*/
}

void Game::render() {
	SDL_RenderClear(renderer); //limpia el render
	personajes[5]->render();
	for (int i = 0; i < 3; i++) {
		personajes[i]->render(vitaminas);
	}
	animaciones_Extra(); //anima las vitaminas
	pinta_Mapa();   //pinta el tablero
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

bool Game::comprueba_colisiones(int x, int y) {
	for (int i = 0; i < 4; i++) {
		if (static_cast<Ghost*>(personajes[i])->posActX == y && static_cast<Ghost*>(personajes[i])->posActX == x) {
			if (vitaminas) {
				static_cast<Ghost*>(personajes[i])->muerte();
			}
			else {
				static_cast<Pacman*>(personajes[5])->reduceVidas();
				static_cast<Pacman*>(personajes[5])->muerte(); //esto funciona increíblemente
			}
		}
	}

	if (static_cast<Pacman*>(personajes[5])->he_Muerto()) {
		exit = true;
	}

	return exit;
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

void Game::delay() { //hace lo del Delay más eficiente
	startTime = SDL_GetTicks();
	frameTime = SDL_GetTicks() - startTime;
	if (frameTime < frameRate) {
		SDL_Delay(frameRate - frameTime);
	}
}

int Game::obtenerPixelX(int posicion) {
	return (winWidth / colsTablero) * posicion;
}

void Game::animaciones_Extra() {
	this->texts[0]->Anima(500, 0, 0, 1, 4); //anima las vitaminas fancy
}

int Game::obtenerPixelY(int posicion) {
	return (winHeight / filasTablero) * posicion;
}

void Game::tiempo_Vitamina() { //temporizador vitaminas
	if (vitaminasTiempoAux > 0)
		vitaminasTiempoAux--;
	else
		vitaminas = false;
}


void Game::menu() {
	texts[4]->Render(renderer);
	SDL_RenderPresent(renderer);
	bool finish = false;
	while (!finish) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_n) {
					this->carga_Archivo(levels[1]);
					finish = true;
				}
				else if (event.key.keysym.sym == SDLK_c) {
					this->carga_Archivo(levels[0]); //carga la partida guardada
					finish = true;
				}
			}
		}
	}
	this->run();
}

void Game::guarda_Partida(string lvl) {
	bool noEscribir = false; //para no sobreescribir
	partidaGuardada.open("level" + lvl + ".dat");
	map->saveToFile(partidaGuardada);
	partidaGuardada << personajes.size() << endl;
	for (int i = 0; i < personajes.size(); i++){
		personajes[i]->saveToFile(partidaGuardada);
	}
	personajes[5]->saveToFile(partidaGuardada);
	partidaGuardada.close();
}

void Game::siguiente_Estado() {
	if (this->win() && levels_Index < 5) { //comrpueba que haya comido todo y ademas sigan existiendo niveles
			levels_Index++;
			delete map; //deletea el map anterior para construir el siguiente
			this->carga_Archivo(levels[levels_Index]); //carga el siguiente archivo
			this->run(); //run!
	}
	else if (static_cast<Pacman*>(personajes[5])->he_Muerto()) {
		game_Over(); 
	}
}

void Game::game_Over() {
	SDL_RenderClear(renderer);
	texts[5]->Render(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}

void Game::save() {
	SDL_Event evento;
	int code = 0;
	while (saveState && !exit) {
		while (SDL_PollEvent(&evento) && saveState) {
			SDL_Delay(100);
			if (evento.key.keysym.sym == SDLK_RETURN) {
				saveState = false;
			}
			else if (evento.key.keysym.sym >= SDLK_0 && evento.key.keysym.sym <= SDLK_9) {
				code = code * 10 + (evento.key.keysym.sym - SDLK_0);
			}
		}
	}
	this->guarda_Partida(to_string(code));
	//ESTO FUNCIONA PERO XD DUPLICA LOS NUMEROS LO CUAL NO ENTIENDO JEJE CREO QUE DETECTA VARIAS PULSACIONES A LA VEZ O ALGO ASI
}