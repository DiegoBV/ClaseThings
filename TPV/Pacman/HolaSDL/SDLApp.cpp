#include "SDLApp.h"
#include <exception>
#include "MainMenuState.h"


SDLApp::SDLApp()
{
	try {
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
		leeTexturas();
		maquinaEstados = new GameStateMachine();
		if (window == nullptr || renderer == nullptr) {
			throw SDLError(SDL_GetError());
		}
		maquinaEstados->pushState(new MainMenuState(this, texts[numTexturaMenu]));
	}
	catch (SDLError& e) {
		cerr << "Caught: " << e.what() << endl;
		cerr << "Tipo: " << typeid(e).name() << endl;
		system("pause");
		this->setExit(true); //cerramos, error critico
	}
}

void SDLApp::handleEvent() {
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else
			maquinaEstados->currentState()->handleEvent(event);
	}
}

void SDLApp::leeTexturas() {
	ifstream texturas;
	try{
		texturas.open(pathInfoTexturas + extTxt); //archivo de texto donde se encuentra la informacion de las diferentes texturas (ruta, filas, columnas, numero de Texturas, etc)
		if (!texturas.is_open()) {
			throw FileNotFoundError("Archivo: " + pathInfoTexturas + extTxt + " no encontrado"); //error de archivo no encontrado
		}
		else {
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
			for (int i = 0; i < numText; i++) {
				if (texts[i] == nullptr) {
					throw SDLError(IMG_GetError()); //controlar el error de texturas nulas
				}
			}
			texturas.close();
		}
	}
	catch (exception& e) {
		cerr << "Caught: " << e.what() << endl;
		cerr << "Tipo: " << typeid(e).name() << endl;
		system("pause");
		this->setExit(true); //cerramos, error critico en las texturas
	}
}

int SDLApp::escribe_Code() {
	SDL_Event evento;
	int code = 0;
	bool saveState = true;
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

void SDLApp::plasmaMensaje() {
	SDL_Rect r = { this->winWidth / 2 - anchura/2, this->winHeight/2 - altura, anchura, altura*2 };
	texts[numTexturaMensaje]->RenderFrame(renderer, r);
	SDL_RenderPresent(renderer);
}
